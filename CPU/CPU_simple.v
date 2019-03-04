`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/12/02 23:41:01
// Design Name: 
// Module Name: CPU_simple
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


module CPU_simple(Clk, Clrn);
    input Clk,Clrn;
    wire [31:0] Inst, Dread;
    wire [31:0] Iaddr, Daddr, Dwrite;
    wire Wmem;
    CPU1 CPU(Clk, Clrn, Inst, Dread, Iaddr, Daddr, Dwrite, Wmem);
    
    DATAMEM DATAMEM(Daddr, Dwrite, Clk, Wmem, Dread);
    
    INSTMEM INSTMEM(Iaddr, Inst);
    
endmodule

module CPU_simple_TEST;
    reg Clk,Clrn;
//    always #20 Clk = ~Clk;
    CPU_simple CPU_simple_test(.Clk(Clk),.Clrn(Clrn));
        initial begin;

            Clk = 0;
            Clrn = 1;
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