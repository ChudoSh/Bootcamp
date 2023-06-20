/*
Dev: BarSH
Rev: YonathanZ
Date: 18.6.23
Status: Binary search, Merge & Quick Sort -
*/

#include <stdlib.h> /*rand*/
#include <stdio.h>  /*printf*/
#include <time.h>   /*clock_t*/
#include <stdlib.h> /*qsort*/

#include "sort.h"

static void BubbleTest();
static void SelectionTest();
static void InsertionTest();
static void CountingTest();
static void RadixTest();
static void MergeTest();
static void QuickTest();


static void TestIterBinarySearch();
static void TestRecBinarySearch();

static int IsSorted(int *arr, size_t size);
static int Compare(const void *x, const void *y);

int main()
{
    
    BubbleTest();
    SelectionTest();
    InsertionTest();
    CountingTest();
    RadixTest();
    MergeTest();
    QuickTest();
    
    TestIterBinarySearch();
    TestRecBinarySearch();

    return (0);
}
 /*===========Test===============*/
static void BubbleTest()
{
    int i = 0;
    int arr[5000] = {0};
    clock_t start = 0;
    clock_t end = 0;

    for (i = 0; i < 5000; ++i)
    {
        arr[i] = rand();
    }

    start = clock();
    printf("start of bubble sort = %ld\n", start);
    BubbleSort(arr, 5000);
    end = clock();
    printf("end of bubble sort = %ld\n", end);

    if (!IsSorted(arr, 5000))
    {
        printf("Bubble \033[1;31mfail\033[0m\n");
        return;
    }

    printf("Bubble \033[1;32msuccess\033[0m!\n");

    for (i = 0; i < 5000; ++i)
    {
        arr[i] = rand();
    }

    start = clock();
    printf("start of quick sort = %ld\n", start);
    qsort(arr, 5000, sizeof(int), &Compare);
    end = clock();
    printf("end of quick sort = %ld\n\n", end);

    
}

static void SelectionTest()
{
    int i = 0;
    int arr[5000] = {0};
    clock_t start = 0;
    clock_t end = 0;

    for (i = 0; i < 5000; ++i)
    {
        arr[i] = rand();
    }

    start = clock();
    printf("start of selection sort = %ld\n", start);
    SelectionSort(arr, 5000);
    end = clock();
    printf("end of selection sort = %ld\n", end);

    if (!IsSorted(arr, 5000))
    {
        printf("Selection \033[1;31mfail\033[0m\n");
        return;
    }

    printf("Selection \033[1;32msuccess\033[0m!\n");

    for (i = 0; i < 5000; ++i)
    {
        arr[i] = rand();
    }

    start = clock();
    printf("start of quick sort = %ld\n", start);
    qsort(arr, 5000, sizeof(int), &Compare);
    end = clock();
    printf("end of quick sort = %ld\n\n", end);

    
}

static void InsertionTest()
{
    int i = 0;
    int arr[5000] = {0};
    clock_t start = 0;
    clock_t end = 0;

    for (i = 0; i < 5000; ++i)
    {
        arr[i] = rand();
    }
    
    start = clock();
    printf("start of insertion sort = %ld\n", start);
    SelectionSort(arr, 5000);
    end = clock();
    printf("end of insertion sort = %ld\n", end);

    if (!IsSorted(arr, 5000))
    {
        printf("Insertion \033[1;31mfail\033[0m\n");
        return;
    }

    printf("Insertion \033[1;32msuccess\033[0m!\n");

    for (i = 0; i < 5000; ++i)
    {
        arr[i] = rand();
    }

    start = clock();
    printf("start of quick sort = %ld\n", start);
    qsort(arr, 5000, sizeof(int), &Compare);
    end = clock();
    printf("end of quick sort = %ld\n\n", end);

   
}

static void CountingTest()
{   
    size_t i = 0; 
    int arr[5000] = {0};
    clock_t start = 0;
    clock_t end = 0;

    for (i = 0; i < 5000; ++i)
    {
        arr[i] = rand() % 100 + 1;
    }

    start = clock();
    printf("start of counting sort = %ld\n", start);
    CountingSort(arr, 5000);
    end = clock();
    printf("end of counting sort = %ld\n", end);

    if (!IsSorted(arr, 5000))
    {
        printf("Counting \033[1;31mfail\033[0m\n\n");
        return;
    }

    printf("Counting \033[1;32msuccess\033[0m!\n\n");
}

static void RadixTest()
{   
    size_t i = 0; 
    int arr[5000] = {0};
    clock_t start = 0;
    clock_t end = 0;

    for (i = 0; i < 5000; ++i)
    {
        arr[i] = rand() % 100 + 1;
    }

    start = clock();
    printf("start of radix sort = %ld\n", start);
    RadixSort(arr, 5000);
    end = clock();
    printf("end of radix sort = %ld\n", end);

    if (!IsSorted(arr, 5000))
    {
        printf("radix \033[1;31mfail\033[0m\n\n");
        return;
    }

    printf("radix \033[1;32msuccess\033[0m!\n\n");
}

static void MergeTest()
{   
    size_t i = 0; 
    int arr[10] = {0};
    clock_t start = 0;
    clock_t end = 0;

    for (i = 0; i < 10; ++i)
    {
        arr[i] = rand() % 100 + 1;
    }

    start = clock();
    printf("start of merge sort = %ld\n", start);
    MergeSort(arr, 10);
    end = clock();
    printf("end of merge sort = %ld\n", end);

    if (!IsSorted(arr, 10))
    {
        printf("merge \033[1;31mfail\033[0m\n\n");
        return;
    }

    printf("merge \033[1;32msuccess\033[0m!\n\n");
}

static void QuickTest()
{   
    size_t i = 0; 
    int arr[5000] = {0};
    clock_t start = 0;
    clock_t end = 0;

    for (i = 0; i < 5000; ++i)
    {
        arr[i] = rand() % 100 + 1;
    }

    start = clock();
    printf("start of quick sort = %ld\n", start);
    QuickSort(arr, 5000, sizeof(int), Compare);
    end = clock();
    printf("end of quick sort = %ld\n", end);

    if (!IsSorted(arr, 5000))
    {
        printf("quick \033[1;31mfail\033[0m\n\n");
        return;
    }

    printf("quick \033[1;32msuccess\033[0m!\n\n");
}
/*=============Static funcs==============*/
static int IsSorted(int *arr, size_t size)
{
    size_t i = 0;

    for (i = 0; i < size - 1; ++i)
    {
        if (arr[i] > arr[i + 1])
        {
            return (0);
        }
    }
    return (1);
}

static int Compare(const void *x, const void *y)
{
    return (*(int *)x - *(int *)y);
}

/*==================Searches=================*/
static void TestIterBinarySearch()
{   
    size_t i = 0; 
    int arr[5000] = {0};
    clock_t start = 0;
    clock_t end = 0;

    for (i = 0; i < 5000; ++i)
    {
        arr[i] = rand() % 100 + 1;
    }

    start = clock();
    printf("start of iterative binary search = %ld\n", start);
    IterBinarySearch(arr, 50, 5000);
    end = clock();
    printf("end of iterative binary search = %ld\n", end);


    printf("IterBinary Search \033[1;32msuccess\033[0m!\n\n");
}

static void TestRecBinarySearch()
{   
    size_t i = 0; 
    int arr[5000] = {0};
    clock_t start = 0;
    clock_t end = 0;

    for (i = 0; i < 5000; ++i)
    {
        arr[i] = rand() % 100 + 1;
    }

    start = clock();
    printf("start of recursive binary search = %ld\n", start);
    RecBinarySearch(arr, 50, 5000);
    end = clock();
    printf("end of recursive binary search = %ld\n", end);


    printf("RecBinarySort \033[1;32msuccess\033[0m!\n\n");
}