import chisel3._ 
import chisel3.util._ 
import Configs._

class ysyx_23060110_MyUART extends Module {
  val io = IO(new Bundle {
    val axi4 = new AXI4Interface
  })


  val w_idle :: w_wait_wvalid :: w_write :: w_wait_bready :: Nil = Enum(4)
  val w_state = RegInit(w_idle)

  val writeAddr = RegInit(0.U(32.W))
  val writeData = RegInit(0.U(XLEN.W))
  val writeStrb = RegInit(0.U((XLEN/8).W))
  val bresp = RegInit(0.U(2.W)) //default 0b00 === OKAY

  io.axi4.arready := 0.B 
  io.axi4.rvalid := 0.B 
  io.axi4.rdata := 0.U
  io.axi4.rresp := 0.U
  io.axi4.awready := w_state === w_idle
  io.axi4.wready := w_state === w_wait_wvalid
  io.axi4.bvalid := w_state === w_wait_bready
  io.axi4.bresp := bresp


  switch(w_state) {
    is(w_idle) {  // awready = 1
      when(io.axi4.awvalid) {
        w_state := w_wait_wvalid
        writeAddr := io.axi4.awaddr
      }
    }

    is(w_wait_wvalid) { // w_ready = 1
      when(io.axi4.wvalid) {
        writeData := io.axi4.wdata
        writeStrb := io.axi4.wstrb
        w_state := w_write
      }
    }

    is(w_write) {
      w_state := w_wait_bready
      printf("%c", writeData(7, 0))
    }

    is(w_wait_bready) { // b_valid = 1
      when(io.axi4.bready) {
        w_state := w_idle
      }
    }
  }

}