import chisel3._
import chisel3.util._
import Configs._
import Instr._
import chisel3.util.experimental.loadMemoryFromFileInline

class Top extends Module {
  val io = IO(new Bundle {
    // IFU
    val inst = Output(UInt(32.W))
    val pc = Output(UInt(XLEN.W))
    // val pcsel = Input(Bool())
    // val snpc = Input(UInt(XLEN.W))
    
    // val rs1 = Input(UInt(RIDXLEN.W))
    // val rs2 = Input(UInt(RIDXLEN.W))
    // val rd = Input(UInt(RIDXLEN.W))
    // val rd_en = Input(Bool()) 
    // val rdv = Input(UInt(XLEN.W))
    // val rs1v = Output(UInt(XLEN.W))
    // val rs2v = Output(UInt(XLEN.W))
  })
  
  // 内存模块
  // 译码器需要判断当前指令是否为访存，生成对应的 valid 和 wen 信号
  val NPC_Mem = Module(new DPIC_MEM)
  val memvalid = Wire(UInt(1.W))
  val memwen = Wire(UInt(1.W))
  val memrdata = Wire(UInt(XLEN.W)) 
  val memsext = Wire(UInt(MEM_SEXT_SEL_WIDTH.W))
  val memraddr = Wire(UInt(XLEN.W))
  val memwaddr = Wire(UInt(XLEN.W))
  val memwdata = Wire(UInt(XLEN.W))
  
  val memwmask = Wire(UInt(WMASKLEN.W))
  val rdata7 = NPC_Mem.io.rdata(7)
  val rdata15 = NPC_Mem.io.rdata(15)
  val rdata31 = NPC_Mem.io.rdata(31)
  memrdata := MuxLookup(memsext, NPC_Mem.io.rdata)(Seq(
    MEM_NSEXT_8 ->  Cat(Fill(XLEN-8, 0.U), NPC_Mem.io.rdata(7, 0)),
    MEM_NSEXT_16->  Cat(Fill(XLEN-16, 0.U), NPC_Mem.io.rdata(15, 0)),
    //MEM_NSEXT_32->  Cat(Fill(XLEN-32, 0.U), NPC_Mem.io.rdata(31, 0)),
    MEM_SEXT_8  ->  Cat(Fill(XLEN-8, rdata7), NPC_Mem.io.rdata(7, 0)),
    MEM_SEXT_16 ->  Cat(Fill(XLEN-16, rdata15), NPC_Mem.io.rdata(15, 0)),
    //rv64 only: 
    //MEM_SEXT_32 ->  Cat(Fill(XLEN-32, rdata31), NPC_Mem.io.rdata(31, 0))
  ))
  NPC_Mem.io.valid := memvalid
  NPC_Mem.io.wen := memwen
  NPC_Mem.io.raddr := memraddr
  NPC_Mem.io.waddr := memwaddr
  NPC_Mem.io.wdata := memwdata
  NPC_Mem.io.wmask := memwmask
  NPC_Mem.io.clk := clock

  // 寄存器
  val R = Mem(32, UInt(XLEN.W))
  
  // PC 模块
  val PC = RegInit(RESET_VECTOR.U(XLEN.W))
  val dnpc = Wire(UInt(XLEN.W))
  val pcsel = Wire(UInt(1.W))
  val wirepc = Wire(UInt(XLEN.W))
  val wireinst = Wire(UInt(XLEN.W))
  wirepc := PC
  io.pc := PC
  val npc = Wire(UInt(XLEN.W))
  npc := Mux(pcsel === 1.U, dnpc, PC + 4.U)
  PC := npc


  def Rread(idx: UInt) = Mux(idx === 0.U, 0.U(XLEN.W), R(idx))
  val rs1v = Wire(UInt(XLEN.W))
  val rs2v = Wire(UInt(XLEN.W))
  val rs1 = Wire(UInt(RIDXLEN.W))
  val rs2 = Wire(UInt(RIDXLEN.W))
  val rd = Wire(UInt(RIDXLEN.W))
  val rd_en = Wire(UInt(1.W))
  val rdv = Wire(UInt(XLEN.W))
  rs1v := Rread(rs1)
  rs2v := Rread(rs2)
  R(rd) := Mux(rd_en === 0.U(1.W), R(rd), rdv)
  R(0) := 0.U
  // 取指模块
  // 根据 PC 取出 inst 之前是在 C++ 里完成的
  // 现在需要额外调用一次 pmem_read() 来实现
  val InstFetcher = Module(new DPIC_IFU)
  InstFetcher.io.pc := wirepc
  //InstFetcher.io.clk := clock
  wireinst := Mux(reset.asBool, 0.U, InstFetcher.io.inst)
  InstFetcher.io.valid := Mux(reset.asBool, 0.U, 1.U)
  io.inst := wireinst
  
  // 译码模块
  val Decoder = Module(new IDU)
  Decoder.io.inst := wireinst
  rs1 := Decoder.io.rs1
  rs2 := Decoder.io.rs2 
  pcsel := Decoder.io.isdnpc
  rd := Decoder.io.rd 
  rd_en := Decoder.io.rd_en
  memvalid := Decoder.io.memvalid
  memwen := Decoder.io.memwen
  memwmask := Decoder.io.memwmask
  memsext := Decoder.io.memsext
  memwdata := MuxLookup(memwmask, rs2v)(Seq(
    1.U  -> rs2v(7, 0),
    3.U  -> rs2v(15, 0),
    15.U -> rs2v(31, 0)
  ))

  // 执行模块
  val ALU = Module(new EXU)
  ALU.io.inst := wireinst
  ALU.io.pc := wirepc
  ALU.io.alu_op := Decoder.io.alu_op
  ALU.io.asel := Decoder.io.alu_sel_a
  ALU.io.bsel := Decoder.io.alu_sel_b
  ALU.io.imm := Decoder.io.imm
  ALU.io.rs1v := rs1v
  ALU.io.rs2v := rs2v
  dnpc := ALU.io.dnpc
  
  memraddr := ALU.io.res
  memwaddr := ALU.io.res

  rdv := Mux(memvalid === 1.U, memrdata, ALU.io.res)
  
  val Ebreak = Module(new DPIC_EBREAK)
  Ebreak.io.isEbreak := Decoder.io.isEbreak
  Ebreak.io.clk := clock
  
}

