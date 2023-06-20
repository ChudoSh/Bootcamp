/*
Dev: BarSH
Rev: YonathanZ
Date: 18.6.23
Status: Binary search, Merge & Quick Sort -
*/

#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h>/*size_t*/

/*Sorting algorithims*/

/***********************************************************************/
/*
Description: sorts and int array using a bubble sort. 
Arghuments:
    - arr : A valid pointer to an int array. 
    - size : The size of the array. 
Return: 
    Nothing. 
Time Complexity: O(n ^ 2)
Space compelxity : O(1)
*/
void BubbleSort(int *arr, size_t size);

/***********************************************************************/
/*
Description: sorts and int array using an insertion sort. 
Arghuments:
    - arr : A valid pointer to an int array. 
    - size : The size of the array. 
Return: 
    Nothing. 
Time Complexity: O(n ^ 2)
Space compelxity : O(1)
*/
void InsertionSort(int *arr, size_t size);

/***********************************************************************/
/*
Description: sorts and int array using a selection sort. 
Arghuments:
    - arr : A valid pointer to an int array. 
    - size : The size of the array. 
Return: 
    Nothing. 
Time Complexity: O(n ^ 2)
Space compelxity : O(1)
*/
void SelectionSort(int *arr, size_t size);

/***********************************************************************/
/*
Description: sorts and int array using a counting sort. 
Arghuments:
    - arr : A valid pointer to an int array. 
    - size : The size of the array. 
Return: 
    Nothing. 
Time Complexity: O(n ^ 2)
Space compelxity : O(1)
*/
int CountingSort(int *arr, size_t size);

/***********************************************************************/
/*
Description: sorts and int array using a Radix sort. 
Arghuments:
    - arr : A valid pointer to an int array. 
    - size : The size of the array. 
Return: 
    Nothing. 
Time Complexity: O(n ^ 2)
Space compelxity : O(1)
*/
int RadixSort(int *arr, size_t size);

/***********************************************************************/
/*
Description: Conducts an iterative binary search. 
Arghuments:
    - arr : A valid pointer to an int array.
    - find : A valid pointer to an int array. 
    - size : The size of the array. value to find
Return: 
    The position, if failed returns Fail. 
Time Complexity: O(log(n))
Space compelxity : O(1)
*/
int IterBinarySearch(int *arr, int find, size_t size);


/***********************************************************************/
/*
Description: Conducts a recursive binary search. 
Arghuments:
    - arr : A valid pointer to an int array.
    - find : A valid pointer to an int array. 
    - size : The size of the array. value to find
Return: 
    The position, if failed returns Fail. 
Time Complexity: O(log(n))
Space compelxity : O(1)
*/
int RecBinarySearch(int *arr, int find, size_t size);

/***********************************************************************/
/*
Description: Conducts a merge sort. 
Arghuments:
    - arr_to_sort : A valid pointer to an int array.
    - num_elements : The size of the array.
Return: 
    SUCCESS if successful, FAIL otherwise 
Time Complexity: O(log(n)) for all cases
Space compelxity : O(n)
*/
int MergeSort(int *arr_to_sort, size_t num_elements);

/***********************************************************************/
/*
Description: Conducts a quick sort. 
Arghuments:
    - base : A valid pointer to an array.
    - nmemb : The size of the array.
    - size : The size of an element in the array.
    - compare : A valid pointer to a compare fucntion.
Return: 
    Nothing.
Time Complexity: O(log(n)) for all cases
Space compelxity : O(n)
*/
void QuickSort(void *base, size_t nmemb, size_t size, 
               int (*compare)(const void *, const void *));


#endif /*__SORT_H__*/