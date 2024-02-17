import chisel3._
import chisel3.util._
import AXI4.* 

// 作为 AXI4-Lite 的 slave 

class FAKE_SRAM(delay: Int) extends Module {
  val io = IO(new Bundle{
    val axi4lite = Flipped(new AXI4LiteInterface)
  })

  val s_idle :: s_read :: s_respond :: Nil = Enum(3)
  val read_state = RegInit(s_idle)
  val delayCounter = RegInit(0.U(5.W))
  val delay = 1.U //这里调延时
  val delayDone = delayCounter === delay // delaydone 表示取回数据了

  val dpic_mem = Module(new DPIC_MEM)


  val readData = RegInit(0.U(XLEN.W))
  val readAddr = RegInit(0.U(32.W))

  io.axi4lite.rvalid := read_state === s_respond
  io.axi4lite.rdata := readData
  io.axi4lite.rresp := 0.U
  io.axi4lite.arready := read_state === s_idle
  dpic_mem.io.raddr := io.axi4lite.araddr
  dpic_mem.io.valid := delayDone

  // 把写地址，写数据和写回复的握手信号置为 0，因为目前还没有实现写操作
  io.axi4lite.awready := false.B
  io.axi4lite.wready := false.B
  io.axi4lite.bvalid := false.B
  io.axi4lite.bresp := 0.U
  // 把 DPIC_MEM 和写相关的信号进行赋值
  dpic_mem.io.waddr := 0.U
  dpic_mem.io.wdata := 0.U
  dpic_mem.io.wen := false.B
  dpic_mem.io.wmask := 0.U
  dpic_mem.io.clk := clock

  //从机读取数据的状态机
  //一共三个状态：idle 等待主机发来 araddr
  //read 进行读取
  //respond 表示读取完成，用 readData 存放读取到的数据，并发回上游
  //发回上游即将 rdata := readData
  //但向readData寄存器赋值是有一个周期延迟的，是不是应该提前赋值？
  //同一个周期内对 reg 进行读写时，会先写再读
  switch(read_state) {
    is(s_idle) {
      // idle 状态下 arready 为 1,等待读地址的 valid 信号
      when(io.axi4lite.arvalid) {
        //如果 ar channel 握手成功，就切换到 s_read
        //并且从机将 araddr 存一下
        //模拟任意周期延迟的存储器，这里用延迟计数器来实现，此处清零
        read_state := s_read
        readAddr := io.axi4lite.araddr
        delayCounter := 0.U
      }
      // arvalid 不为 1 就继续等，直到握手
    }
    is(s_read) {
      // read 状态即存储器进行读取，直到取回数据
      // 进入这一状态说明已经接收到了 araddr
      when(delayDone) { // 模拟经过若干周期后取回了数据
        read_state := s_respond  //即将 rvalid = 1
        // 此时将 dpic_mem.io.valid = 1, 进行读取，并立刻读出数据
      }.otherwise{
        //还没取回数据，给延迟计数器加1
        delayCounter := delayCounter + 1.U
      }
    }
    is(s_respond) {//此时 rvalid 为 1, delayDone仍然为高电平
      // respond 状态下，如果 rready 为 1，说明 master 准备好接收读取的数据了
      // 发回数据，切换回 idle 状态准备接收下一个数据
      readData := dpic_mem.io.rdata // 在 ready 为 1 之前，valid 为真要求发送方保持数据直到 ready 为 1
      when(io.axi4lite.rready) {
        read_state := s_idle
      }
    }
  }

}

