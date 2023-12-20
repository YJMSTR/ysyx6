module DPIC_IFU(valid, pc, inst);
  input valid;
  input [31:0] pc;
  output reg [31:0] inst;
  import "DPI-C" function void pmem_read(
    input int raddr, output int rdata);
  always @(*) begin
    if (valid) begin 
      pmem_read(pc, inst);
    end else begin
      inst = 0;
    end
  end
endmodule