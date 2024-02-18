
import chisel3._ 
import chisel3.util._ 
import Configs._

class LSUIn extends Bundle {
  val wen = Bool()
  val raddr = UInt(32.W)
  val waddr = UInt(32.W)
  val wdata = UInt(XLEN.W)
  val wmask = UInt(XLEN.W)
}

class LSUOut extends Bundle {
  val rdata = UInt(XLEN.W)
}

class LSU extends Module {
  val io = IO(new Bundle {
    val in = Flipped(Decoupled(new LSUIn))
    val out = Decoupled(new LSUOut)
  })
  val dpic_mem = Module(new DPIC_MEM)
  io.in.ready := 1.B
  dpic_mem.io.valid := io.in.valid
  dpic_mem.io.wen := io.in.bits.wen
  dpic_mem.io.raddr := io.in.bits.raddr
  dpic_mem.io.waddr := io.in.bits.waddr
  dpic_mem.io.wdata := io.in.bits.wdata
  dpic_mem.io.wmask := io.in.bits.wmask
  dpic_mem.io.clk := clock
  io.out.valid := RegNext(io.in.valid, 0.B)
  // 手动模拟 1 周期的 SRAM 延迟，仅读取有延迟
  io.out.bits.rdata := RegNext(dpic_mem.io.rdata, 0.U)
  // io.out.bits.rdata := 0.U
}

