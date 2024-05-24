// module DPIC_EBREAK(isEbreak, clk);
//   input isEbreak;
//   input clk;
//   import "DPI-C" function void ebreak();
//   always @(posedge clk) begin
//     if (isEbreak) begin 
//       ebreak();
//     end else begin

//     end
//   end
// endmodule
module DPIC_EBREAK(isEbreak, clk);
  input isEbreak;
  input clk;
  // import "DPI-C" function void ebreak();
  always @(posedge clk) begin
    if (isEbreak) begin 
      // ebreak();
    end else begin

    end
  end
endmodule