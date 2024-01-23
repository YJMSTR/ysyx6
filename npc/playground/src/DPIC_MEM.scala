import chisel3._ 
import chisel3.util._ 
import Configs._ 
class DPIC_MEM extends BlackBox with HasBlackBoxPath{
  val io = IO(new Bundle{
    val valid = Input(Bool())
    val wen = Input(Bool())
    val raddr = Input(UInt(XLEN.W))
    val rdata = Output(UInt(XLEN.W))
    val waddr = Input(UInt(XLEN.W))
    val wdata = Input(UInt(XLEN.W))
    val wmask = Input(UInt(WMASKLEN.W))
    val clk = Input(Clock())
  })
  // val io = IO(new MemIO())
  addPath("./playground/src/vsrc/DPIC_MEM.v")
}
