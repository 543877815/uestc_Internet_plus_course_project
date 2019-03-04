//
// Created by PC on 2018/10/11.
//


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef int ElemType;

#define SIZE 10

// 单链表
typedef struct node {
    int data; // 数据域
    struct node *next; // 指针域
} ListNode, *ListNodePtr;

// 双向链表
typedef struct duNode {
    int data; // 数据域
    struct node *prior, *next; // 指针域
} DuNode, *DuNodePtr, *DuList;


// 单链表的初始化
ListNodePtr LinkedListInit();
// 单链表的建立，头插入法建立单链表
ListNodePtr LinkedListCreatH();

// 单链表的建立，尾插入法建立单链表
ListNodePtr LinkedListCreatT();

// 遍历节点并输出
void ListTraversing(ListNodePtr start);

// 指定位置和值插入节点
ListNodePtr LinkedListInsert(ListNodePtr list, int pos, int value);

// 指定位置的删除节点
ListNodePtr LinkedListDelete(ListNodePtr list, int pos);

// 指定值的删除节点
ListNodePtr LinkedListDeleteByValue(ListNodePtr list, int value);

// 指定位置修改节点的值
ListNodePtr LinkedListUpdate(ListNodePtr list, int pos, int value);

// 就地逆置
ListNodePtr LinkedListReverse(ListNodePtr list);

// 数组转成单链表
ListNodePtr ArraytoList(int *array, int n);

// 单链表求交集
ListNodePtr LinkedListUnion(ListNodePtr starta, ListNodePtr startb);

//  求顺序表的并集
int ArrayUnion(int *array1, int length1, int *array2, int length2, int *array3);

// 求顺序表的交集
int ArrayInterest(int *array1, int length1, int *array2, int length2, int *array3);

// 返回数组最大值
int ArrayMax(int *array, int n);

// 返回数组最小值
int ArrayMin(int *array, int n);

// 返回最大值
int Max(int a, int b);

// 返回最小值
int Min(int a, int b);

// 快速排序
void LinkedListQuickSort(ListNodePtr left, ListNodePtr right);

void ArrayQuickSort(int *array, int left, int right);

// 数组去重
ArrayDeduplication(int *oldArray, int n, int *newArray);

int main() {
    // 初始化
    ListNodePtr LinkedList = LinkedListCreatT();
    printf("\ninit:");
    ListTraversing(LinkedList);
    // 插入
    LinkedListInsert(LinkedList, 10, 10);
    printf("\ninsert:");
    ListTraversing(LinkedList);
    // 按位置删除
    LinkedListDelete(LinkedList, 9);
    printf("\ndelete:");
    ListTraversing(LinkedList);
    // 按值删除
    LinkedListDeleteByValue(LinkedList, 10);
    printf("\ndeleteByValue:");
    ListTraversing(LinkedList);
    // 按位置修改
    LinkedListUpdate(LinkedList, 5, 999);
    printf("\nupdate:");
    ListTraversing(LinkedList);
    // 就地逆置
    LinkedListReverse(LinkedList);
    printf("\nreverse:");
    ListTraversing(LinkedList);

    // 单链表快速排序
    printf("\nafter sort:");
    LinkedListQuickSort(LinkedList, NULL);
    ListTraversing(LinkedList);
    // 创建一个新的链表并递增排序
    ListNodePtr LinkedListSort = LinkedListCreatH();
    printf("\nbefore sort:");
    ListTraversing(LinkedListSort);
    LinkedListQuickSort(LinkedListSort, NULL);
    printf("\nafter sort:");
    ListTraversing(LinkedListSort);
    // 将两个递增有序单链表合并为一个新的有序链表
    ListNodePtr unionLinkedList = LinkedListUnion(LinkedListSort, LinkedList);
    printf("\nunion:");
    ListTraversing(unionLinkedList);

    // 求顺序表的交集
    printf("\nfirst array:1, 2, 4, 2, 2, 5\nsecond array:2, 4, 5, 6, 7");
    int array1[] = {1, 2, 4, 2, 2, 5},
            length1 = sizeof(array1) / sizeof(array1[0]),
            array2[] = {2, 4, 5, 6, 7},
            length2 = sizeof(array2) / sizeof(array2[0]),
            length3 = Min(length1, length2),
            array3[length3];
    length3 = ArrayInterest(array1, length1, array2, length2, array3);
    printf("\nArrayInterest:\n");
    for (int i = 0; i < length3; i++) {
        printf("%d ", array3[i]);
    }

    // 数组去重
    printf("\nfirst array after deduplication:");
    int newArray1[length1];
    int length = ArrayDeduplication(array1, length1, newArray1);
    for (int i = 0; i < length; i++) {
        printf("%d ", newArray1[i]);
    }

    // 求顺序表的并集
    int length4 = Max(length1, length2),
            array4[length4];
    length4 = ArrayUnion(array1, length1, array2, length2, array4);
    printf("\nArrayUnion:\n");
    for (int i = 0; i < length4; i++) {
        printf("%d ", array4[i]);
    }
    return 0;
}

// 数组去重
int ArrayDeduplication(int *oldArray, int n, int *newArray) {
    // 复制
    int copyArray[n];
    for (int i = 0; i < n; i++) {
        copyArray[i] = oldArray[i];
    }
    // 排序
    ArrayQuickSort(copyArray, 0, n - 1);
    int k = 0;
    newArray[k] = copyArray[0];
    for (int j = 1; j < n; j++) {
        if (copyArray[j] != copyArray[j - 1]) {
            k++;
            newArray[k] = copyArray[j];
        }
    }
    free(copyArray);
    return k + 1;
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
        if (j->data <= key->data) {
            i = i->next;
            // 交换
            int temp = i->data;
            i->data = j->data;
            j->data = temp;
        }
        j = j->next;
    }

    int temp = key->data;
    key->data = i->data;
    i->data = temp;

    LinkedListQuickSort(left, i);
    LinkedListQuickSort(i, right);
}

void ArrayQuickSort(int *array, int left, int right) {
    if (left > right) {
        return;
    }
    int i = left, j = right, key = array[left];
    while (i < j) {
        while (array[j] >= key && i < j) {
            j--;
        }
        array[i] = array[j];
        while (array[i] <= key && i < j) {
            i++;
        }
        array[j] = array[i];
    }
    array[i] = key;

    ArrayQuickSort(array, left, i - 1);
    ArrayQuickSort(array, i + 1, right);
}

//  指定位置修改值
ListNodePtr LinkedListUpdate(ListNodePtr list, int pos, int value) {
    ListNode *p = list->next;
    int count = 0;
    while (count != pos && p) {
        p = p->next;
        count++;
    }
    if (count != pos) {
        printf("\noverflow");
        return list;
    }
    p->data = value;
    return list;
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
        ElemType value = rand() % 110; // x为链表数据域中的数据
//        printf("%d ", value);
        ListNode *p = (ListNode *) malloc(sizeof(ListNode)); // 申请新的结点
        p->data = value;    // 结点数据域赋值
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
        ElemType value = rand() % 100; // x为链表数据域中的数据
//        printf("%d ", value);
        ListNode *p = (ListNode *) malloc(sizeof(ListNode)); // 申请新的节点
        p->data = value;// 结点数据域赋值
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
        printf("%d ", listNode->data);
    }
}

// 指定位置和值插入节点
ListNodePtr LinkedListInsert(ListNodePtr list, int pos, int value) {
    int i = 0;
    while (i != pos && list->next) {
        i++;
        list = list->next;
    }

    // 输入超过值
    if (i != pos) {
        printf("\nerror,oversize!");
        return list;
    }

    ListNode *p = (ListNode *) malloc(sizeof(ListNode));
    p->data = value;
    p->next = list->next;
    list->next = p;
    return list;
}

// 指定值的删除节点
ListNodePtr LinkedListDeleteByValue(ListNodePtr list, int value) {
    ListNode *p = list;
    while (p->next) {
        ListNode *q;
        q = p->next;
        if (q->data == value) {
            p->next = q->next;
            q->next = NULL;
            free(q);
        } else {
            p = p->next;
        }
    }
    return list;
}

// 指定位置的删除节点
ListNodePtr LinkedListDelete(ListNodePtr list, int pos) {
    int i = 0;
    while (i != pos && list->next) {
        i++;
        list = list->next;
    }
    // 输入超过值
    if (i != pos || !list->next) {
        printf("\nerror,oversize!");
        return list;
    }
    ListNode *p = (ListNode *) malloc(sizeof(ListNode));
    p = list->next;
    list->next = p->next;
    free(p);
    return list;
}

// 就地逆置 头插法
ListNodePtr LinkedListReverse(ListNodePtr list) {
    ListNode *pre = list,
            *p = pre->next,
            *r = p->next;
    while (r) {
        p->next = r->next;
        r->next = pre->next;
        pre->next = r;
        r = p->next;
    }
    return list;
}

// 数组转成单链表
ListNodePtr ArrayToList(int *array, int n) {
    ListNode *start = LinkedListInit(),
            *r = start;
    int count = 0;
    while (count < n) {
        ListNode *p = (ListNode *) malloc(sizeof(ListNode));
        p->data = array[count];
        r->next = p;
        r = p;
        count++;
    }
    r->next = NULL;
    return start;
}


// 递增单链表合并为一个新的递增单链表
ListNodePtr LinkedListUnion(ListNodePtr starta, ListNodePtr startb) {
    ListNode *r = starta,
            *la = starta->next,
            *lb = startb->next;
    while (la && lb) {
        if (la->data < lb->data) {
            r->next = la;
            r = la;
            la = la->next;
        } else {
            r->next = lb;
            r = lb;
            lb = lb->next;
        }
    }
    if (la) {
        r->next = la;
    } else {
        r->next = lb;
    }
    return starta;
}

// 求顺序表的交集
int ArrayInterest(int *array1, int length1, int *array2, int length2, int *array3) {
    int k = 0;
    for (int i = 0; i < length1; i++) {
        for (int j = 0; j < length2; j++) {
            if (array1[i] == array2[j]) {
                int p;
                for (p = 0; p < k; p++) {
                    if (array3[p] == array2[j]) {
                        break;
                    }
                }
                if (p == k) {
                    array3[k] = array1[i];
                    k++;
                    break;
                }
            }
        }
    }
    return k;
}

//  求顺序表的并集
int ArrayUnion(int *array1, int length1, int *array2, int length2, int *array3) {
    // 复制
    int tempArray[length1+length2];
    for (int i = 0; i < length1; i++) {
        tempArray[i] = array1[i];
    }
    // 求并集
    int k = length1;
    for (int i = 0; i < length2; i++) {
        int j = 0;
        for (j = 0; j < length1; j++) {
            if (array2[i] == tempArray[j]) {
                break;
            }
        }
        if (j >= length1) {
            tempArray[k] = array2[i];
            k++;
        }
    }

    return ArrayDeduplication(tempArray, k, array3);
}

// 返回数组最大值
int ArrayMax(int *array, int n) {
    int Max = -INFINITY;
    for (int i = 0; i < n; i++) {
        if (array[i] > Max) {
            Max = array[i];
        }
    }
    return Max;
}

// 返回数组最小值
int ArrayMin(int *array, int n) {
    int Min = INFINITY;
    for (int i = 0; i < n; i++) {
        if (array[i] < Min) {
            Min = array[i];
        }
    }
    return Min;
}

// 返回最大值
int Max(int a, int b) {
    return a > b ? a : b;
}

// 返回最小值
int Min(int a, int b) {
    return a < b ? a : b;
}
