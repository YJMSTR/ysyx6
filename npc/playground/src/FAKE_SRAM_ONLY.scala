import chisel3._
import chisel3.util._
import chisel3.util.random.LFSR
import Configs._ 

class FAKE_SRAM_ONLY extends Module {
  val io = IO(new Bundle {
    val axi4 = new AXI4Interface 
  })

  val empty_slave = Module(new empty_axi4_slave)
  io.axi4 <> empty_slave.io.axi4

  val r_idle :: r_read :: r_wait_ready :: Nil = Enum(3)
  val r_state = RegInit(r_idle)
  // val delaygen = LFSR(4, 1.B, Some(1))
  val delaygen = 100.U
  val delay = RegInit(1.U(8.W))
  val delayCounter = RegInit(0.U(8.W))
  val delayDone = delayCounter === delay 

  val dpic_mem = Module(new DPIC_MEM)

  val readData = RegInit(0.U(XLEN.W))
  val readAddr = RegInit(0.U(32.W))
  val rvalidReg = RegInit(false.B)

  io.axi4.rvalid := rvalidReg
  io.axi4.rdata := readData
  io.axi4.rresp := 0.U

  io.axi4.arready := r_state === r_idle

  dpic_mem.io.raddr := readAddr
 
  
  dpic_mem.io.clk := clock

  switch(r_state) {
    is(r_idle) {
      readData := 0.U
      when(io.axi4.arvalid){
        readAddr := io.axi4.araddr
        r_state := r_read
        delayCounter := 0.U
        delay := delaygen
      }
    }
    is(r_read){
      when(delayDone){
        rvalidReg := true.B
        readData := dpic_mem.io.rdata
        r_state := r_wait_ready
        
      }.otherwise{
        delayCounter := delayCounter + 1.U
        readData := 0.U
      }
    }
    is(r_wait_ready) {
      when(io.axi4.rready) {
        rvalidReg := false.B  //传输完成，置为false
        r_state := r_idle
      }
    }
  }
  
  val w_idle :: w_wait_wvalid :: w_write :: w_wait_bready :: Nil = Enum(4)
  // 写也有延迟
  val w_state = RegInit(w_idle)

  val writeAddr = RegInit(0.U(32.W))
  val writeData = RegInit(0.U(XLEN.W))
  val writeStrb = RegInit(0.U((XLEN/8).W))
  val bresp = RegInit(0.U(2.W)) //default 0b00 === OKAY

  io.axi4.awready := w_state === w_idle || w_state === w_wait_wvalid
  io.axi4.wready := w_state === w_wait_wvalid
  io.axi4.bvalid := w_state === w_wait_bready
  io.axi4.bresp := bresp

  dpic_mem.io.wen := w_state === w_write
  dpic_mem.io.waddr := writeAddr
  dpic_mem.io.wdata := writeData
  dpic_mem.io.wmask := writeStrb

  switch(w_state) {
    is(w_idle) {  // awready = 1
      when(io.axi4.awvalid) {
        w_state := w_wait_wvalid
        writeAddr := io.axi4.awaddr
      }
    }
    is(w_wait_wvalid) { // w_ready = 1
      when(io.axi4.wvalid) {
        writeData := io.axi4.wdata
        writeStrb := io.axi4.wstrb
        w_state := w_write
      }
    }
    is(w_write) {
      w_state := w_wait_bready
    }
    is(w_wait_bready) { // b_valid = 1
      when(io.axi4.bready) {
        w_state := w_idle
      }
    }
  }

   dpic_mem.io.valid := (delayDone & r_state === r_read) || (w_state === w_write)

}
