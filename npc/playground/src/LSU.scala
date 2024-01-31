import chisel3._ 
import chisel3.util._ 
import Configs._

class LSU(regFileIO: RegFileIO) extends Module {
  val io = IO(new Bundle {
    val in = Flipped(Decoupled(new EXUOut))
    val out = Decoupled(new LSUOut)
  })
  // 暂时先只给 IFU 加延迟, mem 还是组合逻辑
  val dpic_mem = Module(new DPIC_MEM)
  dpic_mem.io.valid := io.memvalid
  dpic_mem.io.wen := io.in.bits.memwen
  dpic_mem.io.raddr := io.in.bits.alu_res
  dpic_mem.io.waddr := io.in.bits.alu_res
  // rs2v 是要写入的数据，alu_res 是要写入/读取的地址
  dpic_mem.io.wdata := io.in.bits.rs2v
  dpic_mem.io.wmask := io.in.bits.memwmask
  dpic_mem.io.clk := clock

  // 暂时先没有延迟
  val rdata = dpic_mem.io.rdata

  io.out.bits.sextrdata := MuxLookup(io.in.bits.memsext, rdata, Seq(
    MEM_NSEXT_8 ->  Cat(Fill(XLEN-8, 0.U), .rdata(7, 0)),
    MEM_NSEXT_16->  Cat(Fill(XLEN-16, 0.U), rdata(15, 0)),
    MEM_NSEXT_32->  Cat(Fill(XLEN-32, 0.U), rdata(31, 0)),
    MEM_SEXT_8  ->  Cat(Fill(XLEN-8, rdata(7)), rdata(7, 0)),
    MEM_SEXT_16 ->  Cat(Fill(XLEN-16, rdata(15)), rdata(15, 0)),
    MEM_SEXT_32 ->  Cat(Fill(XLEN-32, rdata(31)), rdata(31, 0)),
  ))
}

