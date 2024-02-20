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

  val writeAddr = RegInit(0.U(32.W))
  val writeData = RegInit(0.U(XLEN.W))
  val writeMask = RegInit(0.U(8.W))
  
  val r_idle :: r_recv_data :: r_wait_ready :: Nil = Enum(3)
  val r_state = RegInit(r_idle)


  io.axi4lite.arready := r_state === r_idle
  dpic_mem.io.raddr := readAddr
  dpic_mem.io.valid := r_state === (r_recv_data & delayDone)
  switch(r_state) {
    is(r_idle) { // arready == 1
      when(io.axi4lite.arvalid) { 
        //此时握手成功，接收到了 araddr
        readAddr := io.axi4lite.araddr
        // 这里本应对地址进行一些检查，来判断接收到的地址是不是合法地址
        // 如果是，跳转到接收数据的状态 r_recv_data
        // 如果不是，rresp 要被设置，并且返回读响应，这里暂未实现 
        r_state := r_recv_data
      }
      when(io.axi4lite.rready) {
        rvalidReg := false.B
      }
    }
    is(r_recv_data) {
      when(delayDone) {
        rvalidReg := true.B
        readData := dpic_mem.io.rdata
        r_state := r_wait_ready
      }.otherwise{
        delayCounter := delayCounter + 1.U
        readData := 0.U
      }
    }
  }


}

