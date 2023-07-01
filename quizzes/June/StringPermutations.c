#include <stdio.h>
#include <assert.h>
#include <string.h>

void StringPermutations(char *str, size_t start, size_t end);
void Swap(char *x, char *y);

int main(void)
{
    char str[] = "ABC";
    StringPermutations(str, 0, 3);
    return (0);
}

void StringPermutations(char *str, size_t start, size_t end)
{   
    size_t i = 0;
    assert(NULL != str);

    if (start == end)
    {
        printf("%s\n",str);
        return;
    }
    
    for (i = start; i < end; ++i)
    {   
        Swap((str + start), (str + i)); 
        StringPermutations(str, start + 1, end);
        Swap((str + start), (str + i));  
    }

    return;
}
void Swap(char* x, char* y)
{
    char temp = *x;
    *x = *y;
    *y = temp;
}