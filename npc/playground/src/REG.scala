import chisel3._
import chisel3.util._
import Configs._
// 2 读 1 写的 RegFile
class RegFileIO extends Bundle {
  val raddr1 = Input(UInt(5.W))
  val raddr2 = Input(UInt(5.W))
  val rdata1 = Output(UInt(XLEN.W))
  val rdata2 = Output(UInt(XLEN.W))
  val wen = Input(Bool())
  val waddr = Input(UInt(5.W))
  val wdata = Input(UInt(XLEN.W))
}

class RegFile extends Module {
  val io = IO(new RegFileIO) 
  val mem = Mem(32, UInt(XLEN.W))

  when (io.wen) {
    mem(io.waddr) := io.wdata
  }
  io.rdata1 := mem(io.raddr1)
  io.rdata2 := mem(io.raddr2)
}

