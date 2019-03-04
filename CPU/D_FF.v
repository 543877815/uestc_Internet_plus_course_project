`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/06 13:13:10
// Design Name: 
// Module Name: D_FF
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


module D_FF(D,Clk,Q,Qn);
    input D,Clk;
    output Q,Qn;
    wire Clkn,Q0,Qn0;
    not i0(Clkn,Clk);
    D_Latch d0(D,Clkn,Q0,Qn0);
    D_Latch d1(Q0,Clk,Q,Qn);
endmodule

module D_FF_TEST;
    reg D,Clk;
    wire Q,Qn;
    D_FF D_FF_test(.D(D),.Clk(Clk),.Q(Q),.Qn(Qn));
    always #20 Clk = ~Clk;
        initial begin
            Clk = 0;
            D = 1;
            
            #40;
            
            D = 0;
        end
 endmodule
//module D_FF_TEST;
//    reg  D,Clk;
//    wire Q,Qn;
//    wire Clkn,Q0,Qn0;
//    always #50 Clk = ~Clk;
//    D_FF D_FF_test(.D(D),.Clk(Clk),.Q(Q),.Qn(Qn));
//        initial begin;
            