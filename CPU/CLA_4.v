`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/01 16:37:15
// Design Name: 
// Module Name: CLA_4
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

    
//module CLA_4(X0,X1,X2,X3,Y0,Y1,Y2,Y3,Cin,S0,S1,S2,S3,Cout);
//    input Cin,X0,X1,X2,X3,Y0,Y1,Y2,Y3;
//    output S0,S1,S2,S3,Cout;
//    or or1(P0,X0,Y0);
//    or or2(P1,X1,Y1);
//    or or3(P2,X2,Y2);
//    or or4(P3,X3,Y3);
//    and and1(G0,X0,Y0);
//    and and2(G1,X1,Y1);
//    and and3(G2,X2,Y2);
//    and and4(G3,X3,Y3);

module CLA_4(X,Y,Cin,S,Cout);
    input [3:0] X,Y;
    input Cin;
    output Cout;
    output [3:0] S;
    or or1(P0,X[0],Y[0]);
    or or2(P1,X[1],Y[1]);
    or or3(P2,X[2],Y[2]);
    or or4(P3,X[3],Y[3]);
    and and1(G0,X[0],Y[0]);
    and and2(G1,X[1],Y[1]);
    and and3(G2,X[2],Y[2]);
    and and4(G3,X[3],Y[3]);

    not not0(G0_n,G0);
    not not1(G1_n,G1);
    not not2(G2_n,G2);
    not not3(G3_n,G3);
    
    //Cout0
    and and0_1(P0andCin,P0,Cin);
    not not0_1(P0andCin_n,P0andCin);
    and and0_2(Cout0before,G0_n,P0andCin_n);
    not not0_2(Cout0,Cout0before);
    //S0
    and and0_3(P0_and_G0_n,P0,G0_n);
    xor xor0(S[0],P0_and_G0_n,Cin);
    
    //Cout1
    and and1_1(P1andG0,P1,G0);
    not not1_1(P1andG0_n,P1andG0);
    and and1_2(P1andP0andCin,P1,P0,Cin);
    not not1_2(P1andP0andCin_n,P1andP0andCin);
    and and1_3(Cout1before,G1_n,P1andG0_n,P1andP0andCin_n);
    not not1_3(Cout1,Cout1before);
    
    //S1
    and and1_4(P1_and_G1_n,P1,G1_n);
    xor xor1(S[1],P1_and_G1_n,Cout0);
    
    //Cout2
    and and2_1(P2andG1,P2,G1);
    not not2_1(P2andG1_n,P2andG1);
    and and2_2(P2andP1andG0,P2,P1,G0);
    not not2_2(P2andP1andG0_n,P2andP1andG0);
    and and2_3(P2andP1andP0andCin,P2,P1,P0,Cin);
    not not2_3(P2andP1andP0andCin_n,P2andP1andP0andCin);
    and and2_4(Cout2before,G2_n,P2andG1_n,P2andP1andG0_n,P2andP1andP0andCin_n);
    not not2_4(Cout2,Cout2before);
    
    //S2
    and and2_5(P2_and_G2_n,P2,G2_n);
    xor xor2(S[2],P2_and_G2_n,Cout1);
    
    //Cout3
    and and3_1(P3andG2,P3,G2);
    not not3_1(P3andG2_n,P3andG2);
    and and3_2(P3andP2andG1,P3,P2,G1);
    not not3_2(P3andP2andG1_n,P3andP2andG1);
    and and3_3(P3andP2andP1andG0,P3,P2,P1,G0);
    not not3_3(P3andP2andP1andG0_n,P3andP2andP1andG0);
    and and3_4(P3andP2andP1andP0andCin,P3,P2,P1,P0,Cin);
    not not3_4(P3andP2andP1andP0andCin_n,P3andP2andP1andP0andCin);
    and and3_5(Cout3before,G3_n,P3andG2_n,P3andP2andG1_n,P3andP2andP1andG0_n,P3andP2andP1andP0andCin_n);
    not not3_5(Cout3,Cout3before);
    
    //S3
    and and3_6(P3_and_G3_n,P3,G3_n);
    xor xor3(S[3],P3_and_G3_n,Cout2);
    
    assign Cout = Cout3;
endmodule


module CLA_4_Test;
reg Cin,X0,X1,X2,X3,Y0,Y1,Y2,Y3;
wire S0,S1,S2,S3,Cout;
CLA_4 uut (.X0(X0),.X1(X1),.X2(X2),.X3(X3),.Y0(Y0),.Y1(Y1),.Y2(Y2),.Y3(Y3),.Cin(Cin),.S0(S0),.S1(S1),.S2(S2),.S3(S3),.Cout(Cout));
    initial begin
        X0=1;
        X1=0;
        X2=1;
        X3=1;
        Y0=1;
        Y1=1;
        Y2=0;
        Y3=1;
        Cin=1;
        
        #50;
        
        X0=1;
        X1=0;
        X2=0;
        X3=0;
        Y0=1;
        Y1=1;
        Y2=0;
        Y3=1;
        Cin=1;
        
    end
endmodule