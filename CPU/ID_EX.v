`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/16 22:25:07
// Design Name: 
// Module Name: ID_EX
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


module ID_EX(We, Clk, stall, PC_in,PC_out,R1_in,R1_out,R2_in,R2_out,I_in,I_out,Wreg,E_Wreg,Reg2reg,E_Reg2reg,Wmem,E_Wmem,op,E_Op,Aluc,E_Aluc,Aluqb,E_Aluqb,Rd_in,Rd_out,FwdA,E_FwdA,FwdB,E_FwdB);
    input [31:0] PC_in,R1_in,R2_in,I_in;
    input Wreg,Reg2reg,Wmem,Aluqb;
    input [1:0]Aluc;
    input [4:0]Rd_in;
    input [5:0]op;
    input [1:0]FwdA,FwdB;
    input We,Clk, stall;
    output [31:0] PC_out,R1_out,R2_out,I_out;
    output E_Wreg,E_Reg2reg,E_Wmem,E_Aluqb;
    output [1:0]E_Aluc;
    output [4:0]Rd_out;
    output [5:0]E_Op;
    output [1:0]E_FwdA,E_FwdB;
    
    function Clrn1;
        input stall;
        case(stall)
            1:Clrn1 = 0;
            default:Clrn1 = 1;
        endcase
    endfunction
   
    assign Clrn = Clrn1(stall);
    D_FFEC32 PC(PC_in,Clk,We,Clrn,PC_out);
    D_FFEC32 R1(R1_in,Clk,We,Clrn,R1_out);
    D_FFEC32 R2(R2_in,Clk,We,Clrn,R2_out);
    D_FFEC32 I(I_in,Clk,We,Clrn,I_out);
    D_FFEC2 Fwd_A(FwdA,Clk,We,Clrn,E_FwdA);
    D_FFEC2 Fwd_B(FwdB,Clk,We,Clrn,E_FwdB);
    D_FFEC Wr(Wreg, Clk, We, Clrn, E_Wreg);
    D_FFEC Re(Reg2reg, Clk, We, Clrn, E_Reg2reg);
    D_FFEC Wm(Wmem, Clk, We, Clrn, E_Wmem);
    D_FFEC6 Op(op, Clk, We, Clrn, E_Op);
    D_FFEC2 Al(Aluc, Clk, We, Clrn, E_Aluc);
    D_FFEC Alu(Aluqb, Clk, We, Clrn, E_Aluqb);
    D_FFEC5 Rd(Rd_in, Clk, We, Clrn, Rd_out);
endmodule