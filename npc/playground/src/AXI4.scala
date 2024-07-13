import chisel3._ 
import chisel3.util._ 
import Configs._


// slave 视角
class AXI4LiteInterface extends Bundle {
  // AR 读地址
  val araddr = Input(UInt(32.W))
  val arvalid = Input(Bool())
  val arready = Output(Bool())
  // R 读数据
  val rdata = Output(UInt(64.W))
  val rresp = Output(UInt(2.W))
  val rvalid = Output(Bool())
  val rready = Input(Bool())
  // AW 写地址
  val awaddr = Input(UInt(32.W))
  val awvalid = Input(Bool())
  val awready = Output(Bool())
  // W 写数据
  val wdata = Input(UInt(64.W))
  val wstrb = Input(UInt((64/8).W))
  val wvalid = Input(Bool())
  val wready = Output(Bool())
  // B 写回复
  val bresp = Output(UInt(2.W))
  val bvalid = Output(Bool())
  val bready = Input(Bool())
}
// slave 视角
class AXI4Interface extends Bundle {
  // AR 读地址
  val araddr = Input(UInt(32.W))
  val arvalid = Input(Bool())
  val arready = Output(Bool())
  val arid = Input(UInt(4.W))
  val arlen = Input(UInt(8.W))
  val arsize = Input(UInt(3.W))
  val arburst = Input(UInt(2.W))
  // R 读数据
  val rdata = Output(UInt(64.W))
  val rresp = Output(UInt(2.W))
  val rvalid = Output(Bool())
  val rready = Input(Bool())
  val rlast = Output(Bool())
  val rid = Output(UInt(4.W))
  // AW 写地址
  val awaddr = Input(UInt(32.W))
  val awvalid = Input(Bool())
  val awready = Output(Bool())
  val awid = Input(UInt(4.W))
  val awlen = Input(UInt(8.W))
  val awsize = Input(UInt(3.W))
  val awburst = Input(UInt(2.W))
  // W 写数据
  val wdata = Input(UInt(64.W))
  val wstrb = Input(UInt((64/8).W))
  val wvalid = Input(Bool())
  val wready = Output(Bool())
  val wlast = Input(Bool())
  // B 写回复
  val bresp = Output(UInt(2.W))
  val bvalid = Output(Bool())
  val bready = Input(Bool())
  val bid = Output(UInt(4.W))
}
