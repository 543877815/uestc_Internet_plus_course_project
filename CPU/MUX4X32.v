`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/10/30 21:54:11
// Design Name: 
// Module Name: MUX4X32
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


module MUX4X32(A0,A1,A2,A3,S,Y);
    input [31:0] A0,A1,A2,A3;
    input [1:0] S;
    output [31:0] Y;
    reg [1:0] S1;
    always #10 begin
       if(S) S1 <= S;
       else S1 <= 'b00;
     end
    function[31:0] select;
        input [31:0] A0,A1,A2,A3;
        input [1:0]S1;
            case(S1)
                2'b00:select = A0;
                2'b01:select = A1;
                2'b10:select = A2;
                2'b11:select = A3;
            endcase
    endfunction
    assign Y = select(A0,A1,A2,A3,S1);
endmodule

module MUX4X32_TEST;
    reg [31:0] A0, A1, A2, A3;
    reg [1:0] S;
    wire [31:0] Y;
    MUX4X32 MUX4X32_test( .A0(A0), .A1(A1), .A2(A2), .A3(A3), .S(S) , .Y(Y));
        initial begin
            A0 = 'b00000000000000000000000000000000;
            A1 = 'b00000000000000000000000000000001;
            A2 = 'b00000000000000000000000000000010;
            A3 = 'b00000000000000000000000000000011;
            S = 'b00;    
            #20;
            S = 'b01;          
            #20;
            S = 'b10;                           
            #20;
            S = 'b11;
           end
endmodule
       