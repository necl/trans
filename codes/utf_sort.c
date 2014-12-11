#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#ifdef _WIN32
#include<windows.h>
#endif

#define DEFAULT_SORT_NUMBER 10

/* 打印当前时间*/
#define CURRENT_TIME    \
    do{\
        SYSTEMTIME sys;\
        GetLocalTime( &sys ); \
        printf( "\n Current time : %4d-%02d-%02d  %02d:%02d:%02d.%03d \n", \
                            sys.wYear, sys.wMonth, sys.wDay, \
                            sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds \
                    ); \
    }while(0)

/*冒泡排序*/
void bubble_sort(int* data, int count)
{
}

/*插入排序*/
void insert_sort(int* data, int count)
{
    int i, j;
    int tmp;

    for(j = 1; j < count; j++)
    {
        tmp = data[j];
        for(i = j - 1; i >= 0; i--)
        {
            if (data[i] > tmp)
            {
                data[i + 1] = data[i];
            }
            else
            {   
                break;
            }
        }
        data[i + 1] = tmp;
    }
}

/*输出排序数组*/
void dump_data(int* data, int count)
{
    int i;
    
    for (i = 0; i < count; i++ )
    {
        if (i &&(i % 10 == 0))  printf("\n");
        printf(" %8d ", data[i]);
    }
     printf("\n");
}

/* 生成待排序整数数组*/
int generate_rand(int* data, int count)
{
    int i;
    int rand_max = 100;

    while(rand_max < count)
        rand_max *=  10;

    if (rand_max > RAND_MAX)
        rand_max = RAND_MAX;
    
    srand((int)(time(0)));
           
    for( i = 0; i < count; i++)
    {
        data[i] = rand()%rand_max;
    }

    printf("\n Generate %d random integers, and the max is %d (RAND_MAX is %d). \n", count, rand_max, RAND_MAX);

}

/* 生成预期结果、用于检测算法结果*/
int generate_expect(int* data, int count)
{
    insert_sort(data, count);
    return 1;
}

int check_result(int* reault, int* expect, int count)
{
    int i;

    for(i = 0; i < count; i++)
    {
        if (reault[i] != expect[i])
            return 0;
    }
    return 1;
}

int main(int argc, char** argv)
{
    int* ar_orig;
    int* ar_result;
    int* ar_expert;
    int count = 0;
    int result;

#ifdef _WIN32
    LARGE_INTEGER frequency;
    LARGE_INTEGER gen_start, gen_end;
    LARGE_INTEGER exp_start, exp_end;
    LARGE_INTEGER alg_start, alg_end;
    LARGE_INTEGER chk_start, chk_end;
#endif

    CURRENT_TIME;

#ifdef _WIN32
    QueryPerformanceFrequency(&frequency);    
#endif

    {/*计算最大整数*/
        #if 0
        int pre=0, after=1;
        while(after > pre) 
        {
            pre ++; after++;
        }
        printf("pre = %d, after=%d \n ", pre, after);
        #endif
    }

    if (argc == 2)
        count = atoi(argv[1]);
    if (count <=  0)
        count = DEFAULT_SORT_NUMBER;
    
    ar_orig = (int*)malloc(count * sizeof(int) );
    ar_result = (int*)malloc(count * sizeof(int) );
    ar_expert = (int*)malloc(count * sizeof(int) );
    if ((ar_orig == NULL)
        || (ar_result == NULL)
        || (ar_expert == NULL))
        printf("Failed to malloc !\n");


    //生成随机数数组
#ifdef _WIN32
    QueryPerformanceCounter(&gen_start);
#endif

    generate_rand(ar_orig, count);

#ifdef _WIN32
    QueryPerformanceCounter(&gen_end);
    printf("\n Generate random numbers  taking time %g ms. \n", (double)(gen_end.QuadPart - gen_start.QuadPart)*1000/(double)frequency.QuadPart);
#endif


    memcpy(ar_result, ar_orig, count * sizeof(int) );
    memcpy(ar_expert, ar_orig, count * sizeof(int) );
    
    //生成预期结果
#ifdef _WIN32
    QueryPerformanceCounter(&exp_start);
#endif

    generate_expect(ar_expert, count);

#ifdef _WIN32
    QueryPerformanceCounter(&exp_end);
    printf("\n Generate expect result taking time %g ms. \n", (double)(exp_end.QuadPart - exp_start.QuadPart)*1000/(double)frequency.QuadPart);
#endif


    //调用算法函数
#ifdef _WIN32
    QueryPerformanceCounter(&alg_start);
#endif

    insert_sort(ar_result, count);

#ifdef _WIN32
    QueryPerformanceCounter(&alg_end);
    printf("\n Algorithm taking time %g ms. \n", (double)(alg_end.QuadPart - alg_start.QuadPart)*1000/(double)frequency.QuadPart);
#endif


    //检查结果
#ifdef _WIN32
    QueryPerformanceCounter(&chk_start);
#endif

    result = check_result(ar_result, ar_expert, count);

#ifdef _WIN32
    QueryPerformanceCounter(&chk_end);
    printf("\n Checkint result taking time %g ms. \n", (double)(chk_end.QuadPart - chk_start.QuadPart)*1000/(double)frequency.QuadPart);
#endif

    if (result)
        printf("\n The result is OK!\n");
    else
        printf("\n The result is NOK!\n");

    CURRENT_TIME;

}




