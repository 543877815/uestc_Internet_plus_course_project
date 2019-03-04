`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/05 21:30:23
// Design Name: 
// Module Name: add4_head
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module add4_head ( a, b, ci, s, pp, gg);



input[3:0]    a;

input[3:0]    b;

input            ci;



output[3:0]  s;

output          pp;

output          gg;



wire[3:0]       p;

wire[3:0]       g;

wire[2:0]       c;



assign p[0] = a[0] ^ b[0];

assign p[1] = a[1] ^ b[1];

assign p[2] = a[2] ^ b[2];

assign p[3] = a[3] ^ b[3];



assign g[0] = a[0] & b[0];

assign g[1] = a[1] & b[1];

assign g[2] = a[2] & b[2];

assign g[3] = a[3] & b[3];



assign c[0] = (p[0] & ci) | g[0];

assign c[1] = (p[1] & c[0]) | g[1];

assign c[2] = (p[2] & c[1]) | g[2];



assign pp = p[3] & p[2] & p[1] & p[0];

assign gg  = g[3] | (p[3] & (g[2] | p[2] & (g[1] | p[1] & g[0])));



assign s[0] = p[0] ^ ci;

assign s[1] = p[1] ^ c[0];

assign s[2] = p[2] ^ c[1];

assign s[3] = p[3] ^ c[2];



endmodule


module add4_head_TEST;
reg [3:0] a,b;
reg ci;
wire [3:0] s;
wire pp,gg;
add4_head ttt ( .a(a), .b(b), .ci(ci), .s(s), .pp(pp), .gg(gg) );
    initial begin
      a = 'b1000;
      b = 'b0001;
      ci = 1;
    end
endmodule