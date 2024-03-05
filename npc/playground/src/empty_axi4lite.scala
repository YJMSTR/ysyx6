import chisel3._ 
import chisel3.util._ 
import Configs._

class empty_axi4lite_slave extends Module {
  val io = IO(new Bundle{
    val axi4lite = new AXI4LiteInterface
  })
  io.axi4lite.arready := RegInit(0.U)
  io.axi4lite.rvalid :=  RegInit(0.U)
  io.axi4lite.rdata :=   RegInit(0.U)
  io.axi4lite.rresp :=   RegInit(0.U)
  io.axi4lite.awready := RegInit(0.U) 
  io.axi4lite.wready :=  RegInit(0.U) 
  io.axi4lite.bresp :=   RegInit(0.U)
  io.axi4lite.bvalid :=  RegInit(0.U)
}

class empty_axi4lite_master extends Module {
  val io = IO(new Bundle {
    val axi4lite = Flipped(new AXI4LiteInterface)
  })

  io.axi4lite.araddr :=   RegInit(0.U)
  io.axi4lite.arvalid :=  RegInit(0.U) 
  io.axi4lite.rready :=   RegInit(0.U) 
  io.axi4lite.awaddr :=   RegInit(0.U)
  io.axi4lite.awvalid :=  RegInit(0.U)
  io.axi4lite.wdata :=    RegInit(0.U)
  io.axi4lite.wstrb :=    RegInit(0.U) 
  io.axi4lite.wvalid :=   RegInit(0.U) 
  io.axi4lite.bready :=   RegInit(0.U)
}