#include <stdio.h>
#include <assert.h>

int FindElementInCircularlySortedArray(int *arr, int find, size_t arr_size);

int main(void)
{
    int arr[10] = {9, 13 ,15 ,16 ,18 ,1, 4, 6,7,8};

    printf("The number %d is at the index: %d\n",arr[5],FindElementInCircularlySortedArray(arr, 1, 10));

    return (0);
}

int FindElementInCircularlySortedArray(int *arr, int find, size_t size)
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

    else if (arr[start] <= arr[index])
    {
        if (arr[start] <= find && find <= arr[index])
        {
            --(index);
            return (FindElementInCircularlySortedArray(arr, find, index));
        }

        arr += (size_t)(index + 1);
        return (FindElementInCircularlySortedArray(arr, find, size));
    }

    else
    {
        arr += (size_t)(index + 1);
        return (FindElementInCircularlySortedArray(arr, find, size));
    }

    --(index);
    return (FindElementInCircularlySortedArray(arr, find, size)); 
}