import chisel3._
import chisel3.util._

class Top extends Module {
  val io = IO(new Bundle {
    val clk = Input(Clock())
    val rst = Input(Bool())
    val out = Output(UInt(8.W))
    val seg0 = Output(UInt(7.W))
    val seg1 = Output(UInt(7.W))
  })
  io.seg0 := "b1111111".U 
  io.seg1 := "b1111111".U
  withClockAndReset(io.clk, io.rst) {
    val count = RegInit(1.U(8.W))
    count := ((count(4) ^ count(3) ^ count(2) ^ count(0)) << 7) | (count >> 1)
    io.out := count 
    val hexs = VecInit(Seq.fill(2)(Module(new Hex7sec).io))
    hexs(0).data := count(3, 0)
    hexs(1).data := count(7, 4)
    io.seg0 := hexs(0).seg
    io.seg1 := hexs(1).seg
  }
}
