import chisel3._
import Configs._ 
import Instr._ 
import chisel3.util._

// import chisel3.util.experimental.loadMemoryFromFileInline

class IDU() extends Module {
  val io = IO(new Bundle {
    // RV32 和 64 的指令都是 32 位长，除非是 C 扩展
    val inst = Input(UInt(32.W))
    val pc = Input(UInt(XLEN.W))
    // 这两个信号拉到顶，去访问寄存器堆
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
  })
  
  io.rs1 := io.inst(19, 15)
  io.rs2 := io.inst(24, 20)
  io.rd  := io.inst(11, 7) 
  // isword (RV64Only)：判断是否为字运算指令（例如addiw),如果是则为1
  val List(alu_op, alu_sel_a, alu_sel_b, isdnpc, immsel, rden, memvalid, memwen, memwmask, memsext, isword) = ListLookup(
    io.inst,
    List(ALU_NONE, ALU_DATA_NONE, ALU_DATA_NONE, 0.U(1.W), IMM_NONE, 0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W), MEM_SEXT_NONE, 0.U(1.W)),
    //List(ALU_OP, ALU_A, ALU_B, isdnpc, IMMSEL, RDWEN, memvalid, memwen, memwmask, memsext&bits, isword)
    // NONE 就直接全0
    // 只用到一个数据就 none + data， op 设为 add
    Array(
      // U-type
      LUI     -> List(ALU_ADD,          ALU_DATA_NONE,  ALU_DATA_IMM,   0.U(1.W), IMM_U,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      AUIPC   -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   0.U(1.W), IMM_U,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      // I-type 
      LH      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_16,   0.U(1.W)),
      LHU     -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_NSEXT_16,  0.U(1.W)),
      LB      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_8,    0.U(1.W)),
      LBU     -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_NSEXT_8,   0.U(1.W)),
      LW      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_32,   0.U(1.W)),
      LWU     -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_NSEXT_32,  0.U(1.W)),
      LD      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 1.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
       
      ADDI    -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      SLTI    -> List(ALU_SLT,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      SLTIU   -> List(ALU_SLTU,         ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      JALR    -> List(ALU_JALR_OR_JAL,  ALU_DATA_RS1,   ALU_DATA_IMM,   1.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      //rv64: ADDIW 
      ADDIW   -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W)),
      SRAI    -> List(ALU_SRA,          ALU_DATA_RS1,   ALU_DATA_SHAMT, 0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      ANDI    -> List(ALU_AND,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      ORI     -> List(ALU_OR,           ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      XORI    -> List(ALU_XOR,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      SLLI    -> List(ALU_SLL,          ALU_DATA_RS1,   ALU_DATA_SHAMT, 0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      SRLI    -> List(ALU_SRL,          ALU_DATA_RS1,   ALU_DATA_SHAMT, 0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)), 
      SLLIW   -> List(ALU_SLL,          ALU_DATA_RS1,   ALU_DATA_SHAMT, 0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W)),
      SRAIW   -> List(ALU_SRAW,         ALU_DATA_RS1,   ALU_DATA_SHAMT, 0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W)),
      SRLIW   -> List(ALU_SRLW,         ALU_DATA_RS1,   ALU_DATA_SHAMT, 0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W)),

      // J-type
      JAL     -> List(ALU_JALR_OR_JAL,  ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_J,    1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),

      // S-type
      SB      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_S,    0.U(1.W), 1.U(1.W), 1.U(1.W), 1.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      SH      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_S,    0.U(1.W), 1.U(1.W), 1.U(1.W), 3.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      SW      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_S,    0.U(1.W), 1.U(1.W), 1.U(1.W), 15.U(WMASKLEN.W), MEM_SEXT_NONE, 0.U(1.W)),
      SD      -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_S,    0.U(1.W), 1.U(1.W), 1.U(1.W), 255.U(WMASKLEN.W),MEM_SEXT_NONE, 0.U(1.W)),
      // R-type
      ADD     -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      SUB     -> List(ALU_SUB,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      ADDW    -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W)),
      SUBW    -> List(ALU_SUB,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W)),
      SLL     -> List(ALU_SLL,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      SLLW    -> List(ALU_SLL,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W)),
      AND     -> List(ALU_AND,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      SLTU    -> List(ALU_SLTU,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      OR      -> List(ALU_OR,           ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      XOR     -> List(ALU_XOR,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      MUL     -> List(ALU_MUL,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      MULH    -> List(ALU_MULH,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      MULW    -> List(ALU_MUL,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W)),
      MULHU   -> List(ALU_MULHU,        ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      DIVU    -> List(ALU_DIVU,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      DIV     -> List(ALU_DIV,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      DIVW    -> List(ALU_DIV,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W)),
      DIVUW   -> List(ALU_DIVU,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W)),
      REM     -> List(ALU_REM,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      REMU    -> List(ALU_REMU,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      REMW    -> List(ALU_REMW,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W)),
      REMUW   -> List(ALU_REMUW,        ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W)),
      SLT     -> List(ALU_SLT,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      SRA     -> List(ALU_SRA,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      SRAW    -> List(ALU_SRAW,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W)),
      SRL     -> List(ALU_SRL,          ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      SRLW    -> List(ALU_SRLW,         ALU_DATA_RS1,   ALU_DATA_RS2,   0.U(1.W), IMM_NONE, 1.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 1.U(1.W)),


      //B-type
      BEQ     -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_B,    0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      BNE     -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_B,    0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      BGE     -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_B,    0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      BLT     -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_B,    0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      BLTU    -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_B,    0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
      BGEU    -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_B,    0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),

      EBREAK  -> List(ALU_NONE,         ALU_DATA_NONE,  ALU_DATA_NONE,  0.U(1.W), IMM_NONE, 0.U(1.W), 0.U(1.W), 0.U(1.W), 0.U(WMASKLEN.W),  MEM_SEXT_NONE, 0.U(1.W)),
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
  when(io.inst === EBREAK) {
    io.isEbreak := 1.U(1.W)
  }.otherwise {
    io.isEbreak := 0.U(1.W)
  }
  
}
