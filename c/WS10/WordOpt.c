#include <assert.h> /*assert*/
#include <stddef.h>/*size*/
#include <stdio.h>

#include "WordOpt.h"

static void CopyByChar(unsigned char* str, int c, size_t *n)
{
    assert(NULL != str);
    
    *str = (unsigned char)c;
    --*n;       
}

static void CopyByWords(unsigned char* str, unsigned char *buffer, size_t *n)
{
    assert(NULL != str || NULL != buffer); 
     
   *(size_t*)str = *(size_t*)buffer;
    *n = *n - ALIGN;  
}

static RESULT IsAligned(void *p)
{    
    assert(NULL != p);
    
    if(0 == ((size_t)p & (ALIGN - 1)))
    {
        return ALIGNED;
    }
    return FAIL;   
}


void *Memset(void *str, int c, size_t n)
{
     assert(NULL != str);
     
     Memcpy(str, (void*)&c, n);
     
     return str;
}  
   
    
void *Memcpy(void *dest, void *src, size_t n)
{
    size_t i = 0;
    unsigned char *tempdest = NULL;
    unsigned char buffer[ALIGN] = {0};  
    
    assert(NULL != dest || NULL != src);
           
    tempdest = dest;
    
    for(i = 0; i < ALIGN; ++i)
    {
        buffer[i] = *((unsigned char*)src);       
    }
    
   
    while(0 < n)
    {   
        switch(IsAligned(dest))
        {
            case(ALIGNED):
                CopyByWords(tempdest, buffer,   &n);
                tempdest += ALIGN;              
                break;
            
            default:  
                CopyByChar(tempdest, *((int*)src), &n);
                ++tempdest;             
                break;
        }
       
    }
    return dest;
}





