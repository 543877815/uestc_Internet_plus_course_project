//
// 简单选择排序
// Created by PC on 2018/10/5.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 30

void SelectionSort(int *array, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i; j < n; j++) {
            if (array[j] < array[min]) {
                min = j;
            }
        }
        if (min != i) {
            array[i] = array[i] + array[min];
            array[min] = array[i] - array[min];
            array[i] = array[i] - array[min];
        }
    }
}

int main() {
    int i, array[SIZE];
    srand(time(NULL));
    for (i = 0; i < SIZE; i++) {
        array[i] = rand() % 100;
        printf("%d ", array[i]);
    }

    SelectionSort(array, SIZE);
    printf("\n");

    for (i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    return 0;
}