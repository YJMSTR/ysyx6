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

  val fake_sram = Module(new FAKE_SRAM)
  val axi4lite = Module(new AXI4LiteInterface)
  axi4lite <> fake_sram.io.axi4lite

  val mem_state = RegInit(s_idle)
  val mem_idle :: mem_

  

}

