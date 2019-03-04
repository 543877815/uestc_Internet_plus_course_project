`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/02 20:22:31
// Design Name: 
// Module Name: CPU1
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


module CPU1(Clk, Clrn, Inst, Dread, Iaddr, Daddr, Dwrite, Wmem);
    input Clk,Clrn;
    input [31:0] Inst, Dread;
    output [31:0] Iaddr, Daddr, Dwrite;
    output Wmem;
    
    wire [31:0] Q,Qn;
    wire [31:0]MUX4X32_Y;
    wire [31:0]D = MUX4X32_Y;
    parameter En = 1;
//    D_FFEC32 PC (D,Clk,En,Clrn,Q,Qn);
    PC pc(Clk, En, D,Q);
    
    wire [31:0]CLA_32_X = Q;
    wire [31:0]CLA_32_S;
    CLA_32_plus4 cla_32_plus4(CLA_32_X,CLA_32_S);
    
    assign Iaddr = Q;
//    wire [31:0] Addr = Q;
//    wire [31:0] Inst;
//    INSTMEM instmem(Addr, Inst);
    
    wire Se;
    wire [15:0]EXT_X = Inst[15:0];
    wire EXT_Se = Se;
    wire [31:0]EXT_Y;
    EXT16T32 ext16to32(EXT_X,EXT_Se,EXT_Y);
    
    wire [31:0]Sh1;
    SHIFTER32_L2 shift32_L2(EXT_Y,Sh1);

    parameter Sub = 'b0;
    wire [31:0]ADDSUB_S;
    wire Cout = 0;
    ADDSUB_32 addsub_32(Sh1, CLA_32_S, Sub, ADDSUB_S, Cout);
    
    
//    assign addrIn = {Q[31:28],Inst[25:0]};
    wire [31:0]addr = {Q[31:28],Inst[25:0]};
    wire [31:0] Sh2;
    SHIFTER32_L2 shift32_L2_1(addr,Sh2);
    
    
    wire [1:0]Pcsrc;
    wire A1;
    MUX4X32 mux4x32(CLA_32_S,A1,ADDSUB_S,Sh2,Pcsrc,MUX4X32_Y);
    
    wire [5:0]Op = Inst[31:26];
    wire [5:0]Func = Inst [5:0];
    wire [1:0]  Aluc;
    wire Wreg,Aluqb,Regrt, Reg2reg;
    wire ALU_Z;
    CONUNIT conunit(Op, Func, ALU_Z ,Regrt, Se, Wreg, Aluqb, Aluc, Wmem, Pcsrc, Reg2reg);
    
    wire [4:0]rt = Inst[20:16];
    wire [4:0]rd = Inst[15:11];
    wire [4:0]INS_REG_Y;
    MUX2X5 INS_REG(rd, rt, Regrt, INS_REG_Y);
    
    wire [4:0]rs = Inst[25:21];
    wire [4:0]Ra = rs;
    wire [4:0]Rb = rt;
    wire [4:0]Wr = INS_REG_Y;
    wire We = Wreg;
    wire [31:0]ALU_DATAMEM_Y;
    wire [31:0]REG_D = ALU_DATAMEM_Y;
    wire [31:0] Qa, Qb;
    
    REGFILE regfile(Ra, Rb, REG_D, Wr, We, Clk, Clrn, Qa, Qb);
    
    wire [31:0]REG_ALU_Y;
    MUX2X32 REG_ALU(EXT_Y, Qb, Aluqb, REG_ALU_Y);
    
    wire [31:0]ALU_X = Qa;
    wire [31:0]ALU_Y = REG_ALU_Y;
    wire [1:0]ALU_Aluc = Aluc;
//    wire V;
    wire [31:0]ALU_R;
    ALU alu(ALU_X,ALU_Y,ALU_Aluc,ALU_R,ALU_Z);
    
    assign Dwrite = Qb;
    assign Daddr = ALU_R;
//    wire [31:0]DATAMEM_Addr = ALU_R;
//    wire [31:0]Din = Qb;
//    wire DATAMEM_We = Wmem;
//    wire [31:0]Dout;
//    DATAMEM datamem(DATAMEM_Addr, Din, Clk, DATAMEM_We, Dout);
    MUX2X32 ALU_DATAMEM(Dread, ALU_R, Reg2reg, ALU_DATAMEM_Y);
    
endmodule

module CPU1_TEST;
    reg Clk,Clrn;
    reg [31:0] Inst, Dread;
    wire [31:0] Iaddr, Daddr, Dwrite;
    wire Wmem;
    always #20 Clk = ~Clk;
    CPU1 CPU1_test(.Clk(Clk), .Clrn(Clrn), .Inst(Inst), .Dread(Dread), .Iaddr(Iaddr), .Daddr(Daddr), .Dwrite(Dwrite), .Wmem(Wmem));
        initial begin;
            Clrn = 1;
            Clk = 0;
            
            Dread = 32'b00000000000000000000000000000110;
            Inst = 32'b10001100000000011111000011110000;//取出数放在$1
            
            #40;
            
            Dread = 32'b00000000000000000000000000000011;
            Inst = 32'b10001100000000101111000011110000;//取出数放在$2
            
            #40;
            
            Inst = 32'b00000000001000100001100000100000;//$3=$1+$2
            
            #40;
            Inst = 32'b00000000001000100010000000100010;//$4=$1-$2;
            
            #40;
            Inst = 32'b00000000001000100010100000100100;//$5=$1&$2;
            
            #40;
            Inst = 32'b00000000001000100011000000100101;//$6=$1|$2
            
//            #40;
//            Inst = 32'b00001000000000000000000000000001;//j to 00000000000000000000000001
//            Inst = 32'b00100000001001110000000000000001;//$7=$1+1
            
//            #40;
//            Inst = 32'b00110000001010000000000000000001;//$8=$1&1
            
//            #40;
//            Inst = 32'b00110100001010010000000000000001;//$8=$1|1
        end
endmodule