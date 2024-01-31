import chisel3._ 
import chisel3.util._ 
import Configs._

class WBU(regFileIO: RegFileIO) extends Module {
  val io = IO(new Bundle {
    val in = Flipped(Decoupled(new LSUOut))
    val out = Decoupled(new WBUOut)
  })
}

