import chisel3._
import Configs._ 
import Instr._ 
import chisel3.util._
import Configs.ALU_DATA_RS1
import Configs.IMM_NONE
import Configs.MEM_SEXT_32
import Configs.MEM_SEXT_NONE
import Configs.MEM_NSEXT_32
import Configs.ALU_DIVU
// import chisel3.util.experimental.loadMemoryFromFileInline

class IDU() extends Module {
  val io = IO(new Bundle {
    // RV32 和 64 的指令都是 32 位长，除非是 C 扩展
    val inst = Input(UInt(32.W))
    // 这两个信号拉到顶，去访问寄存器堆
    val rs1 = Output(UInt(RIDXLEN.W))
    val rs2 = Output(UInt(RIDXLEN.W))
    val rd  = Output(UInt(RIDXLEN.W))
    val rd_en = Output(Bool())
    val imm = Output(UInt(32.W))
    val alu_op = Output(UInt(ALUCtrlWidth.W))
    val alu_sel_a = Output(UInt(ALU_DATASEL_WIDTH.W))
    val alu_sel_b = Output(UInt(ALU_DATASEL_WIDTH.W))
    // pc 由其它模块传给 alu
    
    val isdnpc = Output(Bool())
    val isEbreak = Output(Bool())

    val memvalid = Output(Bool())
    val memwen = Output(Bool())
    val memwmask = Output(UInt(WMASKLEN.W))
    val memsext = Output(UInt(MEM_SEXT_SEL_WIDTH.W))
    // 目前暂时不用根据指令读取内存
  })

  io.rs1 := io.inst(19, 15)
  io.rs2 := io.inst(24, 20)
  io.rd  := io.inst(11, 7) 

  val List(alu_op, alu_sel_a, alu_sel_b, isdnpc, immsel, rden, memvalid, memwen, memwmask, memsext) = ListLookup(
    io.inst,
    List(ALU_NONE, ALU_DATA_NONE, ALU_DATA_NONE, 0.U(1.W), IMM_NONE, 0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_NONE),
    //List(ALU_OP, ALU_A, ALU_B, isdnpc, IMMSEL, RDWEN, memvalid, memwen, memwmask, memsext&bits)
    // NONE 就直接全0
    // 只用到一个数据就 none + data， op 设为 add
    Array(
      // U-type
      LUI     -> List(ALU_ADD,          ALU_DATA_NONE,  ALU_DATA_IMM,   0.U(1.W), IMM_U,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_NONE),
      AUIPC   -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   0.U(1.W), IMM_U,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_NONE),
      // I-type
      LH      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_16),
      LHU     -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_NSEXT_16),
      LB      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_8),
      LBU     -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_NSEXT_8),
      LW      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_32),
      LWU     -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_NSEXT_32),
      ADDI    -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_NONE),
      SLTI    -> List(ALU_SLT,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_NONE),
      SLTIU   -> List(ALU_SLTU,         ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_NONE),
      JALR    -> List(ALU_JALR_OR_JAL,  ALU_DATA_RS1,   ALU_DATA_IMM,   1.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_NONE),
      //rv64: ADDIW
      SRAI    -> List(ALU_SRA,          ALU_DATA_RS1,   ALU_DATA_SHAMT, 0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_NONE),
      ANDI    -> List(ALU_AND,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_NONE),
      ORI     -> List(ALU_OR,           ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_NONE),
      XORI    -> List(ALU_XOR,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_NONE),
      SLLI    -> List(ALU_SLL,          ALU_DATA_RS1,   ALU_DATA_SHAMT, 0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_NONE),
      SRLI    -> List(ALU_SRL,          ALU_DATA_RS1,   ALU_DATA_SHAMT, 0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_NONE), 

      // J-type
      JAL     -> List(ALU_JALR_OR_JAL,  ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_J,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_NONE),

      // S-type
      SB      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_S,    0.U(1.W), 1.U(1.W), 1.U(1.W), 1.U(WMASKLEN.W), MEM_SEXT_NONE),
      SH      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_S,    0.U(1.W), 1.U(1.W), 1.U(1.W), 3.U(WMASKLEN.W), MEM_SEXT_NONE),
      SW      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_S,    0.U(1.W), 1.U(1.W), 1.U(1.W), 15.U(WMASKLEN.W), MEM_SEXT_NONE),

      // R-type
      ADD     -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      SUB     -> List(ALU_SUB,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      SLL     -> List(ALU_SLL,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      AND     -> List(ALU_AND,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      SLTU    -> List(ALU_SLTU,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      OR      -> List(ALU_OR,           ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      XOR     -> List(ALU_XOR,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      MUL     -> List(ALU_MUL,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      MULH    -> List(ALU_MULH,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      DIVU    -> List(ALU_DIVU,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      DIV     -> List(ALU_DIV,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      REM     -> List(ALU_REM,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      REMU    -> List(ALU_REMU,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      SLT     -> List(ALU_SLT,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      SRA     -> List(ALU_SRA,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      SRL     -> List(ALU_SRL,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),


      //B-type
      BEQ     -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_B,    0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      BNE     -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_B,    0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      BGE     -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_B,    0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      BLT     -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_B,    0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      BLTU    -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_B,    0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),
      BGEU    -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_B,    0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE),

      EBREAK  -> List(ALU_NONE,         ALU_DATA_NONE,  ALU_DATA_NONE,  0.U(1.W), IMM_NONE, 0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_NONE),
    ),
  )

  // immGen 
  val immi = Cat(Fill(XLEN-12, io.inst(31)), io.inst(31, 20))
  val immj_tmp = Cat(io.inst(31), io.inst(19, 12), io.inst(20), io.inst(30,21), 0.U(1.W))
  val immj = Cat(Fill(XLEN-12, immj_tmp(20)), immj_tmp)
  //printf("immj = %x\n", immj)
  val immu = Cat(io.inst(31, 12), 0.U(12.W))
  val imms_tmp = Cat(io.inst(31, 25), io.inst(11, 7))
  val imms = Cat(Fill(XLEN-12, imms_tmp(11)), imms_tmp)
  val immb_tmp = Cat(io.inst(31), io.inst(7), io.inst(30, 25), io.inst(11, 8), 0.U(1.W))
  val immb = Cat(Fill(XLEN-13, immb_tmp(12)), immb_tmp)
  
  io.imm := MuxLookup(immsel, 0.U)(Seq(
    IMM_I->immi, 
    IMM_J->immj, 
    IMM_U->immu,
    IMM_S->imms,
    IMM_B->immb
  ))

  io.alu_op := alu_op 
  io.alu_sel_a := alu_sel_a
  io.alu_sel_b := alu_sel_b
  io.isdnpc := isdnpc
  io.rd_en := rden
  io.memvalid := memvalid
  io.memwen := memwen
  io.memwmask := memwmask 
  io.memsext := memsext
  when(io.inst === EBREAK) {
    io.isEbreak := 1.U(1.W)
  }.otherwise {
    io.isEbreak := 0.U(1.W)
  }
}
