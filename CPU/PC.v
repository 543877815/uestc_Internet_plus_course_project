`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/02 16:35:36
// Design Name: 
// Module Name: PC
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


module PC(
    input Clk,
    input En,
    input [31:0] data_in,
    output [31:0] data_out
    );
    
    reg [31:0] data = 32'b0;
    
    always @(posedge Clk) begin
        data<=data_in;       //enable,input
    end
    function [31:0] data_sub;
        input En;
        input [31:0] data;
            case(En)
                1:data_sub = data - 4;
                default:data_sub = data;
            endcase
    endfunction
    assign data_out = data_sub(En,data);
//    assign data_out = data;
endmodule
