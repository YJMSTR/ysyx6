import chisel3._ 
import chisel3.util._ 

class ysyx_23060110_ps2_keyboard extends BlackBox with HasBlackBoxPath{
  val io = IO(new Bundle {
    val clk = Input(Clock())
    val clrn = Input(Bool())
    val ps2_clk = Input(Clock())
    val ps2_data = Input(Bool())
    val nextdata_n = Input(Bool())
    val data = Output(UInt(8.W))
    val ready = Output(Bool())
    val overflow = Output(Bool())
    val kbd_clk = Output(Clock())
  })
  addPath("./playground/src/vsrc/ps2_keyboard.v")
}