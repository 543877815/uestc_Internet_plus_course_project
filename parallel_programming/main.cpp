#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************
MPI_BCAST(buffer,count,datatype,root,comm)
    IN/OUT　buffer　　  通信消息缓冲区的起始地址(可变)
    IN　　　 count　  　 通信消息缓冲区中的数据个数(整型)
    IN 　　　datatype 　通信消息缓冲区中的数据类型(句柄)
    IN　　　 root　  　　发送广播的根的序列号(整型)
    IN 　　　comm   　　通信子(句柄)
int MPI_Bcast(void* buffer,int count,MPI_Datatype datatype,int root, MPI_Comm comm)

MPI_BCAST是从一个序列号为root的进程将一条消息广播发送到组内的所有进程,
包括它本身在内.调用时组内所有成员都使用同一个comm和root,
其结果是将根的通信消息缓冲区中的消息拷贝到其他所有进程中去.
**********************************************/

#define BLOCK_LOW(id, p, n) ((id) * (n) / (p))
#define BLOCK_HIGH(id, p, n) (BLOCK_LOW((id) + 1, p, n) - 1)
#define BLOCK_SIZE(id, p, n) (BLOCK_LOW((id) + 1) - BLOCK_LOW(id))
#define BLCOK_OWNER(index, p, n) (((p)* (index) +1 ) -1 / (n))
#define MIN(a, b) ((a)<(b)?(a):(b))

int main(int argc, char *argv[]) {
    int count;        /* Local prime count */
    double elapsed_time; /* Parallel execution time */
    int first;        /* Index of first multiple */
    int global_count; /* Global prime count */
    int high_value;   /* Highest value on this proc */
    int id;           /* Process ID number */
    int index;        /* Index of current prime */
    int low_value;    /* Lowest value on this proc */
    char *marked;       /* Portion of 2,...,'n' */
    int n, m;            /* Sieving from 2, ..., 'n' */
    int p;            /* Number of processes */
    int proc0_size;   /* Size of proc 0's subarray */
    int prime;        /* Current prime */
    int size;         /* Elements in 'marked' */

    // 初始化
    // MPI程序启动时“自动”建立两个通信器：
    // MPI_COMM_WORLD:包含程序中所有MPI进程
    // MPI_COMM_SELF：有单个进程独自构成，仅包含自己
    MPI_Init(&argc, &argv);

    // MPI_Barrier是MPI中的一个函数接口
    // 表示阻止调用直到communicator中所有进程完成调用
    MPI_Barrier(MPI_COMM_WORLD);

    // MPI_COMM_RANK 得到本进程的进程号，进程号取值范围为 0, …, np-1
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    // MPI_COMM_SIZE 得到所有参加运算的进程的个数
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    // MPI_WTIME返回一个用浮点数表示的秒数
    // 它表示从过去某一时刻到调用时刻所经历的时间
    elapsed_time = -MPI_Wtime();

    // 参数个数为2：文件名以及问题规模n
    if (argc != 2) {
        if (!id) printf("Command line: %s <m> \n", argv[0]);
        // 结束MPI系统
        MPI_Finalize();
        exit(1);
    }

    // atoi(表示 ascii to integer)是把字符串转换成整型数的一个函数
    n = atoi(argv[1]);


    low_value = 3 + 2 * (id * (n) / p);//进程的第一个数
    high_value = 3 + 2 * ((id + 1) * (n) / p - 1);//进程的最后一个数
    size = (high_value - low_value) / 2 + 1;    //进程处理的数组大小

    marked = (char *) malloc(size);
    if (marked == NULL) {
        printf("Cannot allocate enough memory \n");
        MPI_Finalize();
        exit(1);
    }


    for (int i = 0; i < size; i++) {
        marked[i] = 0;
    }
    if (!id) index = 0;
    prime = 2;
    do {
        if (prime * prime > low_value) {
            first = prime * prime - low_value;
        } else {
            if (!(low_value % prime)) first = 0;
            else first = prime - (low_value % prime);
        }
        for (int i = first; i < size; i += prime) marked[i] = i;
        if (!id) {
            while (marked[++index]); /* find the smallest unmarked */
            prime = index + 2;
        }
        MPI_Bcast(&prime, 1, MPI_INT, 0, MPI_COMM_WORLD);
    } while (prime * prime <= n);

    count = 0;
    for (int i = 0; i < size; i++)
        if (!marked[i]) count++;
    MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    elapsed_time += MPI_Wtime();
    if (!id) {
        printf("%d primes are less than or equal to %d \n", global_count, n);
        printf("Total elapsed time: %10.f\n", elapsed_time);
    }
    MPI_Finalize();
    return 0;
}

