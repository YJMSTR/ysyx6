import chisel3._ 
import chisel3.util._ 

class DPIC_IFU extends BlackBox with HasBlackBoxPath{
  val io = IO(new Bundle {
    //val clk = Input(Clock())
    val valid = Input(Bool())
    val pc = Input(UInt(32.W))
    val inst = Output(UInt(32.W))
    val clk = Input(Clock())
  })
  addPath("./playground/src/vsrc/DPIC_IFU.v")
}