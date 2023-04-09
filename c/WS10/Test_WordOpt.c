#include <assert.h> /*assert*/
#include <stdlib.h>
#include <stdio.h>

#include "WordOpt.h"



static void  *UnAlign()
{    
    assert(NULL != p);
    
    if(0 == ((size_t)p & (ALIGN - 1)))
    {
        return 0;
    }
    
    return -1;   
}



static int IsAligned(void *p)
{    
    assert(NULL != p);
    
    if(0 == ((size_t)p & (ALIGN - 1)))
    {
        return 0;
    }
    
    return -1;   
}



int main()
{
    char *p = (char*)malloc(5 *sizeof(char));
    
    printf("If good alignment is 0, else -1 %d\n", IsAligned();
    
    free(p);
    
    return 0;
}
