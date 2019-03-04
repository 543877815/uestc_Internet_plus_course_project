`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/12 17:46:11
// Design Name: 
// Module Name: CONUNIT
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


module CONUNIT(Op, Func, Z, Regrt, Se, Wreg, Aluqb, Aluc, Wmem, Pcsrc, Reg2reg, V, M_Z, M_Op,E_Rd,M_Rd,E_Wreg,M_Wreg,Rs,Rt,FwdA,FwdB,E_Reg2reg,stall);
    input [5:0] Op, Func,M_Op;
    input Z, V, M_Z;
    output Regrt, Se, Wreg, Aluqb, Wmem, Reg2reg;
    output [1:0] Pcsrc, Aluc;
    input E_Wreg,M_Wreg;
    input [4:0] E_Rd,M_Rd,Rs,Rt;
    output reg [1:0] FwdA,FwdB;
    input E_Reg2reg;
    output stall;
    wire R_type = ~|Op;
    wire I_add = R_type & Func[5] & ~Func[4] & ~Func[3] & ~Func[2] & ~Func[1] & ~Func[0];
    wire I_sub = R_type & Func[5] & ~Func[4] & ~Func[3] & ~Func[2] & Func[1] & ~Func[0];
    wire I_and = R_type & Func[5] & ~Func[4] & ~Func[3] & Func[2] & ~Func[1] & ~Func[0];
    wire I_or =  R_type & Func[5] & ~Func[4] & ~Func[3] & Func[2] & ~Func[1] & Func[0];
    wire I_addi = ~Op[5] & ~Op[4] & Op[3] & ~Op[2] & ~Op[1] & ~Op[0];
    wire I_andi = ~Op[5] & ~Op[4] & Op[3] & Op[2] & ~Op[1] & ~Op[0];
    wire I_ori = ~Op[5] & ~Op[4] & Op[3] & Op[2] & ~Op[1] & Op[0];
    wire I_lw = Op[5] & ~Op[4] & ~Op[3] & ~Op[2] & Op[1] & Op[0];
    wire I_sw = Op[5] & ~Op[4] & Op[3] & ~Op[2] & Op[1] & Op[0];
    wire I_beq = ~Op[5] & ~Op[4] & ~Op[3] & Op[2] & ~Op[1] & ~Op[0];
    wire I_bne = ~Op[5] & ~Op[4] & ~Op[3] & Op[2] & ~Op[1] & Op[0];
    wire I_J = ~Op[5] & ~Op[4] & ~Op[3] & ~Op[2] & Op[1] & ~Op[0];
    
    assign Regrt = I_addi | I_andi | I_ori | I_lw | I_sw | I_beq | I_bne | I_J;
    assign Se = I_addi | I_lw | I_sw | I_beq | I_bne;
    assign Wreg = I_add | I_sub | I_and | I_or | I_addi | I_andi | I_ori | I_lw;
    assign Aluqb = I_add | I_sub | I_and | I_or | I_beq | I_bne;
    assign Aluc[1] = I_and | I_or | I_andi | I_ori;
    assign Aluc[0] = I_sub | I_or | I_ori | I_beq | I_bne;
    assign Wmem = I_sw;
    assign Pcsrc[1] = (I_beq & Z) | (I_bne & ~Z) | I_J;
    assign Pcsrc[0] = I_J;
    assign Reg2reg = I_add | I_sub | I_and | I_or | I_addi | I_andi | I_ori | I_sw | I_beq | I_bne | I_J; 
   
    always @(E_Rd,M_Rd,E_Wreg,M_Wreg,Rs,Rt,Op,Func)begin
            FwdA <= 2'b00;//默认选择
            if((Rs == E_Rd)&(E_Rd!=0)&(E_Wreg==1))begin
                    FwdA <= 2'b10;//和EX级指令存在数据冒险
                end
                else 
                begin
                    if((Rs == M_Rd)&(M_Rd != 0)&(M_Wreg == 1)) begin
                        FwdA <= 2'b01;//和MEM指令存在数据冒险
                    end
                end
            FwdB <= 2'b00;//默认选择
            if((Rt == E_Rd)&(E_Rd!=0)&(E_Wreg==1))begin
                    FwdB <= 2'b10;
            end else begin
            if((Rt == M_Rd)&(M_Rd != 0)&(M_Wreg == 1)) begin
                FwdB <= 2'b01;
            end
        end
       end
       assign stall = ((Rs == E_Rd)|(Rt == E_Rd))&(E_Reg2reg == 0)&(E_Rd!= 0)&(E_Wreg==1);
endmodule

module CONUNIT_TEST;
    reg [5:0] Op, Func;
    reg Z;
    wire Regrt, Se, Wreg, Aluqb, Wmem, Reg2reg;
    wire [1:0] Pcsrc, Aluc;
    CONUNIT CONUNIT_test(.Op(Op), .Func(Func), .Z(Z), .Regrt(Regrt), .Se(Se), .Wreg(Wreg), .Aluqb(Aluqb), .Aluc(Aluc), .Wmem(Wmem), .Pcsrc(Pcsrc), .Reg2reg(Reg2reg));
    initial begin;
        Op = 'b000000;
        Func = 'b100000;
        
        #20;
        
        Op = 'b000000;
        Func = 'b100010;
        
        #20;
        
        Op = 'b000000;
        Func = 'b100100;
        
        #20;
        
        Op = 'b000000;
        Func = 'b100101;
        
        #20;
        
        Op = 'b001000;
        
        #20;
        
        Op = 'b001000;
        
        #20;
        
        Op = 'b001100;
        
        #20;
        
        Op = 'b001101;
        
        #20;
        
        Op = 'b100011;
        
        #20;
        
        Op = 'b101011;
        
        #20;
        
        Op = 'b000100;
        Z = 0;
        
        #20;
        
        Op = 'b000100;
        Z = 1;
    end
endmodule