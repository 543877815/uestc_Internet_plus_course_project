//
// Created by PC on 2018/11/25.
// 二路归并排序
//

#include <stdio.h>
#include <stdlib.h>

#define DataType int

#define MAXSIZE 9

void Traversing(int array[], int size);

void MergeSort(int source[], int destination[], int left, int right);

void Merge(int *source, int *destination, int left, int middle, int right);

int main() {
    DataType A[MAXSIZE] = {24, 58, 17, 79, 27, 30, 8, 80, 12};
    int B[MAXSIZE];
    Traversing(A, MAXSIZE);
    MergeSort(A, B, 0, MAXSIZE);

    Traversing(B, MAXSIZE);

    return 0;
}


void MergeSort(int source[], int destination[], int left, int right) {
    if (left < right) {
        int middle = (left + right) / 2;
        MergeSort(source, destination, left, middle);
        MergeSort(source, destination, middle + 1, right);
        Merge(source, destination, left, middle, right);
    }
}

void Merge(int *source, int *destination, int left, int middle, int right) {
    int i = left, j = middle + 1, k = left;
    // 左右同时按照排序大小开始复制
    while (i != middle + 1 && j != right + 1) {
        if (source[i] > source[j]) {
            destination[k++] = source[j++];
        } else {
            destination[k++] = source[i++];
        }
    }
    // 有一边复制完了，于是把剩下没复制的复制进去
    while (i != middle + 1) {
        destination[k++] = source[i++];
    }
    while (j != right + 1) {
        destination[k++] = source[j++];
    }
    // 将结果返回原数组
    for (i = left; i <= right; i++) {
        source[i] = destination[i];
    }
}

void Traversing(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}