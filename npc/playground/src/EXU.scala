import chisel3._
import chisel3.util._
import Configs._
import Instr._


// import chisel3.util.experimental.loadMemoryFromFileInline

class EXU() extends Module {
  val io = IO(new Bundle {
    val inst = Input(UInt(32.W))
    val rs1v = Input(UInt(XLEN.W))
    val rs2v = Input(UInt(XLEN.W))
    val pc   = Input(UInt(XLEN.W))
    val asel = Input(UInt(ALU_DATASEL_WIDTH.W))
    val bsel = Input(UInt(ALU_DATASEL_WIDTH.W))
    val alu_op = Input(UInt(ALUCtrlWidth.W))
    // val dnpc = Output(UInt(XLEN.W))
    val imm = Input(UInt(XLEN.W))
    val res = Output(UInt(XLEN.W))
    val isword = Input(Bool())
    //val halt = Output(Bool())
  })
  val shamt = io.inst(25, 20)
  val data_A = MuxLookup(io.asel, 0.U(XLEN.W))(Seq(
    ALU_DATA_NONE->0.U(XLEN.W),
    ALU_DATA_RS1->io.rs1v,
    ALU_DATA_RS2->io.rs2v,
    ALU_DATA_PC->io.pc, 
    ALU_DATA_IMM->io.imm,
  ))
  val data_B = MuxLookup(io.bsel, 0.U(XLEN.W))(Seq(
    ALU_DATA_NONE->0.U(XLEN.W),
    ALU_DATA_RS1->io.rs1v,
    ALU_DATA_RS2->io.rs2v,
    ALU_DATA_PC->io.pc, 
    ALU_DATA_IMM->io.imm,
    ALU_DATA_SHAMT->shamt,
  ))

  val data_res = Wire(UInt(XLEN.W))
  val snpc = io.pc + 4.U
  val mul_res = data_A * data_B
  val mulh_res = (data_A.asSInt*data_B.asSInt)(63, 32).asUInt
  val mulhu_res = mul_res(63, 32)
  val rem_res = (data_A.asSInt % data_B.asSInt).asUInt
  val remw_res = (data_A(31, 0).asSInt % data_B(31, 0).asSInt).asUInt
  val remuw_res = (data_A(31, 0) % data_B(31, 0))
  data_res := MuxLookup(io.alu_op, 0.U(XLEN.W))(Seq(
    //ALU_ADD->(data_A + data_B + 1.U),
    ALU_ADD          -> (data_A + data_B),
    ALU_SLT          -> (Mux(data_A.asSInt < data_B.asSInt, 1.U, 0.U)),
    ALU_SLTU         -> (Mux(data_A < data_B, 1.U, 0.U)),
    ALU_SRA          -> ((data_A.asSInt >> data_B(5, 0)).asUInt),
    ALU_AND          -> (data_A & data_B),
    ALU_OR           -> (data_A | data_B),
    ALU_XOR          -> (data_A ^ data_B),
    ALU_SLL          -> (data_A << data_B(5,0)),
    ALU_SRL          -> (data_A >> data_B(5,0)),
    ALU_JALR_OR_JAL  -> (io.pc + 4.U),
    ALU_SUB          -> (data_A-data_B),
    ALU_MUL          -> (mul_res),
    ALU_MULH         -> (Cat(Fill(XLEN-32, mulh_res(31)), mulh_res)),
    ALU_MULHU        -> (Cat(Fill(XLEN-32, mulhu_res(31)), mulhu_res)),
    ALU_DIVU         -> (data_A/data_B),
    ALU_DIV          -> ((data_A.asSInt/data_B.asSInt).asUInt),
    ALU_REM          -> (rem_res),
    ALU_REMU         -> (data_A % data_B),
    ALU_SRAW         -> Cat(Fill(32, 0.U), (data_A(31, 0).asSInt >> data_B(4, 0).asUInt)),
    ALU_SRLW         -> Cat(Fill(32, 0.U), (data_A(31, 0) >> data_B(4, 0))),
    ALU_REMW         -> Cat(Fill(32, 0.U), remw_res),
    ALU_REMUW        -> Cat(Fill(32, 0.U), remuw_res),
  ))
  
  val data_resw = Cat(Fill(XLEN-32, data_res(31)), data_res(31, 0))
  io.res := Mux(io.isword, data_resw, data_res)

  // when(io.inst === JALR) {
  //   io.dnpc := io.rs1v + io.imm
  // }.elsewhen (io.inst === JAL) {
  //   io.dnpc := io.pc + io.imm
  // }.otherwise {
  //   io.dnpc := 0.U
  // }
  
}
