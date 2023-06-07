/*
Dev: BarSH
Rev: 
Status: 
Date: 
*/

#include <assert.h>/*assert*/
#include <stdlib.h>/*strtod*/
#include <string.h>/*strcat*/

#include "parser.h"

int Parse(char *expression, char **buffer)
{
    double num = 0; 

    assert(NULL != str);
    assert(NULL != ops);
    assert(NULL != nums);

    num = strtod(expression, buffer);
}