#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SIZE 10

// 直接插入排序
void InsertionSort(int *array, int n) {
    for (int i = 0; i < n - 1; i++) {
        int t = i + 1, key = array[t];
        while (key < array[t - 1]) {
            array[t] = array[t - 1];
            t--;
        }
        array[t] = key;
    }
}

//二分法插入排序
void BinaryInsertSort(int *array, int n) {
    for (int i = 0; i < n - 1; i++) {
        // 折半查找
        int left = 0, right = i, key = array[i + 1], half = -1;
        while (left <= right) {
            half = (left + right) / 2;
            if (array[half] > key) {
                right = half - 1;
            } else {
                left = half + 1;
            }
        }
        // 赋值
        for (int j = i + 1; j > half; j--) {
            array[j] = array[j - 1];
        }
        array[left] = key;
    }
}

// 希尔排序法，核心思想是缩小增量排序
//
void ShellsSort(int *array, int n, int t) { //t为排序趟数
    for (int i = 1; i <= t; i++) {
        int j, k, temp,
                diHibbard = (int) (pow(2, t - i + 1) - 1);// 计算Hibbard增量
        for (j = diHibbard; j < n; j++) { //分别向每组的有序区域插入
            temp = array[j];
            for (k = j - diHibbard; (k >= j % diHibbard) && array[k] > temp; k -= diHibbard) { //比较与记录后移同时进行
                array[k + diHibbard] = array[k];
            }
            if (k != j - diHibbard) {
                array[k + diHibbard] = temp; // 插入
            }
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

//    InsertionSort(array, SIZE);
//    BinaryInsertSort(array, SIZE);
    ShellsSort(array, SIZE, (int) (log(SIZE + 1) / log(2))); // 排序趟数应为log2(n+1)的整数部分
    printf("\n");

    for (i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    return 0;
}