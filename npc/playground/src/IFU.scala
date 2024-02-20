import chisel3._ 
import chisel3.util._ 
import Configs._

class IFUIn extends Bundle {
  val pc = UInt(XLEN.W)
  val isdnpc = Bool()
}

class IFUOut extends Bundle {
  val pc = UInt(XLEN.W)
  val inst = UInt(32.W)
}

class IFU extends Module {
  val io = IO(new Bundle {
    val in = Flipped(Decoupled(new IFUIn))
    val out = Decoupled(new IFUOut)
  })

  val fake_sram = Module(new FAKE_SRAM_IFU(1.U))
  val readAddr = RegInit(0.U(32.W))

  // fake_sram.io.isdnpc := io.in.bits.isdnpc

  //ar
  fake_sram.io.axi4lite.arvalid := io.in.valid
  fake_sram.io.axi4lite.araddr := io.in.bits.pc
  io.in.ready := fake_sram.io.axi4lite.arready
  //r
  fake_sram.io.axi4lite.rready := io.out.ready
  io.out.valid := fake_sram.io.axi4lite.rvalid & (io.in.bits.isdnpc === 0.B)
  io.out.bits.pc := readAddr
  io.out.bits.inst := fake_sram.io.axi4lite.rdata
  //aw
  fake_sram.io.axi4lite.awvalid := 0.B
  fake_sram.io.axi4lite.awaddr := 0.U
  //w
  fake_sram.io.axi4lite.wvalid := 0.B
  fake_sram.io.axi4lite.wdata := 0.U
  fake_sram.io.axi4lite.wstrb := 0.U
  //b
  fake_sram.io.axi4lite.bready := 0.B
  when(fake_sram.io.axi4lite.arvalid && fake_sram.io.axi4lite.arready) {
    readAddr := fake_sram.io.axi4lite.araddr
    // 如果 ar channel 握手成功，存一下地址等到输出的时候用
  }

}

