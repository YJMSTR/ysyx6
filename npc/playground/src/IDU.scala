import chisel3._
import Configs._ 
import Instr._ 
import chisel3.util._

// import chisel3.util.experimental.loadMemoryFromFileInline

class ysyx_23060110_IDU() extends Module {
  val io = IO(new Bundle {
    // RV32 和 64 的指令都是 32 位长，除非是 C 扩展
    val inst = Input(UInt(32.W))
    val pc = Input(UInt(XLEN.W))
    val rs1 = Output(UInt(RIDXLEN.W))
    val rs2 = Output(UInt(RIDXLEN.W))
    val rd  = Output(UInt(RIDXLEN.W))
    val rd_en = Output(Bool())
    val imm = Output(UInt(XLEN.W))
    val alu_op = Output(UInt(ALUCtrlWidth.W))
    val alu_sel_a = Output(UInt(ALU_DATASEL_WIDTH.W))
    val alu_sel_b = Output(UInt(ALU_DATASEL_WIDTH.W))
    // pc 由其它模块传给 alu
    
    val isdnpc = Output(Bool())
    //val dnpc = Output(UInt(XLEN.W))
    val isEbreak = Output(Bool())

    val memvalid = Output(Bool())
    val memwen = Output(Bool())
    val memwmask = Output(UInt(WMASKLEN.W))
    val memsext = Output(UInt(MEM_SEXT_SEL_WIDTH.W))
    
    val isword = Output(Bool())
    // 是否读取了 rs1 rs2
    val rrs1 = Output(Bool())
    val rrs2 = Output(Bool())
  })
  
  io.rs1 := io.inst(19, 15)
  io.rs2 := io.inst(24, 20)
  io.rd  := io.inst(11, 7) 
  // isword (RV64Only)：判断是否为字运算指令（例如addiw),如果是则为1
  val List(alu_op, alu_sel_a, alu_sel_b, isdnpc, immsel, rden, memvalid, memwen, memwmask, memsext, isword, rrs1, rrs2) = ListLookup(
    io.inst,
    List(ALU_NONE, ALU_DATA_NONE, ALU_DATA_NONE, 0.U(1.W), IMM_NONE, 0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_NONE, 0.U(1.W), 0.B, 0.B),
    //List(ALU_OP, ALU_A, ALU_B, isdnpc, IMMSEL, RDWEN, memvalid, memwen, memwmask, memsext&bits, isword, rrs1, rrs2)
    // NONE 就直接全0
    // 只用到一个数据就 none + data， op 设为 add
    Array(
      // U-type
      LUI     -> List(ALU_ADD,          ALU_DATA_NONE,  ALU_DATA_IMM,   0.U(1.W), IMM_U,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W),  0.B, 0.B),
      AUIPC   -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   0.U(1.W), IMM_U,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W),  0.B, 0.B),
      // I-type 
      LH      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_16,   0.U(1.W),  1.B, 0.B),
      LHU     -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_NSEXT_16,  0.U(1.W),  1.B, 0.B),
      LB      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_8,    0.U(1.W),  1.B, 0.B),
      LBU     -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_NSEXT_8,   0.U(1.W),  1.B, 0.B),
      LW      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_32,   0.U(1.W),  1.B, 0.B),
      LWU     -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_NSEXT_32,  0.U(1.W),  1.B, 0.B),
      LD      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W),  1.B, 0.B),
       
      ADDI    -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 0.B),
      SLTI    -> List(ALU_SLT,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 0.B),
      SLTIU   -> List(ALU_SLTU,         ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 0.B),
      JALR    -> List(ALU_JALR_OR_JAL,  ALU_DATA_RS1,   ALU_DATA_IMM,   1.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 0.B),
      //rv64: ADDIW , 1.B, 0.B
      ADDIW   -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W), 1.B, 0.B),
      SRAI    -> List(ALU_SRA,          ALU_DATA_RS1,   ALU_DATA_SHAMT, 0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 0.B),
      ANDI    -> List(ALU_AND,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 0.B),
      ORI     -> List(ALU_OR,           ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 0.B),
      XORI    -> List(ALU_XOR,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 0.B),
      SLLI    -> List(ALU_SLL,          ALU_DATA_RS1,   ALU_DATA_SHAMT, 0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 0.B),
      SRLI    -> List(ALU_SRL,          ALU_DATA_RS1,   ALU_DATA_SHAMT, 0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 0.B), 
      SLLIW   -> List(ALU_SLL,          ALU_DATA_RS1,   ALU_DATA_SHAMT, 0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W), 1.B, 0.B),
      SRAIW   -> List(ALU_SRAW,         ALU_DATA_RS1,   ALU_DATA_SHAMT, 0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W), 1.B, 0.B),
      SRLIW   -> List(ALU_SRLW,         ALU_DATA_RS1,   ALU_DATA_SHAMT, 0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W), 1.B, 0.B),

      // J-type
      JAL     -> List(ALU_JALR_OR_JAL,  ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_J,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 0.B, 0.B),

      // S-type
      SB      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_S,    0.U(1.W), 1.U(1.W), 1.U(1.W), 1.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      SH      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_S,    0.U(1.W), 1.U(1.W), 1.U(1.W), 3.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      SW      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_S,    0.U(1.W), 1.U(1.W), 1.U(1.W), 15.U(WMASKLEN.W), MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      SD      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_S,    0.U(1.W), 1.U(1.W), 1.U(1.W), 255.U(WMASKLEN.W),MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      // R-type
      ADD     -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      SUB     -> List(ALU_SUB,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      ADDW    -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W), 1.B, 1.B),
      SUBW    -> List(ALU_SUB,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W), 1.B, 1.B),
      SLL     -> List(ALU_SLL,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      SLLW    -> List(ALU_SLL,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W), 1.B, 1.B),
      AND     -> List(ALU_AND,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      SLTU    -> List(ALU_SLTU,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      OR      -> List(ALU_OR,           ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      XOR     -> List(ALU_XOR,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      MUL     -> List(ALU_MUL,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      MULH    -> List(ALU_MULH,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      MULW    -> List(ALU_MUL,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W), 1.B, 1.B),
      MULHU   -> List(ALU_MULHU,        ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      DIVU    -> List(ALU_DIVU,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      DIV     -> List(ALU_DIV,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      DIVW    -> List(ALU_DIV,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W), 1.B, 1.B),
      DIVUW   -> List(ALU_DIVU,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W), 1.B, 1.B),
      REM     -> List(ALU_REM,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      REMU    -> List(ALU_REMU,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      REMW    -> List(ALU_REMW,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W), 1.B, 1.B),
      REMUW   -> List(ALU_REMUW,        ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W), 1.B, 1.B),
      SLT     -> List(ALU_SLT,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      SRA     -> List(ALU_SRA,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      SRAW    -> List(ALU_SRAW,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W), 1.B, 1.B),
      SRL     -> List(ALU_SRL,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      SRLW    -> List(ALU_SRLW,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W), 1.B, 1.B),


      //B-type
      BEQ     -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_B,    0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      BNE     -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_B,    0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      BGE     -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_B,    0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      BLT     -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_B,    0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      BLTU    -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_B,    0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),
      BGEU    -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_B,    0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 1.B, 1.B),

      EBREAK  -> List(ALU_NONE,         ALU_DATA_NONE,  ALU_DATA_NONE,  0.U(1.W), IMM_NONE, 0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 0.B, 0.B),
      NOP     -> List(ALU_NONE,         ALU_DATA_NONE,  ALU_DATA_NONE,  0.U(1.W), IMM_NONE, 0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W), 0.B, 0.B),
    ),
  )

  // immGen 
  val immi = Cat(Fill(XLEN-12, io.inst(31)), io.inst(31, 20))
  val immj_tmp = Cat(io.inst(31), io.inst(19, 12), io.inst(20), io.inst(30,21), 0.U(1.W))
  val immj = Cat(Fill(XLEN-21, immj_tmp(20)), immj_tmp)
  //printf("immj = %x\n", immj)
  val immu = Cat(Fill(XLEN-32, io.inst(31)), io.inst(31, 12), 0.U(12.W))
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
  io.isword := isword
  io.rrs1 := rrs1
  io.rrs2 := rrs2
  when(io.inst === EBREAK) {
    io.isEbreak := 1.U(1.W)
  }.otherwise {
    io.isEbreak := 0.U(1.W)
  }
  
}
