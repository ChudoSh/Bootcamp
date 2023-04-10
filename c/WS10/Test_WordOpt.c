#include <assert.h> /*assert*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "WordOpt.h"


int main()
{
    char test1[100]= "aaaaaaaaaaaaaaaaaaaaaaa";
    char test2[100]= "aaaaaaaaaaaaaaaaaaaaaaa";
    /*if(SUCCESS == memcmp(Memset(test1 + 5,'5',16, memset(test2 + 5,'5',16), 16))
    {
        printf("Test 1 for Memset succeeded!!!\n");
    }
    else
    {  
         printf("Test 1 for Memset failed..\n");
    }
    
    if(SUCCESS == memcmp(Memset(test2,'P',8), memset(test2,'P',8), 10))
    {
        printf("Test 2 for Memset succeeded!!!\n");
    }
    else
    {  
         printf("Test 2 for Memset failed..\n");
    }
    */
    Memset(test1,'5',16);
   /*Memset(test1,'P',8);*/
    memset(test2,'5',16);
    /*memset(test2,'P',8);*/
    printf("%s\n",test1);
    printf("%s\n", test2);

    return 0;
}
