module DPIC_IFU(valid, pc, inst);
  input valid;
  input [63:0] pc;
  output reg [31:0] inst;
  //input clk;
  import "DPI-C" function void npc_pmem_read(
    input longint raddr, output longint rdata);

  reg [63:0] fulldata;
  always @(*) begin
    if (valid) begin
      npc_pmem_read(pc, fulldata);
      inst = fulldata[31:0];
      //$display("npc inst fetch pmem read."); 
    end else begin
      fulldata = 0;
      inst = 0;
    end
  end
endmodule