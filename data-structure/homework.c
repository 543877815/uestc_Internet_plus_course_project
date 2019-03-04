//
// Created by PC on 2018/10/11.
//

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 11

void Reverse(int array[], int length) {
    for (int i = 0; i < length / 2; ++i) {
        array[i] = array[i] + array[length - i - 1];
        array[length - i - 1] = array[i] - array[length - i - 1];
        array[i] = array[i] - array[length - i - 1];
    }
}

int main() {
    int i, array[SIZE];
    srand(time(NULL));
    for (i = 0; i < SIZE; i++) {
        array[i] = rand() % 100;
        printf("%d ", array[i]);
    }

    Reverse(array, SIZE);

    printf("\n");

    for (i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    return 0;

}
