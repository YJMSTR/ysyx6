import chisel3._
import chisel3.util._
import Configs._ 

class XBar extends Module {
  val io = IO(new Bundle {
    val axi4litein = new AXI4LiteInterface
    val axi4liteout0 = Flipped(new AXI4LiteInterface)
    val axi4liteout1 = Flipped(new AXI4LiteInterface)
    val axi4liteout2 = Flipped(new AXI4LiteInterface)
  })
  // out(0): uart
  // out(1): sram
  val empty_slave_in0 = Module(new empty_axi4lite_master)
  val empty_slave_in1 = Module(new empty_axi4lite_master)
  val empty_slave_in2 = Module(new empty_axi4lite_master)
  val empty_master_out = Module(new empty_axi4lite_slave)
  
  io.axi4liteout0 <> empty_slave_in0.io.axi4lite
  io.axi4liteout1 <> empty_slave_in1.io.axi4lite
  io.axi4liteout2 <> empty_slave_in2.io.axi4lite
  io.axi4litein <> empty_master_out.io.axi4lite

  val s_addr = RegInit(0.U(XLEN.W))

  val r_idle :: r_sram_wait :: r_mtime_wait :: Nil = Enum(3)
  val state_r = RegInit(r_idle)

  val w_idle :: w_sram_wait :: w_uart_wait :: Nil = Enum(3)
  val state_w = RegInit(w_idle)

  

  switch(state_r) {
    is (r_idle) {
      when (io.axi4litein.arvalid) {
        when(io.axi4litein.araddr >= MEM_BASE.U(XLEN.W) && io.axi4litein.araddr < MEM_BASE.U(XLEN.W) + MEM_SIZE.U(XLEN.W)) {
          state_r := r_sram_wait
          // 暂时把 RTC 转发给 SRAM
        // }.elsewhen (io.axi4litein.araddr === RTC_ADDR.U(XLEN.W) || io.axi4litein.araddr === (RTC_ADDR.U(XLEN.W) + 4.U)) {
        //   state_r := r_sram_wait
        }.elsewhen(io.axi4litein.araddr === RTC_ADDR.U(XLEN.W) || io.axi4litein.araddr === (RTC_ADDR.U(XLEN.W) + 4.U)){
          state_r := r_mtime_wait
        }.otherwise {
          io.axi4litein.rresp := 3.U // decerr
          io.axi4litein.rvalid := true.B
          printf("decerr r %x\n", io.axi4litein.araddr)
          stop()
          io.axi4litein.rdata := 0.U
          state_r := r_idle
        }
      }
    }
    is (r_sram_wait) {
      io.axi4litein <> io.axi4liteout1
      when (io.axi4litein.rready & io.axi4litein.rvalid) {
        state_r := r_idle
      }
    }
    is (r_mtime_wait) {
      io.axi4litein <> io.axi4liteout2
      when (io.axi4litein.rready & io.axi4litein.rvalid) {
        state_r := r_idle
      }
    }
  }

  switch(state_w) {
    is (w_idle) {
      when (io.axi4litein.awvalid) {
        // RTC 目前直接 DPI-C
        when (io.axi4litein.awaddr >= MEM_BASE.U(XLEN.W) && io.axi4litein.awaddr < MEM_BASE.U(XLEN.W) + MEM_SIZE.U(XLEN.W)) {
          state_w := w_sram_wait
        }.elsewhen (io.axi4litein.awaddr === SERIAL_PORT.U(XLEN.W)) {
       
          state_w := w_uart_wait
          // state_w := w_sram_wait
        }.otherwise {
          io.axi4litein.bresp := 3.U // decerr
          printf("decerr w\n")
          io.axi4litein.bvalid := true.B
          state_w := w_idle
        }
      }
    }
    is (w_sram_wait) {
      io.axi4litein <> io.axi4liteout1
      when (io.axi4litein.bvalid & io.axi4litein.bready) {
        state_w := w_idle
      }
    }
    is (w_uart_wait) {
      io.axi4litein <> io.axi4liteout0
      when (io.axi4litein.bvalid & io.axi4litein.bready) {
        state_w := w_idle
      }
    }
  }


}

