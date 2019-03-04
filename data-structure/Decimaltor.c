//
// Created by PC on 2018/10/27.
//

#include <stdio.h>
#include <stdlib.h>

void Decimaltor(int num, int decimal);

int main() {

    int num = 1234;
    int decimal = 2;// 2 - 9 is legal
    Decimaltor(num, decimal);
    return 0;
}

void Decimaltor(int num, int decimal) {
    int top, k;
    int S[100];
    top = -1;
    while (num != 0) {
        k = num % decimal;
        S[++top] = k;
        num = num / decimal;
    }
    while (top != -1) {
        printf("%d", S[top--]);
    }
}