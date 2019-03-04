//
// Created by PC on 2018/11/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DataType int
#define MAXSIZE 11

void Traversing(int array[], int size);


void RadixSort(int *array, int size);

int findMaxNum(int *array, int size);

int getLoopTimes(int max);

void bucketSort(int *array, int size, int digits);

int main() {
    int a[MAXSIZE] = {2, 343, 342, 1, 123, 43, 4343, 433, 687, 654, 3};
    Traversing(a, MAXSIZE);

    RadixSort(a, MAXSIZE);

    Traversing(a, MAXSIZE);
    return 0;
}

// 基数排序
void RadixSort(int *array, int size) {
    // 获取数组的最大值
    int max = findMaxNum(array, size);
    // 获取最大树的位数，次数也是再分配的次数。
    int loopTimes = getLoopTimes(max);
    // 对每一位进行基数分配
    for (int i = 1; i <= loopTimes; i++) {
        bucketSort(array, size, i);
    }
}

// 将数字分配到各自的桶中，然后按照同的排序输出排序结果
void bucketSort(int *array, int size, int digits) {
    // 建立一组桶
    int buckets[10][MAXSIZE] = {};
    // 求桶的index的除数
    int tempNum = (int) pow(10, digits - 1);    // 位数控制
    for (int i = 0; i < size; i++) {
        int row_index = (array[i] / tempNum) % 10;  // 个十百千位的数字
        for (int j = 0; j < MAXSIZE; j++) {
            if (NULL == buckets[row_index][j]) {    // 加在桶后面
                buckets[row_index][j] = array[i];
                break;
            }
        }
    }

    //将桶中的数，倒回到原有数组中
    int k = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < MAXSIZE; j++) {
            if (NULL != buckets[i][j]) {
                array[k] = buckets[i][j];
                buckets[i][j] = NULL;
                k++;
            }
        }
    }
}

int getLoopTimes(int max) {
    int count = 0;
    while (max != 0) {
        count++;
        max = max / 10;
    }
    return count;
}

int findMaxNum(int *array, int size) {
    int max = -1;
    for (int i = 0; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}


void Traversing(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}