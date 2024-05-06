
import chisel3._ 
import chisel3.util._ 
import Configs._
import Configs.MROM_BASE
import Configs.MROM_SIZE
import Configs.FLASH_BASE
import Configs.FLASH_SIZE
import Configs.UART_BASE


class LSUIn extends Bundle {
  val inst = UInt(32.W)
  val pc = UInt(XLEN.W)
  val alures = UInt(XLEN.W)
  // rs2v 即 wdata
  val memvalid = Bool()
  val wen = Bool()
  val wmask = UInt(WMASKLEN.W)
  val wsext = UInt(MEM_SEXT_SEL_WIDTH.W)
  val raddr = UInt(32.W)
  val waddr = UInt(32.W)
  val wdata = UInt(XLEN.W)
  val rden = Bool()
  val rd = UInt(RIDXLEN.W)
  val csridx = UInt(12.W)
  val csrrv = UInt(XLEN.W)
  val csrwv = UInt(XLEN.W)
  val csr_en = Bool()
}

class LSUOut extends Bundle {
  val inst = UInt(32.W)
  val pc = UInt(XLEN.W)
  val alures = UInt(XLEN.W)
  val memvalid = Bool()
  val rden = Bool()
  val rd = UInt(RIDXLEN.W)
  val memsext = UInt(MEM_SEXT_SEL_WIDTH.W)
  val rdata = UInt(XLEN.W)
  val csridx = UInt(12.W)
  val csrrv = UInt(XLEN.W)
  val csrwv = UInt(XLEN.W)
  val csr_en = Bool()
}

// class LSU extends Module {
//   val io = IO(new Bundle {
//     val in = Flipped(Decoupled(new LSUIn))
//     val out = Decoupled(new LSUOut)
//   })
//   val dpic_mem = Module(new DPIC_MEM)
//   io.in.ready := 1.B
//   dpic_mem.io.valid := io.in.valid
//   dpic_mem.io.wen := io.in.bits.wen
//   dpic_mem.io.raddr := io.in.bits.raddr
//   dpic_mem.io.waddr := io.in.bits.waddr
//   dpic_mem.io.wdata := io.in.bits.wdata
//   dpic_mem.io.wmask := io.in.bits.wmask
//   dpic_mem.io.clk := clock
//   io.out.valid := RegNext(io.in.valid, 0.B)
//   // 手动模拟 1 周期的 SRAM 延迟，仅读取有延迟
//   io.out.bits.rdata := RegNext(dpic_mem.io.rdata, 0.U)
//   // io.out.bits.rdata := 0.U

// }

class ysyx_23060110_LSU extends Module {
  val io = IO(new Bundle {
    val in = Flipped(Decoupled(new LSUIn))
    val out = Decoupled(new LSUOut)
    val axi4_to_arbiter = Flipped(new AXI4Interface)
    val bus_ac = Input(Bool())
    val bus_reqr = Output(Bool())
    val bus_reqw = Output(Bool())
  })
  val is_mrom = WireInit(0.B)
  is_mrom := io.in.bits.raddr >= MROM_BASE.U && io.in.bits.raddr < (MROM_BASE + MROM_SIZE).U
  val is_flash = WireInit(0.B)
  is_flash := io.in.bits.raddr >= FLASH_BASE.U && io.in.bits.raddr < (FLASH_BASE + FLASH_SIZE).U
  val is_uart = WireInit(0.B)
  is_uart := io.in.bits.raddr >= UART_BASE.U && io.in.bits.raddr < (UART_BASE + UART_SIZE).U
  val empty_master = Module(new ysyx_23060110_empty_axi4_master)
  io.axi4_to_arbiter <> empty_master.io.axi4
  //val fake_sram = Module(new FAKE_SRAM_LSU())
  val reqr = RegInit(0.B)
  val reqw = RegInit(0.B)
  io.bus_reqr := reqr 
  io.bus_reqw := reqw
  val readAddr = RegInit(0.U(32.W))
  val readData = RegInit(0.U(XLEN.W))
  val readSize = RegInit(0.U(3.W))

  val r_idle :: r_wait_arready :: r_wait_rvalid :: Nil = Enum(3)
  val r_state = RegInit(r_idle)
  
  val instreg = RegInit(0.U(32.W))
  val pcreg = RegInit(0.U(XLEN.W))
  val memvalidreg = RegInit(0.B)
  val aluresreg = RegInit(0.U(XLEN.W))
  val rdenreg = RegInit(0.B)
  val rdreg = RegInit(0.U(RIDXLEN.W))
  val memsextreg = RegInit(MEM_SEXT_NONE)
  val csridxreg = RegInit(0.U(12.W))
  val csrrvreg = RegInit(0.U(XLEN.W))
  val csrwvreg = RegInit(0.U(XLEN.W))
  val csrenreg = RegInit(0.B)

  // 由于顺序五级流水不会同时进行读和写， 当 io.in.valid 并且 wen 为 0 即为读
  io.axi4_to_arbiter.arvalid := r_state === r_wait_arready 
  io.axi4_to_arbiter.araddr := readAddr
  io.axi4_to_arbiter.rready := r_state === r_wait_rvalid & io.out.ready
  io.axi4_to_arbiter.arsize := readSize
  
  // printf("lsu r_state === %d\n", r_state);
  
  val araddr_unalign_offset = Mux(is_uart | is_flash, 0.U, Mux(is_mrom, io.in.bits.raddr(1, 0), io.in.bits.raddr(2, 0)))
  readSize := MuxLookup(memsextreg, 3.U, Seq(
            MEM_NSEXT_8 ->  0.U,
            MEM_NSEXT_16->  1.U,
            MEM_NSEXT_32->  2.U,
            MEM_SEXT_8  ->  0.U,
            MEM_SEXT_16 ->  1.U,
            MEM_SEXT_32 ->  2.U,
          ))
  val offsetreg = RegInit(0.U(3.W))
  switch(r_state){
    is(r_idle){
      when(io.in.valid && io.in.bits.memvalid && !io.in.bits.wen){
        r_state := r_wait_arready
        reqr := 1.B
        when (araddr_unalign_offset =/= 0.U) {
          offsetreg := araddr_unalign_offset
          readAddr := io.in.bits.raddr
          readSize := MuxLookup(araddr_unalign_offset, 3.U, Seq(
            // | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0
            // |    3          |     2 | 1 | 0 
            3.U -> 2.U,
            2.U -> 2.U,
            1.U -> 1.U,
          ))
        } .otherwise {
          offsetreg := 0.U
          readAddr := io.in.bits.raddr
        }
        // printf("araddr = %x\n", io.in.bits.raddr)
      }
    }
    is(r_wait_arready){ // arvalid = 1
      when(io.bus_ac & io.axi4_to_arbiter.arready){
        //此时把要读取的地址传给 mem，等待其读取完成
        r_state := r_wait_rvalid
        // printf("arsize = %x\n", readSize)
      }
    }
    is(r_wait_rvalid){ // rready = 1
      when(io.axi4_to_arbiter.rvalid){
        readData := io.axi4_to_arbiter.rdata >> (8.U * offsetreg)
        // printf("lsu unaligned raddr = %x rdata = %x  aligned rdata = %x rresp == %d\n" , readAddr, io.axi4_to_arbiter.rdata, io.axi4_to_arbiter.rdata >> (8.U * offsetreg), io.axi4_to_arbiter.rresp)
        when(io.axi4_to_arbiter.rresp === 0.U) {
          r_state := r_idle
          reqr := 0.B
        }
      }
    }
  }

  
  val w_idle :: w_wait_wready :: w_wait_bvalid :: Nil = Enum(3)
  val w_state = RegInit(w_idle)

  val writeAddr = RegInit(0.U(32.W))
  val writeData = RegInit(0.U(XLEN.W))
  val writeStrb = RegInit(0.U((XLEN/8).W))
  val writeSize = WireInit(3.U(3.W))
  val writeResp = RegInit(0.U(2.W))
  val is_sram = WireInit(0.B)
  is_sram := io.in.bits.waddr >= SRAM_BASE.U && io.in.bits.waddr < (SRAM_BASE + SRAM_SIZE).U
  val awaddr_unalign_offset = Mux(!is_sram, 0.U, io.in.bits.waddr(2, 0))

  

  io.axi4_to_arbiter.awaddr := writeAddr
  io.axi4_to_arbiter.awsize := writeSize
  // io.axi4_to_arbiter.awvalid := w_state === w_wait_wready
  io.axi4_to_arbiter.wdata := writeData
  // io.axi4_to_arbiter.wvalid := w_state === w_wait_wready
  io.axi4_to_arbiter.wstrb := writeStrb
  io.axi4_to_arbiter.wlast := 1.B
  // io.axi4_to_arbiter.bready := w_state === w_wait_bvalid
  //printf("wsize = %d\n", writeSize)
  //printf("lsu r_state w_state == %d %d\n", r_state, w_state)
  switch(w_state) {
    is(w_idle) {
      // 由于目前没有同时进行读写，当 valid = 1 且 wen = 1 为写
      io.axi4_to_arbiter.bready := 0.B
      when(io.in.valid && io.in.bits.memvalid && io.in.bits.wen) {
        
        // printf("wmask = %d\n", io.in.bits.wmask)
        w_state := w_wait_wready
        io.axi4_to_arbiter.awvalid := 1.B 
        io.axi4_to_arbiter.wvalid := 1.B
        // when (awaddr_unalign_offset =/= 0.U) { 

        //   // 非对齐写入
        // printf("\nwaddr = %x unalign offset = %x wdata = %x\n\n\n\n\n", io.in.bits.waddr, awaddr_unalign_offset, io.in.bits.wdata)
        // }
        writeAddr := io.in.bits.waddr
        writeData := io.in.bits.wdata << (awaddr_unalign_offset * 8.U)
        writeSize := MuxLookup(io.in.bits.wmask, 2.U, Seq(
          1.U -> 0.U,   // 0b1        -> 1 byte
          3.U -> 1.U,   // 0b11       -> 2 bytes
          15.U -> 2.U,  // 0b1111     -> 4 bytes
          255.U -> 3.U
        ))
        writeStrb := io.in.bits.wmask << awaddr_unalign_offset
        // writeStrb := io.in.bits.wmask
        reqw := 1.B
      }
    }
    is(w_wait_wready) {
      
      io.axi4_to_arbiter.awvalid := 1.B 
      io.axi4_to_arbiter.wvalid := 1.B
      when(io.bus_ac & io.axi4_to_arbiter.awready & io.axi4_to_arbiter.wready) {
        // waddr wdata 传输完成
        // Keep in mind that slaves may do this: awready := wvalid, wready := awvalid 
        // To not cause a loop, we cannot have: wvalid := awready (awvalid := wready)
        // printf("\n wstrb(shifted) = %x wdata(shifted) = %x waddr(unaligned) = %x wsize = %x\n\n\n", writeStrb, writeData, writeAddr, writeSize)
        w_state := w_wait_bvalid 
        //在从设备的AWREADY信号有效后的第一个时钟上升沿，主设备的AWVALID信号必须保持有效
        //因此此处不修改 awvalid 的值
        //但我可以在 bvalid 有效前先拉高 bready

      }
    }
    is(w_wait_bvalid) {
      io.axi4_to_arbiter.bready := 1.B
      when(io.axi4_to_arbiter.bvalid) {
        writeResp := io.axi4_to_arbiter.bresp
        when(io.axi4_to_arbiter.bresp === 0.U) {  // bresp === 0 才表示写入成功，此时再切换状态
          // printf("lsu bresp == %d waddr=%x wready = %d wvalid = %d awready = %d awvalid = %d\n", io.axi4_to_arbiter.bresp, writeAddr, io.axi4_to_arbiter.wready, io.axi4_to_arbiter.wvalid, io.axi4_to_arbiter.awready, io.axi4_to_arbiter.awvalid)
          w_state := w_idle
          io.axi4_to_arbiter.awvalid := 0.B
          io.axi4_to_arbiter.wvalid := 0.B
          reqw := 0.B
        }.otherwise {
          // printf("lsu bresp == %d waddr=%x wready = %d wvalid = %d awready = %d awvalid = %d\n", io.axi4_to_arbiter.bresp, writeAddr, io.axi4_to_arbiter.wready, io.axi4_to_arbiter.wvalid, io.axi4_to_arbiter.awready, io.axi4_to_arbiter.awvalid)
          
        }
      }
    }
  }

  
  //printf("io.out.valid = %d\n", io.out.valid)
  io.out.bits.rdata := readData
  io.in.ready := r_state === r_idle && w_state === w_idle
  


  io.out.bits.inst := instreg 
  io.out.bits.pc := pcreg 
  io.out.bits.memvalid := memvalidreg
  io.out.bits.alures := aluresreg
  io.out.bits.rden := rdenreg 
  io.out.bits.rd := rdreg 
  io.out.bits.memsext := memsextreg 
  io.out.bits.csridx := csridxreg
  io.out.bits.csr_en := csrenreg
  io.out.bits.csrrv := csrrvreg
  io.out.bits.csrwv := csrwvreg

  io.out.valid := r_state === r_idle && w_state === w_idle
  // when (io.in.valid & io.in.ready){
  //   instreg := io.in.bits.inst 
  //   pcreg := io.in.bits.pc
  //   memvalidreg := io.in.bits.memvalid
  //   aluresreg := io.in.bits.alures
  //   rdenreg := io.in.bits.rden
  //   rdreg := io.in.bits.rd
  //   memsextreg := io.in.bits.wsext
  // }

  when (io.in.valid && r_state === r_idle && w_state === w_idle) {
    instreg := io.in.bits.inst 
    pcreg := io.in.bits.pc
    memvalidreg := io.in.bits.memvalid
    aluresreg := io.in.bits.alures
    rdenreg := io.in.bits.rden
    rdreg := io.in.bits.rd
    memsextreg := io.in.bits.wsext
    csridxreg := io.in.bits.csridx
    csrrvreg := io.in.bits.csrrv
    csrenreg := io.in.bits.csr_en
    csrwvreg := io.in.bits.csrwv
  }
}