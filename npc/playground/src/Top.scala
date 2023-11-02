import chisel3._
import chisel3.util._
import chisel3.util.experimental.loadMemoryFromFileInline

class Top extends Module {
  val io = IO(new Bundle {
    // IFU
    val inst = Input(UInt(32.W))
    val pc = Output(UInt(32.W)) 
    val t0 = Output(UInt(32.W))
    val t1 = Output(UInt(32.W))
  })
  val R = Mem(32, UInt(32.W))
  val PC = RegInit("x80000000".U(32.W))
  io.pc := PC
  def Rread(idx: UInt) = Mux(idx === 0.U, 0.U(32.W), R(idx))
  io.t0 := Rread(5.U)
  io.t1 := Rread(6.U)

  val Decoder = Module(new IDU)
  val Executer = Module(new EXU)
  val Ebreak = Module(new DPIC_EBREAK)

  Ebreak.io.clk := clock
  Ebreak.io.isEbreak := Decoder.io.isEbreak
  Decoder.io.inst := io.inst
  Executer.io.isAddi := Decoder.io.isAddi
  Executer.io.isEbreak := Decoder.io.isEbreak
  Executer.io.rs1val := Rread(Decoder.io.rs1)
  Executer.io.rs2val := Rread(Decoder.io.rs2)
  Executer.io.rdvalin := Rread(Decoder.io.rd)
  R(Decoder.io.rd) := Executer.io.rdval
  Executer.io.imm := Decoder.io.sextimmi

  PC := PC + 4.U
  
}

