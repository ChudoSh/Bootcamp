#include <stdio.h>
#include <string.h>

int IsRotation(char *str1, char *str2)
{	
    size_t count = 0;	
    char *p1 = NULL;
    char *p2 = NULL;
    
	if(NULL == str1 || NULL == str2 || strlen(str1) != strlen(str2))
	{
		return -1; 	
	}
    
    p1 = str1 + strlen(str1) - 1;
    p2 = str2;
    
    while('\0' == *p2)
    {
        if(*p2 == *p1)
        {
            ++p1;
            ++p2;
            ++count;              
        }

        if(str1 > p1)
        {   
           return -1;
        }  
    }
 
	return (count == strlen(p1) - 1) ? 0 : -1;
	
}


int main()
{
    
    if(IsRotation("12123","12312") == 0)
    {
        printf("Good Job!\n");
    }
    else
    {
        printf("noob..\n");
    }
    

    return 0; 
}

