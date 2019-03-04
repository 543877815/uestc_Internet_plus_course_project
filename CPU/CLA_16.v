`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/01 16:39:09
// Design Name: 
// Module Name: CLA_16
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


module CLA_16(X,Y,Cin,S,Cout);
    input [15:0] X, Y;
    input Cin;
    output [15:0] S;
    output Cout;

    wire Cout0,Cout1,Cout2;
    CLA_4 add0(X[3:0],Y[3:0],Cin,S[3:0],Cout0);
    CLA_4 add1(X[7:4],Y[7:4],Cout0,S[7:4],Cout1);
    CLA_4 add2(X[11:8],Y[11:8],Cout1,S[11:8],Cout2);
    CLA_4 add3(X[15:12],Y[15:12],Cout2,S[15:12],Cout);
//    CLA_4 add0(X[0],X[1],X[2],X[3],Y[0],Y[1],Y[2],Y[3],Cin,S[0],S[1],S[2],S[3],Cout0);
//    CLA_4 add1(X[4],X[5],X[6],X[7],Y[4],Y[5],Y[6],Y[7],Cout0,S[4],S[5],S[6],S[7],Cout1);
//    CLA_4 add2(X[8],X[9],X[10],X[11],Y[8],Y[9],Y[10],Y[11],Cout1,S[8],S[9],S[10],S[11],Cout2);
//    CLA_4 add3(X[12],X[13],X[14],X[15],Y[12],Y[13],Y[14],Y[15],Cout2,S[12],S[13],S[14],S[15],Cout);     
 endmodule


module CLA_16_TEST;
    reg [15:0] X, Y;
    reg Cin;
    wire[15:0]S;
    wire Cout;
    CLA_16 uut (.X(X),.Y(Y),.Cin(Cin),.S(S),.Cout(Cout));
    initial begin
        X='b0000000000000000;
        Y='b0000111111111111;
        Cin=0;
    end
endmodule