`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/07 23:18:09
// Design Name: 
// Module Name: DEC5T32E
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


module DEC5T32E(I,En,Y);
    input [4:0]I;
    input En;
    output [31:0]Y;
    not i0(In0,I[0]);
    not i1(In1,I[1]);
    not i2(In2,I[2]);
    not i3(In3,I[3]);
    not i4(In4,I[4]);
    not i(En_n,En);
    
    nor y31(Y[0],I[4],I[3],I[2],I[1],I[0],En_n);
    nor y30(Y[1],I[4],I[3],I[2],I[1],In0,En_n);
    nor y29(Y[2],I[4],I[3],I[2],In1,I[0],En_n);
    nor y28(Y[3],I[4],I[3],I[2],In1,In0,En_n);
    nor y27(Y[4],I[4],I[3],In2,I[1],I[0],En_n);
    nor y26(Y[5],I[4],I[3],In2,I[1],In0,En_n);
    nor y25(Y[6],I[4],I[3],In2,In1,I[0],En_n);
    nor y24(Y[7],I[4],I[3],In2,In1,In0,En_n);
    nor y23(Y[8],I[4],In3,I[2],I[1],I[0],En_n);
    nor y22(Y[9],I[4],In3,I[2],I[1],In0,En_n);
    nor y21(Y[10],I[4],In3,I[2],In1,I[0],En_n);
    nor y20(Y[11],I[4],In3,I[2],In1,In0,En_n);
    nor y19(Y[12],I[4],In3,In2,I[1],I[0],En_n);
    nor y18(Y[13],I[4],In3,In2,I[1],In0,En_n);
    nor y17(Y[14],I[4],In3,In2,In1,I[0],En_n);
    nor y16(Y[15],I[4],In3,In2,In1,In0,En_n);
    nor y15(Y[16],In4,I[3],I[2],I[1],I[0],En_n);
    nor y14(Y[17],In4,I[3],I[2],I[1],In0,En_n);
    nor y13(Y[18],In4,I[3],I[2],In1,I[0],En_n);
    nor y12(Y[19],In4,I[3],I[2],In1,In0,En_n);
    nor y11(Y[20],In4,I[3],In2,I[1],I[0],En_n);
    nor y10(Y[21],In4,I[3],In2,I[1],In0,En_n);
    nor y9(Y[22],In4,I[3],In2,In1,I[0],En_n);
    nor y8(Y[23],In4,I[3],In2,In1,In0,En_n);
    nor y7(Y[24],In4,In3,I[2],I[1],I[0],En_n);
    nor y6(Y[25],In4,In3,I[2],I[1],In0,En_n);
    nor y5(Y[26],In4,In3,I[2],In1,I[0],En_n);
    nor y4(Y[27],In4,In3,I[2],In1,In0,En_n);
    nor y3(Y[28],In4,In3,In2,I[1],I[0],En_n);
    nor y2(Y[29],In4,In3,In2,I[1],In0,En_n);
    nor y1(Y[30],In4,In3,In2,In1,I[0],En_n);
    nor y0(Y[31],In4,In3,In2,In1,In0,En_n);
endmodule


module DEC5T32E_TEST;
reg [4:0]I;
reg En;
wire [31:0]Y;
DEC5T32E aaa(.I(I),.En(En),.Y(Y));
    initial begin
            I='b00000;
            En=1;
            #20;
        
            I='b00011;
            #20;
            
            I='b10011;
            #20;
            
            En =0;
    end
endmodule
