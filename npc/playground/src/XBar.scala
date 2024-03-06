import chisel3._
import chisel3.util._
import Configs._ 

class XBar extends Module {
  val io = IO(new Bundle {
    val axi4litein = new AXI4LiteInterface
    val axi4liteout0 = Flipped(new AXI4LiteInterface)
    val axi4liteout1 = Flipped(new AXI4LiteInterface)
  })
  // out(0): uart
  // out(1): sram
  val empty_slave_in0 = Module(new empty_axi4lite_master)
  val empty_slave_in1 = Module(new empty_axi4lite_master)
  val empty_master_out = Module(new empty_axi4lite_slave)
  
  io.axi4liteout0 <> empty_slave_in0.io.axi4lite
  io.axi4liteout1 <> empty_slave_in1.io.axi4lite
  io.axi4litein <> empty_master_out.io.axi4lite

  val s_addr = RegInit(0.U(XLEN.W))

  val s_idle :: s_waitr :: s_waitw :: Nil = Enum(3)
  val state = RegInit(s_idle)

  switch(state) {
    is(s_idle) {
      when (io.axi4litein.arvalid) {
        state := s_waitr 
        s_addr := io.axi4litein.araddr
      }.elsewhen (io.axi4litein.awvalid) {
        state := s_waitw
        s_addr := io.axi4litein.awaddr
      }
    }
    is(s_waitr) {
      when(io.axi4litein.rvalid & io.axi4litein.rready) {
        state := s_idle
        s_addr := 0.U
      }
    }
    is(s_waitw) {
      when(io.axi4litein.bvalid & io.axi4litein.bready) {
        state := s_idle 
        s_addr := 0.U
      }
    }
  }

  when (state =/= s_idle) {
    when (s_addr === SERIAL_PORT.U(XLEN.W)) {
      //printf("XBar UART: araddr = %x\n", s_addr)
      io.axi4liteout0 <> io.axi4litein
      io.axi4liteout1 <> empty_slave_in1.io.axi4lite
    }.elsewhen(s_addr >= MEM_BASE.U(XLEN.W) && s_addr < MEM_BASE.U(XLEN.W) + MEM_SIZE.U(XLEN.W)) {
      //printf("XBar SRAM: araddr = %x\n", s_addr)
      io.axi4liteout1 <> io.axi4litein
      io.axi4liteout0 <> empty_slave_in0.io.axi4lite
    }
  }.otherwise {
    io.axi4liteout0 <> empty_slave_in0.io.axi4lite
    io.axi4liteout1 <> empty_slave_in1.io.axi4lite
    io.axi4litein <> empty_master_out.io.axi4lite
  }
}

