#include <assert.h>/*assert*/
#include <stdlib.h> /*exit*/ 
#include <stdio.h> /*printf*/
#include <string.h>/*memset*/

#include "WordOpt.h"
static void InitBuffer(unsigned char* buffer, int c)
{
    int i = 0; 
    
    for(i = 0; i < WORD; ++i)
    {
        buffer[i] = (unsigned char)c; 
    }
}
static void CopyByChar(unsigned char* str, int c, size_t *n)
{ 
    assert(NULL != str);
    
    *str = (unsigned char)c;
    --*n;       
}

static void CopyByWords(unsigned char* str, unsigned char *buffer, size_t *n)
{
    assert(NULL != str);
    assert(NULL != buffer); 
     
    *(size_t*)str = *(size_t*)buffer;
    *n -= WORD;  
}


void *Memset(void *str, int c, size_t n)
{
    size_t i = 0; 
    unsigned char buffer[WORD];
    unsigned char* temp = NULL;
     
    assert(NULL != str);
    
    InitBuffer(buffer, c);
    
    temp = str;
    
    while (WORD < n)
    {
        if (SUCCESS == IS_ALIGNED(temp))
        {
            CopyByWords(temp, buffer, &n);
            temp += WORD; 
        }
                                    
        elses
        {  
            CopyByChar(temp, c, &n);
            ++temp;            
        }
    }
    
    while (0 < n)
    {
        CopyByChar(temp, c, &n);
        ++temp;
    }
        
    return str;
} 
   
    
void *Memcpy(void *dest, void *src, size_t n)
{
    unsigned char *tempdest = NULL;
    unsigned char *tempsrc = NULL;
    
    assert(NULL != dest);
    assert(NULL != src);
    
    tempdest = dest;
    tempsrc = src;
    
    while (WORD < n)
    {
        if (SUCCESS == IS_ALIGNED(dest))
        {
            CopyByWords(tempdest, tempsrc, &n);
            tempdest += WORD;
            tempsrc += WORD; 
        }             
               
        else
        {  
            CopyByChar(tempdest, *(int*)tempsrc, &n);
            ++tempdest;
            ++tempsrc;            
        }
    }
        
    while (0 < n)
    {
        CopyByChar(tempdest, *(int*)tempsrc, &n);
        ++tempdest;
        ++tempsrc; 
    }
    
    return dest;
}

void *Memmove(void *dest, void *src, size_t n)
{
    unsigned char *tempdest = NULL;    
    unsigned char *tempsrc = NULL;
    
    assert(NULL != dest);
    assert(NULL != src);
    
    tempdest = (unsigned char*)((size_t)dest + n);
    tempsrc = (unsigned char*)((size_t)src + n); 
    
    
    if (0 < ((size_t)dest - (size_t)src))
    { 
        while (WORD < n)
        {                      
            if (SUCCESS == IS_ALIGNED(tempdest))
            {
                tempdest -= WORD;
                tempsrc -= WORD; 
                CopyByWords(tempdest, tempsrc, &n);                                
            }             
                   
            else
            {  
                --tempdest;
                --tempsrc;   
                CopyByChar(tempdest, *(int*)tempsrc, &n);
                         
            }
        }
            
        while (0 < n)
        {
            --tempdest;
            --tempsrc; 
            CopyByChar(tempdest, *(int*)tempsrc, &n);
        }
        
        return dest;
    }
    
    return Memcpy(dest, src, n);
      
}




