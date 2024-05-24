import chisel3._
import Configs._ 
import Instr._ 
import chisel3.util._
//CacheLineSize : Bytes
class CacheIO(CacheLineSize : Int, DataWidth : Int) extends Bundle {
  // val cache_reqr = Input(Bool())  // 请求读取 Cache
  // val cache_reqw = Input(Bool())  // 请求写入 Cache
  val raddr       = Input(UInt(XLEN.W))  // 请求的地址
  val raddr_valid = Input(Bool())
  val raddr_ready = Output(Bool())
  val rsize       = Input(UInt(3.W))
  val rdata       = Output(UInt((DataWidth).W)) // 返回对应的 CacheLine 中的 对应块
  val rdata_valid = Output(Bool())
  val rdata_ready = Input(Bool())
  val waddr       = Input(UInt(XLEN.W))
  val waddr_valid = Input(Bool())
  val waddr_ready = Output(Bool())
  val wdata       = Input(UInt(XLEN.W))
  val wdata_valid = Input(Bool())
  val wdata_ready = Output(Bool()) 
  val wstrb       = Input(UInt((XLEN/8).W))
  val bvalid      = Output(Bool())
  val bready      = Input(Bool())
  val bresp       = Output(UInt(2.W))
  // .. 写着写着发现变成了 AXI4 的样子
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
  
  val r_cache_input_tag = (io.io.raddr >> CacheLineSizeBits.U)
  val w_cache_input_tag = (io.io.waddr >> CacheLineSizeBits.U)
  // Rule! Use Reg of Vec not Vec of Reg!
  // val cache_tag = Vec(CacheLineNum, RegInit(0.U((XLEN-CacheLineSizeBits).W)))
  // val cache_tag = Reg(Vec(CacheLineNum, UInt((XLEN-CacheLineSizeBits).W)))
  // val cache_valid = Reg(Vec(CacheLineNum, Bool()))
  // 上面是原先的 Reg 实现，下面是对应的 SRAM 实现
  val cache_tag = SyncReadMem(CacheLineNum, UInt((XLEN-CacheLineSizeBits).W))
  val cache_valid = SyncReadMem(CacheLineNum, Bool())


  
  val data_cacheline_reg = RegInit(0.U((CacheLineSize*8).W))  // 用于存放要返回的数据对应的 Cache 块

  val reqr_reg = RegInit(0.B)
  val reqw_reg = RegInit(0.B)
  
  // 初始化输出信号
  io.io.waddr_ready := 0.B
  io.io.wdata_ready := 0.B
  io.io.bvalid      := 0.B
  io.io.bresp       := 0.U
}

// DataWidth: 数据块的位数
class ICache(CacheSize : Int, CacheLineSize : Int, DataWidth : Int) extends Cache(CacheSize, CacheLineSize, DataWidth) {
  // 4KiB 的 icache, 若 CacheLineSize = 8B,则有 512 个 cacheline
  assert(CacheLineSize == 8, "ICache only support CacheLineSize = 8B now")  // 暂时仅支持 Cache 块大小为 8B 的访存
  assert(DataWidth == 32, "ICache only support 32bit IO now")
  
  // 即 一次访存读出 2 条指令到 Cache 中，根据 offset 返回对应的指令给 IFU
  // offset === raddr ((CacheLineSizeBits-1)/(DataWidth/8-1), 0)
  val cache_offset = io.io.raddr(CacheLineSizeBits-1, DataWidth/8 - 1 - 1)
  
  
  // assert(CacheLineSize >= 4, "CacheLineSize should >= 4B")
  val r_idle :: r_read_cache :: r_return_data :: axi_s_wait_arready :: axi_s_wait_rvalid :: Nil = Enum(5) 
  val r_state = RegInit(r_idle)

  val axi_reg_readAddr = RegInit(0.U(XLEN.W))

  val axi_reg_outData  = RegInit(0.U(XLEN.W))



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
  val r_cache_input_index = r_cache_input_tag(CacheLineNumBits - 1, 0)

  io.io.raddr_ready := r_state === r_idle
  io.io.rdata_valid := r_state === r_return_data
  io.io.rdata := Mux(cache_offset === 0.U, data_cacheline_reg(31, 0), data_cacheline_reg(63, 32))

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

  val hit = cache_valid(r_cache_input_index) && cache_tag(r_cache_input_index) === r_cache_input_tag
  val r_cache_data_at_index = cache_data.read(r_cache_input_index)
  switch(r_state) {
    is(r_idle) {  // 新增这个状态，是因为 SyncReadMem 的读写均有一个周期延迟
      when (/*io.io.cache_reqr && */io.io.raddr_valid && !io.stall) {
        r_state := r_read_cache
      }
    }
    is(r_read_cache) {  // raddr_ready
       
      when (hit) { 
        // hit
        
        // data_cacheline_reg := cache_data(r_cache_input_index)
        // 从 SyncReadMem 读数据会有一个周期的延迟，即本周期发起读请求，下一个周期才能拿到数据
        data_cacheline_reg := r_cache_data_at_index
        r_state := r_return_data
        // printf("res = %x\n", res_tmp)
      }.otherwise {
        // 未命中，需要通过 AXI4 去取出数据
        // 注意：由于跳转指令的存在，此处的 raddr 可能是未按照 cachelinesize 对齐的 raddr,应按照 cachelinesize 进行对齐
        r_state := axi_s_wait_arready
        axi_reg_readAddr := (io.io.raddr >> CacheLineSizeBits.U) << (CacheLineSizeBits.U)
        reqr_reg := 1.B
      }
      
    }

    is(r_return_data) {
      io.io.rdata := Mux(cache_offset === 0.U, data_cacheline_reg(31, 0),  data_cacheline_reg(63, 32))
      when (io.io.rdata_ready && !io.stall) {
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
        // cache_data(r_cache_input_index) := io.axi4.rdata
        cache_data.write(r_cache_input_index, io.axi4.rdata)
        cache_valid(r_cache_input_index) := 1.B
        cache_tag(r_cache_input_index) := r_cache_input_tag
        reqr_reg := 0.B
        // printf("cache index=%x new rdata=%x\n", r_cache_input_index, io.axi4.rdata)
        when (io.axi4.rresp =/= 0.U) {
          printf("icache rresp = %x\n", io.axi4.rresp)
        }
      }
    }
  }
}

class DCache(CacheSize :Int, CacheLineSize : Int, DataWidth : Int) extends Cache(CacheSize, CacheLineSize, DataWidth) {
  assert(CacheLineSize == 8, "DCache only support CacheLineSize = 8B now")  // 暂时仅支持 Cache 块大小为 8B 的访存
  assert(DataWidth == 64, "DCache only support 64bit IO now")

  // // icache 不需要标记是否 dirty, 但是"写回"的 DCache 要
  // 本处理器使用的 DCache 是“写直通”，因此也不需要
  // val cache_dirty = SyncReadMem(CacheLineNum, UInt((XLEN-CacheLineSizeBits).W))

  // val cache_offset = io.io.raddr(CacheLineSizeBits-1, DataWidth/8-1-1)

  val s_idle :: s_read_cache :: s_return_data :: s_write_cache :: axi_s_wait_arready :: axi_s_wait_rvalid :: axi_s_wait_wready :: axi_s_wait_bresp :: Nil = Enum(8)

  val s_state = RegInit(s_idle)

  val axi_reg_readAddr  = RegInit(0.U(XLEN.W))
  val axi_reg_writeAddr = RegInit(0.U(XLEN.W))
  val axi_reg_writeData = RegInit(0.U(XLEN.W))
  val axi_reg_writeMask = RegInit(0.U(XLEN.W))
  val axi_reg_wstrb     = RegInit(0.U((XLEN/8).W))

  //如果不是直接映射，就需要修改 index 的计算方式
  val r_cache_input_index = r_cache_input_tag(CacheLineNumBits - 1, 0)  
  val w_cache_input_index = w_cache_input_tag(CacheLineNumBits - 1, 0)
  
  io.io.raddr_ready := s_state === s_idle
  io.io.rdata_valid := s_state === s_return_data
  io.io.waddr_ready := s_state === s_idle
  io.io.wdata_ready := s_state === s_idle

  // 注意：DCache 目前的 DataWidth 是 64 bit
  // 所以把整个 data_cacheline_reg 发过来就行
  io.io.rdata := data_cacheline_reg
  
  io.bus_reqr := reqr_reg
  io.bus_reqw := reqw_reg

  // axi4lite
  // 需要处理非缓存地址
  
  io.axi4.arvalid := s_state === axi_s_wait_arready 
  io.axi4.rready := s_state === axi_s_wait_rvalid
  io.axi4.araddr := axi_reg_readAddr
  io.axi4.awaddr := axi_reg_writeAddr
  io.axi4.awvalid := s_state === axi_s_wait_wready
  io.axi4.wdata := axi_reg_writeData
  io.axi4.wstrb := axi_reg_wstrb
  io.axi4.wvalid := s_state === axi_s_wait_wready
  io.axi4.bready := s_state === axi_s_wait_bresp

  
  val r_cache_data_at_index     = cache_data.read(r_cache_input_index)
  val w_cache_data_at_index     = cache_data.read(w_cache_input_index)
  // val cache_dirty_at_index    = cache_dirty.read(r_cache_input_index)
  val r_cache_tag_at_index      = cache_tag.read(r_cache_input_index)
  val w_cache_tag_at_index      = cache_tag.read(w_cache_input_index)
  val r_cache_valid_at_index    = cache_valid.read(r_cache_input_index)
  val w_cache_valid_at_index    = cache_valid.read(w_cache_input_index)
  // val r_cache_data_at_index     = RegInit(0.U((CacheLineSize * 8).W))
  // val cache_dirty_at_index    = RegInit(false.B)
  // val r_cache_tag_at_index      = RegInit(0.U((CacheLineSize * 8).W))
  // val r_cache_valid_at_index    = RegInit(false.B)

  val hit = (r_cache_valid_at_index === true.B) && (r_cache_tag_at_index === r_cache_input_tag) 

  val uncached_r = io.io.raddr < SRAM_BASE.U || io.io.raddr > (SRAM_BASE + SRAM_SIZE).U
  val uncached_w = io.io.waddr < SRAM_BASE.U || io.io.waddr > (SRAM_BASE + SRAM_SIZE).U
  val uncached = uncached_r | uncached_w
  val axi4_readData = RegInit(0.U(XLEN.W))
  switch(s_state) {
    // 读部分基于 icache 的状态机，采用 writethrough 策略。即只要有对 Cache 的修改就将其写回内存。
    is(s_idle) {
      when (io.io.raddr_valid) { 
        s_state := s_read_cache
      }.elsewhen(io.io.waddr_valid) {
        s_state := s_write_cache
      }
    }

    is(s_return_data) {
      // 由于 datawidth 是 64 位，这里就不用再 Mux 了
      io.io.rdata := Mux(!uncached_r, data_cacheline_reg, axi4_readData)
      // LSU 在流水线 stall 时也应该继续执行，故此处判断条件比 ICache 少一个 !stall
      when (io.io.rdata_ready /*&& !io.stall*/ | io.io.bready) {
        s_state := s_idle
      }
    }

    is(s_read_cache) {
      when(hit & !uncached_r) {
        // printf ("read hit cache: addr=%x index=%x data=%x\n", io.io.raddr, r_cache_input_index, r_cache_data_at_index)
        data_cacheline_reg := r_cache_data_at_index
        s_state := s_return_data
      }.otherwise{
        // cache 未命中 或是非可缓存地址，直接用 AXI4 访存
        s_state := axi_s_wait_arready
        // 考虑是否要对齐：
        // SRAM 是按照 8 字节对齐的， LSU 处理过对齐了， Cache 不需要额外处理
        // 此时 r_cache_data_at_index 的值是上一个周期（s_idle 状态）发起读请求，在这个周期返回的值。 
        
        axi_reg_readAddr := io.io.raddr
        reqr_reg := 1.B
      }
    }

    is(axi_s_wait_arready) {
      when(io.bus_ac & io.axi4.arready) {
        s_state := axi_s_wait_rvalid
      }
    }

    is(axi_s_wait_rvalid) {
      when(io.bus_ac & io.axi4.rvalid) {
        s_state := s_return_data
        when (!uncached_r) {
          data_cacheline_reg := io.axi4.rdata
          // 这里对 SyncReadMem 进行写入，可能会面临同一个周期读写的问题，这在chisel中是未定义行为。虽然 icache 里这样写能过仿真，但是有条件还是得实现一个读写转发
          // printf("read: update data at addr = %x cache index=%x  to %x\n", io.io.raddr, r_cache_input_index, io.axi4.rdata)
          cache_data(r_cache_input_index)   := io.axi4.rdata
          cache_valid(r_cache_input_index)  := 1.B
          cache_tag(r_cache_input_index)    := r_cache_input_tag
        }.otherwise {
          axi4_readData := io.axi4.rdata
        }
        reqr_reg := 0.B
        when (io.axi4.rresp =/= 0.U) {
          printf("icache rresp = %x\n", io.axi4.rresp)
        }
      }
    }

    is (s_write_cache) {
      // 采用的策略是：无论是否命中都写回内存，再写回 cache
      // 所以这里不用判断是否命中，直接写回内存就 ok
      s_state           := axi_s_wait_wready
      axi_reg_writeAddr := io.io.waddr
      axi_reg_writeData := io.io.wdata
      axi_reg_wstrb     := io.io.wstrb
      val byteEn        =  Wire(Vec(XLEN/8, Bool()))
      for (i <- 0 until XLEN/8) {
        byteEn(i) := io.io.wstrb(i)
      }
      axi_reg_writeMask := Reverse(Cat(byteEn.map(b => Fill(8, b))))
      
      // axi_reg_writeMask := Cat(byteEn.map(b => Fill(8, b)))
      // 注意：cache 不能直接更新为 wdata，需要先处理 wstrb
      reqw_reg := 1.B
    }

    is(axi_s_wait_wready) {
      when(io.axi4.awready & io.axi4.wready & io.bus_ac) {
        s_state := axi_s_wait_bresp
      }
    }

    is(axi_s_wait_bresp) {
      when(io.bus_ac & io.axi4.bvalid) {
        io.io.bvalid := 1.B
        io.io.bresp  := io.axi4.bresp
        // printf("uncached = %d wstrb=%x writeMask=%x\n", uncached_w, io.io.wstrb, axi_reg_writeMask)
        when (!uncached_w) {
          // data_cacheline_reg := io.io.wdata & axi_reg_writeMask
          // printf("write cache: addr = %x index = %x old data = %x new cacheline data = %x datawithmask = %x\n", io.io.waddr, w_cache_input_index, w_cache_data_at_index, (~axi_reg_writeMask & w_cache_data_at_index) | (axi_reg_writeMask & io.io.wdata) , io.io.wdata & axi_reg_writeMask)
          // 这里错了，应该读出写入后的数据块，放回cache，或者是仅对 cache 块中的 wstrb 对应位置进行修改
          // 错的：cache_data(w_cache_input_index)   := io.io.wdata & axi_reg_writeMask
          s_state := s_idle
          // 用反向掩码清除需要修改的位，再或上修改的新值
          cache_data(w_cache_input_index)   := (~axi_reg_writeMask & w_cache_data_at_index) | (axi_reg_writeMask & io.io.wdata) 
          cache_valid(w_cache_input_index)  := 1.B
          cache_tag(w_cache_input_index)    := w_cache_input_tag
        }.otherwise{
          s_state := s_idle
        }
        reqw_reg := 0.B
        
        when (io.axi4.bresp =/= 0.U) {
          printf("dcache bresp = %x\n", io.axi4.bresp)
        }
      }
    }
  }
}