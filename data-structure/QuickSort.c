#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100



void QuickSort(int *array, int left, int right) {
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

    QuickSort(array, left, i - 1);
    QuickSort(array, i + 1, right);
}

int main() {
    int i, array[SIZE];
    srand(time(NULL));
    for (i = 0; i < SIZE; i++) {
        array[i] = rand() % 100;
        printf("%d ", array[i]);
    }

    QuickSort(array, 0, SIZE - 1);
    printf("\n");

    for (i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    return 0;
}
