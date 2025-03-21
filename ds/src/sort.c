/*
Dev: BarSH
Rev: YonathanZ
Date: 18.6.23
Status: Binary search, Merge & Quick Sort -
*/

#include <assert.h>/*assert*/
#include <stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/

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
static void *Pivoter(void *base, size_t nmemb, size_t *div_point, size_t size,
           int (*compar)(const void *, const void *));
static void GenericSwap(void *data1, void *data2, size_t element_size);


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

int MergeSort(int *arr_to_sort, size_t num_elements)
{
    int *arr1 = NULL;
    int *arr2 = NULL;
    size_t num1 = num_elements / 2;
    size_t num2 = (num_elements / 2) + (num_elements % 2);
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    if (num_elements <= 1)
    {
        return (SUCCESS);
    }

    arr1 = malloc((num1 * sizeof(int)));
    if (NULL == arr1)
    {
        return (FAIL);
    }

    arr2 = malloc((num2 * sizeof(int)));
    if (NULL == arr2)
    {
        free(arr1);
        return (FAIL);
    }

    memcpy(arr1, arr_to_sort, sizeof(int) * num1);
    memcpy(arr2, arr_to_sort + num1, sizeof(int) * num2);

    MergeSort(arr1, num1);
    MergeSort(arr2, num2);

    i = 0;

    while((j < num1) && (i < num2))
	{
		if(arr2[i] >= arr1[j])
		{
			arr_to_sort[k] = arr1[j];
			++(j);
		}
		else if(arr2[i] <= arr1[j])
		{
			arr_to_sort[k] = arr2[i];
			++(i);
		}

        ++(k);
	}

    while(j < num1)
	{
		arr_to_sort[k] = arr1[j];
		++(k);
		++(j);
	}

	while(i < num2)
	{
		arr_to_sort[k] = arr2[i];
		++(k);
		++(i);
	}

    free(arr1);
    free(arr2);

    return (SUCCESS);

       
}

void QuickSort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
	char *pivot = 0;
	char *Begin = NULL;
	size_t div_point = 1;

	assert(NULL != base);
	assert(NULL != compar);

	pivot = (char *)base;
	Begin = (char *)base + size;

	if (1 >= nmemb)
	{
		return;
	}

	if (2 == nmemb)
	{
		if (compar(Begin, pivot) <= 0 )
		{
			GenericSwap(pivot, Begin, sizeof(int));
		}
        
		return;
	}

	Begin = Pivoter(base, nmemb, &div_point, size, compar);

	QuickSort((void *)base, div_point, size, compar);
	QuickSort((void *)(Begin + size), nmemb - div_point - 1, size, compar);
}

/*===========Searches==============*/
int IterBinarySearch(int *arr, int find, size_t size)
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
            start = index + 1;
        }
        else
        {
            end = index - 1; 
        }  
    }

    return (SUCCESS);
}

int RecBinarySearch(int *arr, int find, size_t size)
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

    else if ((index == end && arr[index] != find) || 
             (index == 0 && arr[index] != find))
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

    return (RecBinarySearch(arr, find, size)); 
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

static void *Pivoter(void *base, size_t nmemb, size_t *div_point, size_t size,
           int (*compar)(const void *, const void *))
{
    char *pivot = NULL;
	char *Begin = NULL;
	char *End = NULL;
    
	assert(NULL != base);
	assert(NULL != compar);

	*div_point = 1;

	pivot = (char *)base;
	Begin = (char *)base + size;
	End = (char *)base + size * (nmemb - 1);

    while (Begin != End)
	{
		if (compar(pivot, Begin) <= 0 )
		{
			GenericSwap(Begin, End, size);
			End -= size;
		}
		else
		{
			Begin += size;
			++(*div_point);
		}
	}

    if (compar(pivot, Begin) <= 0 )
	{
		Begin -= size;
		--(*div_point);
	}

	GenericSwap(pivot, Begin, size);

    return (Begin);
}


static void GenericSwap(void *data1, void *data2, size_t element_size)
{
    size_t i = 0;
    char temp;

    assert(NULL != data1);
    assert(NULL != data2);;

    for(i=0; i<element_size; ++i)
    {
        temp = *(((char *)data1)+ i);
        *(((char *)data1)+ i) = *(((char *)data2)+ i);
        *(((char *)data2)+ i) = temp;
    }
}
