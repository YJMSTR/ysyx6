import chisel3._
import chisel3.util._
import Configs._
import Instr._


// import chisel3.util.experimental.loadMemoryFromFileInline

class EXU() extends Module {
  val io = IO(new Bundle {
    val inst = Input(UInt(32.W))
    // val isAddi = Input(Bool())
    // val isEbreak = Input(Bool())
    val rs1v = Input(UInt(XLEN.W))
    val rs2v = Input(UInt(XLEN.W))
    val pc   = Input(UInt(XLEN.W))
    val asel = Input(UInt(ALU_DATASEL_WIDTH.W))
    val bsel = Input(UInt(ALU_DATASEL_WIDTH.W))
    val alu_op = Input(UInt(ALUCtrlWidth.W))
    val dnpc = Output(UInt(XLEN.W))
    val imm = Input(UInt(XLEN.W))
    val res = Output(UInt(XLEN.W))
    //val halt = Output(Bool())
  })

  val data_A = MuxLookup(io.asel, 0.U(32.W), 
  Seq(
    ALU_DATA_NONE->0.U(32.W),
    ALU_DATA_RS1->io.rs1v,
    ALU_DATA_RS2->io.rs2v,
    ALU_DATA_PC->io.pc, 
    ALU_DATA_IMM->io.imm,
  ))
  val data_B = MuxLookup(io.bsel, 0.U(32.W), 
  Seq(
    ALU_DATA_NONE->0.U(32.W),
    ALU_DATA_RS1->io.rs1v,
    ALU_DATA_RS2->io.rs2v,
    ALU_DATA_PC->io.pc, 
    ALU_DATA_IMM->io.imm,
  ))
  
  val data_res = Wire(UInt(XLEN.W))

  data_res := MuxLookup(io.alu_op, 0.U(32.W), 
  Seq(
    ALU_ADD->(data_A + data_B),
    ALU_JALR_OR_JAL->(io.pc + 4.U)
  ))

  io.res := data_res

  when(io.inst === JALR) {
    io.dnpc := io.rs1v + io.imm
  }.elsewhen (io.inst === JAL) {
    io.dnpc := io.pc + io.imm
  }.otherwise {
    io.dnpc := 0.U
  }

}
