`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/24 11:03:22
// Design Name: 
// Module Name: MUX2X5
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


`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/06 11:14:01
// Design Name: 
// Module Name: MUX2X32
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


module MUX2X5(A0,A1,S,Y);
    input [4:0] A0,A1;
    input S;
    output [4:0] Y;
    function [4:0] select;
        input [4:0] A0,A1;
        input S;
            case (S)
                0:select = A0;
                1:select = A1;
            endcase
    endfunction
    assign Y = select(A0,A1,S);
endmodule


module MUX2X5_TEST;
    reg [4:0] A0,A1;
    reg S;
    wire [4:0] Y;
    MUX2X5 MUX2X5_test(.A0(A0), .A1(A1), .S(S), .Y(Y));
        initial begin;
          A0 = 'b11111;
          A1 = 'b00000;
          S = 1;
          
          #20;
          
           A0 = 'b11111;
           A1 = 'b00000;
           S = 0;
        end
endmodule

