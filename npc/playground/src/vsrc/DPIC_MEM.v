// module DPIC_MEM(valid, wen, raddr, rdata, waddr, wdata, wmask, clk);
//   input valid;
//   input wen;
//   input [31:0] raddr;
//   output reg [63:0] rdata;
//   input [31:0] waddr;
//   input [63:0] wdata;
//   input [7:0] wmask;
//   input clk;
//   import "DPI-C" function void npc_pmem_read(
//     input int raddr, output longint rdata);
//   import "DPI-C" function void npc_pmem_write(
//   input int waddr, input longint wdata, input byte wmask);
//   always @(posedge clk) begin
//     if (valid) begin // 有读写请求时
//       if (~wen) begin // 读
//         //$display("npc mem pmem read raddr = %h", raddr); 
//         npc_pmem_read(raddr, rdata);
//       end else begin // 有写请求时
//         //$display("npc mem pmem write. addr = %h, data = %h, mask = %h", waddr, wdata, wmask); 
//         npc_pmem_write(waddr, wdata, wmask);
//         rdata = 0;
//       end
//     end
//     else begin
//       rdata = 0;
//     end
//   end
// endmodule

module DPIC_MEM(valid, wen, raddr, rdata, waddr, wdata, wmask, clk);
  input valid;
  input wen;
  input [31:0] raddr;
  output reg [63:0] rdata;
  input [31:0] waddr;
  input [63:0] wdata;
  input [7:0] wmask;
  input clk;
  // import "DPI-C" function void npc_pmem_read(
  //   input int raddr, output longint rdata);
  // import "DPI-C" function void npc_pmem_write(
  // input int waddr, input longint wdata, input byte wmask);
  reg [7:0] mem[0:255]
  always @(posedge clk) begin
    if (valid) begin // 有读写请求时
      if (~wen) begin // 读
        //$display("npc mem pmem read raddr = %h", raddr); 
        // npc_pmem_read(raddr, rdata);
        rdata = mem[raddr];
      end else begin // 有写请求时
        //$display("npc mem pmem write. addr = %h, data = %h, mask = %h", waddr, wdata, wmask); 
        // npc_pmem_write(waddr, wdata, wmask);
        mem[waddr] = wdata&wmask;
        rdata = 0;
      end
    end
    else begin
      rdata = 0;
    end
  end
endmodule