
import chisel3._ 
import chisel3.util._ 
import Configs._

class LSUIn extends Bundle {
  val wen = Bool()
  val raddr = UInt(XLEN.W)
  val waddr = UInt(XLEN.W)
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
  io.out.valid := 1.B
  // 手动模拟 1 周期的 SRAM 延迟
  // io.out.bits.rdata := RegNext(dpic_mem.rdata)
  io.out.bits.rdata := dpic_mem.io.rdata
}

