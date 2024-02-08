import chisel3._
import chisel3.util._
import Configs._
import Instr._
import chisel3.util.experimental.loadMemoryFromFileInline
import chisel3.experimental.BundleLiterals._

class IDRegBundle extends Bundle {
  val valid = Bool()
  val inst  = UInt(32.W)
  val pc    = UInt(XLEN.W)
}

class EXRegBundle extends Bundle {
  val valid = Bool()
  val inst  = UInt(32.W)
  val pc    = UInt(XLEN.W)
  val rs1v  = UInt(XLEN.W)
  val rs2v  = UInt(XLEN.W)
  val rs1   = UInt(RIDXLEN.W)
  val rs2   = UInt(RIDXLEN.W)
  val imm   = UInt(XLEN.W)
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
  val inst = UInt(32.W)
  val pc = UInt(XLEN.W)
  val alures = UInt(XLEN.W)
  val rs2v = UInt(XLEN.W)
  val memvalid = Bool()
  val memwen = Bool()
  val memwmask = UInt(WMASKLEN.W)
  val memsext = UInt(MEM_SEXT_SEL_WIDTH.W)
  val rden = Bool()
  val rd = UInt(RIDXLEN.W)
}

class WBRegBundle extends Bundle {
  val valid = Bool()
  val inst = UInt(32.W)
  val pc = UInt(XLEN.W)
  val alures = UInt(XLEN.W)
  //val sextrdata = UInt(XLEN.W)
  val rden = Bool()
  val rd = UInt(RIDXLEN.W)
  val memvalid = Bool()
}

class Top extends Module {
  val io = IO(new Bundle {
    val inst = Output(UInt(32.W))
    val pc = Output(UInt(XLEN.W))
  })
  
  val IDReg = RegInit(
    (new IDRegBundle).Lit(
      _.valid -> 1.B,
      _.inst -> 0.U,
      _.pc   -> 0.U
    )
  )
  val EXReg = RegInit(
    (new EXRegBundle).Lit(
      _.valid     -> 1.B,
      _.inst      -> 0.U,
      _.pc        -> 0.U,
      _.rs1       -> 0.U,
      _.rs2       -> 0.U,
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
      _.pc        -> 0.U,
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
  val WBReg = RegInit(
    (new WBRegBundle).Lit(
      _.valid     -> 1.B,
      _.inst      -> 0.U,
      _.pc        -> 0.U,
      _.memvalid  -> 0.B,
      _.alures    -> 0.U,
      //_.sextrdata -> 0.U,
      _.rden      -> 0.B,
      _.rd        -> 0.U
    )
  )

  val IDRegen = WireInit(Bool(), 1.B)
  val EXRegen = WireInit(Bool(), 1.B)
  val LSRegen = WireInit(Bool(), 1.B)
  val WBRegen = WireInit(Bool(), 1.B)
  val ifu_dnpc = Wire(UInt(XLEN.W))
  val pcsel = Wire(Bool())
  val InstFetcher = Module(new IFU)
  val PC = RegInit(UInt(XLEN.W), RESET_VECTOR.U)
  val R = Mem(32, UInt(XLEN.W))
  val dataHazard = WireInit(Bool(), 0.B)
  val stall = WireInit(Bool(), 0.B)
  InstFetcher.io.in.valid := PC =/= 0.U
  InstFetcher.io.in.bits.pc := Mux(stall, InstFetcher.io.out.bits.pc(31, 0), PC(31, 0))
  InstFetcher.io.out.ready := IDRegen
  when (stall) {
    PC := PC
  }.elsewhen (pcsel) {
    PC := ifu_dnpc
  } .otherwise {
    // 如果没有指令，那么就不应该更新 PC
    PC := Mux(InstFetcher.io.in.ready, InstFetcher.io.in.bits.pc + 4.U, PC)
  }

  when (IDRegen) {
    IDReg.inst := Mux(InstFetcher.io.out.valid, InstFetcher.io.out.bits.inst, IDReg.inst)
    IDReg.pc := Mux(InstFetcher.io.out.valid, InstFetcher.io.out.bits.pc, IDReg.pc)
    IDReg.valid := Mux(InstFetcher.io.out.valid, (pcsel =/= 1.B) & (RegNext(pcsel, 0.B) =/= 1.B), IDReg.valid)
  } .otherwise {
    IDReg.inst := IDReg.inst
    IDReg.pc := IDReg.pc
    IDReg.valid := IDReg.valid
  }

 
  stall := dataHazard
  def Rread(idx: UInt) = Mux(idx === 0.U, 0.U(XLEN.W), R(idx))
  
  R(0) := 0.U
  val Decoder = Module(new IDU)
  // when(Decoder.io.rd =/= 0.U && scoreboard(Decoder.io.rd) =/= 1.B && Decoder.io.rd_en) {
  //   scoreboard(Decoder.io.rd) := 1.B
  // } .otherwise {
  //   scoreboard(Decoder.io.rd) := scoreboard(Decoder.io.rd)
  // }
  val pc_plus_imm = Decoder.io.pc + Decoder.io.imm
  //printf("decoder pc = %x, imm = %x, pc_plus_imm = %x\n", Decoder.io.pc, Decoder.io.imm, pc_plus_imm)
  val rs2v = Rread(Decoder.io.rs2)
  val rs1v = Rread(Decoder.io.rs1)
  
  val snpc = Decoder.io.pc + 4.U
  
  when(EXRegen) {
    EXReg.inst := Mux(IDReg.valid, IDReg.inst, 0.U)
    EXReg.pc := Mux(IDReg.valid, IDReg.pc, 0.U)
    EXReg.rs1v := rs1v
    EXReg.rs1 := Decoder.io.rs1
    EXReg.rs2 := Decoder.io.rs2
    EXReg.rs2v := rs2v
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

  } .otherwise {
    EXReg.inst := EXReg.inst
    EXReg.pc := EXReg.pc
    EXReg.rs1v := EXReg.rs1v
    EXReg.rs2v := EXReg.rs2v
    EXReg.rs1 := EXReg.rs1 
    EXReg.rs2 := EXReg.rs2
    EXReg.imm := EXReg.imm
    EXReg.aluop := EXReg.aluop
    EXReg.dataAsel := EXReg.dataAsel
    EXReg.dataBsel := EXReg.dataBsel
    EXReg.memvalid := EXReg.memvalid
    EXReg.memwen := EXReg.memwen
    EXReg.memwmask := EXReg.memwmask
    EXReg.memsext := EXReg.memsext
    EXReg.isEbreak := EXReg.isEbreak
    EXReg.isword := EXReg.isword
    EXReg.rden := EXReg.rden
    EXReg.rd := EXReg.rd  
  }

  when (IDReg.valid) {
    Decoder.io.inst := IDReg.inst
    Decoder.io.pc := IDReg.pc
  } .otherwise {
    // 否则按照空指令进行输入
    Decoder.io.inst := 0.U
    Decoder.io.pc := 0.U
  }
  pcsel := Decoder.io.isdnpc

  val ALU = Module(new EXU)
  when(EXReg.valid) {
    ALU.io.inst := EXReg.inst
    ALU.io.pc := EXReg.pc
    ALU.io.alu_op := EXReg.aluop
    ALU.io.asel := EXReg.dataAsel
    ALU.io.bsel := EXReg.dataBsel
    ALU.io.imm := EXReg.imm
    ALU.io.rs1v := EXReg.rs1v
    ALU.io.rs2v := EXReg.rs2v
    ALU.io.isword := EXReg.isword
    when (LSRegen) {
      LSReg.valid := EXReg.valid
      LSReg.inst := EXReg.inst
      LSReg.pc := EXReg.pc
      LSReg.rs2v := EXReg.rs2v
      LSReg.memvalid := EXReg.memvalid
      LSReg.memwen := EXReg.memwen
      LSReg.memwmask := EXReg.memwmask
      LSReg.memsext := EXReg.memsext 
      LSReg.rden := EXReg.rden
      LSReg.rd := EXReg.rd
    }.otherwise {
      LSReg.valid := LSReg.valid
      LSReg.inst := LSReg.inst
      LSReg.pc := LSReg.pc
      LSReg.rs2v := LSReg.rs2v
      LSReg.memvalid := LSReg.memvalid
      LSReg.memwen := LSReg.memwen
      LSReg.memwmask := LSReg.memwmask
      LSReg.memsext := LSReg.memsext 
      LSReg.rden := LSReg.rden
      LSReg.rd := LSReg.rd
    }
  } .otherwise {
    ALU.io.inst := 0.U 
    ALU.io.pc := 0.U 
    ALU.io.alu_op := ALU_NONE
    ALU.io.asel := ALU_DATA_NONE
    ALU.io.bsel := ALU_DATA_NONE
    ALU.io.imm := 0.U
    ALU.io.rs1v := 0.U
    ALU.io.rs2v := 0.U
    ALU.io.isword := 0.B
    LSReg.inst := 0.U
    LSReg.pc := 0.U
    LSReg.rs2v := 0.U
    LSReg.memvalid := 0.B
    LSReg.memwen := 0.B
    LSReg.memwmask := 0.U
    LSReg.memsext := MEM_SEXT_NONE
    LSReg.rden := 0.B
    LSReg.rd := 0.U
  }
  when (LSRegen) {
    LSReg.alures := ALU.io.res
  } .otherwise {
    LSReg.alures := LSReg.alures
  }
  
  val NPC_Mem = Module(new LSU)
  NPC_Mem.io.out.ready := WBRegen
  val rdata7 = NPC_Mem.io.out.bits.rdata(7)
  val rdata15 = NPC_Mem.io.out.bits.rdata(15)
  val rdata31 = NPC_Mem.io.out.bits.rdata(31)
  val alureslow = Wire(UInt(32.W))
  val sextrdata = WireInit(0.U(XLEN.W))
  val memsextreg = RegNext(LSReg.memsext)
  alureslow := LSReg.alures(31, 0)
  when (LSReg.valid) {
    NPC_Mem.io.in.valid := LSReg.memvalid
    NPC_Mem.io.in.bits.wen := LSReg.memwen
    NPC_Mem.io.in.bits.raddr := alureslow
    NPC_Mem.io.in.bits.waddr := alureslow
    NPC_Mem.io.in.bits.wdata := LSReg.rs2v
    NPC_Mem.io.in.bits.wmask := LSReg.memwmask
    
    sextrdata := MuxLookup(memsextreg, NPC_Mem.io.out.bits.rdata)(Seq(
      MEM_NSEXT_8 ->  Cat(Fill(XLEN-8, 0.U), NPC_Mem.io.out.bits.rdata(7, 0)),
      MEM_NSEXT_16->  Cat(Fill(XLEN-16, 0.U), NPC_Mem.io.out.bits.rdata(15, 0)),
      MEM_NSEXT_32->  Cat(Fill(XLEN-32, 0.U), NPC_Mem.io.out.bits.rdata(31, 0)),
      MEM_SEXT_8  ->  Cat(Fill(XLEN-8, rdata7), NPC_Mem.io.out.bits.rdata(7, 0)),
      MEM_SEXT_16 ->  Cat(Fill(XLEN-16, rdata15), NPC_Mem.io.out.bits.rdata(15, 0)),
      MEM_SEXT_32 ->  Cat(Fill(XLEN-32, rdata31), NPC_Mem.io.out.bits.rdata(31, 0)),
    ))
    when (WBRegen) {
      WBReg.inst := LSReg.inst
      WBReg.pc := LSReg.pc
      WBReg.memvalid := LSReg.memvalid
      WBReg.valid := LSReg.valid
      WBReg.alures := LSReg.alures
      
      WBReg.rden := LSReg.rden
      WBReg.rd := LSReg.rd
    } .otherwise {
      WBReg.valid := WBReg.valid
      WBReg.inst := WBReg.inst
      WBReg.pc := WBReg.pc
      WBReg.memvalid := WBReg.memvalid
      WBReg.alures := WBReg.alures
      //WBReg.sextrdata := WBReg.sextrdata
      WBReg.rden := WBReg.rden
      WBReg.rd := WBReg.rd
    }
  } .otherwise {
    NPC_Mem.io.in.valid := 0.B
    NPC_Mem.io.in.bits.wen := 0.B
    NPC_Mem.io.in.bits.raddr := 0.U
    NPC_Mem.io.in.bits.waddr := 0.U
    NPC_Mem.io.in.bits.wdata := 0.U
    NPC_Mem.io.in.bits.wmask := 0.U
    WBReg.inst := 0.U 
    WBReg.valid := 0.B
    WBReg.pc := 0.U
    WBReg.memvalid := 0.B
    WBReg.alures := 0.U
    //WBReg.sextrdata := 0.U
    WBReg.rden := 0.B
    WBReg.rd := 0.U
  }

  val rdv = Wire(UInt(XLEN.W))
  val wbrd = Wire(UInt(RIDXLEN.W))
  val wbrden = Wire(Bool())
  val wbrdmemvalid = Wire(Bool())
  val wbrdsextrdata = Wire(UInt(XLEN.W))
  val wbrdalures = Wire(UInt(XLEN.W))

  
  
  when (WBReg.valid) {
    wbrd := WBReg.rd
    wbrden := WBReg.rden
    wbrdmemvalid := WBReg.memvalid
    // sextrdata 直通
    wbrdsextrdata := sextrdata
    wbrdalures := WBReg.alures
    io.inst := WBReg.inst
    io.pc := WBReg.pc
  } .otherwise {
    wbrd := 0.U
    wbrden := 0.B
    wbrdmemvalid := 0.B
    wbrdsextrdata := 0.U
    wbrdalures := 0.U
    io.inst := 0.U
    io.pc := 0.U
  }

  rdv := Mux(wbrdmemvalid === 1.B, wbrdsextrdata, wbrdalures)
  //printf("wbrdmemvalid: %d, wbrdsextrdata: %x, wbrdalures: %x, wbrden: %d, rdv: %x\n", wbrdmemvalid, wbrdsextrdata, wbrdalures, wbrden, rdv)
  
  //scoreboard(wbrd) := 0.B
  when(wbrd =/= 0.U) {
    R(wbrd) := Mux(wbrden === 0.B, R(wbrd), rdv)
  } .otherwise {
    R(wbrd) := 0.U
  }
  val rs1ren = Decoder.io.rrs1 && Decoder.io.rs1 =/= 0.U && IDReg.valid
  val rs2ren = Decoder.io.rrs2 && Decoder.io.rs2 =/= 0.U && IDReg.valid
  val EX_RS1_Hazard = Decoder.io.rs1 === Mux(EXReg.valid, EXReg.rd, 0.U) && EXReg.rden
  val EX_RS2_Hazard = Decoder.io.rs2 === Mux(EXReg.valid, EXReg.rd, 0.U) && EXReg.rden
  val WB_RS1_Hazard = Decoder.io.rs1 === Mux(WBReg.valid, WBReg.rd, 0.U) && WBReg.rden
  val WB_RS2_Hazard = Decoder.io.rs2 === Mux(WBReg.valid, WBReg.rd, 0.U) && WBReg.rden
  val LS_RS1_Hazard = Decoder.io.rs1 === Mux(LSReg.valid, LSReg.rd, 0.U) && LSReg.rden
  val LS_RS2_Hazard = Decoder.io.rs2 === Mux(LSReg.valid, LSReg.rd, 0.U) && LSReg.rden
  dataHazard := MuxCase(0.U, Array (
    (rs1ren && (EX_RS1_Hazard | LS_RS1_Hazard | WB_RS1_Hazard)) -> 1.B,
    (rs2ren && (EX_RS2_Hazard | LS_RS2_Hazard | WB_RS2_Hazard)) -> 1.B,
  ))
  //printf("IDUpc=%x rs1ren: %d, rs2ren: %d, EX_RS1_Hazard: %d, EX_RS2_Hazard: %d, WB_RS1_Hazard: %d, WB_RS2_Hazard: %d, LS_RS1_Hazard: %d, LS_RS2_Hazard: %d\n", IDReg.pc, rs1ren, rs2ren, EX_RS1_Hazard, EX_RS2_Hazard, WB_RS1_Hazard, WB_RS2_Hazard, LS_RS1_Hazard, LS_RS2_Hazard)
  when (stall) {
    IDRegen := 0.B
    EXReg.valid := 0.B
    ifu_dnpc := "x114514".U
  } .otherwise { 
    IDRegen := 1.B
    EXReg.valid := 1.B
    ifu_dnpc := MuxCase(0.U, Array(
    (Decoder.io.inst === JALR)  -> (rs1v + Decoder.io.imm),
    (Decoder.io.inst === JAL)   -> (pc_plus_imm),
    (Decoder.io.inst === BEQ)   -> Mux(rs1v === rs2v, pc_plus_imm, snpc),
    (Decoder.io.inst === BNE)   -> Mux(rs1v === rs2v, snpc, pc_plus_imm),
    (Decoder.io.inst === BGE)   -> Mux(rs1v.asSInt >= rs2v.asSInt, pc_plus_imm, snpc),
    (Decoder.io.inst === BGEU)  -> Mux(rs1v >= rs2v, pc_plus_imm, snpc),
    (Decoder.io.inst === BLT)   -> Mux(rs1v.asSInt < rs2v.asSInt, pc_plus_imm, snpc),
    (Decoder.io.inst === BLTU)  -> Mux(rs1v < rs2v, pc_plus_imm, snpc)
  ))
  }
  
  val Ebreak = Module(new DPIC_EBREAK)
  Ebreak.io.isEbreak := EXReg.isEbreak
  Ebreak.io.clk := clock
}

