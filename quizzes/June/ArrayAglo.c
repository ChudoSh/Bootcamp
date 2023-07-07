#include <stdio.h>

int IsFound(char *arr, size_t arr_size, char find);
void Rotate(char *arr, size_t arr_size, int to_rotate);
void Reverse(char *arr, size_t arr_size);
void Swap(char *a, char *b);

int main(void)
{
    char arr1[5] = {'a','b','1','2','c'};
    char arr1_exp_res = 1;
    char arr1_res = 0;
    int i = 0; 

    arr1_res = IsFound(arr1, 5, 'x');
    printf("test 1 expected res:%d recived res:%d\n",arr1_exp_res,arr1_res);

    Rotate(arr1, 5, 3);

    for (i = 0; i < 5; ++i)
    {
        printf("%c\n", arr1[i]); 
    }

    return(0);
}

int IsFound(char *arr, size_t arr_size, char find)
{
    int LUT[256] = {0};

    while (arr_size > 0)
    {
        LUT[(int)*arr] = 1;
        ++(arr);
        --(arr_size);
    }
    
    return (LUT[(int)find]);
}

void Rotate(char *arr, size_t arr_size, int to_rotate)
{ 
    to_rotate %= arr_size;

	Reverse(arr, arr_size - to_rotate);
	Reverse(arr + arr_size - to_rotate, to_rotate);
	Reverse(arr, arr_size);

}

void Reverse(char *arr, size_t arr_size)
{ 
    size_t i = 0;
    size_t j = arr_size - 1; 

    while (i <= j)
    {
        Swap(&arr[i], &arr[j]);

        ++(i);
        --(j);
    }
}

void Swap(char *a, char *b)
{
    char tmp = *a; 
    *a = *b;
    *b = tmp;  
}
