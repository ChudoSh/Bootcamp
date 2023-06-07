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

#include "calculator.h"

#define MALL_CHECK(memory) ((NULL == memory) ? return (MEMORY_ALLOC_ERR) : continue)

enum MACROS
{
    NUM_OF_STATES = 3,  
    CHAR_TABLE = 256 
};

enum BOOL
{
    FALSE = 0,  
    TRUE = 1 
};

typedef enum STATES_FLAG
{ 
    ERROR = 1,
    WAITING_FOR_NUM = 2,
    WAITING_FOR_OP = 3,
    EVALUATE = 4
}state_flag_t;

typedef enum PRECEDENCE
{ 
    INIT = -1,
    ADDITION = 1,
    SUBTRACTION = 1,
    MULITPLICATION = 2,
    DIVISION = 2,
    POWER = 3,
    OPEN_BRACETS = 4,
    CLOSE_BRACETS = 5

}precedence_t;

typedef struct ParsingStacks
{
    stack_t *num_stack;
    stack_t *op_stack;
    char last_parantheses;
}calc_con_t;

typedef state_flag_t (* transit_func)(calc_con_t * , double *, char *);
typedef calculator_status_t (* arithmetics_func)(double * , double *);

typedef struct State
{
    transit_func state;
    state_flag_t next_state;   
}state_t;

typedef struct ArithOperations
{
    arithmetics_func operation;
    precedence_t precedence;   
}arith_op_t;

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

static void InitStateLUT(state_t stateLUT[256][2]);
static void InitArithmeticLUT(arithmetics_func arithmeticLUT[256]);

static void ExecuteOperation(state_t *hanlder, calc_con_t *container, 
                             double *result, char *buffer);
static state_flag_t WaitingForNum(calc_con_t *container, double *result,
                                  char *buffer);
static state_flag_t WaitingForOp(calc_con_t *container, double *result,
                                 char *buffer);
static state_flag_t Evaluate(calc_con_t *container, double *result,
                             char *buffer);
static state_flag_t Error(calc_con_t *container,double *result,
                          char *buffer);


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
    char *buffer = NULL; 
    calculator_status_t current_status = SUCCESS;
    state_t stateLUT[256][2] = {NULL};

    assert(NULL != expression);

    InitStateLUT(stateLUT[][]);

    buffer = (char *)malloc(strlen(expression) + 1);
    MALL_CHECK(buffer);
    
    current_state = WAITING_FOR_NUM;
    handler = &(stateLUT[*(int *)expression][current_state]);
    ExecuteOperation(handler, container, result, buffer); 

    while (ERROR != current_state && '\0' != *buffer)/*assume for now parse returns the proper value*/
    {
        handler = &(stateLUT[*(int *)buffer][current_state]);
        ExecuteOperation(handler, container, result, &buffer);
    }

    return (current_status);
}

static state_flag_t WaitingForNum(calc_con_t *container, double *result,
                                         char **buffer)
{
    char *temp_buffer = NULL;

    assert(NULL != container);
    assert(NULL != result);

    temp_buffer = *buffer;
    
    StackPushBack(GetNumStack(container), (void *)strtod(temp_buffer, buffer));

    return (WAITING_FOR_OP);
}
static state_flag_t WaitingForOp(calc_con_t *container, double *result,
                                 char *buffer)
{    
    precedence_t i = 0;
    char j = '+';
    static precedence_t current_precedence = INIT;
    static arithmetics_func precedenceLUT[256][5]= {NULL};

    assert(NULL != container);
    assert(NULL != result);

    StackPushBack(GetOpsStack(container), *buffer);

    Evaluate(container, result);

    return (WAITING_FOR_NUM);
}

static state_flag_t Error(calc_con_t *container, double *result,
                          char *buffer)
{
    
}

static calculator_status_t Evaluate(calc_con_t *container, double *result)
{   
    char op = '\0';
    double *before = NULL;
    double *after = NULL;
    arithmetics_func handler = NULL;
    arithmetics_func arithmeticLUT[256] = {NULL};
    InitArithmeticLUT(arithmeticLUT[256]);

    after = StackPeek(GetNumStack(container));
    StackPop(GetNumStack(container));

    while('#' != (char *)StackPeek(GetOpsStack(container)))
    {
        op = StackPeek(GetOpsStack(container));
        stackPop(GetOpsStack(container));
        before = StackPeek(GetNumStack(container));
        StackPop(GetNumStack(container));

        handler = arithmeticLUT[op];

        handler(before, after);

        after = StackPeek(GetNumStack(container));
        StackPop(GetNumStack(container));
    }

    before = StackPeek(GetNumStack(container));
    handler = precedenceLUT[op];

    handler(before, after);

    StackPop(GetNumStack(container));

    return (SUCCESS);
}


static calc_con_t *CreateContainer(const char *expression)
{
    calc_con_t *container = NULL;
    char dummy_op = '#';
    double dummy_num = 0;

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

    StackPushBack(GetNumStack(container), &dummy_num);

    container->op_stack = StackCreate((strlen(expression) + 1) * sizeof(double), 
                                                                sizeof(double));
    if (NULL == container->op_stack)
    {   
        StackDestroy(container->num_stack);
        free(container); 
        return (NULL);
    }

    StackPushBack(GetOpStack(container), &dummy_op);

    container->last_parantheses = '\0';

    return (container);
}

static void DestroyContainer(calc_con_t *container)
{
    StackDestroy(GetNumStack(container));
    StackDestroy(GetOpStack(container));
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

static void ExecuteOperation(state_t *handler, calc_con_t *container, 
                             double *result, char *buffer)
{
    assert(NULL != hanlder);
    assert(NULL != container);
    assert(NULL != result);

    handler->next_state = hanlder->state(handler, container, result, buffer);
    current_state = handler->next_state;
}

static void InitStateLUT(state_t stateLUT[256][2])
{
    int i = 0; 
    char init[21] = {'0', '1', '2', '3', '4', '5', '6','7','8','9','+','-'
                      '*','/','^','(','[','{',')',']','}'};
    static int flag = FALSE;
    state_t wfn.state = WaitingForNum;
    state_t wfn.next_state = WAITING_FOR_OP;
    state_t wfo.state = WaitingForOp;
    state_t wfo.next_state = WAITING_FOR_NUM;
    state_t err.state = Error;
    state_t err.next_state = ERROR;

    if (!flag)
    {
        for (i = 0; i < 21; ++i)
        {
            if (i < 10 || init[i] == '(' || init[i] == '{' || init[i] == '[' )
            {
                stateLUT[init[i]][WAITING_FOR_NUM].state = WaitingForNum;
                stateLUT[init[i]][WAITING_FOR_NUM].next_state = WAITING_FOR_OP;
            }

            stateLUT[init[i]][WAITING_FOR_NUM].state = Error;
            stateLUT[init[i]][WAITING_FOR_NUM].next_state = ERROR;
        }
      
/******************************************************************************/
        for (i = 0; i < 21; ++i)
        {
            if ((i >= 10 && i <= 15) || init[i] == ')' 
                || init[i] == ']' || init[i] == '}' )
            {
                stateLUT[init[i]][WAITING_FOR_NUM].state = WaitingForOp;
                stateLUT[init[i]][WAITING_FOR_NUM].next_state = WAITING_FOR_NUM;
            }

            stateLUT[init[i]][WAITING_FOR_OP].state = Error;
            stateLUT[init[i]][WAITING_FOR_OP].next_state = ERROR;
        }

        stateLUT['#'][WAITING_FOR_NUM] = err;
        stateLUT['#'][WAITING_FOR_OP] = finish;/*a function that colapses the calculator*/

        flag = TRUE;
    }
}

static void InitArithmeticOpsLUT(arith_op_t arith_opsLUT[256])
{
    int flag = FALSE; 

    if (!flag)
    {
        arithmeticLUT['+'].operation = Addition;
        arithmeticLUT['+'].precedence = ADDITION;
        arithmeticLUT['-'].operation = Subtraction;
        arithmeticLUT['-'].precedence = SUBTRACTION;
        /*precedenceLUT['-'] = Subtraction;
        precedenceLUT['*'][ADDITION] = Multiplication;
        precedenceLUT['*'][SUBTRACTION] = Multiplication;
        precedenceLUT['*'][MULITPLICATION] = Multiplication; 
        precedenceLUT['/'][ADDITION] = Multiplication;
        precedenceLUT['/'][SUBTRACTION] = Multiplication;
        precedenceLUT['/'][MULITPLICATION] = Multiplication; 
        precedenceLUT['/'][DIVISION] = Division;
        precedenceLUT['^'][ADDITION] = Multiplication;
        precedenceLUT['^'][SUBTRACTION] = Multiplication;
        precedenceLUT['^'][MULITPLICATION] = Multiplication; 
        precedenceLUT['^'][DIVISION] = Division;
        precedenceLUT['^'][POWER] = Power;*/

        flag = TRUE;
    }
}

static void InitPrecedenceLUT(precedence_t precedenceLUT[256])
{
    precedenceLUT['+'] = ADDITION;
    precedenceLUT['-'] = SUBTRACTION;
    /*precedenceLUT['-'] = Subtraction;
    precedenceLUT['*'][ADDITION] = Multiplication;
    precedenceLUT['*'][SUBTRACTION] = Multiplication;
    precedenceLUT['*'][MULITPLICATION] = Multiplication; 
    precedenceLUT['/'][ADDITION] = Multiplication;
    precedenceLUT['/'][SUBTRACTION] = Multiplication;
    precedenceLUT['/'][MULITPLICATION] = Multiplication; 
    precedenceLUT['/'][DIVISION] = Division;
    precedenceLUT['^'][ADDITION] = Multiplication;
    precedenceLUT['^'][SUBTRACTION] = Multiplication;
    precedenceLUT['^'][MULITPLICATION] = Multiplication; 
    precedenceLUT['^'][DIVISION] = Division;
    precedenceLUT['^'][POWER] = Power;*/
}

static void ComparePrecendence(calc_con_t *container, char op)
{
    assert(NULL != container);

    return (StackPeek(GetOpStack(container)) - op);
}




