import chisel3._
import Configs._ 
import Instr._ 
import chisel3.util._

// import chisel3.util.experimental.loadMemoryFromFileInline



class IDU(regFileIO: RegFileIO) extends Module {
  val io = IO(new Bundle {
    // IFU 传来的输入
    val in = Flipped(Decoupled(new IFU_out))
    // IDU 传给 EXU 的输出
    val out = Decoupled(new IDU_out)
    // 不直接传给 EXU 的信号
    // 在译码阶段预先计算出当前指令是否为跳转指令，以及指令的跳转地址 dnpc
    // 并将 dnpc 传回 IFU，使得当前正在译码的指令的下一条指令变为 dnpc 对应的指令 
    // 寄存器堆要单独作为一个模块放外面，计算 dnpc 要读取寄存器，也放外面
    val isdnpc = Output(Bool())
    val rrs1 = Output(Bool())
    val rrs2 = Output(Bool())
  })
  
  io.out.bits.rs1 := io.inst(19, 15)
  io.out.bits.rs2 := io.inst(24, 20)
  io.out.bits.rd  := io.inst(11, 7) 
  // isword (RV64Only)：判断是否为字运算指令（例如addiw),如果是则为1
  val List(alu_op, alu_sel_a, alu_sel_b, isdnpc, immsel, rden, memvalid, memwen, memwmask, memsext, isword, rrs1, rrs2) = ListLookup(
    io.in.inst,
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
  val immi = Cat(Fill(XLEN-12, io.in.bits.inst(31)), io.in.bits.inst(31, 20))
  val immj_tmp = Cat(io.in.bits.inst(31), io.in.bits.inst(19, 12), io.in.bits.inst(20), io.in.bits.inst(30,21), 0.U(1.W))
  val immj = Cat(Fill(XLEN-21, immj_tmp(20)), immj_tmp)
  //printf("immj = %x\n", immj)
  val immu = Cat(Fill(XLEN-32, io.in.bits.inst(31)), io.in.bits.inst(31, 12), 0.U(12.W))
  val imms_tmp = Cat(io.in.bits.inst(31, 25), io.in.bits.inst(11, 7))
  val imms = Cat(Fill(XLEN-12, imms_tmp(11)), imms_tmp)
  val immb_tmp = Cat(io.in.bits.inst(31), io.in.bits.inst(7), io.in.bits.inst(30, 25), io.in.bits.inst(11, 8), 0.U(1.W))
  val immb = Cat(Fill(XLEN-13, immb_tmp(12)), immb_tmp)
  
  io.out.imm := MuxLookup(immsel, 0.U)(Seq(
    IMM_I->immi, 
    IMM_J->immj, 
    IMM_U->immu,
    IMM_S->imms,
    IMM_B->immb
  ))

  io.isdnpc := isdnpc

  io.out.bits.alu_op := alu_op 
  io.out.bits.alu_sel_a := alu_sel_a
  io.out.bits.alu_sel_b := alu_sel_b
  io.out.bits.rd_en := rden
  io.out.bits.memvalid := memvalid
  io.out.bits.memwen := memwen
  io.out.bits.memwmask := memwmask 
  io.out.bits.memsext := memsext
  io.out.bits.isword := isword
  
  io.rrs1 := rrs1
  io.rrs2 := rrs2

  when(io.in.bits.inst === EBREAK) {
    io.out.bits.isEbreak := 1.U(1.W)
  }.otherwise {
    io.out.bits.isEbreak := 0.U(1.W)
  }
  
}
