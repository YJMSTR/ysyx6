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
  })
  val empty_axi4_master = Module(new empty_axi4_master)
  io.axi4 <> empty_axi4_master.io.axi4
  val CacheLineNum = CacheSize / CacheLineSize
  // Chisel 中的同步读写内存，当在同一个始终边缘同时进行读写时，读出的值是未定义的
  // 为了简单起见，此处用触发器存放Cache的数据和元数据
  
  // Rule! Use Reg of Vec not Vec of Reg!
  // val cache_data = Vec(CacheLineNum, RegInit(0.U((CacheLineSize * 8).W)))  
  val cache_data = Reg(Vec(CacheLineNum, UInt((CacheLineSize * 8).W)))
  val CacheLineSizeBits = log2Ceil(CacheLineSize)
  val CacheLineNumBits = log2Ceil(CacheLineNum)
  // cache_tag : 数据块的唯一编号
  
  val cache_input_tag = (io.io.addr >> CacheLineSizeBits.U)
  // Rule! Use Reg of Vec not Vec of Reg!
  // val cache_tag = Vec(CacheLineNum, RegInit(0.U((XLEN-CacheLineSizeBits).W)))
  val cache_tag = Reg(Vec(CacheLineNum, UInt((XLEN-CacheLineSizeBits).W)))

  val cache_valid = RegInit(0.U(CacheLineNum.W))  // 用 1 bit 标识某个 CacheLine 是否有数据
  
  val data_cacheline_reg = RegInit(0.U((CacheLineSize*8).W))  // 用于存放要返回的数据对应的 Cache 块

  val offset = io.io.addr(CacheLineSizeBits-1-1, 0) // 块内偏移
  
}

class ICache(CacheSize : Int, CacheLineSize : Int, DataWidth : Int) extends Cache(CacheSize, CacheLineSize, DataWidth) {
  assert(CacheLineSize == 8, "ICache only support CacheLineSize = 8B now")  // 暂时仅支持 Cache 块大小为 8B 的访存
  // assert(CacheLineSize >= 4, "CacheLineSize should >= 4B")
  val r_idle :: r_return_data :: axi_s_wait_arready :: axi_s_wait_rvalid :: Nil = Enum(4) 
  val r_state = RegInit(r_idle)

  val axi_reg_readAddr = RegInit(0.U(XLEN.W))
  val axi_reg_readSize = RegInit(2.U(MEM_SEXT_SEL_WIDTH.W))
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

  // axi4full burst
  io.axi4.arburst := "b10".B  // 支持 wrap 类型的突发传输
  // 突发传输：主设备向从设备传输事务的控制信息和第一个字节的地址，然后从设备必须在此后的每次传输中计算数据地址
  // burst length：突发传输中包含了几次小传输，axi4 的 incr 类型 burst 支持 1 到 256 次传输，其它的 burst 类型支持 1 到 16 次
  // burst length = AxLEN[7:0] + 1
  
  // 对于 wrap 方式的突发传输，其只支持 2 4 8 16 的突发长度(传输的次数)
  // 所以 cacheline 的大小应该满足 cachelinesize = (arlen+1)*64
  io.axi4.arlen := (CacheLineSize * 8 / 64).U 
  // 总线数据宽度 64 位，可以以 64 为单位，这样传输次数最小
  // arsize : burst size (bytes in a transfer)
  io.axi4.arsize := "b011".U  // 8 bytes in transfer





  // 下面的 counter 不用了，直接实现支持突发传输的 AXI4 即可
  
  /* 
  val counter = RegInit(0.U((CacheLineSizeBits - 2).W)) 
  // counter_max 的作用是要发起的 32 bit 的 AXI 读事务次数
  val counter_max = CacheLineSize.U(CacheLineSizeBits-1, 2)
  */

  switch(r_state) {
    is(r_idle) {
      when (/*io.io.cache_reqr && */io.io.addr_valid) {
        when (cache_valid(cache_input_index) && cache_tag(cache_input_index) === cache_input_tag) { 
          // 命中
          r_state := r_return_data
          data_cacheline_reg := cache_data(cache_input_index)
        }.otherwise {
          // 未命中，需要通过 AXI4 去取出数据
          r_state := axi_s_wait_arready
          axi_reg_readAddr := io.io.addr
          reqr_reg := 1.B
        }
      }
    }
    // is(r_transfer_data) {

    //   // 把之前读出的数据写回 Cache 的对应位置. 
    //   // 每次读出 DataWidth 位的话，就将 cache_data(cache_input_index)的第(counter*DataWidth-1, (counter-1)*DataWidth) 更新为读出的数据
    //   // 但 counter 是 UInt，无法转为字面量
    //   cache_data(cache_input_index) := (cache_data(cache_input_index) )


    //   when(counter === counter_max) {
    //     io.data := data_cacheline_reg
    //     r_state := r_return_data
    //   }.otherwise {
    //     // 对 counter 的自增应该放在 axi_s_wait_rvalid 状态中进行。。？
    //     // counter := counter + 1.U

    //     // 准备发起一次新的读事务
    //     axi_reg_readAddr := Mux(counter === 0.U, io.io.addr, io.io.addr + 4.U)
    //     reqr_reg := 1.B
    //   }
    // }
    is(r_return_data) {
      when (io.io.data_ready) {
        r_state := r_idle
      }
    }
    is(axi_s_wait_arready) {
      // 通过总线在指令存储器中读出指令。ICache发起的请求的读长度都是指令长度，即32位
      when (io.bus_ac & io.axi4.arready) {
        // axi_reg_readSize := 暂时不支持，等到把 毕设分支的 axi4lite 全部升级成 axi4full 才支持
        // 现在全部按读取 64 位数据来处理，读出来再切片
        r_state := axi_s_wait_rvalid
      }
    }
    is(axi_s_wait_rvalid) {
      when(io.axi4.rvalid) {
        r_state := r_return_data
        data_cacheline_reg := io.axi4.rdata
        cache_data(cache_input_index) := io.axi4.rdata
        reqr_reg := 0.B
        when (io.axi4.rresp =/= 0.U) {
          printf("icache rresp = %x\n", io.axi4.rresp)
        }
      }
    }
  }
}