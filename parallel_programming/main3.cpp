#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

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

规约函数 MPI_Reduce()，将通信子内各进程的同一个变量参与规约计算，并向指定的进程输出计算结果
MPI_METHOD MPI_Reduce(
   _In_range_(!= , recvbuf) _In_opt_ const void* sendbuf,  // 指向输入数据的指针
   _When_(root != MPI_PROC_NULL, _Out_opt_) void* recvbuf, // 指向输出数据的指针，即计算结果存放的地方
   _In_range_(>= , 0) int count,                           // 数据尺寸，可以进行多个标量或多个向量的规约
   _In_ MPI_Datatype datatype,                             // 数据类型
   _In_ MPI_Op op,                                         // 规约操作类型
   _mpi_coll_rank_(root) int root,                         // 目标进程号，存放计算结果的进程
   _In_ MPI_Comm comm                                      // 通信子
);
**********************************************/

#define MIN(a, b) ((a)<(b)?(a):(b))

int main(int argc, char *argv[]) {
    int count;              /* Local prime count */
    double elapsed_time;    /* Parallel execution time */
    int first;              /* Index of first multiple */
    int global_count;       /* Global prime count */
    char *marked;           /* Portion of 2,...,'n' */
    int id;                 /* Process ID number */
    int index;              /* Index of current prime */
    int low_index;          /* Lowest index on this proc */
    int low_value;          /* Lowest value on this proc */
    int high_index;         /* Highest index on this proc */
    int high_value;         /* Highest value on this proc */
    int n;                  /* Sieving from 2, ..., 'n' */
    int p;                  /* Number of processes */
    int proc0_size;         /* Size of proc 0's subarray */
    int prime;              /* Current prime */
    int size;               /* Elements in 'marked' */
    char *sub_marked;       /* sub_mark array */
    int sub_low_index;      /* Lowest index on sub_array */
    int sub_low_value;      /* Lowest array on sub_array */
    int sub_high_index;     /* Highest index on sub_array */
    int sub_high_value;     /* Highest index on sub_array */

    // 初始化
    // MPI程序启动时“自动”建立两个通信器：
    // MPI_COMM_WORLD:包含程序中所有MPI进程
    // MPI_COMM_SELF：有单个进程独自构成，仅包含自己
    MPI_Init(&argc, &argv);

    // MPI_COMM_RANK 得到本进程的进程号，进程号取值范围为 0, …, np-1
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    // MPI_COMM_SIZE 得到所有参加运算的进程的个数
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    // MPI_Barrier是MPI中的一个函数接口
    // 表示阻止调用直到communicator中所有进程完成调用
    MPI_Barrier(MPI_COMM_WORLD);

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

    // 表示找 <= n的素数
    n = atoi(argv[1]);


    // Bail out if all the primes used for sieving are not all held by process 0
    proc0_size = (n - 1) / p;

    // 如果有太多进程
    if ((2 + proc0_size) < (int) sqrt((double) n)) {
        if (!id) printf("Too many processes \n");
        MPI_Finalize();
        exit(1);
    }

    /*
     * 先找前sqrt(n)内的素数
     * 小数组
     */
    int sub_n = (int) sqrt((double) n);
    int sub_N = (sub_n - 1) / 2;

    sub_low_index = 0 * (sub_N / p) + MIN(0, sub_N % p); // 进程的第一个数的索引
    sub_high_index = 1 * (sub_N / p) + MIN(1, sub_N % p) - 1; // 进程的最后一个数的索引
    sub_low_value = sub_low_index * 2 + 3; //进程的第一个数
    sub_high_value = (sub_high_index + 1) * 2 + 1;//进程的最后一个数

    sub_marked = (char *) malloc(sub_n);
    if (sub_marked == nullptr) {
        printf("Cannot allocate enough memory \n");
        MPI_Finalize();
        exit(1);
    }

    // 先假定所有的整数都是素数
    for (int i = 0; i < sub_n; i++) sub_marked[i] = 0;

    // 索引初始化为0
    index = 0;

    prime = 3;
    do {
        // 从小数组开始标只会命中第一个条件
        first = (prime * prime - sub_low_value) / 2;
        // 从第一个素数开始，标记该素数的倍数为非素数
        for (int i = first; i < sub_n; i += prime) {
            sub_marked[i] = 1;

        }
        while (sub_marked[++index]);
        prime = index * 2 + 3; // 起始加偏移
    } while (prime * prime <= sub_n);


    /*
     * 大数组
     */
    int N = (n - 1) / 2;
    low_index = id * (N / p) + MIN(id, N % p); // 进程的第一个数的索引
    high_index = (id + 1) * (N / p) + MIN(id + 1, N % p) - 1; // 进程的最后一个数的索引
    low_value = low_index * 2 + 3; //进程的第一个数
    high_value = (high_index + 1) * 2 + 1;//进程的最后一个数
    size = (high_value - low_value) / 2 + 1;    //进程处理的数组大小

    int LEVEL1_CACHE_size = 32768;      // default 32768
    int LEVEL2_CACHE_size = 262144;     // default 262144
    int LEVEL3_CACHE_size = 9485760;    // default 10485760

    int LEVEL1_CACHE_int = LEVEL1_CACHE_size / 4;
    int LEVEL2_CACHE_int = LEVEL2_CACHE_size / 4;
    int LEVEL3_CACHE_int = LEVEL3_CACHE_size / 4;

    int Block_size = LEVEL3_CACHE_int / p ;
    int Block_num = size / Block_size;
    int Block_remain = size % Block_size;

    int Block_id = 0;
    int Block_N = Block_size - 1;
    int Block_low_index = Block_id * Block_N + MIN(Block_id, Block_remain) + low_index;
    int Block_high_index = (Block_id + 1) * Block_N + MIN(Block_id + 1, Block_remain) - 1 + low_index;
    int Block_low_value = Block_low_index * 2 + 3;
    int Block_high_value = (Block_high_index + 1) * 2 + 1;
    int Block_count;

    // allocate this process 's share of the array
    marked = (char *) malloc(Block_size);
    if (marked == nullptr) {
        printf("Cannot allocate enough memory \n");
        MPI_Finalize();
        exit(1);
    }


    // 总计数
    count = 0;

    while (Block_id <= Block_num) {

        // 索引初始化为0
        index = 0;

        // 从3开始搜寻，first为第一个不是素数的位置
        prime = 3;

        // 块计数
        Block_count = 0;

        // 先假定块中的整数都是素数
        for (int i = 0; i < Block_size; i++) marked[i] = 0;

        // 在块内找素数
        do {
            /*确定该进程中素数的第一个倍数的下标 */
            // 如果该素数n*n>low_value，n*(n-i)都被标记了
            // 即n*n为该进程中的第一个素数
            // 其下标为n*n-low_value，并且由于数组大小减半所以除以2
            if (prime * prime > Block_low_value) {
                first = (prime * prime - Block_low_value) / 2;
            } else {
                // 若最小值low_value为该素数的倍数
                // 则第一个倍数为low_value，即其下标为0
                if (!(Block_low_value % prime)) first = 0;
                    // 若最小值low_value不是该素数的倍数
                    // 但是其余数为偶数，那么第一个非素数的索引为该素数剪去求余除以2
                else if (Block_low_value % prime % 2 == 0) first = prime - ((Block_low_value % prime) / 2);
                    // 若最小值low_value不是该素数的倍数
                    // 那么第一个倍数的下标为该素数减去余数的值，并且由于数组大小减半所以除以2
                else first = (prime - (Block_low_value % prime)) / 2;
            }

            // 从第一个素数开始，标记该素数的倍数为非素数
            for (int i = first; i < Block_size; i += prime) {
                marked[i] = 1;
            }

            // 用于找到下一素数的位置
            while (sub_marked[++index]);

            prime = index * 2 + 3; // 起始加偏移

        } while (prime * prime <= Block_high_value);

        // 统计块内计数
        for (int i = 0; i < Block_size; i++) {
            if (marked[i] == 0) {
                Block_count++;
            }
        }

        // 汇总总体计数
        count += Block_count;


        // 处理下一个块
        Block_id++;
        Block_low_index = Block_id * Block_N + MIN(Block_id, Block_remain) + low_index;
        Block_high_index = (Block_id + 1) * Block_N + MIN(Block_id + 1, Block_remain) - 1 + low_index;
        Block_low_value = Block_low_index * 2 + 3;
        if (Block_id == Block_num) {
            Block_high_value = high_value;
            Block_high_index = high_index;
            Block_size = (Block_high_value - Block_low_value) / 2 + 1;
        } else {
            Block_high_value = (Block_high_index + 1) * 2 + 1;
        }

    }

    // 将标记结果发给0号进程
//    printf("id: %d, low: %d, high: %d, size: %d, count:%d \n", id, low_value, high_value, size, count);

    MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // stop the timer
    elapsed_time += MPI_Wtime();
    MPI_Finalize();
    // print the results
    if (!id) {
        printf("%d primes are less than or equal to %d \n", global_count, n);
        printf("Total elapsed time: %10.6f\n", elapsed_time);

        // 以追加的方式打开文件
//        char str1[40] = "../output/record.cache.";
//        char str2[10] = ".txt";
//        char filename[50];
//        sprintf(filename, "%s%d%s", str1, p, str2);
//        FILE *fp;
//        if ((fp = fopen(filename, "a+")) == nullptr) {
//            printf("fail to open file");
//            exit(0);
//        }
//        fprintf(fp, "%d %d %10.6f\n", p, n, elapsed_time);
//        fclose(fp);
    }
    return 0;
}

