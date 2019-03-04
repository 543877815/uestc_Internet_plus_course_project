`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/06 13:04:45
// Design Name: 
// Module Name: EXT16T32
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


module EXT16T32(X,Se,Y);
    input [15:0] X;
    input Se;
    output [31:0]Y;
    wire[31:0]E0,E1;
    wire[15:0]e = {16{X[15]}};
    parameter z = 16'b0;
    assign E0 = {z,X};
    assign E1 = {e,X};
    MUX2X32 i(E0,E1,Se,Y);
endmodule

module EXT16T32_TEST;
    reg [15:0] X;
    reg Se;
    wire [31:0]Y;
    EXT16T32 EXT16T32_test(.X(X), .Se(Se), .Y(Y));
        initial begin;
            Se = 0;
            X = 'b1111000011110000;
        
            #20;
            
            Se = 1;
        end
endmodule