`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/10/30 21:51:26
// Design Name: 
// Module Name: cmosnot
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


module cmosnot(F,A);
    input A;
    output F;
    supply1 Vcc;
    supply0 gnd;
    pmos Q2(F, Vcc, A);
    nmos Q1(F, gnd, A);
endmodule
