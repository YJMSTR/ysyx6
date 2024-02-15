import chisel3._ 
import chisel3.util._ 
import Configs._



class AXI4LiteInterface extends Bundle {
  // AR 读地址
  val araddr = Input(UInt(32.W))
  val arvalid = Input(Bool())
  val arready = Output(Bool())
  // R 读数据
  val rdata = Output(UInt(XLEN.W))
  val rresp = Output(UInt(2.W))
  val rvalid = Output(Bool())
  val rready = Input(Bool())
  // AW 写地址
  val awaddr = Input(UInt(32.W))
  val awvalid = Input(Bool())
  val awready = Output(Bool())
  // W 写数据
  val wdata = Input(UInt(XLEN.W))
  val wstrb = Input(UInt((XLEN/8).W))
  val wvalid = Input(Bool())
  val wready = Output(Bool())
  // B 写回复
  val bresp = Output(UInt(2.W))
  val bvalid = Output(Bool())
  val bready = Input(Bool())
}

