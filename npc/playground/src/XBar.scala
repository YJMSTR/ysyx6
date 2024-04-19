import chisel3._
import chisel3.util._
import Configs._ 
import Configs.CLINT_BASE
import Configs.CLINT_SIZE

class ysyx_23060110_XBar extends Module {
  val io = IO(new Bundle {
    val axi4in = new AXI4Interface
    val axi4out_master = Flipped(new AXI4Interface)
    val axi4out_clint = Flipped(new AXI4Interface)
    // val axi4out2 = Flipped(new AXI4Interface)
    // val axi4out_mrom = Flipped(new AXI4Interface)
  })
  // out(0): uart
  // out(1): sram
  val empty_slave_in_master = Module(new ysyx_23060110_empty_axi4_master)
  val empty_slave_in_clint = Module(new ysyx_23060110_empty_axi4_master)
  // val empty_slave_in2 = Module(new ysyx_23060110_empty_axi4_master)
  // val empty_slave_in_mrom = Module(new ysyx_23060110_empty_axi4_master)
  val empty_master_out = Module(new ysyx_23060110_empty_axi4_slave)
  
  io.axi4out_master <> empty_slave_in_master.io.axi4
  io.axi4out_clint <> empty_slave_in_clint.io.axi4
  io.axi4in <> empty_master_out.io.axi4
  // io.axi4out2 <> empty_slave_in2.io.axi4
  // io.axi4out_mrom <> empty_slave_in_mrom.io.axi4
  // io.axi4in <> empty_master_out.io.axi4

  // val s_addr = RegInit(0.U(XLEN.W))

  // val r_idle :: r_sram_wait :: r_mtime_wait :: r_mrom_wait :: Nil = Enum(4)
  // val state_r = RegInit(r_idle)

  // val w_idle :: w_sram_wait :: w_uart_wait :: Nil = Enum(3)
  // val state_w = RegInit(w_idle)

  

  // switch(state_r) {
  //   is (r_idle) {
  //     when (io.axi4in.arvalid) {
  //       when(io.axi4in.araddr >= MEM_BASE.U(XLEN.W) && io.axi4in.araddr < (MEM_BASE + MEM_SIZE).U(XLEN.W)) {
  //         state_r := r_sram_wait
  //         // 暂时把 RTC 转发给 SRAM
  //       // }.elsewhen (io.axi4in.araddr === RTC_ADDR.U(XLEN.W) || io.axi4in.araddr === (RTC_ADDR.U(XLEN.W) + 4.U)) {
  //       //   state_r := r_sram_wait
  //       }.elsewhen(io.axi4in.araddr === RTC_ADDR.U(XLEN.W) || io.axi4in.araddr === (RTC_ADDR.U(XLEN.W) + 4.U)){
  //         state_r := r_mtime_wait
  //       }.elsewhen(io.axi4in.araddr >= MROM_BASE.U(XLEN.W) && io.axi4in.araddr < (MROM_BASE + MROM_SIZE).U(XLEN.W)) {
  //         state_r := r_mrom_wait
  //       }.otherwise {
  //         io.axi4in.rresp := 3.U // decerr
  //         io.axi4in.rvalid := true.B
  //         printf("decerr r %x\n", io.axi4in.araddr)
  //         io.axi4in.rdata := 0.U
  //         state_r := r_idle
  //       }
  //     }
  //   }
  //   is (r_sram_wait) {
  //     io.axi4in <> io.axi4out1
  //     when (io.axi4in.rready & io.axi4in.rvalid) {
  //       state_r := r_idle
  //     }
  //   }
  //   is (r_mtime_wait) {
  //     io.axi4in <> io.axi4out2
  //     when (io.axi4in.rready & io.axi4in.rvalid) {
  //       state_r := r_idle
  //     }
  //   }
  //   is (r_mrom_wait) {
  //     io.axi4in <> io.axi4out_mrom
  //     when (io.axi4in.rready & io.axi4in.rvalid) {
  //       state_r := r_idle
  //     }
  //   }
  // }

  // switch(state_w) {
  //   is (w_idle) {
  //     when (io.axi4in.awvalid) {
  //       // RTC 目前直接 DPI-C
  //       when (io.axi4in.awaddr >= MEM_BASE.U(XLEN.W) && io.axi4in.awaddr < MEM_BASE.U(XLEN.W) + MEM_SIZE.U(XLEN.W)) {
  //         state_w := w_sram_wait
  //       }.elsewhen (io.axi4in.awaddr === SERIAL_PORT.U(XLEN.W)) {
  //         state_w := w_uart_wait
  //       }.otherwise {
  //         io.axi4in.bresp := 3.U // decerr
  //         printf("decerr w\n")
  //         io.axi4in.bvalid := true.B
  //         state_w := w_idle
  //       }
  //     }
  //   }
  //   is (w_sram_wait) {
  //     io.axi4in <> io.axi4out1
  //     when (io.axi4in.bvalid & io.axi4in.bready) {
  //       state_w := w_idle
  //     }
  //   }
  //   is (w_uart_wait) {
  //     io.axi4in <> io.axi4out0
  //     when (io.axi4in.bvalid & io.axi4in.bready) {
  //       state_w := w_idle
  //     }
  //   }
  // }

  val is_clint = WireInit(0.B)
  is_clint := io.axi4in.araddr >= CLINT_BASE.U && io.axi4in.araddr < (CLINT_BASE + CLINT_SIZE).U
  
  val r_idle :: r_master_wait :: r_clint_wait :: Nil = Enum(3)
  val r_state = RegInit(r_idle)

  switch(r_state) {
    is(r_idle) {
      when (io.axi4in.arvalid) {
        when(is_clint) {
          r_state := r_clint_wait
        } .otherwise {
          r_state := r_master_wait
        }
      }.otherwise{  // 要么没有访存，要么是写入
        io.axi4in <> io.axi4out_master
      }
    }
    is(r_master_wait) {
      io.axi4in <> io.axi4out_master
      when (io.axi4in.rready & io.axi4in.rvalid) {
        r_state := r_idle
      }
    }
    is(r_clint_wait) {
      io.axi4in <> io.axi4out_clint
      when (io.axi4in.rready & io.axi4in.rvalid) {
        r_state := r_idle
      }
    }
  }
  
}