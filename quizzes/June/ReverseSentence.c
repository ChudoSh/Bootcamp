#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>


void ReverseSentence(char *src);
void ReverseWord(char *dest, char *src);


int main(void)
{
    char str[] = "i am the sun and the earth";

    ReverseSentence(str);

    return (0);
}

void ReverseSentence(char *src)
{   
    char *runner = NULL;
    char *start = NULL;

    assert(NULL != src);

    runner = src;
    start = src; 

    while ('\0' != *runner)
    {
        if (' ' == *runner)
        {
            ReverseWord(start, runner - 1);
            start = runner + 1;
        }

        ++(runner);
    }

    ReverseWord(start, runner - 1);
    ReverseWord(src, runner - 1);

    printf("%s\n", src);
}

void ReverseWord(char *start, char *end)
{
    char temp = '\0';

    while (start < end) 
    {
        temp = *start;
        *start = *end;
        ++(start);
        *end = temp;
        --(end);
    }
}
