import chisel3._ 
import chisel3.util._ 
import Configs._

class ysyx_23060110_CLINT extends Module {
  val io = IO(new Bundle {
    val axi4full = new AXI4FullInterface
  })

  val empty_slave = Module(new ysyx_23060110_empty_axi4full_slave)
  io.axi4full <> empty_slave.io.axi4full

  val r_idle :: r_wait_rready :: Nil = Enum(2)
  val r_state = RegInit(r_idle)

  val mtime_csr = RegInit(0.U(64.W))
  mtime_csr := mtime_csr + 1.U
  val rdata = RegInit(0.U(32.W))
  val rresp = RegInit(0.U(2.W))

  io.axi4full.awready := false.B
  io.axi4full.wready := false.B
  io.axi4full.bvalid := false.B
  io.axi4full.bresp := 0.U

  io.axi4full.arready := r_state === r_idle
  io.axi4full.rvalid := r_state === r_wait_rready
  io.axi4full.rdata := rdata
  io.axi4full.rresp := rresp

  switch(r_state) {
    is(r_idle) {
      when(io.axi4full.arvalid) {
        r_state := r_wait_rready
        rdata := Mux(io.axi4full.araddr === RTC_ADDR.U(XLEN.W), mtime_csr(31, 0), mtime_csr(63, 32))
      }
    }
    is(r_wait_rready) {
      when(io.axi4full.rready) {
        r_state := r_idle
      }
    }
  }
}

