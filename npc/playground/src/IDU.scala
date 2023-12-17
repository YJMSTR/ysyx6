import chisel3._
import Configs._ 
import Instr._ 
import chisel3.util._
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
    // 目前暂时不用根据指令读取内存
  })

  io.rs1 := io.inst(19, 15)
  io.rs2 := io.inst(24, 20)
  io.rd  := io.inst(11, 7) 

  val List(alu_op, alu_sel_a, alu_sel_b, isdnpc, immsel, rden) = ListLookup(
    io.inst,
    List(ALU_NONE, ALU_DATA_NONE, ALU_DATA_NONE, 0.U(1.W), IMM_NONE, 0.U(1.W)),
    //List(ALU_OP, ALU_A, ALU_B, isdnpc, IMMSEL, RDEN)
    // NONE 就直接全0
    // 只用到一个数据就 none + data， op 设为 add
    Array(
      ADDI    -> List(ALU_ADD,          ALU_DATA_RS1,   ALU_DATA_IMM,   0.U(1.W), IMM_I,    1.U(1.W)),
      EBREAK  -> List(ALU_NONE,         ALU_DATA_NONE,  ALU_DATA_NONE,  0.U(1.W), IMM_NONE, 0.U(1.W)),
      LUI     -> List(ALU_ADD,          ALU_DATA_NONE,  ALU_DATA_IMM,   0.U(1.W), IMM_U,    1.U(1.W)),
      AUIPC   -> List(ALU_ADD,          ALU_DATA_PC,    ALU_DATA_IMM,   0.U(1.W), IMM_U,    1.U(1.W)),
      JALR    -> List(ALU_JALR_OR_JAL,  ALU_DATA_RS1,   ALU_DATA_IMM,   1.U(1.W), IMM_I,    1.U(1.W)),
      JAL     -> List(ALU_JALR_OR_JAL,  ALU_DATA_PC,    ALU_DATA_IMM,   1.U(1.W), IMM_J,    1.U(1.W)),
    ),
  )

  // immGen 
  val immi = io.inst(31, 20).asSInt
  val immj = Cat(io.inst(31), io.inst(19, 12), io.inst(20), io.inst(30,21), 0.U(1.W)).asSInt
  val immu = Cat(io.inst(31, 12), 0.U(12.W)).asSInt
  
  io.imm := MuxLookup(immsel, 0.S,
    Seq(IMM_I->immi, IMM_J->immj, IMM_U->immu)).asUInt

  io.alu_op := alu_op 
  io.alu_sel_a := alu_sel_a
  io.alu_sel_b := alu_sel_b
  io.isdnpc := isdnpc
  io.rd_en := rden
  when(io.inst === EBREAK) {
    io.isEbreak := 1.U(1.W)
  }.otherwise {
    io.isEbreak := 0.U(1.W)
  }
}
