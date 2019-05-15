#include "mpi.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b)  ((a)<(b)?(a):(b))

int main(int argc, char *argv[]) {
    unsigned long int count;        /* Local prime count */
    double elapsed_time; /* Parallel execution time */
    unsigned long int first;        /* Index of first multiple */
    unsigned long int global_count = 0; /* Global prime count */
    unsigned long long int high_value;   /* Highest value on this proc */
    unsigned long int i;
    int id;           /* Process ID number */
    unsigned long int index;        /* Index of current prime */
    unsigned long long int low_value;    /* Lowest value on this proc */
    char *marked;       /* Portion of 2,...,'n' */
    unsigned long long int n;            /* Sieving from 2, ..., 'n' */
    int p;            /* Number of processes */
    unsigned long int proc0_size;   /* Size of proc 0's subarray */
    unsigned long int prime;        /* Current prime */
    unsigned long int size;         /* Elements in 'marked' */
    unsigned long int low_index;    // 低位对应的全局索引值
    unsigned long int high_index;   // 高位对应的全局索引值
    MPI_Init(&argc, &argv);

    /* Start the timer */

    MPI_Comm_rank(MPI_COMM_WORLD, &id); //获取进程id
    MPI_Comm_size(MPI_COMM_WORLD, &p);  //获取进程数量
    MPI_Barrier(MPI_COMM_WORLD);        //进行同步
    elapsed_time = -MPI_Wtime();

    // if (argc != 2) {
    //     if (!id) printf("Command line: %s <m>\n", argv[0]);
    //     MPI_Finalize();
    //     exit(1);
    // }

    // n = atoll(argv[1]);      //获取要计算的数
    n = 10000000;      //获取要计算的数

    /* Figure out this process's share of the array, as
       well as the integers represented by the first and
       last array elements 计算这个进程在数组中的份额，以及第一个和最后一个数组元素表示的整数*/
    /*********originalSoution*******/
    // low_value = 2 + id * (n - 1) / p;
    // high_value = 1 + (id + 1) * (n - 1) / p;
    // size = high_value - low_value + 1;
    /********solution1**********/
    if (n % 2 == 0)      // 如果给出的是一个偶数，将给出的数减一变为奇数。
        n = n -1;
    // low_value = 3 + id * (n - 1) / p;
    // high_value = 1 + (id + 1) * (n - 1) / p;
    low_index = id * ((n - 1) / 2) / p;
    high_index = (id+1) * ((n-1) / 2) / p;
    low_value = low_index * 2 + 3;
    high_value = high_index * 2 + 1;



    printf("%d:%d-%d\n",id,low_value,high_value);
    size = (high_value - low_value) / 2 + 1;

    /* Bail out if all the primes used for sieving are
       not all held by process 0 如果用于筛选的所有质数不都由进程0持有，则退出*/

    proc0_size = (n - 1) / p;

    if ((2 + proc0_size) < (int) sqrt((double) n)) {
        if (!id) printf("Too many processes\n");
        MPI_Finalize();
        exit(1);
    }

    /* Allocate this process's share of the array.分配此进程在数组中的份额 */

    marked = (char *) malloc(size);

    if (marked == NULL) {
        printf("Cannot allocate enough memory\n");
        MPI_Finalize();
        exit(1);
    }

    for (i = 0; i < size; i++) marked[i] = 0;
    if (!id) index = 0;         // 不明白为什么要一直判断！id----->只有0号进程才会执行。
    prime = 3;
    do {
        if (prime * prime > low_value)
            first = (prime * prime - low_value)/2;
        else {
            if (!(low_value % prime)) first = 0;
            else if(low_value % prime % 2 ==0)
                first = prime - ((low_value % prime)/2);       // 此处在求局部first（数组中第一个可以被prime整除的数）的时候非常巧妙
            else
                first = (prime - (low_value % prime))/2;
        }
        // if (!id)
        //     printf("---%d",first);
        for (i = first; i < size; i += prime)
            marked[i] = 1;
        if (!id) {
            while (marked[++index]);
            // prime = index + 2;
            prime = index * 2 + 3;	// 要重新写出一个prime的计算表达式
        }
        if (p > 1) MPI_Bcast(&prime, 1, MPI_INT, 0, MPI_COMM_WORLD);    //广播，将一个进程中的数据发送到所有进程
    } while (prime * prime <= n);
    count = 0;
    for (i = 0; i < size; i++)
        if (!marked[i])
        {
            count++;    // 统计单个进程中素数的个数，看有多少个0
        }
    if(!id) count++;
    printf("%d:count %d\n",id,count);
    if (p > 1)
        MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM,
                   0, MPI_COMM_WORLD);  // 规约，集合通信，由进程0来计算全局的count

    /* Stop the timer */

    elapsed_time += MPI_Wtime();


    /* Print the results */

    if (!id) {
        printf("The total number of prime: %ld, total time: %10.6f, total node %d\n", global_count, elapsed_time, p);
    }
    MPI_Finalize();
    return 0;

}
