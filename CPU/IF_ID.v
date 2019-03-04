`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/16 22:24:23
// Design Name: 
// Module Name: IF_ID
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


module IF_ID(We, Clk, Clrn, PC_in,PC_out,IR_in,IR_out);
     input We;
//     reg En;

//    always #10 begin
//        if(We) En <= ~We;
//        else En <= 1;
//    end
    
    function En1;
        input We;
            case(We)
                1:En1 = 0;
                default:En1 = 1;
            endcase
    endfunction
    assign En = En1(We);
    input [31:0] PC_in,IR_in;
    input Clk, Clrn;
    output [31:0] PC_out,IR_out;
    D_FFEC32 PC(PC_in,Clk,En,Clrn,PC_out);
    D_FFEC32 IR(IR_in,Clk,En,Clrn,IR_out);
endmodule
