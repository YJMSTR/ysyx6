import chisel3._ 
import chisel3.util._ 
import Configs._

class ysyx_23060110_empty_axi4lite_slave extends Module {
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

class ysyx_23060110_empty_axi4lite_master extends Module {
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

class ysyx_23060110_empty_axi4full_slave extends Module {
  val io = IO(new Bundle{
    val axi4full = new AXI4FullInterface
  })
  io.axi4full.arready := RegInit(0.U)
  io.axi4full.rvalid :=  RegInit(0.U)
  io.axi4full.rdata :=   RegInit(0.U)
  io.axi4full.rresp :=   RegInit(0.U)
  io.axi4full.rlast :=   RegInit(0.U)
  io.axi4full.rid   :=   RegInit(0.U)
  io.axi4full.awready := RegInit(0.U) 
  io.axi4full.wready :=  RegInit(0.U) 
  io.axi4full.bresp :=   RegInit(0.U)
  io.axi4full.bvalid :=  RegInit(0.U)
  io.axi4full.bid :=     RegInit(0.U)
}

class ysyx_23060110_empty_axi4full_master extends Module {
  val io = IO(new Bundle {
    val axi4full = Flipped(new AXI4FullInterface)
  })

  io.axi4full.araddr :=   RegInit(0.U)
  io.axi4full.arvalid :=  RegInit(0.U) 
  io.axi4full.arid :=     RegInit(0.U)
  io.axi4full.arlen :=    RegInit(0.U)
  io.axi4full.arsize :=   RegInit(0.U)
  io.axi4full.arburst :=  RegInit(0.U)
  io.axi4full.rready :=   RegInit(0.U) 
  io.axi4full.awaddr :=   RegInit(0.U)
  io.axi4full.awvalid :=  RegInit(0.U)
  io.axi4full.awid :=     RegInit(0.U)
  io.axi4full.awlen :=    RegInit(0.U)
  io.axi4full.awsize :=   RegInit(0.U)
  io.axi4full.awburst :=  RegInit(0.U)
  io.axi4full.wdata :=    RegInit(0.U)
  io.axi4full.wstrb :=    RegInit(0.U) 
  io.axi4full.wvalid :=   RegInit(0.U)
  io.axi4full.wlast :=    RegInit(0.U)
  io.axi4full.bready :=   RegInit(0.U)
}

