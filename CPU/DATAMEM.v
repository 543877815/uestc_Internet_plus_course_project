`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/12 17:40:06
// Design Name: 
// Module Name: DATAMEM
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


module DATAMEM(Addr, Din, Clk, We, Dout);
    input [31:0] Addr, Din;
    input Clk, We;
    output [31:0] Dout;
    reg [31:0] Ram [31:0];
    
    //read data
    assign Dout = Ram [Addr[6:2]];
//    assign Dout = 32;
    always @(posedge Clk) begin
        if(We) Ram[Addr[6:2]] <= Din;
    end
    
    //write data
    integer i;
    initial begin
        for (i = 0;i < 32 ; i = i + 1)
            Ram[i] = i;
    end
endmodule
