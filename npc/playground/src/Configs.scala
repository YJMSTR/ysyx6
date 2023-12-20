import chisel3._ 

object Configs {
  val XLEN                  = 32
  val WMASKLEN              = 8
  val RESET_VECTOR          = "x80000000"
  val RIDXLEN               = 5
  
  val ALU_DATASEL_WIDTH     = 3
  val IMM_SEL_WIDTH         = 3
  // none 8 16 32 一共四种
  val MEM_SEXT_SEL_WIDTH    = 3
  
  val MEM_NSEXT_8           = 0.U(MEM_SEXT_SEL_WIDTH.W)
  val MEM_NSEXT_16          = 1.U(MEM_SEXT_SEL_WIDTH.W)
  val MEM_NSEXT_32          = 2.U(MEM_SEXT_SEL_WIDTH.W)
  val MEM_SEXT_8            = 3.U(MEM_SEXT_SEL_WIDTH.W)
  val MEM_SEXT_16           = 4.U(MEM_SEXT_SEL_WIDTH.W)
  val MEM_SEXT_32           = 5.U(MEM_SEXT_SEL_WIDTH.W)
  val MEM_SEXT_NONE         = 6.U(MEM_SEXT_SEL_WIDTH.W)

  // ALU_OP
  val ALUCtrlWidth          = 5
  val ALU_NONE              = 0.U(ALUCtrlWidth.W) 
  val ALU_ADD               = 1.U(ALUCtrlWidth.W) 
  val ALU_EBREAK            = 2.U(ALUCtrlWidth.W)
  val ALU_JALR_OR_JAL       = 3.U(ALUCtrlWidth.W)
  val ALU_SLT               = 4.U(ALUCtrlWidth.W)
  val ALU_SLTU              = 5.U(ALUCtrlWidth.W)
  val ALU_SRA               = 6.U(ALUCtrlWidth.W)
  val ALU_SRL               = 7.U(ALUCtrlWidth.W)
  val ALU_SLL               = 8.U(ALUCtrlWidth.W)
  val ALU_AND               = 9.U(ALUCtrlWidth.W)
  val ALU_OR                = 10.U(ALUCtrlWidth.W)
  val ALU_XOR               = 11.U(ALUCtrlWidth.W)
  val ALU_SUB               = 12.U(ALUCtrlWidth.W)
  val ALU_MUL               = 13.U(ALUCtrlWidth.W)
  val ALU_MULH              = 14.U(ALUCtrlWidth.W)
  val ALU_DIV               = 15.U(ALUCtrlWidth.W)
  val ALU_DIVU              = 16.U(ALUCtrlWidth.W)
  val ALU_REMU              = 17.U(ALUCtrlWidth.W)
  val ALU_REM               = 18.U(ALUCtrlWidth.W)

  // ALU 的数据来源:
  val ALU_DATA_NONE         = 0.U(ALUCtrlWidth.W)
  val ALU_DATA_RS1          = 1.U(ALUCtrlWidth.W)
  val ALU_DATA_RS2          = 2.U(ALUCtrlWidth.W)
  val ALU_DATA_PC           = 3.U(ALUCtrlWidth.W)
  val ALU_DATA_IMM          = 4.U(ALUCtrlWidth.W)
  val ALU_DATA_SHAMT        = 5.U(ALUCtrlWidth.W)
  

  // IMMSEL
  val IMM_NONE              = 0.U(IMM_SEL_WIDTH.W)
  
  val IMM_I                 = 1.U(IMM_SEL_WIDTH.W)
  val IMM_J                 = 2.U(IMM_SEL_WIDTH.W)
  val IMM_U                 = 3.U(IMM_SEL_WIDTH.W)
  val IMM_S                 = 4.U(IMM_SEL_WIDTH.W)
  val IMM_B                 = 5.U(IMM_SEL_WIDTH.W)
}

