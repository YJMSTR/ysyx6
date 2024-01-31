import chisel3._ 
import chisel3.util._ 
import Configs._

class IFUIn extends Bundle {
  val pc = UInt(XLEN.W)
}

class IFUOut extends Bundle {
  val pc = UInt(XLEN.W)
  val inst = UInt(32.W)
}

class IFU extends Module {
  val io = IO(new Bundle {
    val in = Flipped(Decoupled(new IFUIn))
    val out = Decoupled(new IFUOut)
  })

  val dpic_ifu = Module(new DPIC_IFU)
  dpic_ifu.io.valid := io.in.valid & Mux(io.in.bits.pc === 0.U, 0.B, 1.B)
  dpic_ifu.io.pc := io.in.bits.pc

  io.in.ready := reset.asBool =/= 1.B
  io.out.bits.inst := RegNext(dpic_ifu.io.inst, 0.U)
  io.out.valid := RegNext(io.in.valid, 0.B)
  io.out.bits.pc := RegNext(dpic_ifu.io.pc, RESET_VECTOR.U)
}

