/*
Dev: BarSh
Rev: AmitaiB
Status: Approved
Date: 13.4.23
*/

#include <assert.h>/*assert*/
#include <stdlib.h> /*exit*/ 
#include <stdio.h> /*printf*/
#include <string.h>/*memset*/


#include "WordOpt.h"


int main()
{
    char test1[100]= "aaaaaaaaaaaaaaaaaaaaaaa";
    char test2[100]= "aaaaaaaaaaaaaaaaaaaaaaa";
    char test5[100]= "ccccccccccccccccccccccc";
    char test6[100]= "ccccccccccccccccccccccc";
    char test[100]= "12345678910111213141516";
    
    printf("Both Memset and Memcpy use Memmove\n");
    
    if(SUCCESS == memcmp(Memset(test1,'5',10), memset(test2,'5',10), 10))
    {
        printf("Test 1 for Memset succeeded!!!\n");
    }
    else
    {  
         printf("Test 1 for Memset failed..\n");
    }
    if(SUCCESS == memcmp(Memset(test5 + 3,'P',8), memset(test6 + 3,'P',8), 3))
    {
        printf("Test 2 for Memset succeeded!!!\n");
    }
    else
    {  
         printf("Test 2 for Memset failed..\n");
    }
    
    if(SUCCESS == memcmp(Memcpy(test1,test, 16), memcpy(test2, test, 16), 16))
    {
        printf("Test for Memcpy succeeded!!!\n");
    }
    else
    {  
         printf("Test for Memcpy failed..\n");
    }
    
    if(SUCCESS == memcmp(Memmove(test5 + 7, test + 2, 10), memmove(test6 + 7,test + 2, 10), 10))
    {
        printf("Test for Memmove algorithm succeeded!!!\n");
    }
    else
    {  
         printf("Test for Memmove algorithm failed..\n");
    }
   
    return 0;
}
