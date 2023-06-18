/*
Dev: BarSH
Rev: EylonE
Date: 30.5.23
Status: Comparison list - Approved
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
Description: Conducts an iterative binary sort. 
Arghuments:
    - arr : A valid pointer to an int array.
    - find : A valid pointer to an int array. 
    - size : The size of the array. value to find
Return: 
    The position, if failed returns Fail. 
Time Complexity: O(log(n))
Space compelxity : O(1)
*/
int IterBinarySort(int *arr, int find, size_t size);


/***********************************************************************/
/*
Description: Conducts an iterative binary sort. 
Arghuments:
    - arr : A valid pointer to an int array.
    - find : A valid pointer to an int array. 
    - size : The size of the array. value to find
Return: 
    The position, if failed returns Fail. 
Time Complexity: O(log(n))
Space compelxity : O(1)
*/
int RecBinarySort(int *arr, int find, size_t size);


#endif /*__SORT_H__*/