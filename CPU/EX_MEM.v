`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/12 15:23:12
// Design Name: 
// Module Name: EX_MEM
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


module EX_MEM(We,Clk, Clrn, PC_in,PC_out,Z_in,M_Z,R_in,R_out,S_in,S_out,Rd_in,Rd_out,E_Wreg,M_Wreg,E_Reg2reg,M_Reg2reg,E_Wmem,M_Wmem,E_Op,M_Op);
    input [31:0] PC_in,R_in,S_in;
    input E_Wreg,E_Reg2reg,E_Wmem,Z_in;
    input [5:0]E_Op;
    input [4:0]Rd_in;
    input We,Clk, Clrn;
    output [31:0] PC_out,R_out,S_out;
    output [4:0]Rd_out;
    output [5:0]M_Op;
    output M_Wreg,M_Reg2reg,M_Wmem,M_Z;
    D_FFEC32 PC(PC_in,Clk,We,Clrn,PC_out);
    D_FFEC Z(Z_in,Clk,We,Clrn,M_Z);
    D_FFEC Wr(E_Wreg,Clk,We,Clrn,M_Wreg);
    D_FFEC Re(E_Reg2reg,Clk,We,Clrn,M_Reg2reg);
    D_FFEC Wm(E_Wmem,Clk,We,Clrn,M_Wmem);
    D_FFEC32 R(R_in,Clk,We,Clrn,R_out);
    D_FFEC32 S(S_in,Clk,We,Clrn,S_out);
    D_FFEC5 Rd(Rd_in,Clk,We,Clrn,Rd_out);
    D_FFEC6 Op(E_Op,Clk,We,Clrn,M_Op);
    
endmodule
