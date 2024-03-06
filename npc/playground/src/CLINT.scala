import chisel3._ 
import chisel3.util._ 
import Configs._

class MyCLINT extends Module {
  val io = IO(new Bundle {
    val axi4lite = new AXI4LiteInterface
  })

  val r_idle :: r_wait_rready :: Nil = Enum(2)
  val r_state = RegInit(r_idle)

  val mtime_csr = RegInit(0.U(64.W))
  mtime_csr := mtime_csr + 1.U
  val rdata = RegInit(0.U(32.W))
  val rresp = RegInit(0.U(2.W))

  io.axi4lite.awready := false.B
  io.axi4lite.wready := false.B
  io.axi4lite.bvalid := false.B
  io.axi4lite.bresp := 0.U

  io.axi4lite.arready := r_state === r_idle
  io.axi4lite.rvalid := r_state === r_wait_rready
  io.axi4lite.rdata := rdata
  io.axi4lite.rresp := rresp

  switch(r_state) {
    is(r_idle) {
      when(io.axi4lite.arvalid) {
        r_state := r_wait_rready
        rdata := Mux(io.axi4lite.araddr === RTC_ADDR.U(XLEN.W), mtime_csr(31, 0), mtime_csr(63, 32))
      }
    }
    is(r_wait_rready) {
      when(io.axi4lite.rready) {
        r_state := r_idle
      }
    }
  }
}

