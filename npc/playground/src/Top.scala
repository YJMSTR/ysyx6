import chisel3._
import chisel3.util._

class Top extends Module {
  val io = IO(new Bundle {
    // val clk = Input(Clock())
    // val rst = Input(Bool())
    val led  = Output(UInt(16.W))
  })
  val count = RegInit(0.U(32.W))
  val led = RegInit(1.U(16.W))

  when(count === 0.U) {
    led := Cat(led(14, 0), led(15))
  }
  count := Mux(count >= 5000000.U, 0.U, count+1.U)

  io.led := led
}
