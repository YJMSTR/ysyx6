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
  val csridx = UInt(CSRIDXLEN.W)
  val csrrv  = UInt(XLEN.W)
  val csrwv = UInt(XLEN.W)
  val csr_en = Bool()
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
  val csridx = UInt(CSRIDXLEN.W)
  val csrrv  = UInt(XLEN.W)
  val csrwv = UInt(XLEN.W)
  val csr_en = Bool()
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
  val csridx = UInt(CSRIDXLEN.W)
  val csrrv  = UInt(XLEN.W)
  val csrwv = UInt(XLEN.W)
  val csr_en = Bool()
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

class ysyx_23060110 extends Module {
  val io = IO(new Bundle {
    val inst = Output(UInt(32.W))
    val pc = Output(UInt(XLEN.W))
    val npc = Output(UInt(XLEN.W))
    val interrupt = Input(Bool())
    val master = Flipped(new AXI4Interface)
    val slave = new AXI4Interface
    // val empty_sram = Flipped(new AXI4Interface)
    // val isebreak = Output(Bool())
  })

  val io_empty_slave = Module(new ysyx_23060110_empty_axi4_slave)
  val io_empty_master = Module(new ysyx_23060110_empty_axi4_master)
  io.slave <> io_empty_slave.io.axi4
  io.master <> io_empty_master.io.axi4
  
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
      _.csridx    -> 0.U,
      _.csrrv     -> 0.U,
      _.csrwv     -> 0.U,
      _.csr_en    -> 0.B,
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
      _.csridx    -> 0.U,
      _.csrrv     -> 0.U,
      _.csrwv     -> 0.U,
      _.csr_en    -> 0.B,
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
      _.csridx    -> 0.U,
      _.csrrv     -> 0.U,
      _.csrwv     -> 0.U,
      _.csr_en    -> 0.B,
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
  val AXI4Arbiter = Module(new ysyx_23060110_MyArbiter)
  // val SRAM = Module(new FAKE_SRAM_ONLY)

  val XBar2 = Module(new ysyx_23060110_XBar)
  // val MyUart = Module(new MyUART)
  val MyClint = Module(new ysyx_23060110_MyCLINT)

  val IDRegen = WireInit(Bool(), 1.B)
  val EXRegen = WireInit(Bool(), 1.B)
  val LSRegen = WireInit(Bool(), 1.B)
  val WBRegen = WireInit(Bool(), 1.B)
  val ISRegen = WireInit(Bool(), 1.B)
  val ifu_dnpc = Wire(UInt(XLEN.W))
  val pcsel = WireInit(Bool(), 0.B)
  val InstFetcher = Module(new ysyx_23060110_IFU)
  val PC = RegInit(UInt(XLEN.W), RESET_VECTOR.U)
  val R = Mem(32, UInt(XLEN.W))
  
  val mstatus = RegInit("xa00001800".U(XLEN.W))
  val mtvec   = RegInit(0.U(XLEN.W))
  val mepc    = RegInit(0.U(XLEN.W))
  val mcause  = RegInit(0.U(XLEN.W))

  

  val dataHazard = WireInit(Bool(), 0.B)
  val stall = WireInit(Bool(), 0.B)
  val next_stall = RegNext(stall)

  InstFetcher.io.axi4_to_arbiter <> AXI4Arbiter.io.ifu_bus.axi4
  InstFetcher.io.bus_ac := AXI4Arbiter.io.ifu_bus.bus_ac

  AXI4Arbiter.io.ifu_bus.bus_reqr := InstFetcher.io.bus_reqr
  AXI4Arbiter.io.ifu_bus.bus_reqw := InstFetcher.io.bus_reqw

  val empty_master = Module (new ysyx_23060110_empty_axi4_master)
  empty_master.io.axi4 <> XBar2.io.axi4in
  // 将 Arbiter 连到 顶层模块的 master
  AXI4Arbiter.io.xbar_bus <> io.master
  MyClint.io.axi4 <> io.slave

  // XBar2.io.axi4out1 <> io.empty_sram
  // XBar2.io.axi4out1 <> SRAM.io.axi4
  // XBar2.io.axi4out0 <> MyUart.io.axi4
  // XBar2.io.axi4out2 <> MyClint.io.axi4
  val empty_slave0 = Module(new ysyx_23060110_empty_axi4_slave)
  val empty_slave1 = Module(new ysyx_23060110_empty_axi4_slave)
  val empty_slave_mrom = Module(new ysyx_23060110_empty_axi4_slave)
  XBar2.io.axi4out0 <> empty_slave0.io.axi4
  XBar2.io.axi4out2 <> MyClint.io.axi4
  XBar2.io.axi4out1 <> empty_slave1.io.axi4
  XBar2.io.axi4out_mrom <> empty_slave_mrom.io.axi4

  InstFetcher.io.out.ready := IDRegen && reset.asBool === 0.B
  InstFetcher.io.in.bits.isdnpc := pcsel
  InstFetcher.io.in.bits.dnpc := Mux(pcsel, ifu_dnpc, 0.U)
  InstFetcher.io.in.bits.stall := stall
  
  when (InstFetcher.io.out.valid) {
    when (IDRegen) {
      IDReg.inst := InstFetcher.io.out.bits.inst
      IDReg.pc := InstFetcher.io.out.bits.pc 
      IDReg.valid := 1.B
    } 
  }.otherwise {
    when (IDRegen) { 
      IDReg.inst := 0.U 
      IDReg.pc := 0.U 
      IDReg.valid := 0.B
    }
  }
  

 
  stall := dataHazard
  def Rread(idx: UInt) = Mux(idx === 0.U, 0.U(XLEN.W), R(idx))
  
  R(0) := 0.U
  val Decoder = Module(new ysyx_23060110_IDU)
  // when(Decoder.io.rd =/= 0.U && scoreboard(Decoder.io.rd) =/= 1.B && Decoder.io.rd_en) {
  //   scoreboard(Decoder.io.rd) := 1.B
  // } .otherwise {
  //   scoreboard(Decoder.io.rd) := scoreboard(Decoder.io.rd)
  // }
  val pc_plus_imm = Decoder.io.pc + Decoder.io.imm
  //printf("decoder pc = %x, imm = %x, pc_plus_imm = %x\n", Decoder.io.pc, Decoder.io.imm, pc_plus_imm)
  val rs2v = Rread(Decoder.io.rs2)
  val rs1v = Rread(Decoder.io.rs1)
  
  // csridx：读 csr 的下标 csrrv：读出的值
  val csridx = Mux(Decoder.io.inst === ECALL, CSR_MTVEC.U(12.W), Decoder.io.inst(31, 20))
  val csrrv  = MuxLookup(csridx, 0.U(XLEN.W), Seq(
    CSR_MCAUSE.U  -> mcause,
    CSR_MSTATUS.U -> mstatus,
    CSR_MEPC.U    -> mepc,
    CSR_MTVEC.U   -> mtvec
  ))

  // csrwv 是要写回 csridx 对应的 csr 的值，当 csr_en 为真时写回

  val csrwv = MuxCase(0.U(XLEN.W), Seq(
    (Decoder.io.inst === CSRRS) -> (rs1v | csrrv),
    (Decoder.io.inst === CSRRW) -> rs1v,
  ))
  // val snpc = Decoder.io.pc + 4.U
  // 当 LSRegen 变高，EXReg 应该先把其内容写入 LSReg 再变高
  // 当 LSRegen 变低，EXRegen 应该立刻变低，不然数据会丢失
  // when (LSRegen) {
  //   EXRegen := RegNext(LSRegen)
  // } .otherwise {
  //   EXRegen := LSRegen
  // }
  EXRegen := LSRegen
  // printf("exregen %d lsregen %d\n", EXRegen, LSRegen);
  // 流水线阻塞会导致  EXReg.valid 被拉低，但其实拉低后 EXReg 中保存的仍然是有效数据，不应该冲刷掉
  when(EXRegen) { // 如果此时 EXReg.valid ，此时 LSRegen 应该也是 1, 理应让 EXReg 当前的数据进入 LSReg
    EXReg.inst := Mux(IDReg.valid, IDReg.inst, 0.U)
    EXReg.pc := Mux(IDReg.valid, IDReg.pc, 0.U)
    EXReg.rs1v := rs1v
    EXReg.rs1 := Decoder.io.rs1
    EXReg.rs2 := Decoder.io.rs2
    EXReg.rs2v := rs2v
    EXReg.csridx := csridx
    EXReg.csrrv := csrrv
    EXReg.csrwv := csrwv
    EXReg.csr_en := Decoder.io.csr_en
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
  }// .otherwise {
  //   EXReg.inst := EXReg.inst
  //   EXReg.pc := EXReg.pc
  //   EXReg.rs1v := EXReg.rs1v
  //   EXReg.rs2v := EXReg.rs2v
  //   EXReg.rs1 := EXReg.rs1 
  //   EXReg.rs2 := EXReg.rs2
  //   EXReg.imm := EXReg.imm
  //   EXReg.aluop := EXReg.aluop
  //   EXReg.dataAsel := EXReg.dataAsel
  //   EXReg.dataBsel := EXReg.dataBsel
  //   EXReg.memvalid := EXReg.memvalid
  //   EXReg.memwen := EXReg.memwen
  //   EXReg.memwmask := EXReg.memwmask
  //   EXReg.memsext := EXReg.memsext
  //   EXReg.isEbreak := EXReg.isEbreak
  //   EXReg.isword := EXReg.isword
  //   EXReg.rden := EXReg.rden
  //   EXReg.rd := EXReg.rd  
  // }

  when (IDReg.valid) {
    Decoder.io.inst := IDReg.inst
    Decoder.io.pc := IDReg.pc
  } .otherwise {
    // 否则按照空指令进行输入
    Decoder.io.inst := 0.U
    Decoder.io.pc := 0.U
  }
  // pcsel := Decoder.io.isdnpc

  val ALU = Module(new ysyx_23060110_EXU)
  when(EXReg.valid ) { 
    ALU.io.inst := EXReg.inst
    ALU.io.pc := EXReg.pc
    ALU.io.alu_op := EXReg.aluop
    ALU.io.asel := EXReg.dataAsel
    ALU.io.bsel := EXReg.dataBsel
    ALU.io.imm := EXReg.imm
    ALU.io.rs1v := EXReg.rs1v
    ALU.io.rs2v := EXReg.rs2v
    ALU.io.isword := EXReg.isword
    ALU.io.csridx := EXReg.csridx
    ALU.io.csrrv  := EXReg.csrrv
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
      LSReg.alures := ALU.io.res
      LSReg.csridx := ALU.io.csridx
      LSReg.csrrv := ALU.io.csrrv
      LSReg.csrwv := EXReg.csrwv
      LSReg.csr_en := EXReg.csr_en
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
    ALU.io.csridx := 0.U 
    ALU.io.csrrv  := 0.U
    ALU.io.isword := 0.B
    when (LSRegen) {
      LSReg.inst := 0.U
      LSReg.pc := 0.U
      LSReg.rs2v := 0.U
      LSReg.csridx := 0.U 
      LSReg.csrrv := 0.U
      LSReg.csrwv := 0.U
      LSReg.memvalid := 0.B
      LSReg.memwen := 0.B
      LSReg.memwmask := 0.U
      LSReg.memsext := MEM_SEXT_NONE
      LSReg.rden := 0.B
      LSReg.csr_en := 0.B
      LSReg.rd := 0.U
    }
  }

  
  val NPC_Mem = Module(new ysyx_23060110_LSU)
  NPC_Mem.io.out.ready := WBRegen
  NPC_Mem.io.bus_ac := AXI4Arbiter.io.lsu_bus.bus_ac
  AXI4Arbiter.io.lsu_bus.bus_reqr := NPC_Mem.io.bus_reqr
  AXI4Arbiter.io.lsu_bus.bus_reqw := NPC_Mem.io.bus_reqw
  AXI4Arbiter.io.lsu_bus.axi4 <> NPC_Mem.io.axi4_to_arbiter

  // printf("LSRegen=%d LSReg.pc = %x\n", LSRegen, LSReg.pc)
  LSRegen := NPC_Mem.io.in.ready //| !LSReg.valid

  val rdata = WBReg.rdata
  val rdata7 = rdata(7)
  val rdata15 = rdata(15)
  val rdata31 = rdata(31)
  val alureslow = Wire(UInt(32.W))
  val wbsextrdata = WireInit(0.U(XLEN.W))
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
    NPC_Mem.io.in.bits.csridx := LSReg.csridx
    NPC_Mem.io.in.bits.csrrv := LSReg.csrrv
    NPC_Mem.io.in.bits.csrwv := LSReg.csrwv
    NPC_Mem.io.in.bits.csr_en := LSReg.csr_en
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
      NPC_Mem.io.in.bits.csridx := 0.U 
      NPC_Mem.io.in.bits.csrrv := 0.U
      NPC_Mem.io.in.bits.csrwv := 0.U
      NPC_Mem.io.in.bits.csr_en := 0.B
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
      WBReg.csridx := NPC_Mem.io.out.bits.csridx
      WBReg.csrrv := NPC_Mem.io.out.bits.csrrv
      WBReg.csrwv := NPC_Mem.io.out.bits.csrwv  
      WBReg.csr_en := NPC_Mem.io.out.bits.csr_en
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
      WBReg.csridx := NPC_Mem.io.out.bits.csridx
      WBReg.csrrv := NPC_Mem.io.out.bits.csrrv
      WBReg.csrwv := NPC_Mem.io.out.bits.csrwv
      WBReg.csr_en := NPC_Mem.io.out.bits.csr_en
    }
  }

  when (WBReg.valid) {
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

    when(WBReg.inst === ECALL) {
      mepc := WBReg.pc 
      mcause := 11.U
    }
    when(WBReg.rden) {
      when (WBReg.rd =/= 0.U) {
        R(WBReg.rd) := Mux(WBReg.memvalid === 1.B, wbsextrdata, WBReg.alures)
      }
    }
    when(WBReg.csr_en) {
      when(WBReg.csridx === CSR_MEPC.U) {
        mepc := WBReg.csrwv
      } .elsewhen (WBReg.csridx === CSR_MCAUSE.U) {
        mcause := WBReg.csrwv 
      } .elsewhen (WBReg.csridx === CSR_MSTATUS.U) {
        mstatus := WBReg.csrwv 
      } .elsewhen (WBReg.csridx === CSR_MTVEC.U) {
        printf("mtvec old value = %x new value = %x pc = %x\n", mtvec, WBReg.csrwv, WBReg.pc)
        mtvec := WBReg.csrwv 
      } .otherwise {

      }
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

  // 对于 ECALL 指令，其会将 csridx 设置为 mtvec
  val zicsr_ren = (Decoder.io.inst === CSRRS || Decoder.io.inst === CSRRW)
  val EX_CSR_Hazard = (csridx === Mux(EXReg.valid, EXReg.csridx, 0.U) && (EXReg.csr_en)) || (EXReg.inst === ECALL && EXReg.valid && (csridx === CSR_MEPC.U || csridx === CSR_MCAUSE.U)) 
  val LS_CSR_Hazard = (csridx === Mux(LSReg.valid, LSReg.csridx, 0.U) && LSReg.csr_en) || (LSReg.inst === ECALL && LSReg.valid && (csridx === CSR_MEPC.U || csridx === CSR_MCAUSE.U))
  val MEM_CSR_Hazard = (csridx === NPC_Mem.io.out.bits.csridx && NPC_Mem.io.out.bits.csr_en) || (NPC_Mem.io.out.bits.inst === ECALL && NPC_Mem.io.out.valid && (csridx === CSR_MEPC.U || csridx === CSR_MCAUSE.U))
  val WB_CSR_Hazard = (csridx === Mux(WBReg.valid, WBReg.csridx, 0.U) && WBReg.csr_en) || (WBReg.inst === ECALL && WBReg.valid && (csridx === CSR_MEPC.U || csridx === CSR_MCAUSE.U))

  val gpr_data_hazard = MuxCase(0.B, Array(
    (rs1ren && (EX_RS1_Hazard | LS_RS1_Hazard | MEM_RS1_Hazard | WB_RS1_Hazard)) -> 1.B,
    (rs2ren && (EX_RS2_Hazard | LS_RS2_Hazard | MEM_RS2_Hazard | WB_RS2_Hazard)) -> 1.B,
  ))

  val csr_data_hazard = zicsr_ren && (EX_CSR_Hazard | LS_CSR_Hazard | MEM_CSR_Hazard | WB_CSR_Hazard)

  val lsu_hazard = Decoder.io.memvalid === 1.U && (Mux(EXReg.valid, EXReg.memvalid, 0.B) | Mux(LSReg.valid, LSReg.memvalid, 0.B) | Mux(NPC_Mem.io.out.valid, NPC_Mem.io.out.bits.memvalid, 0.B) | !LSRegen)

  dataHazard := gpr_data_hazard | csr_data_hazard | lsu_hazard
   
  // ecall: 写入 mepc 和 mcause, 读 mtvec。读写的冒险上面都处理了

  //printf("IDUpc=%x rs1ren: %d, rs2ren: %d, EX_RS1_Hazard: %d, EX_RS2_Hazard: %d, WB_RS1_Hazard: %d, WB_RS2_Hazard: %d, LS_RS1_Hazard: %d, LS_RS2_Hazard: %d\n", IDReg.pc, rs1ren, rs2ren, EX_RS1_Hazard, EX_RS2_Hazard, WB_RS1_Hazard, WB_RS2_Hazard, LS_RS1_Hazard, LS_RS2_Hazard)
  when (stall) {
    InstFetcher.io.in.valid := 0.B
    IDRegen := 0.B
    EXReg.valid := 0.B
    ifu_dnpc := "x114514".U
  } .otherwise { 
    InstFetcher.io.in.valid := reset.asBool === 0.B
    IDRegen := EXRegen
    EXReg.valid := 1.B  // 这个修改有一个周期的延迟，
    // 但 IDReg 和 EXReg 在当前周期就会被更新（因为 IDRegen 是组合信号
    // 这导致了原先在 EXReg 里的数据会被覆盖
    // 此处应该直接将 EXReg 里的数据传给 LSReg() 和 ALU？很难处理
    when (Decoder.io.inst === ECALL) {
      printf("wb ecall; mtvec = %x\n", mtvec)
    }
    ifu_dnpc := MuxCase(0.U, Array(
      (Decoder.io.inst === JALR)  -> (rs1v + Decoder.io.imm),
      (Decoder.io.inst === JAL)   -> (pc_plus_imm),
      (Decoder.io.inst === BEQ)   -> pc_plus_imm,
      (Decoder.io.inst === BNE)   -> pc_plus_imm,
      (Decoder.io.inst === BGE)   -> pc_plus_imm,
      (Decoder.io.inst === BGEU)  -> pc_plus_imm,
      (Decoder.io.inst === BLT)   -> pc_plus_imm,
      (Decoder.io.inst === BLTU)  -> pc_plus_imm,
      (Decoder.io.inst === MRET)  -> mepc,
      (Decoder.io.inst === ECALL) -> mtvec,
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
      (Decoder.io.inst === MRET)  -> 1.B,
      (Decoder.io.inst === ECALL) -> 1.B,
    ))
  }
  
  val Ebreak = Module(new DPIC_EBREAK)
  Ebreak.io.isEbreak := EXReg.isEbreak
  Ebreak.io.clk := clock

  // io.isebreak := EXReg.isEbreak
}

