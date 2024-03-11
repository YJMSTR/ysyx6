import chisel3._
import chisel3.util._
import Configs._ 

class ysyx_23060110_XBar extends Module {
  val io = IO(new Bundle {
    val axi4fullin = new AXI4FullInterface
    val axi4fullout0 = Flipped(new AXI4FullInterface)
    val axi4fullout1 = Flipped(new AXI4FullInterface)
    val axi4fullout2 = Flipped(new AXI4FullInterface)
  })
  // out(0): uart
  // out(1): sram
  val empty_slave_in0 = Module(new ysyx_23060110_empty_axi4full_master)
  val empty_slave_in1 = Module(new ysyx_23060110_empty_axi4full_master)
  val empty_slave_in2 = Module(new ysyx_23060110_empty_axi4full_master)
  val empty_master_out = Module(new ysyx_23060110_empty_axi4full_slave)
  
  io.axi4fullout0 <> empty_slave_in0.io.axi4full
  io.axi4fullout1 <> empty_slave_in1.io.axi4full
  io.axi4fullout2 <> empty_slave_in2.io.axi4full
  io.axi4fullin <> empty_master_out.io.axi4full

  val s_addr = RegInit(0.U(XLEN.W))

  val r_idle :: r_sram_wait :: r_mtime_wait :: Nil = Enum(3)
  val state_r = RegInit(r_idle)

  val w_idle :: w_sram_wait :: w_uart_wait :: Nil = Enum(3)
  val state_w = RegInit(w_idle)

  

  switch(state_r) {
    is (r_idle) {
      when (io.axi4fullin.arvalid) {
        when(io.axi4fullin.araddr >= MEM_BASE.U(XLEN.W) && io.axi4fullin.araddr < MEM_BASE.U(XLEN.W) + MEM_SIZE.U(XLEN.W)) {
          state_r := r_sram_wait
          // 暂时把 RTC 转发给 SRAM
        // }.elsewhen (io.axi4fullin.araddr === RTC_ADDR.U(XLEN.W) || io.axi4fullin.araddr === (RTC_ADDR.U(XLEN.W) + 4.U)) {
        //   state_r := r_sram_wait
        }.elsewhen(io.axi4fullin.araddr === RTC_ADDR.U(XLEN.W) || io.axi4fullin.araddr === (RTC_ADDR.U(XLEN.W) + 4.U)){
          state_r := r_mtime_wait
        }.otherwise {
          io.axi4fullin.rresp := 3.U // decerr
          io.axi4fullin.rvalid := true.B
          printf("decerr r %x\n", io.axi4fullin.araddr)
          io.axi4fullin.rdata := 0.U
          state_r := r_idle
        }
      }
    }
    is (r_sram_wait) {
      io.axi4fullin <> io.axi4fullout1
      when (io.axi4fullin.rready & io.axi4fullin.rvalid) {
        state_r := r_idle
      }
    }
    is (r_mtime_wait) {
      io.axi4fullin <> io.axi4fullout2
      when (io.axi4fullin.rready & io.axi4fullin.rvalid) {
        state_r := r_idle
      }
    }
  }

  switch(state_w) {
    is (w_idle) {
      when (io.axi4fullin.awvalid) {
        // RTC 目前直接 DPI-C
        when (io.axi4fullin.awaddr >= MEM_BASE.U(XLEN.W) && io.axi4fullin.awaddr < MEM_BASE.U(XLEN.W) + MEM_SIZE.U(XLEN.W)) {
          state_w := w_sram_wait
        }.elsewhen (io.axi4fullin.awaddr === SERIAL_PORT.U(XLEN.W)) {
          state_w := w_uart_wait
        }.otherwise {
          io.axi4fullin.bresp := 3.U // decerr
          printf("decerr w\n")
          io.axi4fullin.bvalid := true.B
          state_w := w_idle
        }
      }
    }
    is (w_sram_wait) {
      io.axi4fullin <> io.axi4fullout1
      when (io.axi4fullin.bvalid & io.axi4fullin.bready) {
        state_w := w_idle
      }
    }
    is (w_uart_wait) {
      io.axi4fullin <> io.axi4fullout0
      when (io.axi4fullin.bvalid & io.axi4fullin.bready) {
        state_w := w_idle
      }
    }
  }


}

