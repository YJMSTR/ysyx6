import chisel3._
import chisel3.util._
import Configs._ 

// 作为 AXI4-Lite 的 slave 

class FAKE_SRAM_IFU(delay: UInt) extends Module {
  val io = IO(new Bundle{
    val axi4lite = new AXI4LiteInterface
  })

  val ar_idle :: ar_read :: Nil = Enum(2)
  val ar_state = RegInit(ar_idle)

  val delayCounter = RegInit(0.U(5.W))
  val delayDone = delayCounter === delay // delaydone 表示取回数据了

  val dpic_ifu = Module(new DPIC_IFU)


  val readData = RegInit(0.U(XLEN.W))
  val readAddr = RegInit(0.U(32.W))
  val rvalidReg = RegInit(false.B)

  io.axi4lite.rvalid := rvalidReg
  io.axi4lite.rdata := readData
  io.axi4lite.rresp := 0.U

  io.axi4lite.arready := ar_state === ar_idle

  dpic_ifu.io.pc := readAddr
  dpic_ifu.io.valid := delayDone

  // 把写地址，写数据和写回复的握手信号置为 0，因为目前还没有实现写操作
  io.axi4lite.awready := false.B
  io.axi4lite.wready := false.B
  io.axi4lite.bvalid := false.B
  io.axi4lite.bresp := 0.U

  //从机 ar channel 的状态机
  //idle 等待主机发来 araddr
  //read 进行读取
  //发回上游即将 rdata := readData
  //但向readData寄存器赋值是有一个周期延迟的，是不是应该提前赋值？
  //同一个周期内对 reg 进行读写时，会先写再读
  switch(ar_state) {
    is(ar_idle) {
      // idle 状态下 arready 为 1,等待读地址的 valid 信号
      when(io.axi4lite.arvalid) {
        //如果 ar channel 握手成功，就切换到 ar_read
        //并且从机将 araddr 存一下
        //模拟任意周期延迟的存储器，这里用延迟计数器来实现，此处清零
        ar_state := ar_read
        readAddr := io.axi4lite.araddr
        delayCounter := 0.U
      }
      when(io.axi4lite.rready) {
        // 数据传输完成，将 rvalid 置为 false
        rvalidReg := false.B
      }
      // arvalid 不为 1 就继续等，直到握手
    }
    is(ar_read) {
      // read 状态即存储器进行读取，直到取回数据
      // 进入这一状态说明已经接收到了 araddr
      when(delayDone) { // 模拟经过若干周期后取回了数据
        rvalidReg := true.B  //即将 rvalid = 1
        ar_state := ar_idle
        // 此时将 dpic_mem.io.valid = 1, 进行读取，并立刻读出数据
        readData := dpic_ifu.io.inst // 在 ready 为 1 之前，valid 为真要求发送方保持数据直到 ready 为 1
      }.otherwise{
        //还没取回数据，给延迟计数器加1
        delayCounter := delayCounter + 1.U
      }
    }
  }

}

