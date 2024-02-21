import chisel3._
import chisel3.util._
import Configs._ 

// 作为 AXI4-Lite 的 slave 

class FAKE_SRAM_LSU(delay: UInt) extends Module {
  val io = IO(new Bundle{
    val axi4lite = new AXI4LiteInterface
  })

  val delayCounter = RegInit(0.U(5.W))
  val delayDone = delayCounter === delay 

  val dpic_mem = Module(new DPIC_MEM)

  val readData = RegInit(0.U(XLEN.W))
  val readAddr = RegInit(0.U(32.W))
  val rvalidReg = RegInit(false.B)

  val r_idle :: r_read :: r_wait_ready :: Nil = Enum(3)
  val r_state = RegInit(r_idle)

  io.axi4lite.rvalid := rvalidReg
  io.axi4lite.rdata := readData
  io.axi4lite.rresp := 0.U

  io.axi4lite.arready := r_state === r_idle

  dpic_mem.io.raddr := readAddr
  dpic_mem.io.valid := delayDone & r_state === r_read

  // 把写地址，写数据和写回复的握手信号置为 0，因为目前还没有实现写操作
  io.axi4lite.awready := false.B
  io.axi4lite.wready := false.B
  io.axi4lite.bvalid := false.B
  io.axi4lite.bresp := 0.U

  switch(r_state) {
    is(r_idle) {
      readData := 0.U
      when(io.axi4lite.arvalid){
        readAddr := io.axi4lite.araddr
        r_state := r_read
        delayCounter := 0.U
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
      when(io.axi4lite.rready) {
        rvalidReg := false.B  //传输完成，置为false
        r_state := r_idle
      }
    }
  }
  


}

