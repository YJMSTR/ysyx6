import chisel3._ 
import chisel3.util._ 
import Configs._

class MyUART extends Module {
  val io = IO(new Bundle {
    val axi4lite = new AXI4LiteInterface
  })


  val w_idle :: w_wait_wvalid :: w_write :: w_wait_bready :: Nil = Enum(4)
  val w_state = RegInit(w_idle)

  val writeAddr = RegInit(0.U(32.W))
  val writeData = RegInit(0.U(XLEN.W))
  val writeStrb = RegInit(0.U((XLEN/8).W))
  val bresp = RegInit(0.U(2.W)) //default 0b00 === OKAY

  io.axi4lite.arready := 0.B 
  io.axi4lite.rvalid := 0.B 
  io.axi4lite.rdata := 0.U
  io.axi4lite.rresp := 0.U
  io.axi4lite.awready := w_state === w_idle
  io.axi4lite.wready := w_state === w_wait_wvalid
  io.axi4lite.bvalid := w_state === w_wait_bready
  io.axi4lite.bresp := bresp


  switch(w_state) {
    is(w_idle) {  // awready = 1
      when(io.axi4lite.awvalid) {
        w_state := w_wait_wvalid
        writeAddr := io.axi4lite.awaddr
      }
    }

    is(w_wait_wvalid) { // w_ready = 1
      when(io.axi4lite.wvalid) {
        writeData := io.axi4lite.wdata
        writeStrb := io.axi4lite.wstrb
        w_state := w_write
      }
    }

    is(w_write) {
      w_state := w_wait_bready
      printf("%c", writeData(7, 0))
    }

    is(w_wait_bready) { // b_valid = 1
      when(io.axi4lite.bready) {
        w_state := w_idle
      }
    }
  }

}