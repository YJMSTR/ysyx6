import chisel3._ 
import chisel3.util._ 
import Configs._

class IFUIn extends Bundle {
  val pc = UInt(XLEN.W)
  val isdnpc = Bool()
  val dnpc = UInt(XLEN.W)
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

  val s_idle :: s_wait_dnpc :: Nil = Enum(2)
  val state = RegInit(s_idle)
  val dnpc_reg = RegInit(0.U(XLEN.W))
  val valid_reg = RegInit(1.B)

  //借助状态机模型处理有跳转指令时的 io.out.valid，此时需要将 out.valid 置为 0 来等待 IFU 取回 dnpc。
  switch(state){
    is(s_idle){
      when(io.in.valid){
        when(io.in.bits.isdnpc){
          state := s_wait_dnpc
          dnpc_reg := io.in.bits.dnpc
          valid_reg := 0.B
        }
      }
    }
    is(s_wait_dnpc){
      when(fake_sram.io.axi4lite.rvalid){
        when(fake_sram.io.axi4lite.araddr === dnpc_reg) {
          valid_reg := 1.B  // 取回了跳转指令，此时 valid 才能为 1
          state := s_idle
        }.otherwise{
          valid_reg := 0.B
        }
      }
    }
  }

  //ar
  fake_sram.io.axi4lite.arvalid := io.in.valid
  fake_sram.io.axi4lite.araddr := io.in.bits.pc
  io.in.ready := fake_sram.io.axi4lite.arready
  //r
  fake_sram.io.axi4lite.rready := io.out.ready
  io.out.valid := fake_sram.io.axi4lite.rvalid & valid_reg
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

