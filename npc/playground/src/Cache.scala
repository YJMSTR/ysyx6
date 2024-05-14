import chisel3._
import Configs._ 
import Instr._ 
import chisel3.util._
//CacheLineSize : Bytes
class CacheIO(CacheLineSize : Int, DataWidth : Int) extends Bundle {
  // val cache_reqr = Input(Bool())  // 请求读取 Cache
  // val cache_reqw = Input(Bool())  // 请求写入 Cache
  val addr = Input(UInt(XLEN.W))  // 请求的地址
  val addr_valid = Input(Bool())
  val addr_ready = Output(Bool())
  val data = Output(UInt((DataWidth).W)) // 返回对应的 CacheLine 中的 对应块
  val data_valid = Output(Bool())
  val data_ready = Input(Bool())
} 

class Cache(CacheSize: Int, CacheLineSize : Int, DataWidth : Int) extends Module { 

  assert(CacheSize > CacheLineSize, "CacheSize should >= CacheLineSize")
  assert(CacheLineSize >= 4, "CacheLineSize should >= 4B")
  // CacheLineSize 和 CacheLineNum 必须是 2 的幂
  val io = IO(new Bundle {
    val io = new CacheIO(CacheLineSize, DataWidth)
    val axi4 = Flipped(new AXI4Interface)  // 用于和 Arbiter 相连
    val bus_reqr = Output(Bool())
    val bus_reqw = Output(Bool())
    val bus_ac = Input(Bool())
    val stall = Input(Bool())
  })
  val empty_axi4_master = Module(new empty_axi4_master)
  io.axi4 <> empty_axi4_master.io.axi4
  val CacheLineNum = CacheSize / CacheLineSize
  // Chisel 中的同步读写内存，当在同一个始终边缘同时进行读写时，读出的值是未定义的
  // 为了简单起见，此处用触发器存放Cache的数据和元数据
  
  // Rule! Use Reg of Vec not Vec of Reg!
  // val cache_data = Vec(CacheLineNum, RegInit(0.U((CacheLineSize * 8).W)))  
  // val cache_data = Reg(Vec(CacheLineNum, UInt((CacheLineSize * 8).W)))
  // 上面是用 Reg 实现的，下面尝试用 SRAM
  
  val cache_data = SyncReadMem(CacheLineNum, UInt((CacheLineSize * 8).W))

  val CacheLineSizeBits = log2Ceil(CacheLineSize)
  val CacheLineBeats   = CacheLineSize * 8 / XLEN // 每次传输 XLEN bit, 传输完一个 Cacheline 所需的次数
  assert(CacheLineBeats > 0, "Cache Beats should > 0")
  val CacheLineNumBits = log2Ceil(CacheLineNum)
  // cache_tag : 数据块的唯一编号
  
  val cache_input_tag = (io.io.addr >> CacheLineSizeBits.U)
  // Rule! Use Reg of Vec not Vec of Reg!
  // val cache_tag = Vec(CacheLineNum, RegInit(0.U((XLEN-CacheLineSizeBits).W)))
  val cache_tag = Reg(Vec(CacheLineNum, UInt((XLEN-CacheLineSizeBits).W)))

  val cache_valid = Reg(Vec(CacheLineNum, Bool()))
  // val cache_valid = RegInit(0.U(CacheLineNum.W))  // 用 1 bit 标识某个 CacheLine 是否有数据
  
  val data_cacheline_reg = RegInit(0.U((CacheLineSize*8).W))  // 用于存放要返回的数据对应的 Cache 块
  
}

// DataWidth: 数据块的位数
class ICache(CacheSize : Int, CacheLineSize : Int, DataWidth : Int) extends Cache(CacheSize, CacheLineSize, DataWidth) {
  // 4KiB 的 icache, 若 CacheLineSize = 8B,则有 512 个 cacheline
  assert(CacheLineSize == 8, "ICache only support CacheLineSize = 8B now")  // 暂时仅支持 Cache 块大小为 8B 的访存
  assert(DataWidth == 32, "ICache only support 32bit IO now")
  
  // 即 一次访存读出 2 条指令到 Cache 中，根据 offset 返回对应的指令给 IFU
  // offset === addr ((CacheLineSizeBits-1)/(DataWidth/8-1), 0)
  val cache_offset = io.io.addr(CacheLineSizeBits-1, DataWidth/8 - 1 - 1)
  
  
  // assert(CacheLineSize >= 4, "CacheLineSize should >= 4B")
  val r_idle :: r_return_data :: axi_s_wait_arready :: axi_s_wait_rvalid :: Nil = Enum(4) 
  val r_state = RegInit(r_idle)

  val axi_reg_readAddr = RegInit(0.U(XLEN.W))

  val axi_reg_outData  = RegInit(0.U(XLEN.W))

  val reqr_reg = RegInit(0.B)
  val reqw_reg = RegInit(0.B)

  // switch(axi_state) {
  //   is(axi_s_idle) {
  //     // todo: 设置好 araddr 后转移到 wait_arready
  //     // 考虑合并这个状态机与 Cache 的状态机，从 r_idle 转移到 wait arready 阶段
  //   }
  // }

  // cache_index : 如果把 Cache 看成数组，index 就是数组元素的下标
  // 根据映射关系的不同，Cache index 计算方式也不同
  // 直接映射 Cache 中，直接按照 tag 来计算 index
  // tag % cachesize == index, 对二的幂取模直接取低位即可

  // 替换策略：若新读入的块对应的 index 上已有数据，则用新读入的块替换该块 （FIFO，时间局部性）
  val cache_input_index = cache_input_tag(CacheLineNumBits - 1, 0)

  io.io.addr_ready := r_state === r_idle
  io.io.data_valid := r_state === r_return_data
  io.io.data := Mux(cache_offset === 0.U, data_cacheline_reg(31, 0), data_cacheline_reg(63, 32))

  io.bus_reqr := reqr_reg
  io.bus_reqw := reqw_reg

  // axi4lite
  io.axi4.arvalid := r_state === axi_s_wait_arready 
  io.axi4.rready := r_state === axi_s_wait_rvalid
  io.axi4.araddr := axi_reg_readAddr
  io.axi4.awaddr := 0.U
  io.axi4.awvalid := 0.B
  io.axi4.wdata := 0.U
  io.axi4.wstrb := 0.U
  io.axi4.wvalid := 0.U
  io.axi4.bready := 0.U

  val hit = cache_valid(cache_input_index) && cache_tag(cache_input_index) === cache_input_tag
  val read_res = cache_data.read(cache_input_index)
  switch(r_state) {
    is(r_idle) {  // addr_ready
      when (/*io.io.cache_reqr && */io.io.addr_valid && !io.stall) {
        
        when (hit) { 
          // hit
          
          // data_cacheline_reg := cache_data(cache_input_index)
          // 从 SyncReadMem 读数据会有一个周期的延迟，即本周期发起读请求，下一个周期才能拿到数据
          // 这种情况直接把 io.data 连到 mem
          r_state := r_return_data
          // printf("res = %x\n", res_tmp)
        }.otherwise {
          // 未命中，需要通过 AXI4 去取出数据
          // 注意：由于跳转指令的存在，此处的 addr 可能是未按照 cachelinesize 对齐的 addr,应按照 cachelinesize 进行对齐
          r_state := axi_s_wait_arready
          axi_reg_readAddr := (io.io.addr >> CacheLineSizeBits.U) << (CacheLineSizeBits.U)
          reqr_reg := 1.B
        }
      }
    }

    is(r_return_data) {
      when (!hit) {
        read_res := data_cacheline_reg
      }
      io.io.data := Mux(cache_offset === 0.U, read_res(31, 0),  read_res(63, 32))
      when (io.io.data_ready && !io.stall) {
        r_state := r_idle
      }
    }
    is(axi_s_wait_arready) {
      // 通过总线在指令存储器中读出指令。
      when (io.bus_ac & io.axi4.arready) {
        
        // 现在全部按读取 64 位数据来处理，读出来再切片
        r_state := axi_s_wait_rvalid
      }
    }
    is(axi_s_wait_rvalid) {
      when(io.bus_ac & io.axi4.rvalid) {
        r_state := r_return_data
        data_cacheline_reg := io.axi4.rdata
        // cache_data(cache_input_index) := io.axi4.rdata
        cache_data.write(cache_input_index, io.axi4.rdata)
        cache_valid(cache_input_index) := 1.B
        cache_tag(cache_input_index) := cache_input_tag
        reqr_reg := 0.B
        // printf("cache index=%x new rdata=%x\n", cache_input_index, io.axi4.rdata)
        when (io.axi4.rresp =/= 0.U) {
          printf("icache rresp = %x\n", io.axi4.rresp)
        }
      }
    }
  }
}