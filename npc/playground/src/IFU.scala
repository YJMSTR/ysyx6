
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

class ysyx_23060110_IFU extends Module {
  val io = IO(new Bundle {
    val in = Flipped(Decoupled(new IFUIn))
    val out = Decoupled(new IFUOut)
    val axi4_to_arbiter = Flipped(new AXI4Interface)
    val bus_ac = Input(Bool())
    val bus_reqr = Output(Bool())
    val bus_reqw = Output(Bool())
  })

  val empty_master = Module(new ysyx_23060110_empty_axi4_master)
  io.axi4_to_arbiter <> empty_master.io.axi4
  io.bus_reqw := 0.B // ifu 没有写操作
  val reqr = RegInit(0.B)
  io.bus_reqr := reqr

  val PC = RegInit(RESET_VECTOR.U(XLEN.W))
  val readAddr = RegInit(0.U(32.W))
  val readSize = RegInit(2.U(MEM_SEXT_SEL_WIDTH.W))
  val outAddr = RegInit(0.U(32.W))
  val outData = RegInit(0.U(32.W))

  val s_idle :: s_wait_arready :: s_wait_rvalid :: Nil = Enum(3)
  val state = RegInit(s_idle)



  io.axi4_to_arbiter.arvalid := state === s_wait_arready && reset.asBool === 0.B
  io.axi4_to_arbiter.rready := state === s_wait_rvalid && reset.asBool === 0.B
  io.axi4_to_arbiter.araddr := readAddr
  io.axi4_to_arbiter.arsize := readSize
  io.axi4_to_arbiter.awaddr := 0.U
  io.axi4_to_arbiter.awvalid := 0.B
  io.axi4_to_arbiter.wdata := 0.U
  io.axi4_to_arbiter.wstrb := 0.U
  io.axi4_to_arbiter.wvalid := 0.U
  io.axi4_to_arbiter.bready := 0.U
  
  val dnpc_idle :: dnpc_wait_ready :: dnpc_wait :: Nil = Enum(3)
  val dnpc_state = RegInit(dnpc_idle)
  val dnpc_reg = RegInit(0.U(XLEN.W))
  val dnpc_valid = RegInit(1.B)

  val is_mrom = WireInit(0.B)
  val is_flash = WireInit(0.B)
  val is_psram = WireInit(0.B)
  val is_sram = WireInit(0.B)
  val is_sdram = WireInit(0.B)
  is_mrom := PC >= MROM_BASE.U && PC < (MROM_BASE + MROM_SIZE).U
  is_flash := PC >= FLASH_BASE.U && PC < (FLASH_BASE + FLASH_SIZE).U
  is_psram := PC >= PSRAM_BASE.U && PC < (PSRAM_BASE + PSRAM_SIZE).U
  is_sram := PC >= SRAM_BASE.U && PC < (SRAM_BASE + SRAM_SIZE).U
  is_sdram := PC >= SDRAM_BASE.U && PC < (SDRAM_BASE + SDRAM_SIZE).U
  val araddr_unalign_offset = Mux(is_sram, PC(2, 0), Mux(is_mrom | is_psram | is_sdram, PC(1, 0), 0.U))
  val offsetreg = RegInit(0.U(3.W))
  //注意：当 arvalid 为 1 后， araddr 就不能变了，直到握手成功，因此需要用寄存器存一下
  switch(state){
    is(s_idle){ 
      when (io.in.valid && reset.asBool === 0.B) {
        //printf("reset == 0 PC == %d\n", PC)
        when (io.out.ready) {
          // 如果成功输出了，再转移状态 + 接收输入。
          readAddr := PC
          state := s_wait_arready
          reqr := 1.B
          when(araddr_unalign_offset =/= 0.U) {
            readSize := MuxLookup(araddr_unalign_offset, 3.U, Seq(
              3.U -> 2.U,
              2.U -> 2.U,
              1.U -> 1.U,
            ))
            offsetreg := araddr_unalign_offset
          }.otherwise {
            offsetreg := 0.U
            readSize := 2.U
          }
        }
      }
    }
    is(s_wait_arready){ // 此时 arvalid 为 true
      // 必须要有总线仲裁器的授权，才能转移到下一个状态。不过实际上若 bus_ac = 0, arready 只会是 0
      when(io.bus_ac & io.axi4_to_arbiter.arready){
        PC := Mux(dnpc_valid, PC + 4.U, dnpc_reg)
        // 切换到 wait_rvalid 状态，即将 rready 置为 1 
        state := s_wait_rvalid
        // when (is_mrom === 0.B) {
        //   printf("ifu araddr=%x arsize=%x ismrom=%x offset=%x\n", readAddr, readSize, is_mrom, araddr_unalign_offset)
        // }
      }
    }
    is(s_wait_rvalid){  // 等待 rvalid
      when(io.axi4_to_arbiter.rvalid){
        state := s_idle
        outData := io.axi4_to_arbiter.rdata >> (8.U * offsetreg)
        outAddr := readAddr
        // when(!is_mrom) {
        //   printf("rdata=%x\n", io.axi4_to_arbiter.rdata >> (8.U * offsetreg))
        // }
        reqr := 0.B
        when (io.axi4_to_arbiter.rresp =/= 0.U) {
          printf("r resp = %x raddr = %x\n", io.axi4_to_arbiter.rresp, readAddr)

          outAddr := 0.U
          outData := 0.U
        }
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
  io.in.ready := io.axi4_to_arbiter.arready & io.out.ready
}
