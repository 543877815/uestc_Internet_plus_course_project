`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/10/31 10:56:43
// Design Name: 
// Module Name: MUX2X1
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


module MUX2X1(A0,A1,S,Y);
    input A0,A1,S;
    output Y;
    not i0(S_n,S);
    nand i1(A0_S,A0,S_n);
    nand i2(A1_S,A1,S);
    nand i3(Y,A0_S,A1_S);
endmodule

module MUX2X1_TEST;
    reg A0, A1, S;
    wire Y;
    MUX2X1 MUX2X1_test(.A0(A0),.A1(A1),.S(S),.Y(Y));
        initial begin
            A0 = 1;
            A1 = 0;
            S = 0;
            #20;
            S = 1;
        end
endmodule