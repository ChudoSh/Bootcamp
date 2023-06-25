/*
Dev: BarSH
Rev: ShlomiA
Date: 20.6.23
Status: Approved
*/

#include <assert.h>/*assert*/
#include <stdlib.h>/*malloc*/
#include <string.h>/*memcpy*/
#include <stdio.h>


#include "heap.h"
#include "dvector.h"

#define END_INDEX(heap) (HeapSize(heap) - 1)

enum STATUS
{   
    FAIL = -1, 
    SUCCESS = 0
};

enum HEAP_MAGIC_NUMS
{   
    ROOT_INDEX = 0,
    ONE_ELEM_IN_HEAP = 1, 
    INIT_CAP = 8
};

struct HEAP 
{
	int (*compare)(const void*, const void*);
    dvector_t *arr;         
};


static dvector_t *GetVector(const heap_t *heap);
static int HeapifyUp(heap_t *heap, size_t index);
static void HeapifyDown(heap_t *heap, size_t index);
static int GetCompared(const heap_t *heap, size_t to_check, size_t check_against);
static size_t GetRight(size_t index);
static size_t GetLeft(size_t index);
static size_t GetParent(size_t index);
static int Swap(heap_t *heap, size_t first, size_t second);
static void *GetData(const heap_t *heap, size_t index);

/*=================Main==============*/

/*Creates a heap*/
heap_t *HeapCreate(int (*compare)(const void*, const void*))
{
   heap_t *heap = NULL;

   assert(NULL != compare);

   heap = (heap_t *)malloc(sizeof(heap_t));
   if (NULL == heap)
   {
        return (NULL);
   }

   heap->arr = DVectorCreate(sizeof(void *),  INIT_CAP);
   if (NULL == heap->arr)
   {
        free(heap);
        return (NULL);
   }

   heap->compare = compare;

   return (heap);
}

/*Destroys the heap*/
void HeapDestroy(heap_t *heap)
{
    assert(NULL != heap);

    DVectorDestroy(GetVector(heap));

    free(heap);
}

/*Pushes a new data into the heap*/
int HeapPush(heap_t *heap, const void *data)
{ 
    assert(NULL != heap);

    if (HeapIsEmpty(heap))
    {
       return (DVectorPushBack(GetVector(heap), &data));
    }

    if (FAIL == DVectorPushBack(GetVector(heap), &data))
    {
        return (FAIL);
    }

    return (HeapifyUp(heap, END_INDEX(heap)));
}

/*Pops the heap*/
void HeapPop(heap_t *heap)
{
    assert(NULL != heap);
    assert(!HeapIsEmpty(heap));

    if (FAIL == Swap(heap, ROOT_INDEX, END_INDEX(heap)))
    {
        return; 
    }

    DVectorPopBack(GetVector(heap));

    if(ONE_ELEM_IN_HEAP < HeapSize(heap))
    {
        HeapifyDown(heap, ROOT_INDEX);;
    }
}

/*Shows the minimum value in the heap*/
void *HeapPeek(const heap_t *heap)
{
    assert(NULL != heap);

    return (*(void **)GetData(heap, ROOT_INDEX));
}

/*Gets the num of elements in heap*/
size_t HeapSize(const heap_t *heap)
{
    assert(NULL != heap);

    return (DVectorSize(GetVector(heap)));
}

/*Is the heap empty?*/
int HeapIsEmpty(const heap_t *heap)
{
    assert(NULL != heap);

    return (0 == HeapSize(heap));
}

void *HeapRemove(heap_t *heap, void *data, int(*is_match)(const void *, const void *))
{
    void *removed = NULL; 
    size_t index = 0;

    assert(NULL != heap);
    assert(NULL != is_match); 
   
    while (index < HeapSize(heap) && 
           !is_match(*((void **)GetData(heap ,index)), data))
    {
        ++(index);
    }

    if (index == HeapSize(heap))
    {
        return (NULL);
    }

    removed = *((void **)GetData(heap ,index));

    if (FAIL == Swap(heap, index, END_INDEX(heap)))
    {
        return (NULL);
    }

    DVectorPopBack(GetVector(heap));
    HeapifyDown(heap, index);

    return (removed);
}


/*========Static funcs=========*/
/*Crucial funcs*/
static int HeapifyUp(heap_t *heap, size_t index)
{     
    assert(NULL != heap);

    if (0 == index ||  SUCCESS != GetCompared(heap, index, GetParent(index)))
    {
        return (SUCCESS);
    }

    if (FAIL == Swap(heap, index, GetParent(index)))
    {
        return (FAIL);
    }
    
    return (HeapifyUp(heap, GetParent(index)));   
}

static void HeapifyDown(heap_t *heap, size_t index)
{
    size_t new_index = index;

    assert(NULL != heap);
   
    if (GetLeft(index) < HeapSize(heap) && 
        SUCCESS == GetCompared(heap, GetLeft(index), index))
    {
        index = GetLeft(index);
    }

    if (GetRight(index) < HeapSize(heap) && 
        SUCCESS ==  GetCompared(heap, GetRight(index), index))
    {
        index = GetRight(index);
    }
    
    if (new_index != index) 
    {
        if (FAIL == Swap(heap, new_index, index))
        {
            return;
        }
        
        HeapifyDown(heap ,new_index);
    }
}

static int Swap(heap_t *heap, size_t first, size_t second)
{
    size_t dummy = 0; 
    size_t *temp = &dummy;
    void *first_elem = NULL;
    void *second_elem = NULL;

    assert(NULL != heap);

    first_elem = GetData(heap, first);
    second_elem = GetData(heap, second);

    if (NULL == memcpy(temp, first_elem, sizeof(void *)))
    {
        return (FAIL);
    }
    if (NULL == memcpy(first_elem, second_elem, sizeof(void *)))
    {
        return (FAIL);
    }
    if (NULL == memcpy(second_elem, temp, sizeof(void *)))
    {
        return (FAIL);
    }
    
    return (SUCCESS);
}

/*Getters and setters*/
static dvector_t *GetVector(const heap_t *heap)
{
    assert(NULL != heap);

    return (heap->arr);
}

static void *GetData(const heap_t *heap, size_t index)
{
    return (DVectorGetAccessToElement(GetVector(heap), index));
}

static int GetCompared(const heap_t *heap, size_t to_check, size_t check_against)
{
    assert(NULL != heap);

    if (0 > heap->compare(*((void **)GetData(heap, to_check)), 
                          *((void **)GetData(heap,check_against))))
    {
        return (SUCCESS);
    }

    return (FAIL);
}

static size_t GetRight(size_t index)
{
    return (2 * index + 2); 
}

static size_t GetLeft(size_t index)
{
    return (2 * index + 1); 
}

static size_t GetParent(size_t index)
{
    return ((index - 1) / 2); 
}


void HeapPrint(heap_t *heap)
{
    size_t i = 0; 

    for (i = 0 ; i < HeapSize(heap); ++i)
    {
        printf("%d\n", **(int **)GetData(heap, i));
    } 
}

void HeapSort(heap_t *heap, size_t index)
{
    assert(NULL != heap);

    Swap(heap, ROOT_INDEX, index);
    
    HeapifyDown(heap, index);

    if(0 == index)
    {
        return;
    }
    
    HeapSort(heap, --(index));
}