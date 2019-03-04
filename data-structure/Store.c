//
// Created by PC on 2018/10/14.
// 在某商店的仓库中，对电视机按照其价格从低到高建立一个单链表，链表的每个节点指出同样价格的电视机的台数。
// 现有m台价格为n元的电视机入库。请编写算法完成仓库的进货管理。
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef float ElemType;
#define SIZE 10

// 电视机
typedef struct Node {
    float price;
    int num;
    struct Node *next;
} ListNode, *ListNodePtr;

// 单链表的初始化
ListNodePtr LinkedListInit();

// 单链表的建立，头插入法建立单链表
ListNodePtr LinkedListCreatH();

// 单链表的建立，尾插入法建立单链表
ListNodePtr LinkedListCreatT();

// 遍历节点并输出
void ListTraversing(ListNodePtr start);

// 快速排序
void LinkedListQuickSort(ListNodePtr left, ListNodePtr right);

void Stored(ListNodePtr pNode, float price, int num);

int main() {
    ListNodePtr LinkedList = LinkedListCreatT();
    LinkedListQuickSort(LinkedList, NULL);
    printf("\ninit:");
    ListTraversing(LinkedList);

    int num;
    float price;
    printf("\n请输入电视台数：\n");
    scanf("%d",&num);
    printf("请输入电视价格：\n");
    scanf("%f",&price);

    Stored(LinkedList, price, num);
    ListTraversing(LinkedList);
    return 0;
}

// 添加新的电视机
void Stored(ListNodePtr list, float price, int num) {
    while (list && list->price < price) {
        list = list->next;
    }
    if (list && list->price == price) {
        list->num += num;
    }
    if (list && list->price > price) {
        ListNode *p = (ListNode *) malloc(sizeof(ListNode));
        p->next = list->next;
        p->price = price;
        p->num = num;
        list->next = p;
    }
}

// 单链表的初始化
ListNodePtr LinkedListInit() {
    ListNode *L = (ListNode *) malloc(sizeof(ListNode)); // 申请节点空间
    if (!L) { // 判断是否有足够的内存空间
        printf("申请内存空间失败\n");
    }
    L->next = NULL; // 将next设置为NULL,初始长度为0的单链表
    return L;
}

// 单链表的建立，头插入法建立单链表
ListNodePtr LinkedListCreatH() {
    ListNode *L = LinkedListInit(); // 初始化一个空链表;
    srand((unsigned int) time(NULL));
    for (int i = 0; i < SIZE; i++) {
        ElemType value = rand() * 100; // x为链表数据域中的数据
        int num = rand() % 10; // x为链表数据域中的数据
        ListNode *p = (ListNode *) malloc(sizeof(ListNode)); // 申请新的结点
        p->num = num;
        p->price = value;    // 结点数据域赋值
        p->next = L->next; // 将结点插入到表头L-->|2|-->|1|-->NULL
        L->next = p;
    }
    return L;
}

// 单链表的建立，尾插入法建立单链表
ListNodePtr LinkedListCreatT() {
    ListNode *L = LinkedListInit(); // 初始化一个空链表
    ListNode *r = L; // r始终指向终端结点，开始时指向头结点
    srand((unsigned int) time(NULL));
    for (int i = 0; i < SIZE; i++) {
        ElemType value = rand() % 10000; // x为链表数据域中的数据
        int num = rand() % 10; // x为链表数据域中的数据
        ListNode *p = (ListNode *) malloc(sizeof(ListNode)); // 申请新的节点
        p->num = num;
        p->price = value;// 结点数据域赋值
        r->next = p;// 将结点插入到表头L-->|1|-->|2|-->NULL
        r = p;
    }
    r->next = NULL;
    return L;
}

// 遍历节点并输出
void ListTraversing(ListNodePtr start) {
    printf("\n");
    for (ListNodePtr listNode = start->next; listNode; listNode = listNode->next) {
        printf("%.2f*%d ", listNode->price, listNode->num);
    }
}

// 快速排序
void LinkedListQuickSort(ListNodePtr left, ListNodePtr right) {
    if (left->next == right) {
        return;
    }
    ListNode *key = left->next,
            *i = key,
            *j = key->next;
    while (j != right) {
        if (j->price <= key->price) {
            i = i->next;
            // 交换
            int temp = i->price;
            i->price = j->price;
            j->price = temp;
        }
        j = j->next;
    }

    int temp = key->price;
    key->price = i->price;
    i->price = temp;

    LinkedListQuickSort(left, i);
    LinkedListQuickSort(i, right);
}
