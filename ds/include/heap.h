/*
Dev: BarSH
Rev: 
Date: .6.23
Status: 
*/

#ifndef __HEAP_H__
#define __HEAP_H__

#include "dvector.h"

typedef struct HEAP heap_t;

/*
Name: HeapCreate
Description: Creates a new, empty heap.
Arguments: A compare function, which should return a negative integer if the first argument is less than the second,
           0 if they are equal, and a positive integer if the first argument is greater than the second.
Return: A pointer to the newly created heap.
Time complexity: O(1)
Space complexity: O(1)
*/
heap_t *HeapCreate(int (*compare)(const void*, const void*));

/*
Name: HeapDestroy
Description: Frees all memory associated with the heap.
Arguments: A valid pointer to the heap.
Return: None.
Time complexity: O(1)
Space complexity: O(1)
*/
void HeapDestroy(heap_t *heap);

/*
Name: HeapPush
Description: Inserts a new element into the heap, maintaining the heap property.
Arguments: A valid pointer to the heap, a pointer to the element to be inserted.
Return: 0 if successful, a negative integer if an error occurred.
Time complexity: O(log n), where n is the number of elements in the heap.
Space complexity: O(1)
*/
int HeapPush(heap_t *heap, const void *data);

/*
Name: HeapPop
Description: Removes the top element from the heap, maintaining the heap property.
Arguments: A valid pointer to the heap.
Return: 
Time complexity: O(log n), where n is the number of elements in the heap.
Space complexity: O(1)
*/
void HeapPop(heap_t *heap);

/*
Name: HeapPeek
Description: Returns a pointer to the top element in the heap, without removing it.
Arguments: A valid pointer to the heap.
Return: A pointer to the top element, or NULL if the heap is empty.
Time complexity: O(1)
Space complexity: O(1)
*/
void *HeapPeek(const heap_t *heap);

/*
Name: HeapSize
Description: Returns the number of elements in the heap.
Arguments: A valid pointer to the heap.
Return: The number of elements in the heap.
Time complexity: O(1)
Space complexity: O(1)
*/
size_t HeapSize(const heap_t *heap);

/*
Name: HeapIsEmpty
Description: Checks if the heap is empty.
Arguments: A pointer to the heap.
Return: An integer. Returns 1 if the heap is empty, and 0 otherwise.
Time complexity: O(1)
Space complexity: O(1)
*/
int HeapIsEmpty(const heap_t *heap);

/*
Name: HeapRemove
Description: Removes a specific element from the heap, maintaining the heap property. 
Arguments: A pointer to the heap, a pointer to the data to be removed.
Return: None.
Time complexity: O(n), where n is the number of elements in the heap.
Space complexity: O(1)
*/
void *HeapRemove(heap_t *heap, void *data, int(*is_match)(const void *, const void *));

void HeapPrint(heap_t *heap);

void HeapSort(heap_t *heap, size_t index);

#endif /*__HEAP_H__*/

