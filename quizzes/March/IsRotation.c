#include <stdio.h>
#include <string.h>
#include <assert.h>

int IsRotation(char *str1, char *str2);

int main()
{
    char *x = "121534";
    char *y = "123412";
  
    
    if(IsRotation(x,y) == 0)
    {
        printf("Good Job!\n");
    }
    else
    {
        printf("noob..\n");
    }
    

    return 0; 
}

int IsRotation(char *str1, char *str2)
{	
	size_t count = 0;	
    char *p1 = NULL;
    char *p2 = NULL;
    
    assert(NULL != str1);
    assert(NULL != str2);
    
	if(strlen(str1) != strlen(str2))
	{
		return -1; 	
	}
    
    p1 = str1 + strlen(str1) - 1;
    p2 = str2;
    
    while('\0' != *p2)
    {
        if (*p2 == *p1)
        {
            ++p1;
            ++p2;             
        }
        
        else 
        {   
        	--p1;	
        }
        
        if ('\0' == *p1)
    	{
			p1 = str1;
			++count;
        } 
        
        if (2 == count)
        {   
        	return -1;
        }
    }  
    return 0;	
}


