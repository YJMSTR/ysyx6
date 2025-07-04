
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
}

class LSUOut extends Bundle {
  val inst = UInt(32.W)
  val pc = UInt(XLEN.W)
  val alures = UInt(XLEN.W)
  val memvalid = Bool()
  val rden = Bool()
  val rd = UInt(RIDXLEN.W)
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
    val axi4lite_to_arbiter = Flipped(new AXI4LiteInterface)
    val bus_ac = Input(Bool())
    val bus_reqr = Output(Bool())
    val bus_reqw = Output(Bool())
  })


  //val fake_sram = Module(new FAKE_SRAM_LSU())
  val reqr = RegInit(0.B)
  val reqw = RegInit(0.B)
  io.bus_reqr := reqr 
  io.bus_reqw := reqw
  val readAddr = RegInit(0.U(32.W))
  val readData = RegInit(0.U(XLEN.W))

  val r_idle :: r_wait_arready :: r_wait_rvalid :: Nil = Enum(3)
  val r_state = RegInit(r_idle)

  // 由于顺序五级流水不会同时进行读和写， 当 io.in.valid 并且 wen 为 0 即为读
  io.axi4lite_to_arbiter.arvalid := r_state === r_wait_arready 
  io.axi4lite_to_arbiter.araddr := readAddr
  io.axi4lite_to_arbiter.rready := r_state === r_wait_rvalid & io.out.ready

  switch(r_state){
    is(r_idle){
      when(io.in.valid && io.in.bits.memvalid && !io.in.bits.wen){
        readAddr := io.in.bits.raddr
        r_state := r_wait_arready
        reqr := 1.B
      }
    }
    is(r_wait_arready){ // arvalid = 1
      when(io.bus_ac & io.axi4lite_to_arbiter.arready){
        //此时把要读取的地址传给 mem，等待其读取完成
        r_state := r_wait_rvalid
      }
    }
    is(r_wait_rvalid){ // rready = 1
      when(io.axi4lite_to_arbiter.rvalid){
        readData := io.axi4lite_to_arbiter.rdata
        r_state := r_idle
        reqr := 0.B
      }
    }
  }

  
  val w_idle :: w_wait_awready :: w_wait_wready :: w_wait_bvalid :: Nil = Enum(4)
  val w_state = RegInit(w_idle)

  val writeAddr = RegInit(0.U(32.W))
  val writeData = RegInit(0.U(XLEN.W))
  val writeStrb = RegInit(0.U((XLEN/8).W))

  io.axi4lite_to_arbiter.awaddr := writeAddr
  io.axi4lite_to_arbiter.awvalid := w_state === w_wait_awready
  io.axi4lite_to_arbiter.wdata := writeData
  io.axi4lite_to_arbiter.wvalid := w_state === w_wait_wready
  io.axi4lite_to_arbiter.wstrb := writeStrb
  io.axi4lite_to_arbiter.bready := w_state === w_wait_bvalid

  switch(w_state) {
    is(w_idle) {
      // 由于目前没有同时进行读写，当 valid = 1 且 wen = 1 为写
      when(io.in.valid && io.in.bits.memvalid && io.in.bits.wen) {
        writeAddr := io.in.bits.waddr
        writeData := io.in.bits.wdata 
        writeStrb := io.in.bits.wmask
        w_state := w_wait_awready
        reqw := 1.B
      }
    }
    is(w_wait_awready) {
      when(io.bus_ac & io.axi4lite_to_arbiter.awready) {
        // waddr 传输完成
        w_state := w_wait_wready
      }
    }
    is(w_wait_wready) {
      when(io.axi4lite_to_arbiter.wready) {
        // wdata 传输完成
        w_state := w_wait_bvalid
      }
    }
    is(w_wait_bvalid) {
      when(io.axi4lite_to_arbiter.bvalid) {
        w_state := w_idle
        reqw := 0.B
      }
    }
  }

  
  //printf("io.out.valid = %d\n", io.out.valid)
  io.out.bits.rdata := readData
  io.in.ready := r_state === r_idle && w_state === w_idle
  
  val instreg = RegInit(0.U(32.W))
  val pcreg = RegInit(0.U(XLEN.W))
  val memvalidreg = RegInit(0.B)
  val aluresreg = RegInit(0.U(XLEN.W))
  val rdenreg = RegInit(0.B)
  val rdreg = RegInit(0.U(RIDXLEN.W))
  val memsextreg = RegInit(MEM_SEXT_NONE)

  io.out.bits.inst := instreg 
  io.out.bits.pc := pcreg 
  io.out.bits.memvalid := memvalidreg
  io.out.bits.alures := aluresreg
  io.out.bits.rden := rdenreg 
  io.out.bits.rd := rdreg 
  io.out.bits.memsext := memsextreg 

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
  }
}

