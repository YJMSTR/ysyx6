import chisel3._ 

object Configs {
  val XLEN                  = 32
  val RESET_VECTOR          = "x80000000"
  val RIDXLEN               = 5
  val ALUCtrlWidth          = 4
  val ALU_DATASEL_WIDTH     = 3
  val IMM_SEL_WIDTH         = 3
  // ALU 目前（dummy）要实现：加（addi，auipc，lui）以及空
  // ALU_OP
  val ALU_NONE              = 0.U(ALUCtrlWidth.W) 
  val ALU_ADD               = 1.U(ALUCtrlWidth.W) 
  val ALU_EBREAK            = 2.U(ALUCtrlWidth.W)
  val ALU_JALR_OR_JAL       = 3.U(ALUCtrlWidth.W)


  // ALU 的数据来源:
  val ALU_DATA_NONE         = 0.U(ALUCtrlWidth.W)
  val ALU_DATA_RS1          = 1.U(ALUCtrlWidth.W)
  val ALU_DATA_RS2          = 2.U(ALUCtrlWidth.W)
  val ALU_DATA_PC           = 3.U(ALUCtrlWidth.W)
  val ALU_DATA_IMM         = 4.U(ALUCtrlWidth.W)
  

  // IMMSEL
  val IMM_NONE              = 0.U(IMM_SEL_WIDTH.W)
  
  val IMM_I                 = 1.U(IMM_SEL_WIDTH.W)
  val IMM_J                 = 2.U(IMM_SEL_WIDTH.W)
  val IMM_U                 = 3.U(IMM_SEL_WIDTH.W)
  val IMM_S                 = 4.U(IMM_SEL_WIDTH.W)
}

