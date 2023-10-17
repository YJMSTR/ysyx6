import chisel3._
import chisel3.util._

class Top extends Module {
  val io = IO(new Bundle {
    val sel  = Input(UInt(3.W))
    val A    = Input(UInt(4.W))
    val B    = Input(UInt(4.W))
    val of   = Output(Bool())
    val ez   = Output(Bool())
    val c    = Output(Bool())
    val out  = Output(UInt(4.W))
  })
  io.of := 0.U
  io.ez := 0.U
  io.c := 0.U
  io.out := 0.U
  switch(io.sel) {
    is(0.U) {
      // 使用 +& 自动补到 5 位
      val sum = io.A +& io.B 
      io.of := (io.A(3) === io.B(3)) & (io.A(3) =/= sum(3))
      io.c := sum(4)
      io.out := sum(3, 0)
    }
    is(1.U) {
      val sum = io.A -& io.B
      io.of := (io.A(3) =/= io.B(3) & (io.A(3) === sum(3)))
      io.c := sum(4)
      io.out := sum(3, 0)
    }
    is(2.U) {
      io.out := ~io.A
    }
    is(3.U) {
      io.out := io.A & io.B
    }
    is(4.U) {
      io.out := io.A | io.B
    }
    is(5.U) {
      io.out := io.A ^ io.B 
    }
    is(6.U) {
      io.out := Mux(io.A.asSInt < io.B.asSInt, 1.U, 0.U)
    }
    is(7.U) {
      io.out := Mux(io.A === io.B, 1.U, 0.U)
    }
  } 
  when (io.out === 0.U) {
    io.ez := 1.U
  }
}
