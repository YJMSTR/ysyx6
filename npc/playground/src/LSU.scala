
import chisel3._ 
import chisel3.util._ 
import Configs._

class LSUIn extends Bundle {
  val wen = Bool()
  val raddr = UInt(32.W)
  val waddr = UInt(32.W)
  val wdata = UInt(XLEN.W)
  val wmask = UInt(XLEN.W)
}

class LSUOut extends Bundle {
  val rdata = UInt(XLEN.W)
}

class LSU extends Module {
  val io = IO(new Bundle {
    val in = Flipped(Decoupled(new LSUIn))
    val out = Decoupled(new LSUOut)
  })
  val dpic_mem = Module(new DPIC_MEM)
  io.in.ready := 1.B
  dpic_mem.io.valid := io.in.valid
  dpic_mem.io.wen := io.in.bits.wen
  dpic_mem.io.raddr := io.in.bits.raddr
  dpic_mem.io.waddr := io.in.bits.waddr
  dpic_mem.io.wdata := io.in.bits.wdata
  dpic_mem.io.wmask := io.in.bits.wmask
  dpic_mem.io.clk := clock
  io.out.valid := RegNext(io.in.valid, 0.B)
  // 手动模拟 1 周期的 SRAM 延迟，仅读取有延迟
  io.out.bits.rdata := RegNext(dpic_mem.io.rdata, 0.U)
  // io.out.bits.rdata := 0.U
}

// class LSU extends Module {
//   val io = IO(new Bundle {
//     val in = Flipped(Decoupled(new LSUIn))
//     val out = Decoupled(new LSUOut)
//   })


//   val fake_sram = Module(new FAKE_SRAM_LSU(1.U))
//   val readAddr = RegInit(0.U(32.W))

//   fake_sram.io.axi4lite.arvalid := io.in.valid & !io.in.bits.wen
//   fake_sram.io.axi4lite.araddr := io.in.bits.raddr
//   io.in.ready := fake_sram.io.axi4lite.arready

//   // 等待读出数据并写回寄存器，
//   val s_idle :: s_wait_read :: s_wait_wb :: Nil = Enum(3)
//   val state = RegInit(s_idle)
  
//   switch(state) {
//     is(s_idle) {
//       // 如果读取数据有效，进入等待读取状态，直到
//       when(fake_sram.io.axi4lite.arvalid) {
//         state := s_wait_read
//       }
//     }
//   }
// }

