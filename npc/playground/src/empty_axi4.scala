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

class empty_axi4_slave extends Module {
  val io = IO(new Bundle{
    val axi4 = new AXI4Interface
  })
  io.axi4.arready := RegInit(0.U)
  io.axi4.rvalid :=  RegInit(0.U)
  io.axi4.rdata :=   RegInit(0.U)
  io.axi4.rresp :=   RegInit(0.U)
  io.axi4.rlast :=   RegInit(0.U)
  io.axi4.rid   :=   RegInit(0.U)
  io.axi4.awready := RegInit(0.U) 
  io.axi4.wready :=  RegInit(0.U) 
  io.axi4.bresp :=   RegInit(0.U)
  io.axi4.bvalid :=  RegInit(0.U)
  io.axi4.bid :=     RegInit(0.U)
}

class empty_axi4_master extends Module {
  val io = IO(new Bundle {
    val axi4 = Flipped(new AXI4Interface)
  })

  io.axi4.araddr :=   RegInit(0.U)
  io.axi4.arvalid :=  RegInit(0.U) 
  io.axi4.arid :=     RegInit(0.U)
  io.axi4.arlen :=    RegInit(0.U)
  io.axi4.arsize :=   RegInit(0.U)
  io.axi4.arburst :=  RegInit(0.U)
  io.axi4.rready :=   RegInit(0.U) 
  io.axi4.awaddr :=   RegInit(0.U)
  io.axi4.awvalid :=  RegInit(0.U)
  io.axi4.awid :=     RegInit(0.U)
  io.axi4.awlen :=    RegInit(0.U)
  io.axi4.awsize :=   RegInit(0.U)
  io.axi4.awburst :=  RegInit(0.U)
  io.axi4.wdata :=    RegInit(0.U)
  io.axi4.wstrb :=    RegInit(0.U) 
  io.axi4.wvalid :=   RegInit(0.U)
  io.axi4.wlast :=    RegInit(0.U)
  io.axi4.bready :=   RegInit(0.U)
}