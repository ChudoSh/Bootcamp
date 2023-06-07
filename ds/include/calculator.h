#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

#include "stack.h"

typedef enum STATUS
{
    SUCCESS, 
    MATH_ERR,
    SYNTAX_ERR,
    MEMORY_ALLOC_ERR
}calculator_status_t;

/*
struct ParsingStacks
{
    stack_t *NumStack;
    stack_t *OpStack;
    char last_parenthesis;
};
*/
calculator_status_t Calculator(const char *expression, double *result);

#endif /* __CALCULATOR_H__ */