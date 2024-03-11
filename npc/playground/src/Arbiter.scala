import chisel3._ 
import chisel3.util._ 
import Configs._

class BUS_IO extends Bundle {
  val axi4full = new AXI4FullInterface
  val bus_reqr = Input(Bool())
  val bus_reqw = Input(Bool())
  val bus_ac = Output(Bool())
}

class ysyx_23060110_MyArbiter extends Module {
  val io = IO(new Bundle {
    val ifu_bus = new BUS_IO
    val lsu_bus = new BUS_IO
    val xbar_bus  = Flipped(new AXI4FullInterface)
  })

  val empty_axi4full_ifu = Module(new ysyx_23060110_empty_axi4full_slave)
  val empty_axi4full_lsu = Module(new ysyx_23060110_empty_axi4full_slave)
  val empty_xbar_bus = Module(new ysyx_23060110_empty_axi4full_master)




  val both_idle :: ifu_waitr :: lsu_waitr :: lsu_waitw :: Nil = Enum(4)
  val state = RegInit(both_idle)

  val ifu_ac = RegInit(0.B)
  val lsu_ac = RegInit(0.B)

  io.ifu_bus.bus_ac := ifu_ac 
  io.lsu_bus.bus_ac := lsu_ac


  io.ifu_bus.axi4full <> empty_axi4full_ifu.io.axi4full
  io.lsu_bus.axi4full <> empty_axi4full_lsu.io.axi4full
  io.xbar_bus <> empty_xbar_bus.io.axi4full
  when(state === both_idle) {
    io.ifu_bus.axi4full <> empty_axi4full_ifu.io.axi4full
    io.lsu_bus.axi4full <> empty_axi4full_lsu.io.axi4full
    io.xbar_bus <> empty_xbar_bus.io.axi4full
  }.elsewhen (state === ifu_waitr) {
    io.ifu_bus.axi4full <> io.xbar_bus
    io.lsu_bus.axi4full <> empty_axi4full_lsu.io.axi4full
  }.elsewhen (state === lsu_waitr || state === lsu_waitw) {
    io.lsu_bus.axi4full <> io.xbar_bus
    io.ifu_bus.axi4full <> empty_axi4full_lsu.io.axi4full
  }.otherwise {
    io.ifu_bus.axi4full <> empty_axi4full_ifu.io.axi4full
    io.lsu_bus.axi4full <> empty_axi4full_lsu.io.axi4full
    io.xbar_bus <> empty_xbar_bus.io.axi4full
  }

  // 轮询 先询 ifu 再询 lsu
  switch(state) {
    is(both_idle) {
      when(io.ifu_bus.bus_reqr) {
        state := ifu_waitr 
        ifu_ac := 1.B 
        //printf("arbiter->IFU\n")
      }.elsewhen(io.lsu_bus.bus_reqr) {
        state := lsu_waitr 
        lsu_ac := 1.B 
        //printf("arbiter->LSUR\n")
      }.elsewhen(io.lsu_bus.bus_reqw) {
        state := lsu_waitw
        lsu_ac := 1.B 
        //printf("arbiter->LSUW\n")
      }
    }
    is(ifu_waitr) {
      when(io.ifu_bus.axi4full.rready & io.ifu_bus.axi4full.rvalid) {
        // 读握手，会在这个周期内返回
        state := both_idle
        ifu_ac := 0.B
        //printf("arbiter IFU ret\n")
      }
    }
    is(lsu_waitr) {
      when(io.lsu_bus.axi4full.rready & io.lsu_bus.axi4full.rvalid) {
        state := both_idle
        lsu_ac := 0.B
        //printf("arbiter LSUR ret\n")
      }
    }
    is(lsu_waitw) {
      when(io.lsu_bus.axi4full.bready & io.lsu_bus.axi4full.bvalid) {
        state := both_idle
        lsu_ac := 0.B
        //printf("arbiter LSUW ret\n")
      }
    }
  }
}

