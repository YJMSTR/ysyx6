import chisel3._
import chisel3.util._
import Configs._
import chisel3.util.experimental.loadMemoryFromFileInline

class Top extends Module {
  val io = IO(new Bundle {
    // IFU
    val inst = Input(UInt(XLEN.W))
    val pc = Output(UInt(XLEN.W))
    // val pcsel = Input(Bool())
    // val snpc = Input(UInt(XLEN.W))
    
    // val rs1 = Input(UInt(RIDXLEN.W))
    // val rs2 = Input(UInt(RIDXLEN.W))
    // val rd = Input(UInt(RIDXLEN.W))
    // val rd_en = Input(Bool()) 
    // val rdv = Input(UInt(XLEN.W))
    // val rs1v = Output(UInt(XLEN.W))
    // val rs2v = Output(UInt(XLEN.W))
  })
  
  val R = Mem(32, UInt(XLEN.W))
  
  // PC 模块
  val PC = RegInit(RESET_VECTOR.U(XLEN.W))
  val dnpc = Wire(UInt(XLEN.W))
  val pcsel = Wire(UInt(1.W))
  io.pc := PC
  val npc = Wire(UInt(XLEN.W))
  npc := Mux(pcsel === 1.U, dnpc, PC + 4.U)
  PC := npc


  def Rread(idx: UInt) = Mux(idx === 0.U, 0.U(XLEN.W), R(idx))
  val rs1v = Wire(UInt(XLEN.W))
  val rs2v = Wire(UInt(XLEN.W))
  val rs1 = Wire(UInt(RIDXLEN.W))
  val rs2 = Wire(UInt(RIDXLEN.W))
  val rd = Wire(UInt(RIDXLEN.W))
  val rd_en = Wire(UInt(1.W))
  val rdv = Wire(UInt(XLEN.W))
  rs1v := Rread(rs1)
  rs2v := Rread(rs2)
  R(rd) := Mux(rd_en === 0.U(1.W), R(rd), rdv)
  R(0) := 0.U
  // 取指模块
  // 根据 PC 取出 inst 是在 C++ 里完成的
  
  // 译码模块
  val Decoder = Module(new IDU)
  Decoder.io.inst := io.inst
  rs1 := Decoder.io.rs1
  rs2 := Decoder.io.rs2 
  pcsel := Decoder.io.isdnpc
  rd := Decoder.io.rd 
  rd_en := Decoder.io.rd_en

  // 执行模块
  val ALU = Module(new EXU)
  ALU.io.inst := io.inst
  ALU.io.pc := io.pc
  ALU.io.alu_op := Decoder.io.alu_op
  ALU.io.asel := Decoder.io.alu_sel_a
  ALU.io.bsel := Decoder.io.alu_sel_b
  ALU.io.imm := Decoder.io.imm
  ALU.io.rs1v := rs1v
  ALU.io.rs2v := rs2v
  dnpc := ALU.io.dnpc
 
  rdv := ALU.io.res
  
  val Ebreak = Module(new DPIC_EBREAK)
  Ebreak.io.isEbreak := Decoder.io.isEbreak
  Ebreak.io.clk := clock
  
}

