//
// Created by PC on 2018/10/14.
//  约瑟夫环
//
#include <stdio.h>
#include <stdlib.h>

#define SIZE 41
typedef struct Jonse {
    int code;
    struct Jonse *next;
} Jonse;

void ListTraversing(Jonse *start);

Jonse *LinkedListCreatT();

Jonse *LinkedListInit();

void ShowList(Jonse *pJonse);

void JonseOut(Jonse *start, int total, int out, int left);

int main() {
    Jonse *JonseCircle = LinkedListCreatT();
    printf("\ninit:");
    ShowList(JonseCircle);
    int total = SIZE;
    int out = 3;
    int left = 2;
    JonseOut(JonseCircle, total, out, left);
    return 0;
}

// 进行约瑟夫环游戏
void JonseOut(Jonse *start, int total, int out, int left) {
    Jonse *p = start->next;
    while (total != left && p) {
        int count = 1;
        Jonse *pre = (Jonse *) malloc(sizeof(Jonse));
        while (count != out) {
            pre = p;
            p = p->next;
            count++;
        }
        pre->next = p->next;
        Jonse *temp = (Jonse *) malloc(sizeof(Jonse));
        temp = p;
        p = p->next;
        if (start->next == temp){
            start->next = p;
        }
        free(temp);
        total--;
        ShowList(start);
    }
}

// 将约瑟夫环上所有节点值打印出来
void ShowList(Jonse *head) {
    Jonse *p = head->next;
    printf("\n");
    do {
        printf("%d ", p->code);
        p = p->next;
    } while (p != head->next);
}

// 尾插法创建
Jonse *LinkedListCreatT() {
    Jonse *L = LinkedListInit();
    Jonse *r = (Jonse *) malloc(sizeof(Jonse));
    r = L;
    for (int i = 0; i < SIZE; ++i) {
        Jonse *p = (Jonse *) malloc(sizeof(Jonse));
        p->code = i + 1;
        r->next = p;
        r = p;
    }
    r->next = L->next;
    return L;
}

// 链表初始化
Jonse *LinkedListInit() {
    Jonse *L = (Jonse *) malloc(sizeof(Jonse)); // 申请节点空间
    if (!L) {
        printf("申请内存空间失败\n");
    }
    L->next = NULL;
    return L;
}

// 遍历节点并输出
void ListTraversing(Jonse *start) {
    printf("\n");
    for (Jonse *listNode = start->next; listNode; listNode = listNode->next) {
        printf("%d ", listNode->code);
    }
}