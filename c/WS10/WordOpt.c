#include <assert.h> /*assert*/
#include "WordOpt.h"

void *Memset(void *str, int c, size_t n)
{
    size_t i = 0;
    void *start = NULL;
    char *buffer = NULL;  
    
    assert(NULL != str);
    
    IsAligned(str, 
    
    if(sizeof(*str) < sizeof(n))
    {
        return FAIL;
    }
    
    start = str;
    
    for(i = 0; i < n; ++i)
    {
        str[i] = (char)c; 
    }
 
    
    return start;
 
}
