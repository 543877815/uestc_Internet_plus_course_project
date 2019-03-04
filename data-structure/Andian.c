//
// Created by PC on 2018/10/27.
//

#include <stdio.h>
#include <stdlib.h>

#define M 4
#define N 4

void Andian(int array[M][N], int row, int col);

int main() {
    int A[M][N] = {{9,  7,  6,  8},
                   {20, 26, 22, 25},
                   {28, 36, 25, 30},
                   {12, 4,  2,  6}};
    Andian(A, M, N);
    return 0;
}

void Andian(int array[M][N], int row, int col) {
    for (int i = 0; i < row; i++) {
        int minIndex = 0;
        int minValue = array[i][0];


        int j;
        for (j = 1; j < col; j++) {

            if (array[i][j] < minValue) {
                minIndex = j;
                minValue = array[i][j];
            }
        }

        int k;
        for (k = 0; k < row; k++) {
            if (array[k][minIndex] > minValue) {
                break;
            }
        }

        if (k == row) {
            printf("%d ", array[i][minIndex]);
        }
    }
}