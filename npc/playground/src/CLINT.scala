import chisel3._ 
import chisel3.util._ 
import Configs._

class ysyx_23060110_MyCLINT extends Module {
  val io = IO(new Bundle {
    val axi4 = new AXI4Interface
  })

  val r_idle :: r_wait_rready :: Nil = Enum(2)
  val r_state = RegInit(r_idle)

  val mtime_csr = RegInit(0.U(64.W))
  mtime_csr := mtime_csr + 1.U
  val rdata = RegInit(0.U(32.W))
  val rresp = RegInit(0.U(2.W))

  io.axi4.awready := false.B
  io.axi4.wready := false.B
  io.axi4.bvalid := false.B
  io.axi4.bresp := 0.U

  io.axi4.arready := r_state === r_idle
  io.axi4.rvalid := r_state === r_wait_rready
  io.axi4.rdata := rdata
  io.axi4.rresp := rresp
  io.axi4.rlast := 0.U
  io.axi4.rid := 0.U 
  io.axi4.bid := 0.U 

  switch(r_state) {
    is(r_idle) {
      when(io.axi4.arvalid) {
        r_state := r_wait_rready
        rdata := Mux(io.axi4.araddr === RTC_ADDR.U(XLEN.W), mtime_csr(31, 0), mtime_csr(63, 32))
      }
    }
    is(r_wait_rready) {
      when(io.axi4.rready) {
        r_state := r_idle
      }
    }
  }
}

