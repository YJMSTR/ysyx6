import chisel3._
import chisel3.util._

class Top extends Module {
  val io = IO(new Bundle {
    val ps2_clk = Input(Clock())
    val ps2_data = Input(Bool())
    val ready = Output(Bool())
    val overflow = Output(Bool())
    val seg = Output(Vec(6, UInt(8.W)))
    val nextdata_n = Output(Bool())
  })
  val ps2keyboard = Module(new ps2_keyboard)
  val hexs = VecInit(Seq.fill(6)(Module(new Hex7sec).io))
  val nextdata_n = RegInit(1.U(1.W))
  val resetn = Wire(UInt(1.W))
  val ready = RegInit(0.U(1.W))
  val overflow = RegInit(0.U(1.W))
  val kbddata = ps2keyboard.io.data
  val kbd_clk = ps2keyboard.io.kbd_clk
  ready := ps2keyboard.io.ready
  overflow := ps2keyboard.io.overflow
  resetn := reset;
  io.ready := ready
  io.overflow := overflow
  io.nextdata_n := nextdata_n
  ps2keyboard.io.ps2_clk := io.ps2_clk
  ps2keyboard.io.ps2_data := io.ps2_data
  ps2keyboard.io.clk := clock
  ps2keyboard.io.clrn := ~resetn
  ps2keyboard.io.nextdata_n := nextdata_n
  val counter = RegInit(0.U(1.W))
  withClock(kbd_clk) {
    val keycount = RegInit(0.U(8.W))
    val lastdata = RegInit(0.U(24.W))
    when(nextdata_n.asBool) {
      nextdata_n := 0.U
    } .otherwise {
      nextdata_n := 1.U
    }
    lastdata := Cat(lastdata(15, 0), kbddata)
    val asciidata = MuxLookup(lastdata(7, 0), lastdata(7, 0), Array(
      "h0E".U->"h60".U,
      "h16".U->"h31".U,
      "h1E".U->"h32".U,
      "h26".U->"h33".U,
      "h25".U->"h34".U,
      "h2E".U->"h35".U,
      "h36".U->"h36".U,
      "h3D".U->"h37".U,
      "h3E".U->"h38".U,
      "h46".U->"h39".U,
      "h45".U->"h30".U
    ))
    hexs(0).data := lastdata(3, 0)
    hexs(1).data := lastdata(7, 4)
    hexs(2).data := asciidata(3, 0)
    hexs(3).data := asciidata(7, 4)
    hexs(4).data := keycount(3, 0)
    hexs(5).data := keycount(7, 4)
    when (lastdata(7, 0) === "hF0".U) {
      keycount := keycount + 1.U
    }
  }
  for (i <- 0 until 6) {
    io.seg(i) := hexs(i).seg
  }

}
