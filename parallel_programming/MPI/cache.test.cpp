#include <stdio.h>
#include <stdlib.h>
// #include <linux/types.h>
#include <string.h>
#include <sys/time.h>

#define SIZE_1KB (1024)
#define SIZE_1MB (1024 * 1024)

#define NUMBER 64 * SIZE_1MB
#define MILLION 1000000

__u64 rdtsc()
{
    __u32 hi;
    __u32 lo;

    __asm__ __volatile__(
        "rdtsc"
        : "=a"(lo), "=d"(hi));
    return (__u64)hi << 32 | lo;
}

__u64 gettime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((__u64)(tv.tv_sec)) * MILLION + tv.tv_usec;
}

int test_cache_linesize(int array[], int len, int K)
{
    int i;
    for (i = 0; i < len; i += K)
    {
        array[i] *= 3;
    }
    return 0;
}

int test_cache_capacity(int array[], int cap)
{
    int i;
    int lenmod = cap - 1;
    int times = 64 * SIZE_1MB;
    for (i = 0; i < times; i++)
    {
        array[(i * 16) & (lenmod)]++; /*16 means linesize/sizeof(int) = 16*/
    }
    return 0;
}

int test_cache_associative(int array[], int size, int K)
{
    int i;
    int cur = 0;
    __u64 begin;
    __u64 end;
    begin = gettime();
    for (i = 0; i < SIZE_1MB; i++)
    {
        array[cur]++;
        cur += K;
        if (cur >= size)
            cur = 0;
    }
    end = gettime();

    printf("when size = %10d, K = %10d : test_cache_associative cost %14llu us\n",
           size, K, end - begin);
    return 0;
}

int test_cache()
{
    int *array = NULL;
    array = static_cast<int *>(malloc(NUMBER * sizeof(int)));
    __u64 begin;
    __u64 end;
    int i;
    int K;
    int cap;
    int size;
    if (array == NULL)
    {
        printf("malloc space for array failed \n");
        return -1;
    }

    for (i = 0; i < NUMBER; i++)
    {
        array[i] = i;
    }

    printf("---------test cache linesize-------------------------------------------\n");
    for (K = 1; K < 64 * 1024; K *= 2)
    {
        begin = gettime();
        test_cache_linesize(array, NUMBER, K);
        end = gettime();
        printf("when K = %10d,multiply %10d times,cost %14llu us,average cost %llu us\n",
               K, NUMBER / K, end - begin, (end - begin) / (NUMBER / K));
        if (K == 1)
        {
            begin = gettime();
            test_cache_linesize(array, NUMBER, K);
            end = gettime();
            printf("when K = %10d,multiply %10d times,cost %14llu us,average cost %llu us\n",
                   K, NUMBER / K, end - begin, (end - begin) / (NUMBER / K));
        }
    }

    printf("-----------test cache capacity-------------------------------------------\n");
    for (cap = 1024; cap <= NUMBER; cap *= 2)
    {
        begin = gettime();
        test_cache_capacity(array, cap);
        end = gettime();
        printf("when cap = %10d,cost %14llu us\n",
               cap, end - begin);
        if (cap == 2 * SIZE_1MB / sizeof(int))
        {
            begin = gettime();
            test_cache_capacity(array, 3 * SIZE_1MB / sizeof(int));
            end = gettime();
            printf("when cap = %10d,cost %14llu us\n",
                   3 * SIZE_1MB / sizeof(int), end - begin);
        }
    }
    printf("-----------test cache associative ---------------------------------------\n");

    for (size = 1 * SIZE_1MB; size >= 4 * SIZE_1KB; size /= 2)
    {
        for (K = 64; K <= 576; K += 64)
        {
            test_cache_associative(array, size, K);
        }
    }
    free(array);
    return 0;
}

int main()
{
    test_cache();
    return 0;
}