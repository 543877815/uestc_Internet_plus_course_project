`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/12 15:07:24
// Design Name: 
// Module Name: ALU
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


module ALU(X,Y,Aluc,R,Z,V);
    input [31:0] X,Y;
    input [1:0] Aluc;
    output [31:0] R;
    output Z,V;
    wire  [31:0] d_as, d_and, d_or, d_and_or;
    ADDSUB_32 as32(X, Y, Aluc[0], d_as);
    assign d_and = X&Y;
    assign d_or = X|Y;
    MUX2X32 select1(d_and, d_or, Aluc[0], d_and_or);
    MUX2X32 select2(d_as, d_and_or, Aluc[1], R);
    assign Z = ~|R;
    assign V = (~Aluc[1]&~Aluc[0]&~X[31]&~Y[31]&R[31])|(~Aluc[0]&~Aluc[1]&X[31]&Y[31]&~R[31])|(~Aluc[1]&Aluc[0]&~X[31]&Y[31]&R[31])|(~Aluc[1]&Aluc[0]&X[31]&~Y[31]&~R[31]);
endmodule

module ALU_TEST;
    reg [31:0]X,Y;
    reg [1:0]Aluc;
    wire[31:0] R;
    wire Z,V;
    ALU ALU_test(.X(X),.Y(Y),.Aluc(Aluc),.R(R),.Z(Z),.V(V));
        initial begin;
            X = 'b11110000111100001111000011110000;
            Y = 'b00001111000011110000111100001111;
            Aluc = 'b00;
            
            #20;
            
            Aluc = 'b01;
            
            #20;
            
            Aluc = 'b10;
            
            #20;
            Aluc = 'b11;
       end
endmodule