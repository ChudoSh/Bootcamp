void *Memcpy(void *dest, void *src, size_t n);

#define WORD (sizeof(size_t))
#define IS_ALIGNED(p) ((size_t)p % WORD)

int main()
{
	return (0);
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
			*(size_t*)tempdest = *(size_t*)tempsrc;
			
			n -= WORD;
			tempdest += WORD;
			tempsrc += WORD; 
        }             
               
        else
        {  
            *(size_t*)tempdest = *(size_t*)tempsrc;
            
    		--(n); 
            ++(tempdest);
            ++(tempsrc);            
        }
    }
        
    while (0 < n)
    {
        CopyByChar(tempdest, *(int*)tempsrc, &n);
        ++(tempdest);
        ++(tempsrc); 
    }
    
    return (dest);
}

