//
// Created by PC on 2018/11/1.
// 统计海量数据中最大的K个数（Top-K问题）
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define DataType int

void HeapShift(int array[], int size, int start);  // 堆调整

void HeapSort(int array[], int size);   // 堆排序

void Top_k(int Tarray[], int Tsize, const int array[], int size); // Top-K

int findKthLargest(int *nums, int numsSize, int k); // 找到最大的第K个数

void Traversing(int array[], int size); // 遍历堆

void swap(int *a, int *b);  // 交换

void createDotFile(const char *filename, char *title, int *array, int size);

void createDotFile1(const char *filename, char *title, int *array, int size, int Old, int New);

int main() {
    int size = 100;
    DataType A[size];
    FILE *fp = fopen("./data/data.txt", "r+");
    if (fp == NULL)
        exit(0x01);
    DataType keynumber;
    for (int i = 0; i < size; i++) {
        fscanf(fp, "%d", &keynumber);
        A[i] = keynumber;
    }
    Traversing(A, size);

    int k = 10;
    int Top[k];

    Top_k(Top, k, A, size);
    Traversing(Top, k);

    printf("findKthLargest: %d", findKthLargest(A, size, k));
}

// // 找到最大的第K个数，leedcode - 215. Kth Largest Element in an Array
int findKthLargest(int *nums, int numsSize, int k) {
    int Tarray[k];
    for (int i = 0; i < k; i++) {
        Tarray[i] = nums[i];
    }
    for (int i = k / 2 - 1; i >= 0; i--) {
        HeapShift(Tarray, k - 1, i);
    }
    // 维护小顶堆
    for (int j = k; j < numsSize; j++) {
        if (nums[j] > Tarray[0]) {
            Tarray[0] = nums[j];
            for (int i = k / 2 - 1; i >= 0; i--) {
                HeapShift(Tarray, k - 1, i);
            }
        }
    }
    HeapSort(Tarray, k);
    Traversing(Tarray, k);
    return Tarray[k - 1];
}

// 堆排序，从0开始编号
void HeapSort(int array[], int size) {
    // 构建初始堆
    for (int i = size / 2 - 1; i >= 0; i--) {
        HeapShift(array, size - 1, i);
    }
    for (int j = size - 1; j > 0; j--) {
        // 堆顶元素和堆中的最后一个元素交换
        swap(&array[0], &array[j]);
        // 重新调整结构，使其继续满足堆定义
        HeapShift(array, j - 1, 0);
    }
}

// 维护最大k个数的数组
void Top_k(int Tarray[], int Tsize, const int array[], int size) {
    // 构建初始小顶堆
    for (int i = 0; i < Tsize; i++) {
        Tarray[i] = array[i];
    }
    createDotFile("./dotFile/TopK_init.dot", "Init Heap", Tarray, Tsize);
    system("dot -Tpng ./dotFile/TopK_init.dot -o ./dotFile/TopK_init.png");

    for (int i = Tsize / 2 - 1; i >= 0; i--) {
        HeapShift(Tarray, Tsize - 1, i);
    }
    createDotFile("./dotFile/TopK_Adjust.dot", "Adjust Heap", Tarray, Tsize);
    system("dot -Tpng ./dotFile/TopK_Adjust.dot -o ./dotFile/TopK_Adjust.png");

    // 维护小顶堆
    for (int j = Tsize; j < size; j++) {
        int old = 0;
        if (array[j] > Tarray[0]) {
            old = Tarray[0];
            Tarray[0] = array[j];
            for (int i = Tsize / 2 - 1; i >= 0; i--) {
                HeapShift(Tarray, Tsize - 1, i);
            }
        }
        if (j <= 2 * Tsize) {
            char *dotPath = (char *) malloc(100);
            sprintf(dotPath, "./dotFile/Time%d.dot", j + 1);
            char *title = (char *) malloc(100);
            sprintf(title, "Time = %d", j + 1);
            createDotFile1(dotPath, title, Tarray, Tsize, old, array[j]);
            char *order = (char *) malloc(100);
            sprintf(order, "dot -Tpng ./dotFile/Time%d.dot -o ./dotFile/Time%d.png", j + 1, j + 1);
            system(order);
        }
    }
}

void createDotFile1(const char *filename, char *title, int *array, int size, int Old, int New) {
    FILE *fp = fopen(filename, "w"); // 文件指针
    if (fp == NULL) {   // 为NULL则返回
        printf("File cannot open!");
        exit(0);
    }
    fprintf(fp, "digraph G {\n");   // 开头
    fprintf(fp, "graph[label=\"%s\"];", title);

    fprintf(fp, "newInsert[shape=Mcircle,color=blue, label=\"%d\"];\n", New);
    for (int i = 0; i < size; ++i) {
        if (array[i] == New) {
            fprintf(fp, "%d[shape=circle,color=blue];\n", array[i]);
            if (Old != 0) {
                fprintf(fp, "%d[shape=doublecircle,color=red];\n", Old);
            }
        } else {
            fprintf(fp, "%d[shape=circle];\n", array[i]);
        }

        int left_index = 2 * i + 1;
        if (left_index < size) {
            fprintf(fp, "%d->%d;\n", array[i], array[left_index]);
        }
        int right_index = 2 * i + 2;
        if (right_index < size) {
            fprintf(fp, "%d->%d;\n", array[i], array[right_index]);
        }
    }
    if (New < array[0]) {
        fprintf(fp, "notInsert[shape=doublecircle,color=red,label=\"%d\"];\n", New);
    }

    fprintf(fp, "%d->struct[color=white];", array[size - 1]);
    fprintf(fp, "struct [shape=record,label=\"{value|address}");
    for (int k = 0; k < size; ++k) {
        fprintf(fp, "|{%d|%d}", array[k], k);
    }
    fprintf(fp, "\"];\n");
    fprintf(fp, "}\n"); // 结尾
    fclose(fp); // 关闭IO
}

void createDotFile(const char *filename, char *title, int *array, int size) {
    FILE *fp = fopen(filename, "w"); // 文件指针
    if (fp == NULL) {   // 为NULL则返回
        printf("File cannot open!");
        exit(0);
    }
    fprintf(fp, "digraph G {\n");   // 开头
    fprintf(fp, "graph[label=\"%s\"];", title);
    for (int i = 0; i < size; ++i) {
        fprintf(fp, "%d [shape=circle];\n", array[i]);
        int left_index = 2 * i + 1;
        if (left_index < size) {
            fprintf(fp, "%d->%d;\n", array[i], array[left_index]);
        }
        int right_index = 2 * i + 2;
        if (right_index < size) {
            fprintf(fp, "%d->%d;\n", array[i], array[right_index]);
        }
    }
    fprintf(fp, "%d->struct[color=white];", array[size - 1]);
    fprintf(fp, "struct [shape=record,label=\"{value|address}");
    for (int k = 0; k < size; ++k) {
        fprintf(fp, "|{%d|%d}", array[k], k);
    }
    fprintf(fp, "\"];\n");
    fprintf(fp, "}\n"); // 结尾
    fclose(fp); // 关闭IO
}

// 交换
void swap(int *a, int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

// 遍历
void Traversing(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 堆调整
void HeapShift(int array[], int size, int start) {
    int dad = start; // 父亲节点
    int son = 2 * dad + 1; // 儿子节点
    while (son <= size) {
        // 找子节点的最大值
        if (son + 1 <= size && array[son] > array[son + 1]) {
            son++;
        }
        if (array[dad] < array[son]) {
            return;
        } else {
            swap(&array[dad], &array[son]);
            // 查看交换是否导致子根结构混乱，若是，则向下调整；
            dad = son;
            son = 2 * dad + 1;
        }
    }
}