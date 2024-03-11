import chisel3._
import chisel3.util._

class ysyx_23060110_Hex7seg extends Module {
  val io = IO(new Bundle {
    val data = Input(UInt(4.W))
    val seg  = Output(UInt(7.W))
  })
  io.seg := "b0000000".U
  switch(io.data) {
    is (0.U) {
      io.seg := "b0000001".U
    }
    is (1.U) {
      io.seg := "b1001111".U
    }
    is (2.U) {
      io.seg := "b0010010".U 
    }
    is (3.U) {
      io.seg := "b0000110".U 
    }
    is (4.U) {
      io.seg := "b1001100".U 
    }
    is (5.U) {
      io.seg := "b0100100".U 
    }
    is (6.U) {
      io.seg := "b0100000".U
    }
    is (7.U) {
      io.seg := "b0001111".U
    }
    is (8.U) {
      io.seg := "b0000000".U
    }
    is (9.U) {
      io.seg := "b0000100".U
    }
    is (10.U) {
      io.seg := "b0001000".U
    }
    is (11.U) {
      io.seg := "b1100000".U
    }
    is (12.U) {
      io.seg := "b0110001".U
    }
    is (13.U) {
      io.seg := "b1000010".U
    }
    is (14.U) {
      io.seg := "b0110000".U
    }
    is (15.U) {
      io.seg := "b0111000".U
    }
  }
}