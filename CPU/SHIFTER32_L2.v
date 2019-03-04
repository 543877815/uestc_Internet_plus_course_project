`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/02 17:09:22
// Design Name: 
// Module Name: SHIFTER32_L2
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


module SHIFTER32_L2(X,Sh);
    input [31:0] X;
    output [31:0]Sh;
    wire [4:0]Sa;
    assign Arith = 1;
    assign Sa[0]=0;
    assign Sa[1]=1;
    assign Sa[2]=0;
    assign Sa[3]=0;
    assign Sa[4]=0;
    assign Right = 0;
    wire [31:0] T4,S4,T3,S3,T2,S2,T1,S1,T0;
    wire a = X[31]&Arith;
    wire [15:0]e = {16{a}};
    parameter z = 16'b0;
    wire [31:0] L1u,L1d,L2u,L2d,L3u,L3d,L4u,L4d,L5u,L5d;
    
    assign L1u = {X[15:0],z};
    assign L1d = {e,X[31:16]};
    MUX2X32 M1l(L1u,L1d,Right,T4);
    MUX2X32 M1D(X,T4,Sa[4],S4);
    
    assign L2u = {S4[23:0],z[7:0]};
    assign L2d = {e[7:0],S4[31:8]};
    MUX2X32 M2l(L2u,L2d,Right,T3);
    MUX2X32 M2D(S4,T3,Sa[3],S3);
    
    assign L3u = {S3[27:0],z[3:0]};
    assign L3d = {e[3:0],S3[31:4]};
    MUX2X32 M3l(L3u,L3d,Right,T2);
    MUX2X32 M3D(S3,T2,Sa[2],S2);
    
    assign L4u = {S2[29:0],z[1:0]};
    assign L4d = {e[1:0],S2[31:2]};
    MUX2X32 M4l(L4u,L4d,Right,T1);
    MUX2X32 M4D(S2,T1,Sa[1],S1);
    
    assign L5u = {S1[30:0],z[0]};
    assign L5d = {e[0],S1[31:1]};
    MUX2X32 M5l(L5u,L5d,Right,T0);
    MUX2X32 M5D(S1,T0,Sa[0],Sh);
endmodule

module SHIFTER32_L2_TEST;
    reg [31:0] X;
    wire [31:0] Sh;
    SHIFTER32_L2 SHIFTER32_L2_test(.X(X),.Sh(Sh));
    initial begin
      X = 'b00000000000000000000000000000001;
      
      #20;
      
      X = 'b00000000000000000000000000000100;

      
      #20;
      
      X = 'b10000000000000000000000000010000;

    end
endmodule