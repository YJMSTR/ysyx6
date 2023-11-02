import chisel3._
import chisel3.util._
// import chisel3.util.experimental.loadMemoryFromFileInline

class EXU() extends Module {
  val io = IO(new Bundle {
    //val inst = Input(UInt(32.W))
    val isAddi = Input(Bool())
    val isEbreak = Input(Bool())
    val rs1val = Input(UInt(32.W))
    val rs2val = Input(UInt(32.W))
    val rdvalin = Input(UInt(32.W))
    val imm = Input(UInt(32.W))
    val rdval = Output(UInt(32.W))
    //val halt = Output(Bool())
  })
  io.rdval := Mux1H(Seq(
    io.isAddi -> (io.rs1val + io.imm),
    io.isEbreak -> io.rdvalin
  ))
}
