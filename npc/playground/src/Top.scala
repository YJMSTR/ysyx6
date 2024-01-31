import chisel3._
import chisel3.util._
import Configs._
import Instr._
import chisel3.util.experimental.loadMemoryFromFileInline
import chisel3.experimental.BundleLiterals._

object StageConnect {
  def apply[T <: Data](left: DecoupledIO[T], right: DecoupledIO[T], arch: String): Unit = {
    if      (arch == "single")   { right.bits := left.bits }
    else if (arch == "multi")    { right <> left }
    else if (arch == "pipeline") { right <> RegEnable(left, left.fire) }
    else if (arch == "ooo")      { right <> Queue(left, 16) }
  }
}

class IFUIn extends Bundle {
  val pc = Output(UInt(XLEN.W))
}

class IFUOut extends Bundle {
  val pc = Output(UInt(XLEN.W))
  val inst = Output(UInt(32.W))
}
// IDU_in 直接用 Flipped(Decouple(ifu_out))，其它同理
// 没有直接和下一阶段相连的信号就单独拉出来，不放在 in/out 里
class IDUOut extends Bundle {
  val inst = Output(UInt(32.W))
  val pc = Output(UInt(XLEN.W))
  val rs1 = Output(UInt(RIDXLEN.W))
  val rs2 = Output(UInt(RIDXLEN.W))
  val rs1v = Output(UInt(XLEN.W))
  val rs2v = Output(UInt(XLEN.W))
  val rd = Output(UInt(RIDXLEN.W))
  val rd_en = Output(Bool())
  val imm = Output(UInt(XLEN.W))
  
  val alu_sel_a = Output(UInt(ALU_DATASEL_WIDTH.W))
  val alu_sel_b = Output(UInt(ALU_DATASEL_WIDTH.W))
  val alu_op = Output(UInt(ALUCtrlWidth.W))

  val isEbreak = Output(Bool())
  val memvalid = Output(Bool())
  val memwen = Output(Bool())
  val memwmask = Output(UInt(WMASKLEN.W))
  val memsext = Output(UInt(MEM_SEXT_SEL_WIDTH.W))
  val isword = Output(Bool())
}

class EXUOut extends Bundle {
  val alu_res = Output(UInt(XLEN.W))
  val rs2v = Output(UInt(XLEN.W))
  val memvalid = Output(Bool())
  val memwen = Output(Bool())
  val memwmask = Output(UInt(WMASKLEN.W))
  val memsext = Output(UInt(MEM_SEXT_SEL_WIDTH.W))
  val isword = Output(Bool())
}

class LSUOut extends Bundle {
  // 经过符号位扩展的 rdata
  val sextrdata = Output(UInt(XLEN.W))

  // 此外还有一些控制信号，调试用的数据等要传给 wbu

}



class Top extends Module {
  val io = IO(new Bundle {
    val inst = Output(UInt(32.W))
    val pc = Output(UInt(XLEN.W))
  })
  
  // 寄存器堆
  // 其它模块可以通过 chisel 的参数化模块机制来跨模块访问寄存器堆的 IO 接口
  val R = Module(new REG)

  val ifu = Module(new IFU(R.io))
  val idu = Module(new IDU(R.io))
  val exu = Module(new EXU(R.io))
  val lsu = Module(new LSU(R.io))
  val wbu = Module(new WBU(R.io))

  StageConnect(ifu.io.out, idu.io.in)
  StageConnect(idu.io.out, exu.io.in)
  StageConnect(exu.io.out, lsu.io.in)
  StageConnect(lsu.io.out, wbu.io.in)


  val isdnpc = WireInit(0.B)
  val dnpc = WireInit(0.U(XLEN.W))
  val snpc = ifu.io.out.bits.pc + 4.U
  ifu.io.in.valid := reset.asBool =/= 1.B
  // 其实 SRAM 也有流水线，如果取回指令要 x 个周期，其实这 x 个周期内会读入新的 pc？
  // 目前实现的 SRAM IFU 是多周期非流水的，如果取回指令要一个周期，就阻塞一个周期再读入新 pc
  // 怎么阻塞？把取回的 inst 和对应的 pc 一起输出，并判断当前 pc 是否等于这个 pc,如果不是接着阻塞直到是为止
  // 通过把 out.valid 和 in.ready 拉低作为阻塞
  // 把 ifu.io.out.bits.pc + 4.U 作为 snpc
  // 目前 dnpc 的实现可能不太正确，先不管
  ifu.io.in.bits.pc := Mux(isdnpc, dnpc, snpc)
  // 先不考虑跳转指令，仅连接好流水线

  
  val R = Module(new REG)
  // 这里通过给 rs1 和 rs2 赋值来取得 rs1v 和 rs2v 的话，其它模块怎么办呢？
  // 五级流水仅 idu 读取寄存器值，其它模块通过 idu 传给流水段间寄存器的值来获取 rs1v 和 rs2v
  R.io.raddr1 := idu.io.out.rs1
  R.io.raddr2 := idu.io.out.rs2
  val rs1v = R.io.rdata1
  val rs2v = R.io.rdata2

  val pc_plus_imm = idu.io.out.pc + idu.io.out.imm

  // 与译码模块相关的数据线
  isdnpc := idu.io.isdnpc
  // dnpc 预执行，这里用到的 snpc 是用 ifu 输出的 pc + 4 算的，并不是当前跳转指令所对应的 pc，所以这里的 dnpc 也不对
  // 但是目前不考虑跳转指令，所以先不管
   dnpc := MuxCase(0.U, Array(
    (idu.io.out.bits.inst === JALR)  -> (rs1v + idu.io.out.bits.imm),
    (idu.io.out.bits.inst === JAL)   -> (pc_plus_imm),
    (idu.io.out.bits.inst === BEQ)   -> Mux(rs1v === rs2v, pc_plus_imm, snpc),
    (idu.io.out.bits.inst === BNE)   -> Mux(rs1v === rs2v, snpc, pc_plus_imm),
    (idu.io.out.bits.inst === BGE)   -> Mux(rs1v.asSInt >= rs2v.asSInt, pc_plus_imm, snpc),
    (idu.io.out.bits.inst === BGEU)  -> Mux(rs1v >= rs2v, pc_plus_imm, snpc),
    (idu.io.out.bits.inst === BLT)   -> Mux(rs1v.asSInt < rs2v.asSInt, pc_plus_imm, snpc),
    (idu.io.out.bits.inst === BLTU)  -> Mux(rs1v < rs2v, pc_plus_imm, snpc)
  ))
  // 此外 译码阶段还要判断是否有数据冒险
  // 当前指令是否要读取 rs1
  val rs1ren = idu.rrs1 && idu.io.out.bits.rs1 =/= 0.U && idu.io.in.valid
  // 当前指令是否要读取 rs2
  val rs2ren = idu.rrs2 && idu.io.out.bits.rs2 =/= 0.U && idu.io.in.valid
  val EX_RS1_Hazard = idu.io.out.rs1 === Mux(idu.io.out.valid, idu.io.out.bits.rd, 0.U) && idu.io.out.ready
  val EX_RS2_Hazard = idu.io.out.rs2 === Mux(idu.io.out.valid, idu.io.out.bits.rd, 0.U) && idu.io.out.ready
  val WB_RS1_Hazard = idu.io.out.rs1 === Mux(lsu.io.out.valid, lsu.io.out.bits.rd, 0.U) && lsu.io.in.ready
  val WB_RS2_Hazard = idu.io.out.rs2 === Mux(lsu.io.out.valid, lsu.io.out.bits.rd, 0.U) && lsu.io.in.ready
  val LS_RS1_Hazard = idu.io.out.rs1 === Mux(exu.io.out.valid, exu.io.out.bits.rd, 0.U) && exu.io.in.ready

  val Ebreak = Module(new DPIC_EBREAK)
  Ebreak.io.isEbreak := exu.io.in.isEbreak
  Ebreak.io.clk := clock
}

