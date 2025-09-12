// This very simple example can be retimed to use a single register.
//
// Churchroad backend currently requires this to be set.
(* top *)
module needs_retiming(
  input logic clk,
  input logic a,
  input logic b,
  output logic y
);

  logic a_r, b_r;
  always_ff @(posedge clk) begin
    a_r <= a;
    b_r <= b;
  end

  assign y = a_r & b_r;
endmodule