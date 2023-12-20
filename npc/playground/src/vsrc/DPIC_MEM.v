module DPIC_MEM(valid, wen, raddr, rdata, waddr, wdata, wmask);
  input valid;
  input wen;
  input [31:0] raddr;
  output reg [31:0] rdata;
  input [31:0] waddr;
  input [31:0] wdata;
  input [7:0] wmask;
  import "DPI-C" function void pmem_read(
    input int raddr, output int rdata);
  import "DPI-C" function void pmem_write(
  input int waddr, input int wdata, input byte wmask);
  always @(*) begin
    if (valid) begin // 有读写请求时
      if (~wen) begin // 读
        pmem_read(raddr, rdata);
      end else begin // 有写请求时
        pmem_write(waddr, wdata, wmask);
        rdata = 0;
      end
    end
    else begin
      rdata = 0;
    end
  end
endmodule