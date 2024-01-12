module DPIC_IFU(valid, pc, inst, clk);
  input valid;
  input [31:0] pc;
  output reg [31:0] inst;
  input clk;
  import "DPI-C" function void npc_pmem_read(
    input int raddr, output int rdata);
  always @(posedge clk) begin
    if (valid) begin 
      npc_pmem_read(pc, inst);
      //$display("npc inst fetch pmem read."); 
    end else begin
      inst = 0;
    end
  end
endmodule