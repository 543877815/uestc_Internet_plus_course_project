`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/06 13:16:28
// Design Name: 
// Module Name: D_FFEC
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


module D_FFEC(D,Clk,En,Clrn,Q,Qn);
    input D,Clk,En,Clrn;
    output Q,Qn;
    wire Y0,Y_C;
    MUX2X1 m0(Q,D,En,Y0);
    and i0(Y_C,Y0,Clrn);
    D_FF d0(Y_C,Clk,Q,Qn);
endmodule

module D_FFEC_TEST;
    reg  D,Clk,En,Clrn;
    wire Q,Qn;
    always #50 Clk = ~Clk;
    D_FFEC D_FFEC_test(.D(D),.Clk(Clk),.Q(Q),.En(En),.Clrn(Clrn),.Qn(Qn));
        initial begin;
            Clk = 0;
        
            D = 1;
            En = 1;
            Clrn = 1;
            #100;
            
            D = 0;
            En = 1;
            Clrn = 1;
            #100;
            
            En = 0;
            Clrn = 1;
            #100;
            
            Clrn = 0;
        end
endmodule
