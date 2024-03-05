import chisel3._
import chisel3.util._
import Configs._ 

class XBar extends Module {
  val io = IO(new Bundle {
    val axi4litein = new AXI4LiteInterface
    val axi4liteout0 = Flipped(new AXI4LiteInterface)
    val axi4liteout1 = Flipped(new AXI4LiteInterface)
  })
  // out(0): uart
  // out(1): sram
  val empty_slave_in0 = Module(new empty_axi4lite_master)
  val empty_slave_in1 = Module(new empty_axi4lite_master)
  
  io.axi4liteout0 <> empty_slave_in0.io.axi4lite
  io.axi4liteout1 <> empty_slave_in1.io.axi4lite

  val araddr = RegInit(0.U(XLEN.W))

  when (araddr === SERIAL_PORT.U(XLEN.W)) {
    io.axi4liteout0 <> io.axi4litein
    io.axi4liteout1 <> empty_slave_in1.io.axi4lite
  }.otherwise {
    io.axi4liteout1 <> io.axi4litein
    io.axi4liteout0 <> empty_slave_in0.io.axi4lite
  }
}

