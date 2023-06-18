/*
Dev: BarSH
Rev: EylonE
Date: 30.5.23
Status: Approved
*/

#include <assert.h>/*assert*/
#include <stdlib.h> /*malloc*/

#include "sort.h"

#define COUNT_SIZE (101)
#define RADIX_SIZE (10)

enum BOOLEAN
{
    FALSE = 0, 
    TRUE = 1
};

enum STATUS
{
    FAIL = -1,
    SUCCESS = 0 
};

static void Swap(int* a, int* b);
static int GetMaxDigit(int* arr, size_t size);
static int CountingRadix(int *arr, size_t size, int digit);

void BubbleSort(int *arr, size_t size)
{
    size_t i = 0;
    int to_sort = TRUE;  

    assert(NULL != arr);
    assert(0 < size);

    while (to_sort)
    {
        to_sort = FALSE;
        for (i = 0 ; i < size - 1; ++i)
         {
            if (arr[i] > arr[i + 1])
            {
                Swap(&arr[i], &arr[i + 1]);
                to_sort = TRUE;
            }
        } 
    }    
}

void SelectionSort(int *arr, size_t size)
{
    size_t i = 0;
    size_t j = 0;
    size_t min = 0;

    assert(NULL != arr);
    assert(0 < size);

    for (i = 0; i < size - 1; ++i)
    {
        min = i;
        for (j = i + 1 ; j < size; ++j)
         {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }

        if(min != i)
        {
            Swap(&arr[min], &arr[i]);
        }
    }    
}

void InsertionSort(int *arr, size_t size)
{
    size_t i = 0;
    int j = 0;

    assert(NULL != arr);
    assert(0 < size);

    for (i = 1; i < size; ++i)
    {
        j = i - 1;
        while (arr[j] > arr[j + 1] && 0 <= j)
        {
            Swap(&arr[j + 1], &arr[j]);
            --(j);
        }  
    }    
}

int CountingSort(int *arr, size_t size)
{
    int counting_array[COUNT_SIZE] = {0};
    int *output_array = NULL; 
    size_t i  = 0;
    int j  = 0;

    assert(NULL != arr);
    assert(0 < size);

    output_array = (int *)malloc(size * sizeof(int));
    if (NULL == output_array)
    {
        return (FAIL);
    }

    for (i = 0; i < size; ++i)
    {
        ++(counting_array[arr[i]]);       
    }

    for (j = 1; j <= COUNT_SIZE; ++j)
    {
        counting_array[j] += counting_array[j - 1];       
    }

    for (j = size - 1 ; 0 <= j; --j)
    {
        output_array[counting_array[arr[j]] - 1] = arr[j]; 
        --(counting_array[arr[j]]);           
    }

    for (i = 0; i < size; ++i)
    {
       arr[i] = output_array[i];       
    }

    free(output_array);
    
    return (SUCCESS);       
}

int RadixSort(int *arr, size_t size)
{
    int i  = 0; 
    int max = 0;

    assert(NULL != arr);
    assert(0 < size);

    max = GetMaxDigit(arr, size);

    for (i = 1; max / i > 0 ; i *= 10)
    {
        if (-1 == CountingRadix(arr, size, i))
        {
            return (FAIL);
        }
    }

    return (SUCCESS);
}


int IterBinarySort(int *arr, int find, size_t size)
{
    int index  = 0;
    int start = 0; 
    int end = 0;
 
    assert(NULL != arr);
    assert(0 < size);

    end = size;

    while (start <= find)
    {
        index = start + (end - start)/2;

        if (arr[index] == find)
        {
            return (index); 
        }
        else if (arr[index] < find)
        {
            start = index +1;
        }
        else
        {
            end = index - 1; 
        }  
    }

    return (SUCCESS);
}

int RecBinarySort(int *arr, int find, size_t size)
{
    int index  = 0;
    int start = 0;
    int end = 0;
 
    assert(NULL != arr);
    assert(0 < size);

    end = size;
    index = start + (end - start)/2;

    if (arr[index] == find)
    {
        return (index); 
    }

    else if (index == end && arr[index] != find)
    {
        return (FAIL);
    }

    else if (index == 0 && arr[index] != find)
    {
        return (FAIL);
    }

    if (arr[index] < find)
    {
        ++(arr);
    }
    else
    {
       --(size); 
    } 

    return RecBinarySort(arr, find, size); 
}

/******************************static functions********************************/
static void Swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int GetMaxDigit(int* arr, size_t size)
{
    int max = 0;
    size_t i = 0;
    
    assert(NULL != arr);
    assert(0 < size);

    max = arr[0];

    for (i = 0; i < size - 1; ++i)
    {
        if (max < arr[i + 1])
        {
            max = arr[i + 1];
        }
    }

    return (max);
}

static int CountingRadix(int *arr, size_t size, int digit)
{
    int counting_array[RADIX_SIZE] = {0};
    int *output_array = NULL; 
    size_t i = 0;
    int j = 0;

    assert(NULL != arr);
    assert(0 < size);

    output_array = (int *)malloc(size * sizeof(int));
    if (NULL == output_array)
    {
        return (-1);
    }

    for (i = 0; i < size; ++i)
    {
        ++(counting_array[(arr[i] / digit) % 10]);       
    }

    for (i = 1; i < RADIX_SIZE; ++i)
    {
        counting_array[i] += counting_array[i - 1];       
    }

    for (j = size - 1 ; 0 <= j; --j)
    {
        output_array[counting_array[(arr[j] / digit) % 10] - 1] = arr[j]; 
        --(counting_array[(arr[j] / digit) % 10]);           
    }

    for (i = 0; i < size; ++i)
    {
       arr[i] = output_array[i];       
    }

    free(output_array);

    return (0);       
}


