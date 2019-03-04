`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/11/24 10:39:06
// Design Name: 
// Module Name: gate-circuit
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


module gate_circuit(X, Y, Z, F);
    input X, Y, Z;
    output F;
    and and1 (XandY, X, Y);
    and and2 (YandZ, Y, Z);
    not not1 (Y_n, Y);
    nor nor1 (XandY_nor_Y_n, XandY, Y_n);
    or or1(F, XandY_nor_Y_n, YandZ);
endmodule


module gate_circuit_TEST;
    reg X, Y, Z;
    wire F;
    gate_circuit gate_circuit_test(.X(X), .Y(Y), .Z(Z), .F(F));
        initial begin;
            X=0;Y=0;Z=0;#20;
            X=0;Y=0;Z=1;#20;
            X=0;Y=1;Z=0;#20;
            X=0;Y=1;Z=1;#20;
            X=1;Y=0;Z=0;#20;
            X=1;Y=0;Z=1;#20;
            X=1;Y=1;Z=0;#20;
            X=1;Y=1;Z=1;#20;
        end
endmodule