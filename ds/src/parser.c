#include <stdlib.h> /*strtod*/
#include <assert.h> /*assert*/

#include "parser.h"

#define ASCII_ELEM (256)
#define UNUSED(x) ((void)x)
/*
typedef enum RET_TYPE
{
    ERR,
    NUM,
    ADD_SUB,
    DIV_MULTI,
    OPEN_BRACKET,
    CLOSE_BRACKET,
    POW,
    NUM_OF_RETS
}ret_type_t;
*/

typedef enum BOOL
{
    FALSE, 
    TRUE
}bool_t;

ret_type_t returns[ASCII_ELEM] = {0};

ret_type_t ParseWNum(const char *str, double *num, char **buffer)
{
    assert(NULL != str);
    assert(NULL != num);
    assert(NULL != buffer);

    LutInit();
    *num = strtod(str, buffer);

    if(0 != *num || ((0 == *num) && ('0' == *str)))
    {
        return(NUM);
    }

     ++(*buffer);
    return (returns[(int)*str]);
}

ret_type_t ParseWOp(const char *str, double *num, char **buffer)
{
    assert(NULL != str);
    assert(NULL != num);
    assert(NULL != buffer);

    UNUSED(num);
    UNUSED(buffer);

    *buffer = (char *)str;
    *buffer = (char *)*buffer + 1;

    return (returns[(int)*str]);
}


void LutInit()
{
    size_t i = 0;
    static bool_t to_init = FALSE;

    assert(NULL != returns);

    if (!to_init)
    {
        returns['('] = OPEN_BRACKET;
        returns['['] = OPEN_BRACKET;
        returns['{'] = OPEN_BRACKET;

        returns[')'] = CLOSE_BRACKET;
        returns[']'] = CLOSE_BRACKET;
        returns['}'] = CLOSE_BRACKET;

        returns['0'] = NUM;
        returns['1'] = NUM;
        returns['2'] = NUM;
        returns['3'] = NUM;
        returns['4'] = NUM;
        returns['5'] = NUM;
        returns['6'] = NUM;
        returns['7'] = NUM;
        returns['8'] = NUM;
        returns['9'] = NUM;

        returns['\0'] = END;

        returns['+'] = ADD_SUB;
        returns['-'] = ADD_SUB;
        returns['*'] = DIV_MULTI;
        returns['/'] = DIV_MULTI;
        returns['^'] = POW;

        for(i = 0; i < ASCII_ELEM; ++i)
        {
            if(0 == returns[i])
            {
                returns[i] = ERR;
            }
        }

        to_init = TRUE;
    }
}
