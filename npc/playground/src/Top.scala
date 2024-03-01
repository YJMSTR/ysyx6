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
  val rden = Bool()
  val rd = UInt(RIDXLEN.W)
  val memvalid = Bool()
  val memsext = UInt(MEM_SEXT_SEL_WIDTH.W)
  val rdata = UInt(XLEN.W)
}

class ISRegBundle extends Bundle {
  val valid = Bool()
  val inst = UInt(32.W)
  val pc = UInt(XLEN.W)
}

class Top extends Module {
  val io = IO(new Bundle {
    val inst = Output(UInt(32.W))
    val pc = Output(UInt(XLEN.W))
    val npc = Output(UInt(XLEN.W))
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
      _.rd        -> 0.U,
      _.memsext   -> MEM_SEXT_NONE,
      _.rdata     -> 0.U,
    )
  )

  val ISReg = RegInit(
    (new ISRegBundle).Lit(
      _.valid -> 1.B,
      _.inst -> 0.U,
      _.pc -> 0.U
    )
  )
  val IDRegen = WireInit(Bool(), 1.B)
  val EXRegen = WireInit(Bool(), 1.B)
  val LSRegen = WireInit(Bool(), 1.B)
  val WBRegen = WireInit(Bool(), 1.B)
  val ISRegen = WireInit(Bool(), 1.B)
  val ifu_dnpc = Wire(UInt(XLEN.W))
  val pcsel = WireInit(Bool(), 0.B)
  val InstFetcher = Module(new IFU)
  val PC = RegInit(UInt(XLEN.W), RESET_VECTOR.U)
  val R = Mem(32, UInt(XLEN.W))
  val dataHazard = WireInit(Bool(), 0.B)
  val stall = WireInit(Bool(), 0.B)

 
  InstFetcher.io.out.ready := IDRegen
  InstFetcher.io.in.bits.isdnpc := pcsel
  InstFetcher.io.in.bits.dnpc := Mux(pcsel, ifu_dnpc, 0.U)
  // InstFetcher.io.in.bits.pc := PC
  // when (stall) {
  //   PC := PC
  //   InstFetcher.io.in.bits.pc := InstFetcher.io.out.bits.pc(31, 0)
  // }.elsewhen (pcsel) {
  //   //todo:此处应该等待 IFU 的 ready 为真再赋值 dnpc
  //   PC := ifu_dnpc
  //   InstFetcher.io.in.bits.pc := PC
  // } .otherwise {
  //   // 如果没有指令，那么就不应该更新 PC
  //   PC := Mux(InstFetcher.io.out.fire, InstFetcher.io.out.bits.pc + 4.U, PC)
  //   InstFetcher.io.in.bits.pc := PC
  // }

  // 如果上一条指令（即当前处于译码阶段的指令）是跳转指令，那么就不应该更新 IDReg，
  // 而应该冲刷掉 IFU 里正在取指的指令
  // 
  when (IDRegen) {
    IDReg.inst := Mux(InstFetcher.io.out.valid, InstFetcher.io.out.bits.inst, 0.U)
    IDReg.pc := Mux(InstFetcher.io.out.valid, InstFetcher.io.out.bits.pc, 0.U) 
    IDReg.valid := InstFetcher.io.out.valid
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
  
  // val snpc = Decoder.io.pc + 4.U
  EXRegen := LSRegen | !EXReg.valid
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
  // pcsel := Decoder.io.isdnpc

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

  // 当 NPC_Mem.io.in.ready 为 false，并且上游模块的 valid 为 true 时，
  // 需要保持这些数据直到 NPC_Mem.io.in.ready 为 true
  // 靠上游模块保持数据，还是靠级间寄存器保持数据？
  // 如果不保持：当 Mem.io.in.ready 为 false，
  // 即 mem 的 arready 为 false，
  // 传入的读地址可能不会被接收（丢失了）
  // 因为传入 LSReg 的读取指令只会持续一个周期
  // IFU 没有上游模块，因此没有这个问题
  LSRegen := NPC_Mem.io.in.ready | !LSReg.valid
  // 先不考虑丢失的问题，跑一下看看波形

  val rdata = WBReg.rdata
  val rdata7 = rdata(7)
  val rdata15 = rdata(15)
  val rdata31 = rdata(31)
  val alureslow = Wire(UInt(32.W))
  val wbsextrdata = WireInit(0.U(XLEN.W))
  // val lsalures = WireInit(0.U(XLEN.W))
  // val wbalures = WireInit(0.U(XLEN.W))
  // reg for debug
  // val wbsextrdatareg = RegInit(0.U(XLEN.W))
  // wbsextrdatareg := wbsextrdata
  //printf("wbsextrdata = %x, wbsextrdatareg = %x\n", wbsextrdata, wbsextrdatareg)
  alureslow := LSReg.alures(31, 0)
  NPC_Mem.io.in.valid := LSReg.valid
  when (LSReg.valid) {  
    // LSReg 和 NPC_Mem 的握手(对 ready 的判断)在 NPC_Mem 里处理，此处直接连线即可
    // 当 valid 为 1 但 ready 不为 1 时，发送方应保持数据并保持 valid 不变直到 ready 为 1。
    // 此处的发送方即为 LSReg，其 en 的条件保证了这一点
    NPC_Mem.io.in.bits.inst := LSReg.inst 
    NPC_Mem.io.in.bits.pc := LSReg.pc 
    NPC_Mem.io.in.bits.alures := LSReg.alures
    // rs2v 即 wdata
    NPC_Mem.io.in.bits.memvalid := LSReg.memvalid
    NPC_Mem.io.in.bits.wen := LSReg.memwen
    NPC_Mem.io.in.bits.wmask := LSReg.memwmask
    NPC_Mem.io.in.bits.wsext := LSReg.memsext
    NPC_Mem.io.in.bits.raddr := alureslow
    NPC_Mem.io.in.bits.waddr := alureslow
    NPC_Mem.io.in.bits.wdata := LSReg.rs2v
    NPC_Mem.io.in.bits.rden := LSReg.rden
    NPC_Mem.io.in.bits.rd := LSReg.rd   
  }.otherwise {
    //when (NPC_Mem.io.in.ready) {
      NPC_Mem.io.in.bits.inst := 0.U
      NPC_Mem.io.in.bits.pc := 0.U 
      NPC_Mem.io.in.bits.alures := 0.U
      NPC_Mem.io.in.bits.memvalid := 0.B 
      NPC_Mem.io.in.valid := 0.B
      NPC_Mem.io.in.bits.wen := 0.U 
      NPC_Mem.io.in.bits.raddr := 0.U 
      NPC_Mem.io.in.bits.waddr := 0.U 
      NPC_Mem.io.in.bits.wdata := 0.U 
      NPC_Mem.io.in.bits.wmask := 0.U
      NPC_Mem.io.in.bits.wsext := MEM_SEXT_NONE
      NPC_Mem.io.in.bits.rden := 0.B 
      NPC_Mem.io.in.bits.rd := 0.U
    //}
  }

  WBRegen := ISRegen | !WBReg.valid
  when (NPC_Mem.io.out.valid) {
    when (WBRegen) {
      WBReg.inst := NPC_Mem.io.out.bits.inst
      WBReg.pc := NPC_Mem.io.out.bits.pc
      WBReg.valid := NPC_Mem.io.out.valid
      WBReg.memvalid := NPC_Mem.io.out.bits.memvalid
      WBReg.alures := NPC_Mem.io.out.bits.alures
      WBReg.rden := NPC_Mem.io.out.bits.rden
      WBReg.rd := NPC_Mem.io.out.bits.rd
      WBReg.memsext := NPC_Mem.io.out.bits.memsext
      WBReg.rdata := NPC_Mem.io.out.bits.rdata
    }
  }.otherwise {
    when (WBRegen) {
      WBReg.inst := 0.U 
      WBReg.pc := 0.U
      WBReg.valid := 0.B 
      WBReg.memvalid := 0.B 
      WBReg.alures := 0.U 
      WBReg.rden := 0.B
      WBReg.rd := 0.U 
      WBReg.memsext := MEM_SEXT_NONE
      WBReg.rdata := 0.B
    }
  }

  when (WBReg.valid & ISRegen) {
    ISReg.valid := WBReg.valid
    ISReg.inst := WBReg.inst
    ISReg.pc := WBReg.pc
    io.npc := LSReg.pc
    // rdata := WBReg.rdata
    wbsextrdata := MuxLookup(WBReg.memsext, rdata)(Seq(
      MEM_NSEXT_8 ->  Cat(Fill(XLEN-8, 0.U), rdata(7, 0)),
      MEM_NSEXT_16->  Cat(Fill(XLEN-16, 0.U), rdata(15, 0)),
      MEM_NSEXT_32->  Cat(Fill(XLEN-32, 0.U), rdata(31, 0)),
      MEM_SEXT_8  ->  Cat(Fill(XLEN-8, rdata7), rdata(7, 0)),
      MEM_SEXT_16 ->  Cat(Fill(XLEN-16, rdata15), rdata(15, 0)),
      MEM_SEXT_32 ->  Cat(Fill(XLEN-32, rdata31), rdata(31, 0)),
    ))
    when(WBReg.rden && WBReg.rd =/= 0.U) {
      R(WBReg.rd) := Mux(WBReg.memvalid === 1.B, wbsextrdata, WBReg.alures)
    }
    // wbalures := WBReg.alures
  } .otherwise {
    io.npc := 0.U
    ISReg.valid := 0.B 
    ISReg.pc := 0.U 
    ISReg.inst := 0.U
  }

  when(ISReg.valid) {
    io.inst := ISReg.inst
    io.pc := ISReg.pc
  } .otherwise {
    io.inst := 0.U
    io.pc := 0.U
  }

  val rs1ren = Decoder.io.rrs1 && Decoder.io.rs1 =/= 0.U && IDReg.valid
  val rs2ren = Decoder.io.rrs2 && Decoder.io.rs2 =/= 0.U && IDReg.valid
  val EX_RS1_Hazard = Decoder.io.rs1 === Mux(EXReg.valid, EXReg.rd, 0.U) && EXReg.rden
  val EX_RS2_Hazard = Decoder.io.rs2 === Mux(EXReg.valid, EXReg.rd, 0.U) && EXReg.rden
  val LS_RS1_Hazard = Decoder.io.rs1 === Mux(LSReg.valid, LSReg.rd, 0.U) && LSReg.rden
  val LS_RS2_Hazard = Decoder.io.rs2 === Mux(LSReg.valid, LSReg.rd, 0.U) && LSReg.rden
  val MEM_RS1_Hazard = Decoder.io.rs1 === NPC_Mem.io.out.bits.rd && NPC_Mem.io.out.bits.rden
  val MEM_RS2_Hazard = Decoder.io.rs2 === NPC_Mem.io.out.bits.rd && NPC_Mem.io.out.bits.rden
  val WB_RS1_Hazard = Decoder.io.rs1 === Mux(WBReg.valid, WBReg.rd, 0.U) && WBReg.rden
  val WB_RS2_Hazard = Decoder.io.rs2 === Mux(WBReg.valid, WBReg.rd, 0.U) && WBReg.rden
  dataHazard := MuxCase(0.U, Array (
    (rs1ren && (EX_RS1_Hazard | LS_RS1_Hazard | MEM_RS1_Hazard | WB_RS1_Hazard)) -> 1.B,
    (rs2ren && (EX_RS2_Hazard | LS_RS2_Hazard | MEM_RS2_Hazard | WB_RS2_Hazard)) -> 1.B,
  ))
  //printf("IDUpc=%x rs1ren: %d, rs2ren: %d, EX_RS1_Hazard: %d, EX_RS2_Hazard: %d, WB_RS1_Hazard: %d, WB_RS2_Hazard: %d, LS_RS1_Hazard: %d, LS_RS2_Hazard: %d\n", IDReg.pc, rs1ren, rs2ren, EX_RS1_Hazard, EX_RS2_Hazard, WB_RS1_Hazard, WB_RS2_Hazard, LS_RS1_Hazard, LS_RS2_Hazard)
  when (stall) {
    InstFetcher.io.in.valid := 0.B
    IDRegen := 0.B
    EXReg.valid := 0.B
    ifu_dnpc := "x114514".U
  } .otherwise { 
    InstFetcher.io.in.valid := 1.B
    IDRegen := EXRegen | !IDReg.valid
    EXReg.valid := 1.B
    ifu_dnpc := MuxCase(0.U, Array(
      (Decoder.io.inst === JALR)  -> (rs1v + Decoder.io.imm),
      (Decoder.io.inst === JAL)   -> (pc_plus_imm),
      (Decoder.io.inst === BEQ)   -> pc_plus_imm,
      (Decoder.io.inst === BNE)   -> pc_plus_imm,
      (Decoder.io.inst === BGE)   -> pc_plus_imm,
      (Decoder.io.inst === BGEU)  -> pc_plus_imm,
      (Decoder.io.inst === BLT)   -> pc_plus_imm,
      (Decoder.io.inst === BLTU)  -> pc_plus_imm,
    ))
    pcsel := MuxCase(0.U, Array(
      (Decoder.io.inst === JALR)  -> 1.B,
      (Decoder.io.inst === JAL)   -> 1.B,
      (Decoder.io.inst === BEQ)   -> (rs1v === rs2v),
      (Decoder.io.inst === BNE)   -> (rs1v =/= rs2v),
      (Decoder.io.inst === BGE)   -> (rs1v.asSInt >= rs2v.asSInt),
      (Decoder.io.inst === BGEU)  -> (rs1v >= rs2v),
      (Decoder.io.inst === BLT)   -> (rs1v.asSInt < rs2v.asSInt),
      (Decoder.io.inst === BLTU)  -> (rs1v < rs2v),
    ))
  }
  
  val Ebreak = Module(new DPIC_EBREAK)
  Ebreak.io.isEbreak := EXReg.isEbreak
  Ebreak.io.clk := clock
}

