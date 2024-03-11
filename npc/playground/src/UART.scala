import chisel3._ 
import chisel3.util._ 
import Configs._

class ysyx_23060110_UART extends Module {
  val io = IO(new Bundle {
    val axi4full = new AXI4FullInterface
  })


  val w_idle :: w_wait_wvalid :: w_write :: w_wait_bready :: Nil = Enum(4)
  val w_state = RegInit(w_idle)

  val writeAddr = RegInit(0.U(32.W))
  val writeData = RegInit(0.U(XLEN.W))
  val writeStrb = RegInit(0.U((XLEN/8).W))
  val bresp = RegInit(0.U(2.W)) //default 0b00 === OKAY

  io.axi4full.arready := 0.B 
  io.axi4full.rvalid := 0.B 
  io.axi4full.rdata := 0.U
  io.axi4full.rresp := 0.U
  io.axi4full.awready := w_state === w_idle
  io.axi4full.wready := w_state === w_wait_wvalid
  io.axi4full.bvalid := w_state === w_wait_bready
  io.axi4full.bresp := bresp


  switch(w_state) {
    is(w_idle) {  // awready = 1
      when(io.axi4full.awvalid) {
        w_state := w_wait_wvalid
        writeAddr := io.axi4full.awaddr
      }
    }

    is(w_wait_wvalid) { // w_ready = 1
      when(io.axi4full.wvalid) {
        writeData := io.axi4full.wdata
        writeStrb := io.axi4full.wstrb
        w_state := w_write
      }
    }

    is(w_write) {
      w_state := w_wait_bready
      printf("%c", writeData(7, 0))
    }

    is(w_wait_bready) { // b_valid = 1
      when(io.axi4full.bready) {
        w_state := w_idle
      }
    }
  }

}