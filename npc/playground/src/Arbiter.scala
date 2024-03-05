import chisel3._ 
import chisel3.util._ 
import Configs._

class BUS_IO extends Bundle {
  val axi4lite = new AXI4LiteInterface
  val bus_reqr = Input(Bool())
  val bus_reqw = Input(Bool())
  val bus_ac = Output(Bool())
}

class MyArbiter extends Module {
  val io = IO(new Bundle {
    val ifu_bus = new BUS_IO
    val lsu_bus = new BUS_IO
    val slave_sram  = Flipped(new AXI4LiteInterface)
  })

  val empty_axi4lite_ifu = Module(new empty_axi4lite_slave)
  val empty_axi4lite_lsu = Module(new empty_axi4lite_slave)
  val empty_axi4lite_sram = Module(new empty_axi4lite_master)




  val both_idle :: ifu_waitr :: lsu_waitr :: lsu_waitw :: Nil = Enum(4)
  val state = RegInit(both_idle)

  val ifu_ac = RegInit(0.B)
  val lsu_ac = RegInit(0.B)

  io.ifu_bus.bus_ac := ifu_ac 
  io.lsu_bus.bus_ac := lsu_ac


  io.ifu_bus.axi4lite <> empty_axi4lite_ifu.io.axi4lite
  io.lsu_bus.axi4lite <> empty_axi4lite_lsu.io.axi4lite
  io.slave_sram <> empty_axi4lite_sram.io.axi4lite
  when(state === both_idle) {
    io.ifu_bus.axi4lite <> empty_axi4lite_ifu.io.axi4lite
    io.lsu_bus.axi4lite <> empty_axi4lite_lsu.io.axi4lite
    io.slave_sram <> empty_axi4lite_sram.io.axi4lite
  }.elsewhen (state === ifu_waitr) {
    io.ifu_bus.axi4lite <> io.slave_sram
    io.lsu_bus.axi4lite <> empty_axi4lite_lsu.io.axi4lite
  }.elsewhen (state === lsu_waitr || state === lsu_waitw) {
    io.lsu_bus.axi4lite <> io.slave_sram
    io.ifu_bus.axi4lite <> empty_axi4lite_lsu.io.axi4lite
  }.otherwise {
    io.ifu_bus.axi4lite <> empty_axi4lite_ifu.io.axi4lite
    io.lsu_bus.axi4lite <> empty_axi4lite_lsu.io.axi4lite
    io.slave_sram <> empty_axi4lite_sram.io.axi4lite
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
      when(io.ifu_bus.axi4lite.rready & io.ifu_bus.axi4lite.rvalid) {
        // 读握手，会在这个周期内返回
        state := both_idle
        ifu_ac := 0.B
        //printf("arbiter IFU ret\n")
      }
    }
    is(lsu_waitr) {
      when(io.lsu_bus.axi4lite.rready & io.lsu_bus.axi4lite.rvalid) {
        state := both_idle
        lsu_ac := 0.B
        //printf("arbiter LSUR ret\n")
      }
    }
    is(lsu_waitw) {
      when(io.lsu_bus.axi4lite.bready & io.lsu_bus.axi4lite.bvalid) {
        state := both_idle
        lsu_ac := 0.B
        //printf("arbiter LSUW ret\n")
      }
    }
  }
}

