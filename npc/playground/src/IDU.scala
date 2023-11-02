import chisel3._
import chisel3.util._
// import chisel3.util.experimental.loadMemoryFromFileInline

class IDU() extends Module {
  val io = IO(new Bundle {
    val inst = Input(UInt(32.W))
    val isAddi = Output(Bool())
    val isEbreak = Output(Bool())
    // 这两个信号拉到顶，去访问寄存器堆
    val rs1 = Output(UInt(5.W))
    val rs2 = Output(UInt(5.W))
    val rd  = Output(UInt(5.W))
    val sextimmi = Output(UInt(32.W))
    // 目前暂时不用根据指令读取内存
  })
  // I type 
  val Ibundle = new Bundle {
    val immi    = UInt(12.W)
    val rs1     = UInt(5.W)
    val funct3  = UInt(3.W)
    val rd      = UInt(5.W)
    val opcode  = UInt(7.W)
  }
  def SignEXT(immi: UInt) = Cat(Fill(20, immi(11)), immi)
  val inst = io.inst.asTypeOf(Ibundle)
  io.isAddi := (inst.opcode === "b0010011".U) && (inst.funct3 === "b000".U)
  io.isEbreak := (inst.asUInt === "x00100073".U)
  io.rs1 := inst.rs1
  io.sextimmi := SignEXT(inst.immi)
  io.rs2 := 0.U 
  io.rd := inst.rd
}
