module DPIC_IFU(valid, pc, inst);
  input valid;
  input [31:0] pc;
  output reg [31:0] inst;
  //input clk;
  import "DPI-C" function void npc_pmem_read(
    input int raddr, output longint rdata);

  reg [63:0] fulldata;
  always @(*) begin
    if (valid) begin
      // $display("npc inst fetch pmem read."); 
      // $display("pc value: %d", pc);
      npc_pmem_read(pc, fulldata);
      inst = fulldata[31:0];
      
    end else begin
      fulldata = 0;
      inst = 0;
    end
  end
endmodule