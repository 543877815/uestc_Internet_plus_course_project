`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/02 17:23:23
// Design Name: 
// Module Name: CLA_32_plus4
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


module CLA_32_plus4(X,S,En);
    input [31:0] X;
    input En;
    output [31:0]S;
    assign S = X + 'b00000000000000000000000000000100;
endmodule

module CLA_32_plus4_TEST;
    reg [31:0] X;
    wire [31:0] S;
    CLA_32_plus4 CLA_32_plus4_test(.X(X),.S(S));
        initial begin;
            X = 'b00000000000000000000000000000100;
            #20;
            X = 'b00000000000000000000000000000000;
            #20;
            X = 'b00000000000000000000000000001000;
        end
endmodule