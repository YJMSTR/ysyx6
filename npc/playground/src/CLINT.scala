import chisel3._ 
import chisel3.util._ 
import Configs._

class MyCLINT extends Module {
  val io = IO(new Bundle {
    val axi4 = new AXI4Interface
  })

  val empty_slave = Module(new empty_axi4_slave)
  io.axi4 <> empty_slave.io.axi4

  val r_idle :: r_wait_rready :: Nil = Enum(2)
  val r_state = RegInit(r_idle)

  val mtime_csr = RegInit(0.U((64).W))
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
  
  switch(r_state) {
    is(r_idle) {
      when(io.axi4.arvalid) {
        assert(io.axi4.araddr === RTC_ADDR.U || io.axi4.araddr === (RTC_ADDR+4).U)
        r_state := r_wait_rready
        rdata := Mux(io.axi4.araddr === RTC_ADDR.U, mtime_csr(31, 0), mtime_csr(63, 32))
      }
    }
    is(r_wait_rready) {
      when(io.axi4.rready) {
        r_state := r_idle
      }
    }
  }
}

