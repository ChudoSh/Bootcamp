#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


/* EXE 1*/


void TF(int num)
{
    int i = 1; 

    if(0 >= num)
    {
        perror("Num smaller than 1");
        exit(0);
    } 
      
    for(i = 1; i <= num; ++i)
    {           
        if(!(i % 3) ||!(i % 5))
        {
            printf("%c%c\n",'T' * !(i % 3),'F' * !(i % 5));
        }
        else
        { 
        	printf("%d\n", num);
        }            
    }       
}

void ReverseString(char *str)
{
    char *runner = NULL;

    assert(NULL != str);
  
    runner = str;
      
    str = str + strlen(str);
    
    while('\0' != *runner)
    { 
        switch(isupper(*str))
        {
            case(0):
                printf("%c",*str);
                break;
            default:
                printf("%c",tolower(*str));
                break; 
        }
        --str;
        ++runner;
    } 
    
    switch(isupper(*str))
    {
        case(0):
            printf("%c",*str);
            break;
        default:
            printf("%c",tolower(*str));
            break; 
    }
    
    printf("\n");      
}


int main()
{
    char *str = "HeLLo WolRd";
    
    ReverseString(str);
    
    TF(35);
    
    return 0; 
}



/*void Main(int argc, charargv[]) Main Func doesnt retrun anything, Error 1 related to the return
{
    int num; 
    const int num2 = 6;
    const int num3; 

    printf("%d", num);Prints nothing, error
    scanf("%d", num); Receives an number input for num
    printf("10 divided by %d is %f", num, 100/num);num is int not float, will give a warning reagrding the escape


    char ch = 97; Turns to the related ASCII character

    num3 = num2 - 5; Error due to num2 is const
    printf("%f", num3); Warning due escape for float

    num = 4.7; Num will be 4
    (double)num = 4.7; cannot cast on the left hand-side, error

    num = 2 * num++; Unspecified behaviour


    return (0); void function but retruns int, error
}
*/

/*EXE 2*/

/* a. Returns A since 1 is still treated as int*/
/* b. Returns B since -1 is turned into unsigend int which is 255*/

