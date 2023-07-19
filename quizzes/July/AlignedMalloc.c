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
    void* p1 = NULL; /*original block*/
    void** p2 = NULL; /*aligned block*/

    assert(0 < alignment);

    int offset = alignment - 1 + sizeof(void*);
    
    if ((p1 = (void*)malloc(required_bytes + offset)) == NULL)
    {
       return (NULL);
    }
    
    p2 = (void**)(((size_t)(p1) + offset) & ~(alignment - 1));
    p2[-1] = p1;
    return p2;
}

void AlignedFree(void *p)
{
    free(((void**)p)[-1]);
}