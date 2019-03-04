`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/02 23:30:46
// Design Name: 
// Module Name: CPU_backup
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


//module CPU_backup(Clk, Clrn, Inst[31:0], Dread[31:0], Iaddr[31:0], Daddr[31:0], Dwrite[31:0], Wmem);
//    input Clk,Clrn;
//    input [31:0] Inst, Dread;
//    output [31:0] Iaddr, Daddr, Dwrite;
//    output Wmem;
    
//    wire [31:0] Q;
//    wire [31:0] D = MUX4X32_Y;
//    D_FFEC32 PC (D,Clk,En,Clrn,Q,Qn);
   
//    wire [31:0]CLA_32_X = Q;
//    wire [31:0]CLA_32_S;
//    CLA_32_plus4 cla_32_plus4(CLA_32_X,CLA_32_S);
    
//    wire [31:0] Addr = Q;
//    wire [31:0] Inst;
//    INSTMEM instmem(Addr, Inst);
    
//    wire [15:0]EXT_X = Inst[15:0];
//    wire EXT_Se = Se;
//    wire [31:0]EXT_Y;
//    EXT16T32 ext16to32(EXT_X,EXT_Se,EXT_Y);
    
//    wire [31:0]Sh1;
//    SHIFTER32_L2 shift32_L2(EXT_Y,Sh1);

//    assign Sub = 0;
//    wire [31:0]ADDSUB_S;
//    ADDSUB_32(Sh1, CLA_32_S, Sub, ADDSUB_S, Cout);
    
//    wire [31:0]MUX4X32_Y;
//    MUX4X32(CLA_32_S,A1,ADDSUB_S,Sh2,Pcsrc,MUX4X32_Y);
    
//    wire [25:0] addr = Inst[25:0];
//    wire [31:0] Sh2;
//    SHIFTER32_L2 shift32_L2_1(addr,Sh2); 
    
//    wire [5:0]Op = Inst[31:26];
//    wire [5:0]Func = Inst [5:0];
//    wire [1:0] Pcsrc, Aluc;
//    wire Wreg,Se,Aluqb,Regrt,Wmem, Reg2reg;
//    CONUNIT conunit(Op, Func, Z , Regrt, Se, Wreg, Aluqb, Aluc, Wmem, Pcsrc, Reg2reg);
    
//    wire [4:0]rt = Inst[20:16];
//    wire [4:0]rd = Inst[15:11];
//    wire [4:0]INS_REG_YY;
//    MUX2X5 INS_REG(rd, rt, Regrt, INS_REG_YY);
    
//    wire [4:0]rs = Inst[25:21];
//    wire [4:0]Ra = rs;
//    wire [4:0]Rb = rt;
//    wire [4:0]Wr = INS_REG_YY;
//    wire We = Wreg;
//    wire [31:0]REG_D = ALU_DATAMEM_Y;
//    wire [31:0] Qa, Qb;
//    REGFILE regfile(Ra, Rb, REG_D, Wr, We, Clk, Clrn, Qa, Qb);
    
//    wire [31:0]REG_ALU_Y;
//    MUX2X32 REG_ALU(Qb, EXT_Y, Aluqb, REG_ALU_Y);
    
//    wire [31:0]ALU_X = Qa;
//    wire [31:0]ALU_Y = Qb;
//    wire [1:0]ALU_Aluc = Aluc;
//    wire ALU_Z,V;
//    wire [31:0]ALU_R;
//    ALU(ALU_X,ALU_Y,ALU_Aluc,ALU_R,ALU_Z,V);
    
//    wire [31:0]DATAMEM_Addr = ALU_R;
//    wire [31:0]Din = Qb;
//    wire DATAMEM_We = Wmem;
//    wire [31:0]Dout;
//    DATAMEM datamem(DATAMEM_Addr, Din, Clk, DATAMEM_We, Dout);
    
//    wire [31:0]ALU_DATAMEM_Y;
//    MUX2X32 ALU_DATAMEM(Dout, ALU_R, Reg2reg, ALU_DATAMEM_Y);
    
//endmodule
