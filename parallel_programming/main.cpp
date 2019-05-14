<<<<<<< HEAD
#include "mpi.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "error.h"

using namespace std;

/************************************************
MPI_BCAST(buffer,count,datatype,root,comm)
    IN/OUT¡¡buffer¡¡¡¡  Í¨ÐÅÏûÏ¢»º³åÇøµÄÆðÊ¼µØÖ·(¿É±ä)
    IN¡¡¡¡¡¡ count¡¡  ¡¡ Í¨ÐÅÏûÏ¢»º³åÇøÖÐµÄÊý¾Ý¸öÊý(ÕûÐÍ)
    IN ¡¡¡¡¡¡datatype ¡¡Í¨ÐÅÏûÏ¢»º³åÇøÖÐµÄÊý¾ÝÀàÐÍ(¾ä±ú)
    IN¡¡¡¡¡¡ root¡¡  ¡¡¡¡·¢ËÍ¹ã²¥µÄ¸ùµÄÐòÁÐºÅ(ÕûÐÍ)
    IN ¡¡¡¡¡¡comm   ¡¡¡¡Í¨ÐÅ×Ó(¾ä±ú)
int MPI_Bcast(void* buffer,int count,MPI_Datatype datatype,int root, MPI_Comm comm)

MPI_BCASTÊÇ´ÓÒ»¸öÐòÁÐºÅÎªrootµÄ½ø³Ì½«Ò»ÌõÏûÏ¢¹ã²¥·¢ËÍµ½×éÄÚµÄËùÓÐ½ø³Ì,
°üÀ¨Ëü±¾ÉíÔÚÄÚ.µ÷ÓÃÊ±×éÄÚËùÓÐ³ÉÔ±¶¼Ê¹ÓÃÍ¬Ò»¸öcommºÍroot,
Æä½á¹ûÊÇ½«¸ùµÄÍ¨ÐÅÏûÏ¢»º³åÇøÖÐµÄÏûÏ¢¿½±´µ½ÆäËûËùÓÐ½ø³ÌÖÐÈ¥.

¹æÔ¼º¯Êý MPI_Reduce()£¬½«Í¨ÐÅ×ÓÄÚ¸÷½ø³ÌµÄÍ¬Ò»¸ö±äÁ¿²ÎÓë¹æÔ¼¼ÆËã£¬²¢ÏòÖ¸¶¨µÄ½ø³ÌÊä³ö¼ÆËã½á¹û
MPI_METHOD MPI_Reduce(
   _In_range_(!= , recvbuf) _In_opt_ const void* sendbuf,  // Ö¸ÏòÊäÈëÊý¾ÝµÄÖ¸Õë
   _When_(root != MPI_PROC_NULL, _Out_opt_) void* recvbuf, // Ö¸ÏòÊä³öÊý¾ÝµÄÖ¸Õë£¬¼´¼ÆËã½á¹û´æ·ÅµÄµØ·½
   _In_range_(>= , 0) int count,                           // Êý¾Ý³ß´ç£¬¿ÉÒÔ½øÐÐ¶à¸ö±êÁ¿»ò¶à¸öÏòÁ¿µÄ¹æÔ¼
   _In_ MPI_Datatype datatype,                             // Êý¾ÝÀàÐÍ
   _In_ MPI_Op op,                                         // ¹æÔ¼²Ù×÷ÀàÐÍ
   _mpi_coll_rank_(root) int root,                         // Ä¿±ê½ø³ÌºÅ£¬´æ·Å¼ÆËã½á¹ûµÄ½ø³Ì
   _In_ MPI_Comm comm                                      // Í¨ÐÅ×Ó
);
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
    int n;            /* Sieving from 2, ..., 'n' */
    int p;            /* Number of processes */
    int proc0_size;   /* Size of proc 0's subarray */
    int prime;        /* Current prime */
    int size;         /* Elements in 'marked' */

    // ³õÊ¼»¯
    // MPI³ÌÐòÆô¶¯Ê±¡°×Ô¶¯¡±½¨Á¢Á½¸öÍ¨ÐÅÆ÷£º
    // MPI_COMM_WORLD:°üº¬³ÌÐòÖÐËùÓÐMPI½ø³Ì
    // MPI_COMM_SELF£ºÓÐµ¥¸ö½ø³Ì¶À×Ô¹¹³É£¬½ö°üº¬×Ô¼º
    MPI_Init(&argc, &argv);

    // MPI_COMM_RANK µÃµ½±¾½ø³ÌµÄ½ø³ÌºÅ£¬½ø³ÌºÅÈ¡Öµ·¶Î§Îª 0, ¡­, np-1
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    // MPI_COMM_SIZE µÃµ½ËùÓÐ²Î¼ÓÔËËãµÄ½ø³ÌµÄ¸öÊý
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    // MPI_BarrierÊÇMPIÖÐµÄÒ»¸öº¯Êý½Ó¿Ú
    // ±íÊ¾×èÖ¹µ÷ÓÃÖ±µ½communicatorÖÐËùÓÐ½ø³ÌÍê³Éµ÷ÓÃ
    MPI_Barrier(MPI_COMM_WORLD);

    // MPI_WTIME·µ»ØÒ»¸öÓÃ¸¡µãÊý±íÊ¾µÄÃëÊý
    // Ëü±íÊ¾´Ó¹ýÈ¥Ä³Ò»Ê±¿Ìµ½µ÷ÓÃÊ±¿ÌËù¾­ÀúµÄÊ±¼ä

    elapsed_time = -MPI_Wtime();

    // ²ÎÊý¸öÊýÎª2£ºÎÄ¼þÃûÒÔ¼°ÎÊÌâ¹æÄ£n
    if (argc != 2) {
        if (!id) printf("Command line: %s <m> \n", argv[0]);
        // ½áÊøMPIÏµÍ³
        MPI_Finalize();
        exit(1);
    }

    // ±íÊ¾ÕÒ <= nµÄËØÊý
    n = atoi(argv[1]);
//    low_value = 2 + id * (n - 1) / p;//½ø³ÌµÄµÚÒ»¸öÊý
//    high_value = 1 + (id + 1) * (n - 1) / p;//½ø³ÌµÄ×îºóÒ»¸öÊý
//    size = high_value - low_value + 1;    //½ø³Ì´¦ÀíµÄÊý×é´óÐ¡

    int N = n - 1;
    low_value = 2 + id * (N / p) + MIN(id, N % p);//½ø³ÌµÄµÚÒ»¸öÊý
    high_value = 2 + (id + 1) * (N / p) + MIN(id + 1, N % p) - 1;//½ø³ÌµÄ×îºóÒ»¸öÊý
    size = high_value - low_value + 1;    //½ø³Ì´¦ÀíµÄÊý×é´óÐ¡


    // Bail out if all the primes used for sieving are not all held by process 0
    proc0_size = (n - 1) / p;

    // Èç¹ûÓÐÌ«¶à½ø³Ì
    if ((2 + proc0_size) < (int) sqrt((double) n)) {
        if (!id) printf("Too many processes \n");
        MPI_Finalize();
        exit(1);
    }

    // allocate this process 's share of the array
    marked = (char *) malloc(size);
    if (marked == nullptr) {
        printf("Cannot allocate enough memory \n");
        MPI_Finalize();
        exit(1);
    }

    // ÏÈ¼Ù¶¨ËùÓÐµÄÕûÊý¶¼ÊÇËØÊý
    for (int i = 0; i < size; i++) marked[i] = 0;

    // Ë÷Òý³õÊ¼»¯Îª0
    if (!id) index = 0;

    // ´Ó2¿ªÊ¼ËÑÑ°
    prime = 2;
    do {
        /*È·¶¨¸Ã½ø³ÌÖÐËØÊýµÄµÚÒ»¸ö±¶ÊýµÄÏÂ±ê */
        // Èç¹û¸ÃËØÊýn*n>low_value£¬n*(n-i)¶¼±»±ê¼ÇÁË
        // ¼´n*nÎª¸Ã½ø³ÌÖÐµÄµÚÒ»¸öËØÊý
        // ÆäÏÂ±êÎªn*n-low_value
        if (prime * prime > low_value) {
            first = prime * prime - low_value;
        } else {
            // Èô×îÐ¡Öµlow_valueÎª¸ÃËØÊýµÄ±¶Êý
            // ÔòµÚÒ»¸ö±¶ÊýÎªlow_value£¬¼´ÆäÏÂ±êÎª0
            if (!(low_value % prime)) first = 0;
                // Èô×îÐ¡Öµlow_value²»ÊÇ¸ÃËØÊýµÄ±¶Êý
                // ÄÇÃ´µÚÒ»¸ö±¶ÊýµÄÏÂ±êÎª¸ÃËØÊý¼õÈ¥ÓàÊýµÄÖµ
            else first = prime - (low_value % prime);
        }

        // ´ÓµÚÒ»¸öËØÊý¿ªÊ¼£¬±ê¼Ç¸ÃËØÊýµÄ±¶ÊýÎª·ÇËØÊý
        for (int i = first; i < size; i += prime) marked[i] = 1;

        // Ö»ÓÐid=0µÄ½ø³Ì²Åµ÷ÓÃ£¬ÓÃÓÚÕÒµ½ÏÂÒ»ËØÊýµÄÎ»ÖÃ
        if (!id) {
            while (marked[++index]);
            prime = index + 2;
        }

        // Ö»ÓÐid=0µÄ½ø³Ì²Åµ÷ÓÃ£¬ÓÃÓÚ½«ÏÂÒ»¸öËØÊý¹ã²¥³öÈ¥
        if (p > 1) {
            MPI_Bcast(&prime, 1, MPI_INT, 0, MPI_COMM_WORLD);
        }

    } while (prime * prime <= n);

    // ½«±ê¼Ç½á¹û·¢¸ø0ºÅ½ø³Ì
//    printf("id: %d, low: %d, high: %d, size: %d\n", id, low_value, high_value, size);
    count = 0;
    for (int i = 0; i < size; i++)
        if (marked[i] == 0) {
            count++;
//            printf("%d ", i + low_value);
        }
//    printf("\n");
    if (p > 1) MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // stop the timer
    elapsed_time += MPI_Wtime();

    // print the results
    if (!id) {
        printf("%d primes are less than or equal to %d \n", global_count, n);
        printf("Total elapsed time: %10.6f\n", elapsed_time);
    }
=======
// #include <mpi.h>
// #include <math.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// /************************************************
// MPI_BCAST(buffer,count,datatype,root,comm)
//     IN/OUTï¿½ï¿½bufferï¿½ï¿½ï¿½ï¿½  Í¨ï¿½ï¿½ï¿½ï¿½Ï¢ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê¼ï¿½ï¿½Ö·(ï¿½É±ï¿½)
//     INï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ countï¿½ï¿½  ï¿½ï¿½ Í¨ï¿½ï¿½ï¿½ï¿½Ï¢ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ðµï¿½ï¿½ï¿½ï¿½Ý¸ï¿½ï¿½ï¿½(ï¿½ï¿½ï¿½ï¿½)
//     IN ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½datatype ï¿½ï¿½Í¨ï¿½ï¿½ï¿½ï¿½Ï¢ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ðµï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½(ï¿½ï¿½ï¿½)
//     INï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ rootï¿½ï¿½  ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Í¹ã²¥ï¿½Ä¸ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ðºï¿½(ï¿½ï¿½ï¿½ï¿½)
//     IN ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½comm   ï¿½ï¿½ï¿½ï¿½Í¨ï¿½ï¿½ï¿½ï¿½(ï¿½ï¿½ï¿½)
// int MPI_Bcast(void* buffer,int count,MPI_Datatype datatype,int root, MPI_Comm comm)

// MPI_BCASTï¿½Ç´ï¿½Ò»ï¿½ï¿½ï¿½ï¿½ï¿½Ðºï¿½Îªrootï¿½Ä½ï¿½ï¿½Ì½ï¿½Ò»ï¿½ï¿½ï¿½ï¿½Ï¢ï¿½ã²¥ï¿½ï¿½ï¿½Íµï¿½ï¿½ï¿½ï¿½Úµï¿½ï¿½ï¿½ï¿½Ð½ï¿½ï¿½ï¿½,
// ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½.ï¿½ï¿½ï¿½ï¿½Ê±ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ð³ï¿½Ô±ï¿½ï¿½Ê¹ï¿½ï¿½Í¬Ò»ï¿½ï¿½commï¿½ï¿½root,
// ï¿½ï¿½ï¿½ï¿½ï¿½Ç½ï¿½ï¿½ï¿½ï¿½ï¿½Í¨ï¿½ï¿½ï¿½ï¿½Ï¢ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ðµï¿½ï¿½ï¿½Ï¢ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ð½ï¿½ï¿½ï¿½ï¿½ï¿½È¥.
// **********************************************/

// #define BLOCK_LOW(id, p, n) ((id) * (n) / (p))
// #define BLOCK_HIGH(id, p, n) (BLOCK_LOW((id) + 1, p, n) - 1)
// #define BLOCK_SIZE(id, p, n) (BLOCK_LOW((id) + 1) - BLOCK_LOW(id))
// #define BLCOK_OWNER(index, p, n) (((p)* (index) +1 ) -1 / (n))
// #define MIN(a, b) ((a)<(b)?(a):(b))

// int main(int argc, char *argv[]) {
//     int count;        /* Local prime count */
//     double elapsed_time; /* Parallel execution time */
//     int first;        /* Index of first multiple */
//     int global_count; /* Global prime count */
//     int high_value;   /* Highest value on this proc */
//     int id;           /* Process ID number */
//     int index;        /* Index of current prime */
//     int low_value;    /* Lowest value on this proc */
//     char *marked;       /* Portion of 2,...,'n' */
//     int n, m;            /* Sieving from 2, ..., 'n' */
//     int p;            /* Number of processes */
//     int proc0_size;   /* Size of proc 0's subarray */
//     int prime;        /* Current prime */
//     int size;         /* Elements in 'marked' */

//     // ï¿½ï¿½Ê¼ï¿½ï¿½
//     // MPIï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê±ï¿½ï¿½ï¿½Ô¶ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Í¨ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
//     // MPI_COMM_WORLD:ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½MPIï¿½ï¿½ï¿½ï¿½
//     // MPI_COMM_SELFï¿½ï¿½ï¿½Ðµï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ì¶ï¿½ï¿½Ô¹ï¿½ï¿½É£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ô¼ï¿½
//     MPI_Init(&argc, &argv);

//     // MPI_Barrierï¿½ï¿½MPIï¿½Ðµï¿½Ò»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ó¿ï¿½
//     // ï¿½ï¿½Ê¾ï¿½ï¿½Ö¹ï¿½ï¿½ï¿½ï¿½Ö±ï¿½ï¿½communicatorï¿½ï¿½ï¿½ï¿½ï¿½Ð½ï¿½ï¿½ï¿½ï¿½ï¿½Éµï¿½ï¿½ï¿½
//     MPI_Barrier(MPI_COMM_WORLD);

//     // MPI_COMM_RANK ï¿½Ãµï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ÌµÄ½ï¿½ï¿½ÌºÅ£ï¿½ï¿½ï¿½ï¿½Ìºï¿½È¡Öµï¿½ï¿½Î§Îª 0, ï¿½ï¿½, np-1
//     MPI_Comm_rank(MPI_COMM_WORLD, &id);

//     // MPI_COMM_SIZE ï¿½Ãµï¿½ï¿½ï¿½ï¿½Ð²Î¼ï¿½ï¿½ï¿½ï¿½ï¿½Ä½ï¿½ï¿½ÌµÄ¸ï¿½ï¿½ï¿½
//     MPI_Comm_size(MPI_COMM_WORLD, &p);

//     // MPI_WTIMEï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½ï¿½Ã¸ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê¾ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
//     // ï¿½ï¿½ï¿½ï¿½Ê¾ï¿½Ó¹ï¿½È¥Ä³Ò»Ê±ï¿½Ìµï¿½ï¿½ï¿½ï¿½ï¿½Ê±ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê±ï¿½ï¿½
//     elapsed_time = -MPI_Wtime();

//     // ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Îª2ï¿½ï¿½ï¿½Ä¼ï¿½ï¿½ï¿½ï¿½Ô¼ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ä£n
//     if (argc != 2) {
//         if (!id) printf("Command line: %s <m> \n", argv[0]);
//         // ï¿½ï¿½ï¿½ï¿½MPIÏµÍ³
//         MPI_Finalize();
//         exit(1);
//     }

//     // atoi(ï¿½ï¿½Ê¾ ascii to integer)ï¿½Ç°ï¿½ï¿½Ö·ï¿½ï¿½ï¿½×ªï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
//     n = atoi(argv[1]);


//     low_value = 3 + 2 * (id * (n) / p);//ï¿½ï¿½ï¿½ÌµÄµï¿½Ò»ï¿½ï¿½ï¿½ï¿½
//     high_value = 3 + 2 * ((id + 1) * (n) / p - 1);//ï¿½ï¿½ï¿½Ìµï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½ï¿½ï¿½
//     size = (high_value - low_value) / 2 + 1;    //ï¿½ï¿½ï¿½Ì´ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ð¡

//     marked = (char *) malloc(size);
//     if (marked == NULL) {
//         printf("Cannot allocate enough memory \n");
//         MPI_Finalize();
//         exit(1);
//     }


//     for (int i = 0; i < size; i++) {
//         marked[i] = 0;
//     }
//     if (!id) index = 0;
//     prime = 2;
//     do {
//         if (prime * prime > low_value) {
//             first = prime * prime - low_value;
//         } else {
//             if (!(low_value % prime)) first = 0;
//             else first = prime - (low_value % prime);
//         }
//         for (int i = first; i < size; i += prime) marked[i] = i;
//         if (!id) {
//             while (marked[++index]); /* find the smallest unmarked */
//             prime = index + 2;
//         }
//         MPI_Bcast(&prime, 1, MPI_INT, 0, MPI_COMM_WORLD);
//     } while (prime * prime <= n);

//     count = 0;
//     for (int i = 0; i < size; i++)
//         if (!marked[i]) count++;
//     MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
//     elapsed_time += MPI_Wtime();
//     if (!id) {
//         printf("%d primes are less than or equal to %d \n", global_count, n);
//         printf("Total elapsed time: %10.f\n", elapsed_time);
//     }
//     MPI_Finalize();
//     return 0;
// }


#include <stdint.h>
#include <iostream>
#include <mpi.h>
#include <stdint.h>
using namespace std;

int main(int argc,char* argv[]){
    cout<<"hello"<<endl;
    int myid, numprocs;
    int  namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Get_processor_name(processor_name,&namelen); 
    std::cout<<"Hello World! Process"<<myid<<"of"<<numprocs<<" on "<<processor_name<<std::endl;
>>>>>>> 7204af4e94cc719eed7ef6963f1c0c2d760f8b31
    MPI_Finalize();

    // ÒÔ×·¼ÓµÄ·½Ê½´ò¿ªÎÄ¼þ
//    char str1[30] = "../output/record.init.";
//    char str2[10] = ".txt";
//    char filename[50];
//    sprintf(filename, "%s%d%s", str1, p, str2);
//    FILE *fp;
//    if ((fp = fopen(filename,"a+")) == nullptr){
//        printf("fail to open file");
//        exit(0);
//    }
//    fprintf(fp, "%d %d %10.6f\n", p, n, elapsed_time);
//    fclose(fp);
    return 0;
}
