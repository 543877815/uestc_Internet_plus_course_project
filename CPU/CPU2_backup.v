`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/17 13:42:07
// Design Name: 
// Module Name: CPU2_backup
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


module CPU2_backup(Clk, Clrn, Inst[31:0], Dread[31:0], Iaddr[31:0], Daddr[31:0], Dwrite[31:0], Wmem);
   input Clk,Clrn;
   input [31:0] Inst, Dread;
   output [31:0] Iaddr, Daddr, Dwrite;
   output Wmem;
    
   wire [31:0] Q;
   wire [31:0] D = MUX4X32_Y;
   parameter En = 1;
   PC pc(Clk, En, D,Q);
   
   wire [31:0]CLA_32_X = Q;
   wire [31:0]CLA_32_S;
   CLA_32_plus4 cla_32_plus4(CLA_32_X,CLA_32_S);
    
   assign Iaddr = Q;
//    wire [31:0] Addr = Q;
//    wire [31:0] Inst;
//    INSTMEM instmem(Addr, Inst);
    
   parameter IF_ID_We = 1;
   wire [31:0]IF_ID_IR_in = Inst;
   wire [31:0]IF_ID_PC_in = CLA_32_S;
   wire [31:0]IF_ID_IR_out,IF_ID_PC_out;
   IF_ID if_id(IF_ID_We, Clk, Clrn, IF_ID_PC_in,IF_ID_PC_out,IF_ID_IR_in,IF_ID_IR_out);
    
   wire [15:0]EXT_X = IF_ID_IR_out[15:0];
   wire EXT_Se = Se;
   wire [31:0]EXT_Y;
   EXT16T32 ext16to32(EXT_X,EXT_Se,EXT_Y);
    
   wire [31:0]MUX4X32_Y;
   wire [31:0]MUX4X32_A2 = EX_MEM_PC_out;
   wire [31:0]MUX4X32_A1,MUX4X32_A3;
   wire [1:0] MUX4X32_S = Pcsrc;
   MUX4X32 mux4m32(CLA_32_S,MUX4X32_A1 ,MUX4X32_A2,MUX4X32_A3,MUX4X32_S,MUX4X32_Y);
    
//    wire [31:0]addr = {Q[31:28],ID_EX_IR_out[25:0]};
//    wire [31:0] Sh2;
//    SHIFTER32_L2 shift32_L2_1(addr,Sh2);
        
//    wire [25:0] addr = IF_ID_IR_out[25:0];
//    wire [31:0] Sh2;
//    SHIFTER32_L2 shift32_L2_1(addr,Sh2); 
    
   wire [5:0]Op = IF_ID_IR_out[31:26];
   wire [5:0]Func = IF_ID_IR_out [5:0];
   wire [1:0] Pcsrc, Aluc;
   wire CON_M_Z = M_Z;
   wire [5:0]CON_M_Op = M_Op;
   wire Wreg,Se,Aluqb,Regrt,Wmem, Reg2reg;
   wire CON_V;
   CONUNIT conunit(Op, Func,  , Regrt, Se, Wreg, Aluqb, Aluc, Wmem, Pcsrc, Reg2reg,CON_V ,CON_M_Z, CON_M_Op);
   
   wire [4:0]rt = IF_ID_IR_out[20:16];
   wire [4:0]rd = IF_ID_IR_out[15:11];
   wire [4:0]INS_REG_YY;
   MUX2X5 INS_REG(rd, rt, Regrt, INS_REG_YY);
    
   wire [4:0]rs = IF_ID_IR_out[25:21];
   wire [4:0]Ra = rs;
   wire [4:0]Rb = rt;
   wire [4:0]Wr = MEM_WB_Rd_out;
   wire We = W_Wreg;
   wire [31:0]REG_D = ALU_DATAMEM_Y;
   wire [31:0] Qa, Qb;
   wire Clk_n = ~Clk;
   REGFILE regfile(Ra, Rb, REG_D, Wr, We, Clk, Clrn, Qa, Qb);
    
   wire [31:0]ID_EX_PC_in = IF_ID_PC_out;
   wire [31:0]ID_EX_R1_in = Qa;
   wire [31:0]ID_EX_R2_in = Qb;
   wire [31:0]I_in = EXT_Y;
   wire [4:0]ID_EX_Rd_in = INS_REG_YY;
   wire [31:0]ID_EX_PC_out,ID_EX_R1_out,ID_EX_R2_out,I_out;
   wire [4:0]ID_EX_Rd_out;
   wire [5:0]E_Op;
   wire E_Wreg,E_Reg2reg,E_Wmem,E_Aluqb;
   wire [1:0]E_Aluc;
   
   parameter ID_EX_We = 1;
   ID_EX id_ex(ID_EX_We,Clk, Clrn,ID_EX_PC_in,ID_EX_PC_out,ID_EX_R1_in,ID_EX_R1_out, ID_EX_R2_in,ID_EX_R2_out,I_in,I_out,
   Wreg,E_Wreg,  Reg2reg,E_Reg2reg,Wmem,E_Wmem, Op,E_Op, Aluc,E_Aluc, Aluqb,E_Aluqb, ID_EX_Rd_in,ID_EX_Rd_out);
   
   wire [31:0]Sh1;
   SHIFTER32_L2 shift32_L2(I_out,Sh1);
   
   parameter Sub = 0;
   wire [31:0]ADDSUB_S;
   ADDSUB_32 addsub_32(Sh1, ID_EX_PC_out, Sub, ADDSUB_S);
        
   wire [31:0]REG_ALU_Y;
   MUX2X32 REG_ALU(I_out, ID_EX_R2_out, E_Aluqb, REG_ALU_Y);
    
   wire [31:0]ALU_X = ID_EX_R1_out;
   wire [31:0]ALU_Y = REG_ALU_Y;
   wire [1:0]ALU_Aluc = E_Aluc;
   wire ALU_Z,V;
   wire [31:0]ALU_R;
   ALU alu(ALU_X,ALU_Y,ALU_Aluc,ALU_R,ALU_Z,V);
    
   parameter EX_MEM_We = 1;
   wire [31:0]EX_MEM_PC_in = ADDSUB_S;
   wire Z_in = ALU_Z;
   wire [31:0]R_in = ALU_R;
   wire [31:0]S_in = ID_EX_R2_out;
   wire [4:0]EX_MEM_Rd_in = ID_EX_Rd_out;
   wire [5:0]M_Op;
   wire [4:0]EX_MEM_Rd_out;
   wire [31:0]EX_MEM_PC_out,R_out,S_out;
   wire M_Wreg,M_Reg2reg,M_Wmem,M_Z;
   EX_MEM ex_mem(EX_MEM_We,Clk, Clrn, EX_MEM_PC_in,EX_MEM_PC_out,Z_in,M_Z,R_in,R_out,S_in,S_out,EX_MEM_Rd_in,EX_MEM_Rd_out,E_Wreg,M_Wreg,E_Reg2reg,M_Reg2reg,E_Wmem,M_Wmem,E_Op,M_Op);
    
   assign Daddr = R_out;
   assign Dwrite = S_out;
   assign Wmem = M_Wmem;
//    wire [31:0]DATAMEM_Addr = R_out;
//    wire [31:0]Din = S_out;
//    wire DATAMEM_We = M_Wmem;
//    wire [31:0]Dout;
//    DATAMEM datamem(DATAMEM_Addr, Din, Clk, DATAMEM_We, Dout);
    
   parameter MEM_WB_We = 1;
   wire [31:0]D_in = R_out;
   wire [31:0]D_out;
   wire [31:0]C_in = Dread;
   wire [31:0]C_out;
   wire [4:0]MEM_WB_Rd_in = EX_MEM_Rd_out;
   wire [4:0]MEM_WB_Rd_out;
   wire W_Wreg,W_Reg2reg;
   MEM_WB mem_wb(MEM_WB_We,Clk,Clrn,D_in,D_out,C_in,C_out,MEM_WB_Rd_in,MEM_WB_Rd_out,M_Wreg,W_Wreg,M_Reg2reg,W_Reg2reg);
    
   wire [31:0]ALU_DATAMEM_Y;
   wire [31:0]ALU_DATAMEM_Y0 = C_out;
   wire [31:0]ALU_DATAMEM_Y1 = D_out;
   MUX2X32 ALU_DATAMEM(ALU_DATAMEM_Y0, ALU_DATAMEM_Y1, W_Reg2reg, ALU_DATAMEM_Y);
endmodule
