#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 20

void BubbleSort(int array[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                array[j] = array[j] + array[j + 1];
                array[j + 1] = array[j] - array[j + 1];
                array[j] = array[j] - array[j + 1];
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
    BubbleSort(array, SIZE);
    printf("\n");
    for (i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    return 0;
}