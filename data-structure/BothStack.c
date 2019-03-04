//
// Created by PC on 2018/10/14.
// 两栈共享空间的存储结构
//

#include <stdio.h>
#include <stdlib.h>

#define STACKSIZE 100
typedef int dataType;
typedef struct BothStack {
    dataType data[STACKSIZE];
    dataType top1;
    dataType top2;
} BothStack, *BothStackP;


void InitBothStack(BothStack *BothStack);

void PushBothStack(BothStack *S, int i, int value);

int PopBothStack(BothStack *S, int i);

int main() {
    BothStack *stack = (BothStack *) malloc(sizeof(BothStack));
    InitBothStack(stack);
    PushBothStack(stack, 1, 10);
    PushBothStack(stack, 2, 20);

    printf("%d %d", PopBothStack(stack, 1), PopBothStack(stack, 2));
    return 0;
}

int PopBothStack(BothStack *S, int i) {
    if (i != 1 && i != 2) {
        printf("error!");
        return -1;
    }
    if (i == 1) {
        if (S->top1 == -1) {
            printf("overflow!");
            return -1;
        } else {
            int PopValue = S->data[S->top1];
            S->top1--;
            return PopValue;
        }
    } else {
        if (S->top2 == STACKSIZE) {
            printf("overflow!");
            return -1;
        } else {
            int PopValue = S->data[S->top2];
            S->top2++;
            return PopValue;
        }
    }
}

void PushBothStack(BothStack *S, int i, int value) {
    if (i != 1 && i != 2) {
        printf("error!");
        return;
    }
    if (S->top1 + 1 == S->top2) {
        printf("overflow!");
        return;
    }
    if (i == 1) {
        S->top1++;
        S->data[S->top1] = value;
    } else {
        S->top2--;
        S->data[S->top2] = value;
    }
}

void InitBothStack(BothStack *BothStack) {
    BothStack->top1 = -1;
    BothStack->top2 = STACKSIZE;
}