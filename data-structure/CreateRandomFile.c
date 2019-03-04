//
// Created by PC on 2018/11/8.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main() {
    srand((unsigned int) time(NULL));
    FILE *fp;
    int size = 100;
    int i, d;

    fp = fopen("./data/data.txt", "w");
    if (fp == NULL) {
        printf("File cannot open!");
        exit(0);
    }

    for (int j = 0; j < size; ++j) {
        d = rand() % 1000;
        if (j % 10 == 0 && j != 0) {
            fprintf(fp, "\n");
        }
        fprintf(fp, "%d ", d);
    }

    fclose(fp);
    return 0;
}