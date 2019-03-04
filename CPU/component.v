`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/15 15:10:51
// Design Name: 
// Module Name: component
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


module component(A,Clk,Q2Q,Q1Q,Q0Q,Z);
    input A,Clk;
    output Q2Q,Q1Q,Q0Q,Z;
    wire Q2_Q,Q1_Q,Q0_Q;
    
    and and1(Q2_D,A,Z);
    D_FF Q2(Q2_D,Clk,Q2_Q,Q2_Qn);
    assign Q2Q = Q2_Q;
    assign Q2Q = Q2_Q;
    D_FF Q1(Q2_Q,Clk,Q1_Q,Q1_Qn);
    assign Q1Q = Q1_Q;
    D_FF Q0(Q1_Q,Clk,Q0_Q,Q0_Qn);
    assign Q0Q = Q0_Q;
    
    nor nor1(Q2_QnorQ1_Q,Q2_Q,Q1_Q);
    xor xor1(Q3_QxorQ2_Q,Q1_Q,Q0_Q);
    
    xor xor3(Z,Q2_QnorQ1_Q,Q3_QxorQ2_Q);
endmodule


module component_TEST;
    reg A,Clk;
    wire Q2Q,Q1Q,Q0Q,Z;
    wire Q2_Q,Q1_Q,Q0_Q;
    always #50 Clk = ~Clk;
    component component_test(.A(A),.Clk(Clk),.Q2Q(Q2Q),.Q1Q(Q1Q),.Q0Q(Q0Q),.Z(Z));
    initial begin

        Clk = 0;
        
        A=0;
        #150;
        
        A=0;
        #150;
        
        A=1;
        #150;
        
        A=1;
        #150;
        
        A=0;
        #50;
    end
endmodule
        
