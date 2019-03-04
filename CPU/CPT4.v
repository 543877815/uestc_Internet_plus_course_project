`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/06 11:35:44
// Design Name: 
// Module Name: CPT4
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


module CPT4(A,B,Y);
    input [3:0] A,B;
    output Y;
    xor i0(D0,A[0],B[0]);
    xor i1(D1,A[1],B[1]);
    xor i2(D2,A[2],B[2]);
    xor i3(D3,A[3],B[3]);
    nor i4(Y,D0,D1,D2,D3);
endmodule
