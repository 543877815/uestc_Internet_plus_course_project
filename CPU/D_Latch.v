`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/06 13:09:40
// Design Name: 
// Module Name: D_Latch
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


module D_Latch(D,En,Q,Qn);
    input D,En;
    output Q,Qn;
    wire Sn,Rn,Dn;
    not i0(Dn,D);
    nand i1(Sn,D,En);
    nand i2(Rn,En,Dn);
    nand i3(Q,Sn,Qn);
    nand i4(Qn,Q,Rn);
endmodule

module D_Latch_TEST;
    reg D,En;
    wire Q,Qn;
    D_Latch ddd( .D(D), .En(En), .Q(Q), .Qn(Qn) );
    initial begin;

       D=1;
       En=1;
       #20;
       D=0;
       En=1;
       #20;
       En=0;
       D=0;
       En=0;
       #20;
       D=1;
       En=0;
       #20;
     end
endmodule
