// module DFF with synchronous reset
module DFF(q, d, clk, reset);

output q; 
input d, clk, reset;
reg q;

always @(posedge reset or negedge clk)
if (reset)
  q = 1'b0;
else
  q = d;

endmodule

module MUX4_1(s0, s1, i0, i1, i2, i3, o);
//---------------------------------------------
//Declare input, output port
//Declare parameter type( wire or reg)
output o; 
input s0, s1, i0, i1, i2, i3;
wire o;

assign o = ( s0 == 0 && s1 == 0 ) ? i0 : (s0 == 1 && s1 == 0 )? i1: ( s0 == 0 && s1 == 1 )? i2 : i3 ;
//---------------------------------------------
//Design your program by using assignment
//e.g. assign o = i & s ; ......

endmodule

module Shift_Register(i, s, o, clk, reset, r);
//---------------------------------------------
//Declare input, output port
//Declare parameter type( wire or reg)
input [1:0]s ;
input [7:0]i ;
input clk, reset, r ;
output [7:0] o; 
wire [7:0]d;
wire [7:0]o;
MUX4_1 mux1(s[0], s[1], o[0], r, o[1], i[0], d[0]);
DFF d1(o[0], d[0], clk, reset);
MUX4_1 mux2(s[0], s[1], o[1], o[0], o[2], i[1], d[1]);
DFF d2(o[1], d[1], clk, reset);
MUX4_1 mux3(s[0], s[1], o[2], o[1], o[3], i[2], d[2]);
DFF d3(o[2], d[2], clk, reset);
MUX4_1 mux4(s[0], s[1], o[3], o[2], o[4], i[3], d[3]);
DFF d4(o[3], d[3], clk, reset);
MUX4_1 mux5(s[0], s[1], o[4], o[3], o[5], i[4], d[4]);
DFF d5(o[4], d[4], clk, reset);
MUX4_1 mux6(s[0], s[1], o[5], o[4], o[6], i[5], d[5]);
DFF d6(o[5], d[5], clk, reset);
MUX4_1 mux7(s[0], s[1], o[6], o[5], o[7], i[6], d[6]);
DFF d7(o[6], d[6], clk, reset);
MUX4_1 mux8(s[0], s[1], o[7], o[6], r, i[7], d[7]);
DFF d8(o[7], d[7], clk, reset);
endmodule
