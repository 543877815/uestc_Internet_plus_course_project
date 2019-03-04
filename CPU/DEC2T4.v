`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/10/31 10:52:15
// Design Name: 
// Module Name: DEC2T4
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


module DEC2T4(I0,I1,En,Y0,Y1,Y2,Y3);
    input I0,I1,En;
    output Y0,Y1,Y2,Y3;
    not i0(I0_n,I0);
    not i1(I1_n,I1);
    not i2(En_n,En);
    nor nor0(Y0,I0,I1,En_n);
    nor nor1(Y1,I0,I1_n,En_n);
    nor nor2(Y2,I0_n,I1,En_n);
    nor nor3(Y3,I0_n,I1_n,En_n);
endmodule
