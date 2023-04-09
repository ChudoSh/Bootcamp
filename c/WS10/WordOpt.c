#include <assert.h> /*assert*/
#include <stddef.h>/*size*/
#include <stdio.h>

#include "WordOpt.h"

static RESULT IsAligned(void *p)
{    
    assert(NULL != p);
    
    if(SUCCESS == ((size_t)p & (ALIGN - 1)))
    {
        return ALIGNED;
    }
    
    return FAIL;   
}


void *Memset(void *str, int c, size_t n)
{
    size_t i = 0;
    unsigned char *temp = NULL;
    char buffer[ALIGN] = {0};  
    
    assert(NULL != str);
  
    if(sizeof(str) <= n)/*check again if its an error*/
    {
        perror("Given n bigger than the size of the string");
    }
    
    for(i = 0; i < ALIGN; ++i)
    {
        buffer[i] = (unsigned char)(c);
    }
    
    temp = str;
    i = 0; 
    
    while(n)
    {   
        if(ALIGNED == IsAligned(str))
        {  
            *temp = (size_t)buffer;
            n -= ALIGN;
            *temp  += ALIGN;
        }
        
        else if(FAIL == IsAligned(str))
        {       
            *temp = (unsigned char)c;
            --n;
            ++temp;
        } 
    }
    
    return str;
}
