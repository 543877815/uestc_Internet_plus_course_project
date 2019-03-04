//
// Created by PC on 2018/11/1.
// 堆排序 升序
//Traversing
#include <stdio.h>
#include <stdlib.h>

#define DataType int

void Traversing(int array[], int size);

void HeapSort(int array[], int size);

void HeapShift(int array[], int size, int start);

void swap(int *a, int *b);

int main() {
    int size = 9;
    DataType A[9] = {24, 58, 17, 79, 27, 30, 8, 80, 12};
    Traversing(A, size);
    HeapSort(A, size);

    Traversing(A, size);
    return 0;
}

// 从0开始编号
void HeapSort(int array[], int size) {
    // 构建初始堆
    for (int i = size / 2 - 1; i >= 0; i--) {
        HeapShift(array, size - 1, i);
    }
    Traversing(array, size);
    for (int j = size - 1; j > 0; j--) {
        // 堆顶元素和堆中的最后一个元素交换
        swap(&array[0], &array[j]);
        // 重新调整结构，使其继续满足堆定义
        HeapShift(array, j - 1, 0);
    }
}

void HeapShift(int array[], int size, int start) {
    int dad = start; // 父亲节点
    int son = 2 * dad + 1; // 儿子节点
    while (son <= size) {
        // 找子节点的最大值
        if (son + 1 <= size && array[son] < array[son + 1]) {
            son++;
        }
        if (array[dad] > array[son]) {
            return;
        } else {
            swap(&array[dad], &array[son]);


            // 查看交换是否导致子根结构混乱，若是，则向下调整；
            dad = son;
            son = 2 * dad + 1;
        }
    }
}

void swap(int *a, int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void Traversing(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}