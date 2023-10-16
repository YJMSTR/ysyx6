import chisel3._
import chisel3.util._

class Top extends Module {
  val io = IO(new Bundle {
    // val clk = Input(Clock())
    val Y     = Input(UInt(2.W))
    // val rst = Input(Bool())
    val X0    = Input(UInt(2.W))
    val X1    = Input(UInt(2.W))
    val X2    = Input(UInt(2.W))
    val X3    = Input(UInt(2.W))
    val F     = Output(UInt(2.W))
  })
  io.F := MuxLookup(io.Y, io.X0, Array(
    1.U->io.X1,
    2.U->io.X2,
    3.U->io.X3
  ))
}
