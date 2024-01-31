import chisel3._ 
import chisel3.util._ 
import Configs._

class IFU(regFileIO: RegFileIO) extends Module {
  val io = IO(new Bundle {
    val in = Flipped(Decoupled(new IFUIn))
    val out = Decoupled(new IFUOut)
  })
  val s_idle :: s_wait_ready :: Nil = Enum(2)
  val state = RegInit(s_idle)
  val dpic_ifu = Module(new DPIC_IFU)

  val stall = io.out.bits.pc =/= io.in.bits.pc
  io.in.ready := !stall
  io.out.valid := !stall

  dpic_ifu.valid := io.in.valid 
  io.in.ready := 1.B
  dpic_ifu.pc := io.in.bits.pc

  val outpc = RegNext(dpic_ifu.io.pc, RESET_VECTOR.U)
  val outinst = RegNext(dpic_ifu.io.inst, 0.U)

  state := MuxLookup(state, s_idle, List(
    // idle 状态：      若 out.valid 则表示准备好发送数据了，等待下游模块 ready
    s_idle       -> Mux(io.out.valid, s_wait_ready, s_idle),
    // wait_ready 状态：若 out.ready 则表示下游准备好了，握手成功，可以发送数据并切换回空闲状态，准备接收新数据
    s_wait_ready -> Mux(io.out.ready, s_idle, s_wait_ready)
  ))

  io.out.bits.pc := outpc
  io.out.bits.inst := outinst
  
}

