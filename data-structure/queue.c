//
// Created by PC on 2018/10/27.
//

#include <stdio.h>
#include <stdlib.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

typedef int dataType;

// 单链表
typedef struct node {
    dataType data; // 数据域
    struct node *next; // 指针域
} ListNode, *ListNodePtr;

// 单链表的初始化
ListNodePtr LinkedListInit();

// 遍历节点并输出
void ListTraversing(ListNodePtr start);

void Enqueue(ListNodePtr *rear, dataType value);

void Dequeue(ListNodePtr *rear);

BOOL isLoop(ListNodePtr pHead);

// 考虑了单链表带环的情况
int LoopLength(ListNodePtr pHead);

ListNode *findLoopEntrance(ListNodePtr pHead);

int main() {
    ListNodePtr rear = NULL;

    Enqueue(&rear, 1);
    Enqueue(&rear, 2);
    Enqueue(&rear, 3);
    Enqueue(&rear, 4);
    ListTraversing(rear);
    printf("\nisLoop: %d", isLoop(rear));
    printf("\nlength is: %d", LoopLength(rear));

    printf("\nentry is: %d", findLoopEntrance(rear)->data);
    Dequeue(&rear);
    Dequeue(&rear);

    return 0;
}

ListNode *findLoopEntrance(ListNodePtr pHead) {
    ListNodePtr fast = pHead;
    ListNodePtr slow = pHead;
    while (fast != NULL && fast->next != NULL) {

        fast = fast->next->next;
        slow = slow->next;
        //如果有环，则fast会超过slow一圈
        if (fast == slow) {
            break;
        }
    }
    if (fast == NULL || fast->next == NULL)
        return NULL;
    // 从头结点到入口的距离，等于相遇点到入口的距离
    slow = pHead;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}

int LoopLength(ListNodePtr pHead) {
    if (isLoop(pHead) == FALSE)
        return 0;
    ListNodePtr slow = pHead;
    ListNodePtr fast = pHead;
    int length = 0;
    BOOL begin = FALSE;
    BOOL again = FALSE;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
        // 超两圈后停止计数，跳出循环
        if (fast == slow && again == TRUE){
            break;
        }

        // 超一圈后开始计数
        if (fast == slow && again == FALSE) {
            begin = TRUE;
            again = TRUE;
        }
        // 计数
        if (begin == TRUE){
            length++;
        }
    }

    return length;
}

BOOL isLoop(ListNodePtr pHead) {
    ListNodePtr slow = pHead;
    ListNodePtr fast = pHead;

    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;

        if (fast == slow) {
            break;
        }
    }

    if (fast == NULL || fast->next == NULL) {
        return FALSE;
    } else {
        return TRUE;
    }
}

void Dequeue(ListNodePtr *rear) {
    if (*rear == NULL) {
        printf("overflow!");
        return;
    } else {
        ListNodePtr p = (*rear)->next;
        if ((*rear) == p) {
            (*rear) = NULL;
        } else {
            (*rear)->next = p->next;
        }
        free(p);
    }

}

void Enqueue(ListNodePtr *rear, dataType value) {
    ListNodePtr p = LinkedListInit();
    p->data = value;
    if ((*rear) == NULL) {
        (*rear) = p;
        (*rear)->next = (*rear);
    } else {
        p->next = (*rear)->next;
        (*rear)->next = p;
        (*rear) = p;
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

// 遍历节点并输出
void ListTraversing(ListNodePtr start) {
    int length = LoopLength(start);
    int i = 0;
    for (ListNodePtr listNode = start->next; listNode; listNode = listNode->next) {
        if (i == length)break;
        printf("%d ", listNode->data);
        i++;
    }
}
