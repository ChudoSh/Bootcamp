#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

enum BOOL
{
    FALSE, 
    TRUE
};

void SortOnesnZeroes(int *arr, size_t size);

int main(void)
{
    int i = 0;
    int arr[10] = {1,0,0,1,0,1,0,0,1,0};


    for (i = 0; i < 10; ++i)
    {
        printf("%d",arr[i]);
    }

    printf("\n");


    SortOnesnZeroes(arr, 10);

    for (i = 0; i < 10; ++i)
    {
        printf("%d",arr[i]);
    }

    printf("\n");

    return (0);
}

void SortOnesnZeroes(int *arr, size_t size)
{   
    int *ones = NULL;
    int *zeroes = NULL;
    
    assert(NULL != arr);

    ones = arr + size - 1; 
    zeroes = arr;

    while (zeroes <= ones)
    {
        if (TRUE == *zeroes && FALSE == *ones)
        {
            *zeroes = FALSE;
            *ones = TRUE;  
        }

        else if (TRUE == *ones)
        {
            --(ones);
        }

        ++(zeroes);
    }
}


