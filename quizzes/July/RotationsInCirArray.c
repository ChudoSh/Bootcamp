#include <stdio.h>
#include <assert.h>

int FindElementInCircularlySortedArray(int *arr, size_t size);

int main(void)
{
    int arr[10] = {9, 13 ,15 ,16 ,18 ,1, 4, 6,7,8};

    printf("The numberof rotation is %d\n",FindElementInCircularlySortedArray(arr, 10));

    return (0);
}

int FindElementInCircularlySortedArray(int *arr, size_t size)
{
    int index  = 0;
    int start = 0;
    int end = 0;
 
    assert(NULL != arr);
    assert(0 < size);

    end = size;
    index = start + (end - start)/2;

    if (arr[index] > arr[index + 1])
    {
        return (index + 1); 
    }

    else if (arr[start] <= arr[index])
    {
        if (arr[start] <= arr[index])
        {
            --(index);
            return (FindElementInCircularlySortedArray(arr, index));
        }

        arr += (size_t)(index + 1);
        return (FindElementInCircularlySortedArray(arr, size));
    }

    else
    {
        arr += (size_t)(index + 1);
        return (FindElementInCircularlySortedArray(arr,  size));
    }

    --(index);
    return (FindElementInCircularlySortedArray(arr, index)); 
}