import chisel3._ 
import chisel3.util._ 
import Configs._

class IFUIn extends Bundle {
  //val pc = UInt(XLEN.W)
  // 注意：Decoder 传出的 isdnpc 信号仅仅用于标识当前指令是否为跳转指令，并不一定真的会跳转。 
  // 改一下 IFU 传入的 isdnpc，改成真的要跳转时才能为真
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

  val PC = RegInit(RESET_VECTOR.U(XLEN.W))
  val fake_sram = Module(new FAKE_SRAM_IFU(1.U))
  val readAddr = RegInit(0.U(32.W))
  val outAddr = RegInit(0.U(32.W))
  val outData = RegInit(0.U(32.W))

  // fake_sram.io.isdnpc := io.in.bits.isdnpc

  val s_idle :: s_wait_arready :: s_wait_rvalid :: Nil = Enum(3)
  val state = RegInit(s_idle)

  fake_sram.io.axi4lite.arvalid := state === s_wait_arready
  fake_sram.io.axi4lite.rready := state === s_wait_rvalid
  fake_sram.io.axi4lite.araddr := readAddr

  fake_sram.io.axi4lite.awaddr := 0.U
  fake_sram.io.axi4lite.awvalid := 0.B
  fake_sram.io.axi4lite.wdata := 0.U
  fake_sram.io.axi4lite.wstrb := 0.U
  fake_sram.io.axi4lite.wvalid := 0.U
  fake_sram.io.axi4lite.bready := 0.U
  
  val dnpc_idle :: dnpc_wait_ready :: dnpc_wait :: Nil = Enum(3)
  val dnpc_state = RegInit(dnpc_idle)
  val dnpc_reg = RegInit(0.U(XLEN.W))
  val dnpc_valid = RegInit(1.B)

  //注意：当 arvalid 为 1 后， araddr 就不能变了，直到握手成功，因此需要用寄存器存一下
  switch(state){
    is(s_idle){ // io.in.valid 恒为 1，因此此处不进行判断
      // arvalid := state === s_wait_arready
      when (io.out.ready) {
        // 如果成功输出了，再转移状态 + 接收输入。
        readAddr := PC
        state := s_wait_arready
      }
    }
    is(s_wait_arready){ // 此时 arvalid 为 true
      when(fake_sram.io.axi4lite.arready){
        // 读地址通道握手成功，等待 rvalid.
        PC := Mux(dnpc_valid, PC + 4.U, dnpc_reg)
        // 切换到 wait_rvalid 状态，即将 rready 置为 1 
        state := s_wait_rvalid
      }
    }
    is(s_wait_rvalid){  // 保持数据，等待输出
      when(fake_sram.io.axi4lite.rvalid){
        state := s_idle
        outData := fake_sram.io.axi4lite.rdata
        outAddr := readAddr
      }
    }
  }
  

  when(dnpc_valid) {
    when (io.in.bits.isdnpc & io.in.valid) {
      dnpc_valid := 0.B // 这个修改要延迟一个周期才会生效，但此时可能已经有指令被取出准备输出了
      // 可以给 io.out.valid 加一个条件，如果当前 in.isdnpc = 1,那么这个周期要把 valid 置为 0
      // 这样就解决了寄存器要延迟一个周期写入的问题
      dnpc_reg := io.in.bits.dnpc
    }
  } .otherwise {
    dnpc_valid := dnpc_reg === outAddr
  }

  io.out.valid := state === s_idle && dnpc_valid && !io.in.bits.isdnpc
  io.out.bits.pc := readAddr
  io.out.bits.inst := outData
  io.in.ready := fake_sram.io.axi4lite.arready & io.out.ready
}
