`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/16 21:22:28
// Design Name: 
// Module Name: CPU_new
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


module CPU_new(Clk, Clrn);
    input Clk,Clrn;
    wire [31:0] Inst, Dread;
    wire [31:0] Iaddr, Daddr, Dwrite;
    wire Wmem;
    CPU2 CPU(Clk, Clrn, Inst, Dread, Iaddr, Daddr, Dwrite, Wmem);
   
    DATAMEM DATAMEM(Daddr, Dwrite, Clk, Wmem, Dread);
   
    INSTMEM INSTMEM(Iaddr, Inst);
endmodule


module CPU_new_TEST;
    reg Clk,Clrn;
//    always #20 Clk = ~Clk;
    CPU_new CPU_new_test(.Clk(Clk),.Clrn(Clrn));
        initial begin;
            
            
            Clrn = 1;
            Clk = 0;
            #20;
           
           
            Clk =~Clk;
            
            #20;
            Clk =~Clk;
            #20;
            Clk =~Clk;
            
            #20;
            Clk =~Clk;
            #20; 
            Clk =~Clk;
            
            #20;
            Clk =~Clk;
            #20;
            Clk =~Clk;
            
            #20;
            Clk =~Clk;
            #20;
            Clk =~Clk;
//            //以上为5个周期
            
            #20;
            
            Clk =~Clk;
            #20;
            Clk =~Clk;
            
            #20;
            Clk =~Clk;
            #20;
            Clk =~Clk;
            
            #20;
            Clk =~Clk;
            #20;
            Clk =~Clk;
            
            #20;
            Clk =~Clk;
            #20;
            Clk =~Clk;
            
            #20;
            Clk =~Clk;
            #20;
            Clk =~Clk;
            
            #20;
            Clk =~Clk;
            #20;
            Clk =~Clk;
            
            #20;
            Clk =~Clk;
            #20;
            Clk =~Clk;
             
            #20;
            Clk =~Clk;
            #20;
            Clk =~Clk;
             
            #20;
            Clk =~Clk;
            #20;
            Clk =~Clk;
              
            #20;
            Clk =~Clk;
            #20;
            Clk =~Clk;
           
            #20;
            Clk =~Clk;
            #20;
            Clk =~Clk;    
            
             #20;
             Clk =~Clk;
             #20;
             Clk =~Clk; 
             
             #20;
             Clk =~Clk;
             #20;
             Clk =~Clk;                 
                                   
        end
endmodule