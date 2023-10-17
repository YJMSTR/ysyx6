import chisel3._
import chisel3.util._

class Top extends Module {
  val io = IO(new Bundle {
    val data = Input(Vec(8, Bool()))
    val Y    = Output(Bool())
    val out  = Output(UInt(3.W))
    val seg0 = Output(UInt(7.W))
  })
  val tmp = io.data.asUInt
  io.Y   := tmp.orR
  val encoded = Wire(UInt(3.W))
  encoded := 0.U
  for (i <- 0 until 8) {
    when (io.data(i)) {
      encoded := i.U 
    }
  }
  io.seg0 := "b1111111".U
  switch (encoded) {
    is (0.U) {
      io.seg0 := "b0000001".U
    }
    is (1.U) {
      io.seg0 := "b1001111".U
    }
    is (2.U) {
      io.seg0 := "b0010010".U 
    }
    is (3.U) {
      io.seg0 := "b0000110".U 
    }
    is (4.U) {
      io.seg0 := "b1001100".U 
    }
    is (5.U) {
      io.seg0 := "b0100100".U 
    }
    is (6.U) {
      io.seg0 := "b0100000".U
    }
    is (7.U) {
      io.seg0 := "b0001111".U
    }
  }
  io.out := encoded
}
