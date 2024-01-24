import chisel3._
import chisel3.util._
import Configs._
import Instr._
import chisel3.util.experimental.loadMemoryFromFileInline
import chisel3.experimental.BundleLiterals._

class IDRegBundle extends Bundle {
  val valid = Bool()
  //val en    = Bool()
  val inst  = UInt(32.W)
  val pc    = UInt(XLEN.W)
}

class EXRegBundle extends Bundle {
  val valid = Bool()
  //val en    = Bool()
  // debug
  val inst  = UInt(32.W)
  val pc    = UInt(XLEN.W)
  // data
  val rs1v  = UInt(XLEN.W)
  val rs2v  = UInt(XLEN.W)
  val imm   = UInt(XLEN.W)
  // ctrl
  val dataAsel  = UInt(ALU_DATASEL_WIDTH.W)
  val dataBsel  = UInt(ALU_DATASEL_WIDTH.W)
  val aluop     = UInt(ALUCtrlWidth.W)
  val memvalid  = Bool()
  val memwen    = Bool()
  val memwmask  = UInt(WMASKLEN.W)
  val memsext   = UInt(MEM_SEXT_SEL_WIDTH.W)
  val isdnpc    = Bool()
  val isEbreak  = Bool()
  val isword    = Bool()
  val rden      = Bool()
  val rd        = UInt(RIDXLEN.W)
}

class LSRegBundle extends Bundle {
  val valid = Bool()
  //val en    = Bool()
  // debug
  val inst = UInt(32.W)
  val pc = UInt(XLEN.W)
  // data 
  val alures = UInt(XLEN.W)
  val rs2v = UInt(XLEN.W)
  // ctrl
  val memvalid = Bool()
  val memwen = Bool()
  val memwmask = UInt(WMASKLEN.W)
  val memsext = UInt(MEM_SEXT_SEL_WIDTH.W)
  val rden = Bool()
  val rd = UInt(RIDXLEN.W)
}

class WBRegBundle extends Bundle {
  val valid = Bool()
  //val en    = Bool()
  // debug 
  val inst = UInt(32.W)
  val pc = UInt(XLEN.W)
  // data
  val alures = UInt(XLEN.W)
  val sextrdata = UInt(XLEN.W)
  // ctrl 
  val rden = Bool()
  val rd = UInt(RIDXLEN.W)
  val memvalid = Bool()
}

class Top extends Module {
  val io = IO(new Bundle {
    val inst = Output(UInt(32.W))
    val pc = Output(UInt(XLEN.W))
  })
  
  // ID Reg
  val IDReg = RegInit(
    (new IDRegBundle).Lit(
      //_.en    = 1.B,
      _.valid -> 1.B,
      _.inst -> 0.U,
      _.pc   -> "x7ffffffc".U
    )
  )
  // EX Reg
  val EXReg = RegInit(
    (new EXRegBundle).Lit(
      _.valid     -> 1.B,
      //_.en        = 1.B,
      _.inst      -> 0.U,
      _.pc        -> RESET_VECTOR.U,
      _.rs1v      -> 0.U,
      _.rs2v      -> 0.U,
      _.imm       -> 0.U,
      _.dataAsel  -> ALU_DATA_NONE,
      _.dataBsel  -> ALU_DATA_NONE,
      _.aluop     -> ALU_NONE,
      _.memvalid  -> 0.B,
      _.memwen    -> 0.B,
      _.memwmask  -> 0.U,
      _.memsext   -> MEM_SEXT_NONE,
      _.isdnpc    -> 0.B,
      _.isEbreak  -> 0.B,
      _.isword    -> 0.B,
      _.rden      -> 0.B,
      _.rd        -> 0.U
    )
  )
  val LSReg = RegInit(
    (new LSRegBundle).Lit(
      _.valid     -> 1.B,
      _.inst      -> 0.U,
      _.pc        -> RESET_VECTOR.U,
      _.alures    -> 0.U,
      _.rs2v      -> 0.U,
      _.memvalid  -> 0.B,
      _.memwen    -> 0.B,
      _.memwmask  -> 0.U,
      _.memsext   -> MEM_SEXT_NONE,
      _.rden      -> 0.B,
      _.rd        -> 0.U
    )
  )
  // WB Reg
  val WBReg = RegInit(
    (new WBRegBundle).Lit(
      _.valid     -> 1.B,
      //_.en        = 1.B,
      _.inst      -> 0.U,
      _.pc        -> RESET_VECTOR.U,
      _.memvalid  -> 0.B,
      _.alures    -> 0.U,
      _.sextrdata -> 0.U,
      _.rden      -> 0.B,
      _.rd        -> 0.U
    )
  )

  // 根据 PC 取出 inst 之前是在 C++ 里完成的
  // 现在需要额外调用一次 pmem_read() 来实现
  // PC 模块
  // val PC = RegInit(RESET_VECTOR.U(XLEN.W))
  val dnpc = Wire(UInt(XLEN.W))
  val pcsel = Wire(UInt(1.W))
  // val wirepc = Wire(UInt(XLEN.W))
  // val wireinst = Wire(UInt(32.W))
  // wirepc := PC
  // io.pc := PC
  // val npc = Wire(UInt(XLEN.W))
  // npc := 
  val InstFetcher = Module(new DPIC_IFU)
  InstFetcher.io.pc := Mux(pcsel === 1.U, dnpc, IDReg.pc + 4.U)
  IDReg.pc := InstFetcher.io.pc
  //InstFetcher.io.clk := clock
  // wireinst := Mux(reset.asBool, 0.U, InstFetcher.io.inst)
  InstFetcher.io.valid := Mux(reset.asBool, 0.U, 1.U)
  IDReg.inst := InstFetcher.io.inst
  
  io.inst := InstFetcher.io.inst
  io.pc := InstFetcher.io.pc
  // 译码模块
  // 寄存器
  val R = Mem(32, UInt(XLEN.W))
  def Rread(idx: UInt) = Mux(idx === 0.U, 0.U(XLEN.W), R(idx))
  //val rs1v = Wire(UInt(XLEN.W))
  //val rs2v = Wire(UInt(XLEN.W))
  //val rs1 = Wire(UInt(RIDXLEN.W))
  //val rs2 = Wire(UInt(RIDXLEN.W))
  //val rd = Wire(UInt(RIDXLEN.W))
  //val rd_en = Wire(UInt(1.W))
  
  R(0) := 0.U
  val Decoder = Module(new IDU)
  val pc_plus_imm = Decoder.io.pc + Decoder.io.imm
  val rs1v = Rread(Decoder.io.rs1)
  val rs2v = Rread(Decoder.io.rs2)
  val snpc = Decoder.io.pc + 4.U
  dnpc := MuxCase(0.U, Array(
    (Decoder.io.inst === JALR)  -> (rs1v + Decoder.io.imm),
    (Decoder.io.inst === JAL)   -> (pc_plus_imm),
    (Decoder.io.inst === BEQ)   -> Mux(rs1v === rs2v, pc_plus_imm, snpc),
    (Decoder.io.inst === BNE)   -> Mux(rs1v === rs2v, snpc, pc_plus_imm),
    (Decoder.io.inst === BGE)   -> Mux(rs1v.asSInt >= rs2v.asSInt, pc_plus_imm, snpc),
    (Decoder.io.inst === BGEU)  -> Mux(rs1v >= rs2v, pc_plus_imm, snpc),
    (Decoder.io.inst === BLT)   -> Mux(rs1v.asSInt < rs2v.asSInt, pc_plus_imm, snpc),
    (Decoder.io.inst === BLTU)  -> Mux(rs1v < rs2v, pc_plus_imm, snpc)
  ))
  EXReg.inst := IDReg.inst
  EXReg.rs1v := Rread(Decoder.io.rs1)
  EXReg.rs2v := Rread(Decoder.io.rs2)
  EXReg.imm  := Decoder.io.imm

  EXReg.aluop := Decoder.io.alu_op
  EXReg.dataAsel := Decoder.io.alu_sel_a
  EXReg.dataBsel := Decoder.io.alu_sel_b

  EXReg.memvalid := Decoder.io.memvalid
  EXReg.memwen   := Decoder.io.memwen
  EXReg.memwmask := Decoder.io.memwmask 
  EXReg.memsext  := Decoder.io.memsext

  EXReg.isEbreak := Decoder.io.isEbreak
  EXReg.isword := Decoder.io.isword
  EXReg.rden := Decoder.io.rd_en
  EXReg.rd := Decoder.io.rd

  EXReg.inst := IDReg.inst
  EXReg.pc := IDReg.pc
  Decoder.io.inst := IDReg.inst
  Decoder.io.pc := IDReg.pc
  pcsel := Decoder.io.isdnpc

  // rs1 := Decoder.io.rs1
  // rs2 := Decoder.io.rs2 
  // pcsel := Decoder.io.isdnpc
  // rd := Decoder.io.rd 
  // memvalid := Decoder.io.memvalid
  // memwen := Decoder.io.memwen
  // memwmask := Decoder.io.memwmask
  // memsext := Decoder.io.memsext
  // memwdata := MuxLookup(memwmask, rs2v)(Seq(
  //   1.U  -> rs2v(7, 0),
  //   3.U  -> rs2v(15, 0),
  //   15.U -> rs2v(31, 0),
  //   255.U-> rs2v(63, 0)
  // ))
  // val isword = Decoder.io.isword




  // 执行模块
  val ALU = Module(new EXU)
  ALU.io.inst := EXReg.inst
  ALU.io.pc := EXReg.pc
  ALU.io.alu_op := EXReg.aluop
  ALU.io.asel := EXReg.dataAsel
  ALU.io.bsel := EXReg.dataBsel
  ALU.io.imm := EXReg.imm
  ALU.io.rs1v := EXReg.rs1v
  ALU.io.rs2v := EXReg.rs2v
  ALU.io.isword := EXReg.isword
  LSReg.inst := EXReg.inst
  LSReg.pc := EXReg.pc
  LSReg.alures := ALU.io.res
  LSReg.rs2v := EXReg.rs2v
  LSReg.memvalid := EXReg.memvalid
  LSReg.memwen := EXReg.memwen
  LSReg.memwmask := EXReg.memwmask
  LSReg.memsext := EXReg.memsext 
  LSReg.rden := EXReg.rden
  LSReg.rd := EXReg.rd
  // 访存模块
  // 译码器需要判断当前指令是否为访存，生成对应的 valid 和 wen 信号
  val NPC_Mem = Module(new DPIC_MEM)
  // val memvalid = Wire(UInt(1.W))
  // val memwen = Wire(UInt(1.W))
  // val memrdata = Wire(UInt(XLEN.W)) 
  // val memsext = Wire(UInt(MEM_SEXT_SEL_WIDTH.W))
  // val memraddr = Wire(UInt(XLEN.W))
  // val memwaddr = Wire(UInt(XLEN.W))
  // val memwdata = Wire(UInt(XLEN.W))
  
  // val memwmask = Wire(UInt(WMASKLEN.W))
  NPC_Mem.io.valid := LSReg.memvalid
  NPC_Mem.io.wen := LSReg.memwen
  NPC_Mem.io.raddr := LSReg.alures
  NPC_Mem.io.waddr := LSReg.alures
  NPC_Mem.io.wdata := LSReg.rs2v
  NPC_Mem.io.wmask := LSReg.memwmask
  NPC_Mem.io.clk := clock

  WBReg.inst := LSReg.inst
  WBReg.pc := LSReg.pc
  WBReg.memvalid := LSReg.memvalid
  WBReg.alures := LSReg.alures
  val rdata7 = NPC_Mem.io.rdata(7)
  val rdata15 = NPC_Mem.io.rdata(15)
  val rdata31 = NPC_Mem.io.rdata(31)
  WBReg.sextrdata := MuxLookup(LSReg.memsext, NPC_Mem.io.rdata)(Seq(
    MEM_NSEXT_8 ->  Cat(Fill(XLEN-8, 0.U), NPC_Mem.io.rdata(7, 0)),
    MEM_NSEXT_16->  Cat(Fill(XLEN-16, 0.U), NPC_Mem.io.rdata(15, 0)),
    MEM_NSEXT_32->  Cat(Fill(XLEN-32, 0.U), NPC_Mem.io.rdata(31, 0)),
    MEM_SEXT_8  ->  Cat(Fill(XLEN-8, rdata7), NPC_Mem.io.rdata(7, 0)),
    MEM_SEXT_16 ->  Cat(Fill(XLEN-16, rdata15), NPC_Mem.io.rdata(15, 0)),
    //rv64 only: 
    MEM_SEXT_32 ->  Cat(Fill(XLEN-32, rdata31), NPC_Mem.io.rdata(31, 0)),
  ))
  WBReg.rden := LSReg.rden
  WBReg.rd := LSReg.rd

  // memraddr := ALU.io.res
  // memwaddr := ALU.io.res


  // 写回模块
  val rdv = Wire(UInt(XLEN.W))
  R(WBReg.rd) := Mux(WBReg.rden === 0.B, R(WBReg.rd), rdv)
  rdv := Mux(WBReg.memvalid === 1.U, WBReg.sextrdata, WBReg.alures)
  
  // Ebreak 要放在EX阶段执行，防止前面有指令未执行完成就退出了
  val Ebreak = Module(new DPIC_EBREAK)
  Ebreak.io.isEbreak := EXReg.isEbreak
  Ebreak.io.clk := clock
}

