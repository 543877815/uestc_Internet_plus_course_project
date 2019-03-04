`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/06 10:13:14
// Design Name: 
// Module Name: ADDSUB_32
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


module ADDSUB_32(X, Y, Sub, S, Cout);
    input [31:0] X,Y;
    input Sub;
    output [31:0]S;
    output Cout;
    wire Cout1;
    CLA_32 adder0 (X, Y^{32{Sub}}, Sub, S, Cout);
endmodule

module ADDSUB_32_TEST;
reg [31:0] X,Y;
reg Sub;
wire [31:0]S;
wire Cout;
ADDSUB_32 addsubtest ( .X(X), .Y(Y), .Sub(Sub), .S(S), .Cout(Cout));
    initial begin
      X = 'b00001111000011110000111100001111;
      Y = 'b01110000111100001111000011110000;
      Sub = 1;
      #20;
      X = 'b01110000111100001111000011110000;
      Y = 'b00001111000011110000111100001111;
      #20;
      Sub = 0;
    end
endmodule