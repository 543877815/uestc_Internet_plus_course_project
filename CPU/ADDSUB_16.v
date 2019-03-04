`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/06 09:45:38
// Design Name: 
// Module Name: ADDSUB_16
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


module ADDSUB_16(X, Y, Sub, S, Cout);

    input [15:0] X, Y; 
    input Sub;
    
    output [15:0] S;
    output Cout;
    
    CLA_16 adder0 (X, Y^{16{Sub}}, Sub, S, Cout);

endmodule


module ADDSUB_16_TEST;
reg [15:0] X,Y;
reg Sub;
wire [15:0] S;
wire Cout;
ADDSUB_16 addsubtest ( .X(X), .Y(Y), .Sub(Sub), .S(S), .Cout(Cout));
    initial begin
      X = 136;
      Y = 17;
      Sub = 1;
      
      #20;
      X = 'b1111111111111111;
      Y = 'b1111111111111110;
      Sub = 1;
    end
endmodule