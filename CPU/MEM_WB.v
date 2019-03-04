`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/12 15:23:12
// Design Name: 
// Module Name: MEM_WB
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


module MEM_WB(We,Clk, Clrn,D_in,D_out,C_in,C_out,Rd_in,Rd_out,M_Wreg,W_Wreg,M_Reg2reg,W_Reg2reg);
    input [31:0] D_in,C_in;
    input [4:0]Rd_in;
    input M_Wreg,M_Reg2reg;
    input We,Clk, Clrn;
    output [31:0] D_out,C_out;
    output [4:0]Rd_out;
    output W_Wreg,W_Reg2reg;
    D_FFEC32 D(D_in,Clk,We,Clrn,D_out);
    D_FFEC32 C(C_in,Clk,We,Clrn,C_out);
    D_FFEC5 Rd(Rd_in,Clk,We,Clrn,Rd_out);
    D_FFEC Wr(M_Wreg,Clk,We,Clrn,W_Wreg);
    D_FFEC Re(M_Reg2reg,Clk,We,Clrn,W_Reg2reg);
endmodule
