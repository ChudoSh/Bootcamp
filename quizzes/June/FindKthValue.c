#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "../ds/include/heap.h"

int Compare(const void *a, const void *b);
int FindMinKthValue(int *arr, int k, size_t size);;

int main(void)
{
    int arr[10] = {20,30,50,1,3,4,5,1234,33,21};

    printf("The %d smallest number is: \n", 3,FindMinKthValue(arr, 3, 10));

    return (0);
}

int FindMinKthValue(int *arr, int k, size_t size)
{   
    heap_t *heap = NULL;
    int result = 0; 
    
    assert(NULL != arr);
    assert(k < size);

    heap = HeapCreate(Compare);

    while (0 < size)
    {
        HeapPush(heap, *arr);
        
        --(size);
        ++(arr);
    }

    while (0 < k)
    {
        HeapPop(heap);
        --(k);
    }

    result = *(int *)HeapPeek(heap);

    HeapDestroy(heap);

    return (result);

}

int Compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
