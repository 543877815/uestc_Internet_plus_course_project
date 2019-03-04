`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/12 15:23:12
// Design Name: 
// Module Name: REG32
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


module REG32(D, En, Clk, Clrn, 
Q31, Q30, Q29, Q28, Q27, Q26, Q25,
Q24, Q23, Q22, Q21, Q20, Q19, Q18, Q17,
Q16, Q15, Q14, Q13, Q12, Q11, Q10, Q9,
Q8, Q7, Q6, Q5, Q4, Q3, Q2, Q1, Q0);
    input [31:0] D, En;
    input Clk, Clrn;
    output [31:0] Q31, Q30, Q29, Q28, Q27, Q26, Q25,
    Q24, Q23, Q22, Q21, Q20, Q19, Q18, Q17,
    Q16, Q15, Q14, Q13, Q12, Q11, Q10, Q9,
    Q8, Q7, Q6, Q5, Q4, Q3, Q2, Q1, Q0;
    D_FFEC32 q31(D,Clk,En[31],Clrn,Q31);
    D_FFEC32 q30(D,Clk,En[30],Clrn,Q30);
    D_FFEC32 q29(D,Clk,En[29],Clrn,Q29);
    D_FFEC32 q28(D,Clk,En[28],Clrn,Q28);
    D_FFEC32 q27(D,Clk,En[27],Clrn,Q27);
    D_FFEC32 q26(D,Clk,En[26],Clrn,Q26);
    D_FFEC32 q25(D,Clk,En[25],Clrn,Q25);
    D_FFEC32 q24(D,Clk,En[24],Clrn,Q24);
    D_FFEC32 q23(D,Clk,En[23],Clrn,Q23);
    D_FFEC32 q22(D,Clk,En[22],Clrn,Q22);
    D_FFEC32 q21(D,Clk,En[21],Clrn,Q21);
    D_FFEC32 q20(D,Clk,En[20],Clrn,Q20);
    D_FFEC32 q19(D,Clk,En[19],Clrn,Q19);
    D_FFEC32 q18(D,Clk,En[18],Clrn,Q18);
    D_FFEC32 q17(D,Clk,En[17],Clrn,Q17);
    D_FFEC32 q16(D,Clk,En[16],Clrn,Q16);
    D_FFEC32 q15(D,Clk,En[15],Clrn,Q15);
    D_FFEC32 q14(D,Clk,En[14],Clrn,Q14);
    D_FFEC32 q13(D,Clk,En[13],Clrn,Q13);
    D_FFEC32 q12(D,Clk,En[12],Clrn,Q12);
    D_FFEC32 q11(D,Clk,En[11],Clrn,Q11);
    D_FFEC32 q10(D,Clk,En[10],Clrn,Q10);
    D_FFEC32 q9 (D,Clk,En[9],Clrn,Q9);
    D_FFEC32 q8 (D,Clk,En[8],Clrn,Q8);
    D_FFEC32 q7 (D,Clk,En[7],Clrn,Q7);
    D_FFEC32 q6 (D,Clk,En[6],Clrn,Q6);
    D_FFEC32 q5 (D,Clk,En[5],Clrn,Q5);
    D_FFEC32 q4 (D,Clk,En[4],Clrn,Q4);
    D_FFEC32 q3 (D,Clk,En[3],Clrn,Q3);
    D_FFEC32 q2 (D,Clk,En[2],Clrn,Q2);
    D_FFEC32 q1 (D,Clk,En[1],Clrn,Q1);
    assign Q0 = 0;
endmodule

module REG32_TEST;
        reg [31:0] D, En;
        reg Clk, Clrn;
        wire [31:0] Q31, Q30, Q29, Q28, Q27, Q26, Q25,
        Q24, Q23, Q22, Q21, Q20, Q19, Q18, Q17,
        Q16, Q15, Q14, Q13, Q12, Q11, Q10, Q9,
        Q8, Q7, Q6, Q5, Q4, Q3, Q2, Q1, Q0;
        REG32 REG32_test(.D(D), .En(En), .Clk(Clk), .Clrn(Clrn),  
        .Q31(Q31), .Q30(Q30), .Q29(Q29), .Q28(Q28), .Q27(Q27), .Q26(Q26), .Q25(Q25),
        .Q24(Q24), .Q23(Q23), .Q22(Q22), .Q21(Q21), .Q20(Q20), .Q19(Q19), .Q18(Q18), .Q17(Q17),
        .Q16(Q16), .Q15(Q15), .Q14(Q14), .Q13(Q13), .Q12(Q12), .Q11(Q11), .Q10(Q10), .Q9(Q9),
        .Q8(Q8), .Q7(Q7), .Q6(Q6), .Q5(Q5), .Q4(Q4), .Q3(Q3), .Q2(Q2), .Q1(Q1), .Q0(Q0));
        always #20 Clk = ~Clk;
       initial begin;
            Clk = 0;
            D = 'b11110000111100001111000011110000;
            En = 'b11111111111111111111111111111111;
            Clrn = 1;
            
            #40;
            
            D = 'b00001111000011110000111100001111;
            
            #40
            
            D = 'b00110011001100110011001100110011;
            
            #40;
            
            D = 'b11001100110011001100110011001100;
            
       end
endmodule
