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
  val shamt = io.inst(24, 20)
  val data_A = MuxLookup(io.asel, 0.U(32.W))(Seq(
    ALU_DATA_NONE->0.U(32.W),
    ALU_DATA_RS1->io.rs1v,
    ALU_DATA_RS2->io.rs2v,
    ALU_DATA_PC->io.pc, 
    ALU_DATA_IMM->io.imm,
  ))
  val data_B = MuxLookup(io.bsel, 0.U(32.W))(Seq(
    ALU_DATA_NONE->0.U(32.W),
    ALU_DATA_RS1->io.rs1v,
    ALU_DATA_RS2->io.rs2v,
    ALU_DATA_PC->io.pc, 
    ALU_DATA_IMM->io.imm,
    ALU_DATA_SHAMT->shamt,
  ))

  val data_res = Wire(UInt(XLEN.W))
  val snpc = io.pc + 4.U

  data_res := MuxLookup(io.alu_op, 0.U(32.W))(Seq(
    //ALU_ADD->(data_A + data_B + 1.U),
    ALU_ADD->(data_A + data_B),
    ALU_SLT->(Mux(data_A.asSInt < data_B.asSInt, 1.U, 0.U)),
    ALU_SLTU->(Mux(data_A < data_B, 1.U, 0.U)),
    ALU_SRA->((data_A.asSInt >> data_B(4, 0)).asUInt),
    ALU_AND->(data_A & data_B),
    ALU_OR->(data_A | data_B),
    ALU_XOR->(data_A ^ data_B),
    ALU_SLL->(data_A << data_B(4,0)),
    ALU_SRL->(data_A >> data_B(4,0)),
    ALU_JALR_OR_JAL->(io.pc + 4.U),
    ALU_SUB->(data_A-data_B),
    ALU_MUL->(data_A*data_B)(31, 0),
    ALU_MULH->(data_A*data_B)(63,32),
    ALU_DIVU->(data_A/data_B),
    ALU_DIV->((data_A.asSInt/data_B.asSInt).asUInt),
    ALU_REM->((data_A.asSInt % data_B.asSInt).asUInt),
    ALU_REMU->(data_A % data_B),

  ))

  io.res := data_res

  // when(io.inst === JALR) {
  //   io.dnpc := io.rs1v + io.imm
  // }.elsewhen (io.inst === JAL) {
  //   io.dnpc := io.pc + io.imm
  // }.otherwise {
  //   io.dnpc := 0.U
  // }
  io.dnpc := MuxCase(0.U, Array(
    (io.inst === JALR)  -> (io.rs1v + io.imm),
    (io.inst === JAL)   -> (io.pc + io.imm),
    (io.inst === BEQ)   -> Mux(io.rs1v === io.rs2v, data_res, snpc),
    (io.inst === BNE)   -> Mux(io.rs1v === io.rs2v, snpc, data_res),
    (io.inst === BGE)   -> Mux(io.rs1v.asSInt >= io.rs2v.asSInt, data_res, snpc),
    (io.inst === BGEU)  -> Mux(io.rs1v >= io.rs2v, data_res, snpc),
    (io.inst === BLT)   -> Mux(io.rs1v.asSInt < io.rs2v.asSInt, data_res, snpc),
    (io.inst === BLTU)  -> Mux(io.rs1v < io.rs2v, data_res, snpc)
  ))
}
