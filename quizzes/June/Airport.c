#include <stdio.h>

int AirPort(int *arr, size_t arr_size);

int main(void)
{
    int arr1[5] = {123,456,789,123,456};
    int arr1_exp_res = 789;
    int arr1_res = 0;

    int arr2[23] = {1,2,3,4,5,6,7,8,9,10,11,12,12,10,9,8,7,6,5,4,3,2,1};
    int arr2_exp_res = 11;
    int arr2_res = 0;

    int arr3[5] = {123,789,789,123,456};
    int arr3_exp_res = 456;
    int arr3_res = 0;

    arr1_res = AirPort(arr1, 5);
    printf("test 1 expected res:%d recived res:%d\n",arr1_exp_res,arr1_res);

    arr2_res = AirPort(arr2, 23);
    printf("test 1 expected res:%d recived res:%d\n",arr2_exp_res,arr2_res);

    arr3_res = AirPort(arr3, 5);
    printf("test 1 expected res:%d recived res:%d\n",arr3_exp_res,arr3_res);


    return(0);
}

int AirPort(int *arr, size_t arr_size)
{
    int res = 0;

    while (arr_size > 0)
    {
        res ^= *arr;
        ++(arr);
        --(arr_size);
    }
    
    return (res);
}
