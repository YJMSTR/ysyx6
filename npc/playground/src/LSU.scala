
import chisel3._ 
import chisel3.util._ 
import Configs._


class LSUIn extends Bundle {
  val inst = UInt(32.W)
  val pc = UInt(XLEN.W)
  val alures = UInt(XLEN.W)
  // rs2v 即 wdata
  val memvalid = Bool()
  val wen = Bool()
  val wmask = UInt(XLEN.W)
  val wsext = UInt(MEM_SEXT_SEL_WIDTH.W)
  val raddr = UInt(32.W)
  val waddr = UInt(32.W)
  val wdata = UInt(XLEN.W)
  val rden = Bool()
  val rd = UInt(RIDXLEN.W)
  val csridx = UInt(CSRIDXLEN.W)
  val csrrv = UInt(XLEN.W)
  val csrwv = UInt(XLEN.W)
  val csr_en = Bool()
}

class LSUOut extends Bundle {
  val inst = UInt(32.W)
  val pc = UInt(XLEN.W)
  val alures = UInt(XLEN.W)
  val memvalid = Bool()
  val rden = Bool()
  val rd = UInt(RIDXLEN.W)
  val csridx = UInt(CSRIDXLEN.W)
  val csrrv = UInt(XLEN.W)
  val csrwv = UInt(XLEN.W)
  val csr_en = Bool()
  val memsext = UInt(MEM_SEXT_SEL_WIDTH.W)
  val rdata = UInt(XLEN.W)
}

// class LSU extends Module {
//   val io = IO(new Bundle {
//     val in = Flipped(Decoupled(new LSUIn))
//     val out = Decoupled(new LSUOut)
//   })
//   val dpic_mem = Module(new DPIC_MEM)
//   io.in.ready := 1.B
//   dpic_mem.io.valid := io.in.valid
//   dpic_mem.io.wen := io.in.bits.wen
//   dpic_mem.io.raddr := io.in.bits.raddr
//   dpic_mem.io.waddr := io.in.bits.waddr
//   dpic_mem.io.wdata := io.in.bits.wdata
//   dpic_mem.io.wmask := io.in.bits.wmask
//   dpic_mem.io.clk := clock
//   io.out.valid := RegNext(io.in.valid, 0.B)
//   // 手动模拟 1 周期的 SRAM 延迟，仅读取有延迟
//   io.out.bits.rdata := RegNext(dpic_mem.io.rdata, 0.U)
//   // io.out.bits.rdata := 0.U

// }

class LSU extends Module {
  val io = IO(new Bundle {
    val in = Flipped(Decoupled(new LSUIn))
    val out = Decoupled(new LSUOut)
    val axi4_to_arbiter = Flipped(new AXI4Interface)
    val bus_ac = Input(Bool())
    val bus_reqr = Output(Bool())
    val bus_reqw = Output(Bool())
  })



  val empty_master = Module(new empty_axi4_master)
  io.axi4_to_arbiter <> empty_master.io.axi4

  //val fake_sram = Module(new FAKE_SRAM_LSU())
  val reqr = RegInit(0.B)
  val reqw = RegInit(0.B)
  io.bus_reqr := reqr 
  io.bus_reqw := reqw
  val rready       = WireInit(1.B)
  val wready       = WireInit(1.B)
  val readAddr     = RegInit(0.U(32.W))
  val readData     = RegInit(0.U(XLEN.W))
  val readSize     = RegInit(0.U(3.W))
  val writeAddr    = RegInit(0.U(32.W))
  val writeData    = RegInit(0.U(XLEN.W))
  val writeStrb    = RegInit(0.U((XLEN/8).W))

  val r_is_sram = WireInit(0.B)
  r_is_sram := io.in.bits.raddr >= SRAM_BASE.U && io.in.bits.raddr < (SRAM_BASE + SRAM_SIZE).U
  val w_is_sram = WireInit(0.B)
  w_is_sram := io.in.bits.waddr >= SRAM_BASE.U && io.in.bits.waddr < (SRAM_BASE + SRAM_SIZE).U

  // 未实现 DCache 时的状态机
  // val r_idle :: r_wait_arready :: r_wait_rvalid :: Nil = Enum(3)
  // val r_state = RegInit(r_idle)

  // // 由于顺序五级流水不会同时进行读和写， 当 io.in.valid 并且 wen 为 0 即为读
  // io.axi4_to_arbiter.arvalid := r_state === r_wait_arready 
  // io.axi4_to_arbiter.araddr := readAddr
  // io.axi4_to_arbiter.rready := r_state === r_wait_rvalid & io.out.ready

  // switch(r_state){
  //   is(r_idle){
  //     when(io.in.valid && io.in.bits.memvalid && !io.in.bits.wen){
  //       readAddr := io.in.bits.raddr
  //       r_state := r_wait_arready
  //       reqr := 1.B
  //       rready := 0.B
  //     }
  //   }
  //   is(r_wait_arready){ // arvalid = 1
  //     rready := 0.B
  //     when(io.bus_ac & io.axi4_to_arbiter.arready){
  //       //此时把要读取的地址传给 mem，等待其读取完成
  //       r_state := r_wait_rvalid
  //     }
  //   }
  //   is(r_wait_rvalid){ // rready = 1
  //     rready := 0.B
  //     when(io.axi4_to_arbiter.rvalid){
  //       readData := io.axi4_to_arbiter.rdata
  //       r_state := r_idle
  //       reqr := 0.B
  //       rready := 1.B
  //     }
  //   }
  // }

  
  // val w_idle :: w_wait_awready :: w_wait_wready :: w_wait_bvalid :: Nil = Enum(4)
  // val w_state = RegInit(w_idle)

  // val writeAddr = RegInit(0.U(32.W))
  // val writeData = RegInit(0.U(XLEN.W))
  // val writeStrb = RegInit(0.U((XLEN/8).W))

  // io.axi4_to_arbiter.awaddr := writeAddr
  // io.axi4_to_arbiter.awvalid := w_state === w_wait_awready
  // io.axi4_to_arbiter.wdata := writeData
  // io.axi4_to_arbiter.wvalid := w_state === w_wait_wready
  // io.axi4_to_arbiter.wstrb := writeStrb
  // io.axi4_to_arbiter.bready := w_state === w_wait_bvalid

  // switch(w_state) {
  //   is(w_idle) {
  //     // 由于目前没有同时进行读写，当 valid = 1 且 wen = 1 为写
  //     when(io.in.valid && io.in.bits.memvalid && io.in.bits.wen) {
  //       writeAddr := io.in.bits.waddr
  //       writeData := io.in.bits.wdata 
  //       writeStrb := io.in.bits.wmask
  //       w_state := w_wait_awready
  //       reqw := 1.B
  //       wready := 0.B
  //     }
  //   }
  //   is(w_wait_awready) {
  //     wready := 0.B
  //     when(io.bus_ac & io.axi4_to_arbiter.awready) {
  //       // waddr 传输完成
  //       w_state := w_wait_wready
  //       // printf("pc = %x lsu addr = %x\n", io.out.bits.pc, writeAddr)
  //     }
  //   }
  //   is(w_wait_wready) {
  //     wready := 0.B
  //     when(io.axi4_to_arbiter.wready) {
  //       // wdata 传输完成
  //       w_state := w_wait_bvalid
  //     }
  //   }
  //   is(w_wait_bvalid) {
  //     wready := 0.B
  //     when(io.axi4_to_arbiter.bvalid) {
  //       w_state := w_idle
  //       reqw := 0.B
  //       wready := 1.B
  //     }
  //   }
  // }

  // 实现了 DCache 的状态机
  // 非可缓存地址放在 DCache 里处理，那些地址直接读对应的设备
  // 注意：读取cache时返回的是一个cacheline的数据，需要 lsu 从中提取出自己需要的数据。因此首先要按照 cacheline 的大小计算出地址偏移量，再移位。
  // 注意2：对于不可缓存的地址，不需要移位。lsu 中判断了是否为 sram，如果是，就进行移位操作。
  val r_align_offset = RegInit(0.U(3.W))
  val r_idle :: r_cache_reqr :: r_cache_return :: Nil = Enum(3)
  val r_state = RegInit(r_idle)
  val w_align_offset = RegInit(0.U(3.W))
  val w_idle :: w_cache_reqw :: w_cache_return :: Nil = Enum(3)
  val w_state = RegInit(w_idle)
  
  val dcache = Module(new DCache(4096, 8, 64))

  dcache.io.axi4            <> io.axi4_to_arbiter
  dcache.io.bus_ac          := io.bus_ac
  dcache.io.io.raddr_valid  := r_state === r_cache_reqr
  dcache.io.io.raddr        := readAddr
  dcache.io.io.rsize        := readSize
  dcache.io.io.rdata_ready  := r_state === r_cache_return
  dcache.io.stall           := 0.B                // dcache 不需要处理 stall 信号
  dcache.io.io.waddr_valid  := w_state === w_cache_reqw
  dcache.io.io.wdata_valid  := w_state === w_cache_reqw
  dcache.io.io.waddr        := writeAddr
  dcache.io.io.wdata        := writeData
  dcache.io.io.wstrb        := writeStrb
  dcache.io.io.bready       := w_state === w_cache_return

  io.bus_reqr := dcache.io.bus_reqr
  io.bus_reqw := dcache.io.bus_reqw
  
  val r_offset_reg = RegInit(0.U(3.W))
  val w_offset_reg = RegInit(0.U(3.W))


  switch(r_state) {
    is(r_idle) {
      when (io.in.valid && io.in.bits.memvalid && !io.in.bits.wen) {
        r_align_offset := Mux(r_is_sram, io.in.bits.raddr(2, 0), 0.U)
        readAddr  := Mux(r_is_sram, Cat(io.in.bits.raddr(31, 3), 0.U(3.W)), io.in.bits.raddr) // 如果是 sram，按 8 字节对齐
        r_state   := r_cache_reqr
        rready    := 0.B
        r_offset_reg := Mux(r_is_sram, io.in.bits.raddr(2, 0), 0.U)
      }
    }

    is(r_cache_reqr) {
      rready := 0.B
      when(dcache.io.io.raddr_ready) {
        r_state := r_cache_return
      }
    }

    is(r_cache_return) {
      rready := 0.B
      when(dcache.io.io.rdata_valid) {
        // printf("lsu raddr = %x is_sram = %d r_align_offset = %x rdata=%x\n", dcache.io.io.raddr + r_offset_reg, r_is_sram, io.in.bits.raddr(2, 0), Mux(r_is_sram, dcache.io.io.rdata >> (r_offset_reg * 8.U), dcache.io.io.rdata))
        readData  := Mux(r_is_sram, dcache.io.io.rdata >> (r_offset_reg * 8.U), dcache.io.io.rdata)
        r_state   := r_idle
        rready    := 1.B
      }
    }
  }
  
  switch(w_state) {
    is(w_idle) {
      when (io.in.valid && io.in.bits.memvalid && io.in.bits.wen) {
        w_align_offset := Mux(w_is_sram, io.in.bits.waddr(2, 0), 0.U)
        w_offset_reg := Mux(w_is_sram, io.in.bits.waddr(2, 0), 0.U)
        writeAddr := Mux(w_is_sram, Cat(io.in.bits.waddr(31, 3), 0.U(3.W)), io.in.bits.waddr)
        writeData := io.in.bits.wdata << (io.in.bits.waddr(2,0) * 8.U)
        writeStrb := io.in.bits.wmask << (io.in.bits.waddr(2,0))
        w_state   := w_cache_reqw
        wready    := 0.B
      }
    }

    is(w_cache_reqw) {
      wready := 0.B
      when (dcache.io.io.waddr_ready & dcache.io.io.wdata_ready) {
        // printf("lsu writeaddr = %x writedata(aligned) = %x wstrb(aligned)=%x offset=%x\n", writeAddr, writeData, writeStrb, w_offset_reg)
        w_state := w_cache_return
      }
    }

    is(w_cache_return) {
      wready := 0.B
      when (dcache.io.io.bvalid) {
        w_state     := w_idle
        wready      := 1.B
      }
    }
  }
  //printf("io.out.valid = %d\n", io.out.valid)
  io.out.bits.rdata := readData
  // io.in.ready := r_state === r_idle && w_state === w_idle
  io.in.ready := rready & wready
  
  val instreg = RegInit(0.U(32.W))
  val pcreg = RegInit(0.U(XLEN.W))
  val memvalidreg = RegInit(0.B)
  val aluresreg = RegInit(0.U(XLEN.W))
  val rdenreg = RegInit(0.B)
  val rdreg = RegInit(0.U(RIDXLEN.W))
  val memsextreg = RegInit(MEM_SEXT_NONE)
  val csridxreg = RegInit(0.U(CSRIDXLEN.W))
  val csrrvreg = RegInit(0.U(XLEN.W))
  val csrwvreg = RegInit(0.U(XLEN.W))
  val csrenreg = RegInit(0.B)

  io.out.bits.inst := instreg 
  io.out.bits.pc := pcreg 
  io.out.bits.memvalid := memvalidreg
  io.out.bits.alures := aluresreg
  io.out.bits.rden := rdenreg 
  io.out.bits.rd := rdreg 
  io.out.bits.memsext := memsextreg 
  io.out.bits.csridx := csridxreg
  io.out.bits.csrrv := csrrvreg
  io.out.bits.csrwv := csrwvreg
  io.out.bits.csr_en := csrenreg

  io.out.valid := r_state === r_idle && w_state === w_idle
  // when (io.in.valid & io.in.ready){
  //   instreg := io.in.bits.inst 
  //   pcreg := io.in.bits.pc
  //   memvalidreg := io.in.bits.memvalid
  //   aluresreg := io.in.bits.alures
  //   rdenreg := io.in.bits.rden
  //   rdreg := io.in.bits.rd
  //   memsextreg := io.in.bits.wsext
  // }

  when (io.in.valid && r_state === r_idle && w_state === w_idle) {
    instreg := io.in.bits.inst 
    pcreg := io.in.bits.pc
    memvalidreg := io.in.bits.memvalid
    aluresreg := io.in.bits.alures
    rdenreg := io.in.bits.rden
    rdreg := io.in.bits.rd
    memsextreg := io.in.bits.wsext
    csridxreg := io.in.bits.csridx
    csrrvreg := io.in.bits.csrrv
    csrwvreg := io.in.bits.csrwv
    csrenreg := io.in.bits.csr_en
  }
}

