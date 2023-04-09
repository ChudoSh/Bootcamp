#include <assert.h> /*assert*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "WordOpt.h"


int main()
{
    char test[10] = "BANANANANA";
    
    if(SUCCESS == memcmp(Memset(test,'5',2), memset(test,'5',2), 10))
    {
        printf("Test 1 for Memset succeeded!!!\n");
    }
    else
    {  
         printf("Test 1 for Memset failed..\n");
    }
    
    if(SUCCESS == memcmp(Memset(test,'A',10), memset(test,'A',10), 10))
    {
        printf("Test 2 for Memset succeeded!!!\n");
    }
    else
    {  
         printf("Test 2 for Memset failed..\n");
    }
 
   
    
    return 0;
}
