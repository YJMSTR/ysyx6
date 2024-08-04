import chisel3._
import chisel3.util._

object Seg7ToHex {
  def apply(seg: UInt) = {
    val s = new Seg7ToHex(seg)
    s.data
  }
}

class Seg7ToHex (seg: UInt) {
    val data = MuxLookup(seg, 0.U)(Seq(
      "b0000001".U -> RegInit(0.U(4.W)),
      "b1001111".U -> RegInit(1.U(4.W)),
      "b0010010".U -> RegInit(2.U(4.W)),
      "b0000110".U -> RegInit(3.U(4.W)),
      "b1001100".U -> RegInit(4.U(4.W)),
      "b0100100".U -> RegInit(5.U(4.W)),
      "b0100000".U -> RegInit(6.U(4.W)),
      "b0001111".U -> RegInit(7.U(4.W)),
      "b0000000".U -> RegInit(8.U(4.W)),
      "b0000100".U -> RegInit(9.U(4.W)),
      "b0001000".U -> RegInit(10.U(4.W)),
      "b1100000".U -> RegInit(11.U(4.W)),
      "b0110001".U -> RegInit(12.U(4.W)),
      "b1000010".U -> RegInit(13.U(4.W)),
      "b0110000".U -> RegInit(14.U(4.W)),
      "b0111000".U -> RegInit(15.U(4.W))
    ))
}

object HexToSeg7 {
  def apply(hex: UInt) = {
    val s = new HexToSeg7(hex)
    s.data
  }
}

class HexToSeg7 (hex: UInt) {
  val data = MuxLookup(hex, 0.U)(Seq(
    0.U   -> RegInit("b0000001".U(7.W)),
    1.U   -> RegInit("b1001111".U(7.W)),
    2.U   -> RegInit("b0010010".U(7.W)),
    3.U   -> RegInit("b0000110".U(7.W)),
    4.U   -> RegInit("b1001100".U(7.W)),
    5.U   -> RegInit("b0100100".U(7.W)),
    6.U   -> RegInit("b0100000".U(7.W)),
    7.U   -> RegInit("b0001111".U(7.W)),
    8.U   -> RegInit("b0000000".U(7.W)),
    9.U   -> RegInit("b0000100".U(7.W)),
    10.U  -> RegInit("b0001000".U(7.W)),
    11.U  -> RegInit("b1100000".U(7.W)),
    12.U  -> RegInit("b0110001".U(7.W)),
    13.U  -> RegInit("b1000010".U(7.W)),
    14.U  -> RegInit("b0110000".U(7.W)),
    15.U  -> RegInit("b0111000".U(7.W))
  ))
}

