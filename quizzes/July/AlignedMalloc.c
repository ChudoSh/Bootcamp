#include <stdio.h>
#include <stdlib.h>

void *AlignedMalloc(size_t required_bytes, size_t alignment);
void AlignedFree(void *p);

int main()
{
    int *banana = (int *)AlignedMalloc(500, 16);
    int i = 0; 

    return (0);   
}

void *AlignedMalloc(size_t required_bytes, size_t alignment)
{
    void *p1 = NULL; /*original block*/
    void **p2 = NULL; /*aligned block*/
    size_t offset = 0;

    assert(0 < alignment);

    offset = alignment - 1 + sizeof(void *);

    p1 = (void*)malloc(required_bytes + offset);
    if (NULL == p1)
    {
       return (NULL);
    }
    
    p2 = (void **)(((size_t)(p1) + offset) & ~(alignment - 1));
    p2[-1] = p1;
    return p2;
}

void AlignedFree(void *p)
{
    free(((void **)p)[-1]);
}

/* void *AlignedMalloc(size_t bytes, size_t alignment)
{
    void *p1 = NULL;
    void *p2 = NULL;
    size_t address = 0;

    assert(0 < bytes);
    assert(0 < alignment);

    p1 = (void *)malloc(bytes + alignment + sizeof(size_t));
    if (p1 == NULL)
    {
        return NULL;
    }

    address = (size_t)p1 + alignment + sizeof(size_t);

    p2 = (void *)(address - (address % alignment));

    *((size_t *)p2 - 1) = (size_t)p1;

    return p2;
} */
