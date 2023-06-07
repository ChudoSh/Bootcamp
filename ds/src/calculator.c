/*
Dev: BarSH
Rev: 
Status: 
Date: 
*/



#include <assert.h>/*assert*/
#include <stdlib.h>/*malloc*/
#include <math.h> /*pow*/
#include <string.h> /*strlen*/

#include "stack.h"
#include "parser.h"
#include "calculator.h"

#define MALL_CHECK(memory) ((NULL == memory) ? return (NULL) : continue)

enum MACROS
{
    NUM_OF_STATES = 3,  
    CHAR_TABLE = 256 
};

typedef enum STATES_FLAG
{ 
    ERROR,
    WAITING_FOR_NUM,
    WAITING_FOR_OP,
    EVALUATE
}state_flag_t;

typedef struct ParsingStacks
{
    stack_t *num_stack;
    stack_t *op_stack;
    char last_parantheses;
}calc_con_t;

static calculator_status_t InitCalculate(calc_con_t *container,
                                         const char *expression,
                                         double *result);
static calc_con_t *CreateContainer(const char *expression);
static void DestroyContainer(calc_con_t *container);
static void Addition(double *dest, double *to_add);
static void Subtraction(double *dest, double *to_add);
static void Multiplication(double *dest, double *to_add);
static void Division(double *dest, double *to_add);
static void Power(double *dest, double *to_add);

static calculator_status_t WaitingForNum(calc_con_t *container, char character
                                         double *result);
static calculator_status_t WaitingForOp(calc_con_t *container, char character
                                        double *result);
static calculator_status_t Evaluate(calc_con_t *container, char character
                                    double *result);
static calculator_status_t Error(calc_con_t *container, char character
                                 double *result);

typedef state_flag_t (* transit_func)(calc_con_t * , char );
typedef calculator_status_t (* arithmetics_func)(double * , double *);

typedef struct State
{
    transit_func handler;
    state_flag_t next_state;   
}state_t;

calculator_status_t Calculator(const char *expression, double *result)
{
    calc_con_t *container = NULL;
    calculator_status_t status = SUCCESS; 

    assert(NULL != expression);
    assert(NULL != result);
    
    container = CreateContainer((char *)expression);
    if (NULL == container)
    {
        return (MEMORY_ALLOC_ERR);
    }

    status = InitCalculate(container, expression, result);
    DestroyContainer(container);

    return (status);
}


/**************************static functions************************************/
static calculator_status_t InitCalculate(calc_con_t *container,
                                         const char *expression,
                                         double *result)
{   
    state_t *handler = NULL;
    state_flag_t current_state = WAITING_FOR_NUM;
    calculator_status_t current_status = SUCCESS;
    char character = '\0';

    assert(NULL != expression);

    character = Parse((char *)expression);
    handler = WaitingForNum(container, character);

    while (ERROR != current_state && '#' != character)/*assume for now parse returns the proper value*/
    {
        character = Parse((char *)expression);
        handler = stateLUT[character][current_state];
        current_state = handler->next_state;
        ++(expression);
    }
    
    current_status = handler(container, result);

    return (current_status);
}

static void InitStateLUT(state_t **stateLUT)
{
    size_t i = 0; 
    size_t j = 0;
    static int flag = 0;
    state_t wfn = {WaitingForNum, WAITING_FOR_OP};
    state_t wfo = {WaitingForOp, WAITING_FOR_NUM};
    state_t err = {Error, ERROR};
    state_t evaluate = {Evaluate, EVALUATE};/*?*/

    if (!flag)
    {
        stateLUT['0'][WAITING_FOR_NUM] = wfn;
        stateLUT['1'][WAITING_FOR_NUM] = wfn; 
        stateLUT['2'][WAITING_FOR_NUM] = wfn;
        stateLUT['3'][WAITING_FOR_NUM] = wfn;
        stateLUT['4'][WAITING_FOR_NUM] = wfn;
        stateLUT['5'][WAITING_FOR_NUM] = wfn;
        stateLUT['6'][WAITING_FOR_NUM] = wfn;
        stateLUT['7'][WAITING_FOR_NUM] = wfn;
        stateLUT['8'][WAITING_FOR_NUM] = wfn;
        stateLUT['9'][WAITING_FOR_NUM] = wfn; 
        stateLUT['+'][WAITING_FOR_NUM] = err;
        stateLUT['*'][WAITING_FOR_NUM] = err; 
        stateLUT['/'][WAITING_FOR_NUM] = err;
        stateLUT['^'][WAITING_FOR_NUM] = err;
        stateLUT['('][WAITING_FOR_NUM] = wfn;
        stateLUT['{'][WAITING_FOR_NUM] = wfn;
        stateLUT['['][WAITING_FOR_NUM] = wfn;
        stateLUT[')'][WAITING_FOR_NUM] = err;
        stateLUT['}'][WAITING_FOR_NUM] = err;
        stateLUT[']'][WAITING_FOR_NUM] = err;
        stateLUT['0'][WAITING_FOR_OP] = err;
        stateLUT['1'][WAITING_FOR_OP] = err; 
        stateLUT['2'][WAITING_FOR_OP] = err;
        stateLUT['3'][WAITING_FOR_OP] = err;
        stateLUT['4'][WAITING_FOR_OP] = err;
        stateLUT['5'][WAITING_FOR_OP] = err;
        stateLUT['6'][WAITING_FOR_OP] = err;
        stateLUT['7'][WAITING_FOR_OP] = err;
        stateLUT['8'][WAITING_FOR_OP] = err;
        stateLUT['9'][WAITING_FOR_OP] = err; 
        stateLUT['+'][WAITING_FOR_OP] = wfo;
        stateLUT['*'][WAITING_FOR_OP] = wfo; 
        stateLUT['/'][WAITING_FOR_OP] = wfo;
        stateLUT['^'][WAITING_FOR_OP] = wfo;
        stateLUT['('][WAITING_FOR_OP] = err;
        stateLUT['{'][WAITING_FOR_OP] = err;
        stateLUT['['][WAITING_FOR_OP] = err;
        stateLUT[')'][WAITING_FOR_OP] = wfo;
        stateLUT['}'][WAITING_FOR_OP] = wfo;
        stateLUT[']'][WAITING_FOR_OP] = wfo;
        stateLUT['#'][WAITING_FOR_NUM] = err;
        stateLUT['#'][WAITING_FOR_OP] = evaluate;
    }


}

static calculator_status_t WaitingForNum(calc_con_t *container, 
                                         precedence_t current_precedence
                                         double *result)
{
    assert(NULL != container);
    assert(NULL != result);

    


}
static calculator_status_t WaitingForOp(calc_con_t *container, 
                                        precedence_t current_precedence,
                                        double *result)
{
    assert()

}

static calculator_status_t Error(calc_con_t *container, char character
                                 double *result)
{
    
}

static calculator_status_t Evaluate(calc_con_t *container,
                                    double *result)
{

}


static calc_con_t *CreateContainer(const char *expression)
{
    calc_con_t *container = NULL;

    assert(NULL != expression);
    assert(0 < strlen(expr_size));

    container = (calc_con_t *)malloc(sizeof(calc_con_t));
    MALL_CHECK(container);

    container->num_stack = StackCreate(strlen(expression) + 1,  sizeof(char));
    if (NULL == container->num_stack)
    {
        free(container);
        return (NULL);
    }

    container->op_stack = StackCreate((strlen(expression) + 1) * sizeof(double), 
                                                                sizeof(double));
    if (NULL == container->op_stack)
    {   
        StackDestroy(container->num_stack);
        free(container); 
        return (NULL);
    }

    container->last_parantheses = '\0';

    return (container);
}

static void DestroyContainer(calc_con_t *container)
{
    StackDestroy(container->num_stack);
    StackDestroy(container->num_stack);
    free(container);
}

stack_t *GetNumStack(calc_con_t *container)
{
    return (container->num_stack);
}

stack_t *GetOpsStack(calc_con_t *container)
{
    return (container->op_stack);
}

static void Addition(double *dest, double *to_add)
{
    return ((*dest) + (*to_add));
}
static void Subtraction(double *dest, double *to_subtract)
{
    return ((*dest) - (*to_subtract));
}
static void Multiplication(double *dest, double *to_mulitply)
{
    return ((*dest) * (*to_mulitply));
}
static void Division(double *dest, double *to_divide)
{
    return ((*dest) / (*to_divide));
}
static void Power(double *dest, double *to_raise)
{
    return (pow((*dest), (*to_raise)));
}




