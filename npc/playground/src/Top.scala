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
    switch (count(3, 0)) {
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
      is (8.U) {
        io.seg0 := "b0000000".U
      }
      is (9.U) {
        io.seg0 := "b0000100".U
      }
      is (10.U) {
        io.seg0 := "b0001000".U
      }
      is (11.U) {
        io.seg0 := "b1100000".U
      }
      is (12.U) {
        io.seg0 := "b0110001".U
      }
      is (13.U) {
        io.seg0 := "b1000010".U
      }
      is (14.U) {
        io.seg0 := "b0110000".U
      }
      is (15.U) {
        io.seg0 := "b0111000".U
      }
    }
    switch (count(7, 4)) {
      is (0.U) {
        io.seg1 := "b0000001".U
      }
      is (1.U) {
        io.seg1 := "b1001111".U
      }
      is (2.U) {
        io.seg1 := "b0010010".U 
      }
      is (3.U) {
        io.seg1 := "b0000110".U 
      }
      is (4.U) {
        io.seg1 := "b1001100".U 
      }
      is (5.U) {
        io.seg1 := "b0100100".U 
      }
      is (6.U) {
        io.seg1 := "b0100000".U
      }
      is (7.U) {
        io.seg1 := "b0001111".U
      }
      is (8.U) {
        io.seg1 := "b0000000".U
      }
      is (9.U) {
        io.seg1 := "b0000100".U
      }
      is (10.U) {
        io.seg1 := "b0001000".U
      }
      is (11.U) {
        io.seg1 := "b1100000".U
      }
      is (12.U) {
        io.seg1 := "b0110001".U
      }
      is (13.U) {
        io.seg1 := "b1000010".U
      }
      is (14.U) {
        io.seg1 := "b0110000".U
      }
      is (15.U) {
        io.seg1 := "b0111000".U
      }
    }
  }
}
