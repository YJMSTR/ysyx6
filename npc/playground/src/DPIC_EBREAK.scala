import chisel3._ 
import chisel3.util._ 

class DPIC_EBREAK extends BlackBox with HasBlackBoxPath{
  val io = IO(new Bundle {
    val isEbreak = Input(Bool())
    val clk = Input(Clock())    
  })
  addPath("./playground/src/vsrc/DPIC_EBREAK.v")
}
