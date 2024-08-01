import chisel3._ 

object Configs {
  val XLEN                  = 32
  val WMASKLEN              = 4
  val RESET_VECTOR          = "x30000000"
  val RIDXLEN               = 5
  val CSRIDXLEN             = 12

  val CLINT_BASE            = 0x0200_0000L
  val CLINT_SIZE            = 0x0001_0000L
  val MROM_BASE             = 0x2000_0000L
  val MROM_SIZE             = 0x0000_1000L
  val SRAM_BASE             = 0x0f00_0000L
  val SRAM_SIZE             = 0x0000_2000L
  val PSRAM_BASE            = 0x8000_0000L
  val PSRAM_SIZE            = 0x2000_0000L
  val SDRAM_BASE            = 0xa000_0000L
  val SDRAM_SIZE            = 0x2000_0000L
  // val MEM_BASE              = 0x80000000L
  // val MEM_SIZE              = 0x8000000L
  val FLASH_BASE            = 0x30000000L
  val FLASH_SIZE            = 0x10000000L
  val UART_BASE             = 0x10000000L
  val UART_SIZE             = 0x7L           // 一共 7 个 8 字节的 UART16550 寄存器
  val RTC_ADDR              = CLINT_BASE
  val GPIO_BASE             = 0x1000_2000L
  val GPIO_SIZE             = 0x1000_200fL

// #define CSR_MTVEC   0x305
// #define CSR_MEPC    0x341
// #define CSR_MCAUSE  0x342
  val CSR_MTVEC             = 0x305
  val CSR_MEPC              = 0x341
  val CSR_MCAUSE            = 0x342
  val CSR_MSTATUS           = 0x300
  val CSR_MVENDORID         = 0xF11
  val CSR_MARCHID           = 0xF12

  val ALU_DATASEL_WIDTH     = 3
  val IMM_SEL_WIDTH         = 6
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
  val ALU_MULHU             = 19.U(ALUCtrlWidth.W)
  val ALU_SRAW              = 20.U(ALUCtrlWidth.W)
  val ALU_SRLW              = 21.U(ALUCtrlWidth.W)
  val ALU_REMW              = 22.U(ALUCtrlWidth.W)
  val ALU_REMUW             = 23.U(ALUCtrlWidth.W)

  // ALU 的数据来源:
  val ALU_DATA_NONE         = 0.U(ALU_DATASEL_WIDTH.W)
  val ALU_DATA_RS1          = 1.U(ALU_DATASEL_WIDTH.W)
  val ALU_DATA_RS2          = 2.U(ALU_DATASEL_WIDTH.W)
  val ALU_DATA_PC           = 3.U(ALU_DATASEL_WIDTH.W)
  val ALU_DATA_IMM          = 4.U(ALU_DATASEL_WIDTH.W)
  val ALU_DATA_SHAMT        = 5.U(ALU_DATASEL_WIDTH.W)
  val ALU_DATA_CSR          = 6.U(ALU_DATASEL_WIDTH.W)
  

  // IMMSEL
  val IMM_NONE              = 0.U(IMM_SEL_WIDTH.W)
  
  val IMM_I                 = 1.U(IMM_SEL_WIDTH.W)
  val IMM_J                 = 2.U(IMM_SEL_WIDTH.W)
  val IMM_U                 = 3.U(IMM_SEL_WIDTH.W)
  val IMM_S                 = 4.U(IMM_SEL_WIDTH.W)
  val IMM_B                 = 5.U(IMM_SEL_WIDTH.W)
}

