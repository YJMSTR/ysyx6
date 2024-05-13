import chisel3._ 
import chisel3.util._ 
import Configs._

class IFUIn extends Bundle {
  //val pc = UInt(XLEN.W)
  // 注意：Decoder 传出的 isdnpc 信号仅仅用于标识当前指令是否为跳转指令，并不一定真的会跳转。 
  // 改一下 IFU 传入的 isdnpc，改成真的要跳转时才能为真
  val stall = Bool()
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
    val axi4_to_arbiter = Flipped(new AXI4Interface)
    val bus_ac = Input(Bool())
    val bus_reqr = Output(Bool())
    val bus_reqw = Output(Bool())
  })

  // val s_idle :: s_wait_arready :: s_wait_rvalid :: Nil = Enum(3)
  val s_idle :: s_cache_reqr :: s_cache_return :: Nil = Enum(3)
  val state = RegInit(s_idle)

  // io.bus_reqw := 0.B // ifu 没有写操作
  // val reqr = RegInit(0.B)
  // io.bus_reqr := reqr

  val PC = RegInit(RESET_VECTOR.U(XLEN.W))
  val readAddr = RegInit(0.U(32.W))
  val outAddr = RegInit(0.U(32.W))
  val outData = RegInit(0.U(32.W))

  val icache = Module(new ICache(4096, 8, 32))
  icache.io.axi4 <> io.axi4_to_arbiter
  icache.io.bus_ac := io.bus_ac
  icache.io.io.addr_valid := state === s_cache_reqr
  icache.io.io.addr := readAddr
  icache.io.io.data_ready := state === s_cache_return
  icache.io.stall := io.in.bits.stall
  io.bus_reqr := icache.io.bus_reqr
  io.bus_reqw := icache.io.bus_reqw

  // io.axi4_to_arbiter.arvalid := state === s_wait_arready && reset.asBool === 0.B
  // io.axi4_to_arbiter.rready := state === s_wait_rvalid && reset.asBool === 0.B
  // io.axi4_to_arbiter.araddr := readAddr
  // io.axi4_to_arbiter.awaddr := 0.U
  // io.axi4_to_arbiter.awvalid := 0.B
  // io.axi4_to_arbiter.wdata := 0.U
  // io.axi4_to_arbiter.wstrb := 0.U
  // io.axi4_to_arbiter.wvalid := 0.U
  // io.axi4_to_arbiter.bready := 0.U
  
  val dnpc_idle :: dnpc_wait_ready :: dnpc_wait :: Nil = Enum(3)
  val dnpc_state = RegInit(dnpc_idle)
  val dnpc_reg = RegInit(0.U(XLEN.W))
  val dnpc_valid = RegInit(1.B)

  //注意：当 arvalid 为 1 后， araddr 就不能变了，直到握手成功，因此需要用寄存器存一下
  switch(state){
    is(s_idle){ 
      when (io.in.valid && reset.asBool === 0.B && !io.in.bits.stall) {
        //printf("reset == 0 PC == %d\n", PC)
        when (io.out.ready) {
          // 如果成功输出了，再转移状态 + 接收输入。
          readAddr := PC
          state := s_cache_reqr // 请求访问 Cache，设置 addr
        }
      }
    }
    is(s_cache_reqr) {
      when (icache.io.io.addr_ready && !io.in.bits.stall) {
        // 发完地址以后，就可以更新PC了。
        // 根据 cache 命中情况的不同，此处 bus_ac 不一定为 1
        PC := Mux(dnpc_valid, PC + 4.U, dnpc_reg)
        state := s_cache_return
      }
    }
    is(s_cache_return) {
      when (icache.io.io.data_valid & !io.in.bits.stall) {
        outData := icache.io.io.data
        outAddr := readAddr
        state := s_idle
      }
    }
    // is(s_wait_arready){ // 此时 arvalid 为 true
    //   // 必须要有总线仲裁器的授权，才能转移到下一个状态。不过实际上若 bus_ac = 0, arready 只会是 0
    //   when(io.bus_ac & io.axi4_to_arbiter.arready){
    //     PC := Mux(dnpc_valid, PC + 4.U, dnpc_reg)
    //     // 切换到 wait_rvalid 状态，即将 rready 置为 1 
    //     state := s_wait_rvalid
    //   }
    // }
    // is(s_wait_rvalid){  // 等待 rvalid
    //   when(io.axi4_to_arbiter.rvalid){
    //     state := s_idle
    //     outData := io.axi4_to_arbiter.rdata
    //     outAddr := readAddr
    //     reqr := 0.B
    //   }
    // }
  }
  

  when(dnpc_valid) {
    when (io.in.bits.isdnpc & io.in.valid & !io.in.bits.stall) {
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
  io.in.ready := io.axi4_to_arbiter.arready & io.out.ready
}
