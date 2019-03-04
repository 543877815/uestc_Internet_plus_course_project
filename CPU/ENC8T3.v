`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/06 13:27:06
// Design Name: 
// Module Name: ENC8T3
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


module ENC8T3(I,Y,Idle);
    input [7:0] I;
    output [2:0] Y;
    output Idle;
    
    not n0(I0,I[0]);
    not n1(I1,I[1]);
    not n2(I2,I[2]);
    not n3(I3,I[3]);
    not n4(I4,I[4]);
    not n5(I5,I[5]);
    not n6(I6,I[6]);
    not n7(I7,I[7]);
    
    and and7(H7,I[7]);
    and and6(H6,I[6],I7);
    and and5(H5,I[5],I6,I7);
    and and4(H4,I[4],I5,I6,I7);
    and and3(H3,I[3],I4,I5,I6,I7);
    and and2(H2,I[2],I3,I4,I5,I6,I7);
    and and1(H1,I[1],I2,I3,I4,I5,I6,I7);
    and and0(H0,I[0],I1,I2,I3,I4,I5,I6,I7);
    
    or or1(Y[2],H4,H5,H6,H7);
    or or2(Y[1],H2,H3,H6,H7);
    or or3(Y[0],H1,H3,H5,H7);
    and andIdle (Idle,I0,I1,I2,I3,I4,I5,I6,I7);
endmodule

module ENC8T3_TEST;
    reg [7:0] I;
    wire [2:0] Y;
    wire Idle;
    ENC8T3 ENC8T3_test(.I(I),.Y(Y),.Idle(Idle));
        initial begin
            I = 'b10000000; 
            #20;
            I = 'b10110000;
            #20;
            I = 'b01000000;
            #20;
            I = 'b00000001;
        end
endmodule