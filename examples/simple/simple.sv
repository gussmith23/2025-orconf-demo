
// Churchroad backend currently requires this to be set.
(* top *)
module simple(
  input logic clk,
  input logic rst_n,
  input logic a,
  input logic b,
  output logic y
);

  assign y = a & b;
  
endmodule