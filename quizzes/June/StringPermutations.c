#include <stdio.h>
#include <assert.h>
#include <string.h>

void StringPermutationsIter(char *str);
void StringPermutationsRec(char *str, size_t size);
void Swap(char *x, char *y);

int main(void)
{
    
    StringPermutationsIter("ABC");
    return (0);
}

void StringPermutationsIter(char *str)
{   
    size_t i = 0;
    char *start_run = NULL; 
    char *end_run = NULL;
     
    assert(NULL != str);
   
    start_run = str;
    end_run += strlen(str);

    while ('\0' != *str)
    {
        if (start_run == end_run)
        {
            printf("%s",str);
        }

        Swap(end_run, start_run);

        while (start_run != end_run)
        {
            
            if (start_run == end_run)
            {
                printf("%s",str);
            }
            Swap(end_run, start_run);

            ++(start_run);
            --(end_run);
        }
        printf("\n");
        ++(str);
    }
}
void Swap(char* x, char* y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}