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
#include <stdio.h> /*strlen*/

#include "calculator.h"

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
    WAITING_FOR_NUM = 1,
    WAITING_FOR_OP = 2,
    FINISH = 3,
    ERROR = 4
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

state_flag_t current_state = WAITING_FOR_NUM;

typedef struct ParsingStacks
{
    stack_t *num_stack;
    stack_t *op_stack;
    char last_parantheses;
}calc_con_t;

typedef state_flag_t (* transit_func)(calc_con_t * , char **);
typedef void (* arithmetics_func)(double * , double *);

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
stack_t *GetNumStack(calc_con_t *container);
stack_t *GetOpStack(calc_con_t *container);

static void Addition(double *dest, double *to_add);
static void Subtraction(double *dest, double *to_add);
static void Multiplication(double *dest, double *to_add);
static void Division(double *dest, double *to_add);
static void Power(double *dest, double *to_add);

static void InitStateLUT(state_t stateLUT[CHAR_TABLE][NUM_OF_STATES]);
static void InitArithmeticOpsLUT(arith_op_t *arith_opsLUT);
static int ComparePrecendence(precedence_t before, precedence_t after);

static void ExecuteOperation(state_t *hanlder, calc_con_t *container, char **buffer);
static state_flag_t WaitingForNum(calc_con_t *container, char **buffer);
static state_flag_t WaitingForOp(calc_con_t *container, char **buffer);
static calculator_status_t Evaluate(calc_con_t *container);
static state_flag_t Error(calc_con_t *container, char **buffer);
static calculator_status_t Finish(calc_con_t *container, double *result);
static state_flag_t DummyFunc(calc_con_t *container, char **buffer);


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
    state_t stateLUT[CHAR_TABLE][NUM_OF_STATES] = {NULL};

    assert(NULL != expression);

    InitStateLUT(stateLUT);

    buffer = (char *)malloc(strlen(expression) + 1);
    if (NULL == buffer)
    {
        return (MEMORY_ALLOC_ERR);
    }
    
    current_state = WAITING_FOR_NUM;
    buffer = (char *)expression;
    handler = &(stateLUT[(int)(*buffer)][current_state]);
    ExecuteOperation(handler, container, &buffer); 

    while (ERROR != current_state && '\0' != *buffer && FINISH != current_state)/*assume for now parse returns the proper value*/
    {
        handler = &(stateLUT[(int)(*buffer)][current_state]);
        ExecuteOperation(handler, container, &buffer);
    }

    return (Finish(container ,result));
}

static state_flag_t WaitingForNum(calc_con_t *container, char **buffer)
{
    char **temp_buffer = NULL;

    double num = 0; 

    assert(NULL != container);

    temp_buffer = buffer;
    num = strtod(*temp_buffer, buffer);
    
    StackPush(GetNumStack(container), &num);

    return (WAITING_FOR_OP);
}
static state_flag_t WaitingForOp(calc_con_t *container, char **buffer)
{    
    char **temp_buffer = NULL;

    assert(NULL != container);

    StackPush(GetOpStack(container), *buffer);

    strtod(*temp_buffer, buffer)

    Evaluate(container);

    return (WAITING_FOR_NUM);
}

static state_flag_t Error(calc_con_t *container, char **buffer)
{
    
    printf("in error");
    return (ERROR);
}

static calculator_status_t Finish(calc_con_t *container, double *result)
{   
    char op = '\0';
    double *num_before = NULL;
    double *num_after = NULL;
    double evaluation = 0; 
    precedence_t to_check = INIT;
    arith_op_t *handler = NULL;
    arith_op_t arith_opsLUT[CHAR_TABLE] = {NULL};

    InitArithmeticOpsLUT(arith_opsLUT);

    num_after = StackPeek(GetNumStack(container));
    StackPop(GetNumStack(container));

    op = *(int *)StackPeek(GetOpStack(container));
    StackPop(GetOpStack(container));

    handler = &arith_opsLUT[(int)op];
    to_check = 
        arith_opsLUT[*(int *)(StackPeek(GetNumStack(container)))].precedence;

    while('#' != op)
    {
        op = *(char *)StackPeek(GetOpStack(container));
        StackPop(GetOpStack(container));
        num_before = StackPeek(GetNumStack(container));
        StackPop(GetNumStack(container));

        handler = &arith_opsLUT[(int)op];

        handler->operation(num_before, num_after);
        evaluation = *num_before + *num_after;
        StackPush(GetNumStack(container), &evaluation);

        num_after = StackPeek(GetNumStack(container));
        StackPop(GetNumStack(container));
    }

    num_before = StackPeek(GetNumStack(container));
    handler = &arith_opsLUT[(int)op];

    handler->operation(num_before, num_after);
    evaluation = *num_before + *num_after;
    StackPush(GetNumStack(container), &evaluation);

    StackPop(GetNumStack(container));

    return (SUCCESS);
}

static calculator_status_t Evaluate(calc_con_t *container)
{   
    char op = '\0';
    double *num_before = NULL;
    double *num_after = NULL;
    double evaluation = 0; 
    precedence_t to_check = INIT;
    arith_op_t *handler = NULL;
    arith_op_t arith_opsLUT[CHAR_TABLE] = {NULL};


    InitArithmeticOpsLUT(arith_opsLUT);

    /*num_after = StackPeek(GetNumStack(container));
    StackPop(GetNumStack(container));*/

    op = *(char *)StackPeek(GetOpStack(container));

    handler = &arith_opsLUT[(int)op];

    while(0 <= ComparePrecendence(to_check, handler->precedence) && 
          2 <= StackSize(GetNumStack(container)))
    {
        StackPop(GetOpStack(container));
    to_check = 
        arith_opsLUT[*(int *)(StackPeek(GetOpStack(container)))].precedence;

        /*op = *(char *)StackPeek(GetOpStack(container));
        StackPop(GetOpStack(container));*/
        num_before = StackPeek(GetNumStack(container));
        StackPop(GetNumStack(container));

        handler = &arith_opsLUT[(int)op];

        handler->operation(num_before, num_after);
        evaluation = *num_before + *num_after;
        StackPush(GetNumStack(container), &evaluation);

        num_after = StackPeek(GetNumStack(container));
        StackPop(GetNumStack(container));
    }

    /*num_before = StackPeek(GetNumStack(container));
    handler = &arith_opsLUT[(int)op];

    handler->operation(num_before, num_after);
    evaluation = *num_before + *num_after;
    StackPush(GetNumStack(container), &evaluation);

    StackPop(GetNumStack(container));*/

    return (SUCCESS);
}

static calc_con_t *CreateContainer(const char *expression)
{
    calc_con_t *container = NULL;
    char dummy_op = '#';
    double dummy_num = 0;

    assert(NULL != expression);
    assert(0 < strlen(expression));

    container = (calc_con_t *)malloc(sizeof(calc_con_t));
    if (NULL == container)
    {
        return (NULL);
    }

    container->num_stack = StackCreate(strlen(expression) + 1,  sizeof(double));
    if (NULL == container->num_stack)
    {
        free(container);
        return (NULL);
    }

    StackPush(GetNumStack(container), &dummy_num);

    container->op_stack = StackCreate((strlen(expression) + 1), sizeof(char));
    if (NULL == container->op_stack)
    {   
        StackDestroy(container->num_stack);
        free(container); 
        return (NULL);
    }

    StackPush(GetOpStack(container), &dummy_op);

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

stack_t *GetOpStack(calc_con_t *container)
{
    return (container->op_stack);
}
static void Addition(double *dest, double *to_add)
{
    (*dest) + (*to_add);
}
static void Subtraction(double *dest, double *to_subtract)
{
    (*dest) - (*to_subtract);
}
static void Multiplication(double *dest, double *to_mulitply)
{
    (*dest) * (*to_mulitply);
}
static void Division(double *dest, double *to_divide)
{
    (*dest) / (*to_divide);
}
static void Power(double *dest, double *to_raise)
{
    (pow((*dest), (*to_raise)));
}

static void ExecuteOperation(state_t *handler, calc_con_t *container, 
                             char **buffer)
{
    assert(NULL != handler);
    assert(NULL != container);
    assert(NULL != buffer);

    handler->next_state = handler->state(container, buffer);
    current_state = handler->next_state;
}

static void InitStateLUT(state_t stateLUT[CHAR_TABLE][NUM_OF_STATES])
{
    /*int i = 0; 
    char init[21] = {'0', '1', '2', '3', '4', '5', '6','7','8','9','+','-',
                      '*','/','^','(','[','{',')',']','}'};*/
    static int flag = FALSE;

    if (!flag)
    {
    stateLUT['0'][WAITING_FOR_NUM].state = WaitingForNum;
    stateLUT['0'][WAITING_FOR_NUM].next_state = WAITING_FOR_OP;
    stateLUT['1'][WAITING_FOR_NUM].state = WaitingForNum;
    stateLUT['1'][WAITING_FOR_NUM].next_state = WAITING_FOR_OP;
    stateLUT['2'][WAITING_FOR_NUM].state = WaitingForNum;
    stateLUT['2'][WAITING_FOR_NUM].next_state = WAITING_FOR_OP;
    stateLUT['3'][WAITING_FOR_NUM].state = WaitingForNum;
    stateLUT['3'][WAITING_FOR_NUM].next_state = WAITING_FOR_OP;
    stateLUT['4'][WAITING_FOR_NUM].state = WaitingForNum;
    stateLUT['4'][WAITING_FOR_NUM].next_state = WAITING_FOR_OP;
    stateLUT['5'][WAITING_FOR_NUM].state = WaitingForNum;
    stateLUT['5'][WAITING_FOR_NUM].next_state = WAITING_FOR_OP;
    stateLUT['6'][WAITING_FOR_NUM].state = WaitingForNum;
    stateLUT['6'][WAITING_FOR_NUM].next_state = WAITING_FOR_OP;
    stateLUT['7'][WAITING_FOR_NUM].state = WaitingForNum;
    stateLUT['7'][WAITING_FOR_NUM].next_state = WAITING_FOR_OP;
    stateLUT['8'][WAITING_FOR_NUM].state = WaitingForNum;
    stateLUT['8'][WAITING_FOR_NUM].next_state = WAITING_FOR_OP; 
    stateLUT['9'][WAITING_FOR_NUM].state = WaitingForNum;
    stateLUT['9'][WAITING_FOR_NUM].next_state = WAITING_FOR_OP;
    stateLUT['+'][WAITING_FOR_NUM].next_state = ERROR;
    stateLUT['+'][WAITING_FOR_NUM].state = Error;
    stateLUT['-'][WAITING_FOR_NUM].next_state = ERROR;
    stateLUT['-'][WAITING_FOR_NUM].state = Error;
    stateLUT['*'][WAITING_FOR_NUM].next_state = ERROR;
    stateLUT['*'][WAITING_FOR_NUM].state = Error;
    stateLUT['/'][WAITING_FOR_NUM].next_state = ERROR; 
    stateLUT['/'][WAITING_FOR_NUM].state = Error;
    stateLUT['^'][WAITING_FOR_NUM].next_state = ERROR;
    stateLUT['^'][WAITING_FOR_NUM].state = Error;
    stateLUT['^'][WAITING_FOR_NUM].next_state = ERROR;
    stateLUT['('][WAITING_FOR_NUM].state = WaitingForNum;
    stateLUT['('][WAITING_FOR_NUM].next_state = WAITING_FOR_OP;
    stateLUT['['][WAITING_FOR_NUM].state = WaitingForNum;
    stateLUT['['][WAITING_FOR_NUM].next_state = WAITING_FOR_OP;
    stateLUT['{'][WAITING_FOR_NUM].state = WaitingForNum;
    stateLUT['{'][WAITING_FOR_NUM].next_state = WAITING_FOR_OP; 
    stateLUT[')'][WAITING_FOR_NUM].state = Error;
    stateLUT[')'][WAITING_FOR_NUM].next_state = ERROR;
    stateLUT[']'][WAITING_FOR_NUM].state = Error;
    stateLUT[']'][WAITING_FOR_NUM].next_state = ERROR;
    stateLUT['}'][WAITING_FOR_NUM].state = Error;
    stateLUT['}'][WAITING_FOR_NUM].next_state = ERROR;   

    stateLUT['0'][WAITING_FOR_OP].state = Error;
    stateLUT['0'][WAITING_FOR_OP].next_state = ERROR;
    stateLUT['1'][WAITING_FOR_OP].state = Error;
    stateLUT['1'][WAITING_FOR_OP].next_state = ERROR;
    stateLUT['2'][WAITING_FOR_OP].state = Error;
    stateLUT['2'][WAITING_FOR_OP].next_state = ERROR;
    stateLUT['3'][WAITING_FOR_OP].state = Error;
    stateLUT['3'][WAITING_FOR_OP].next_state = ERROR;
    stateLUT['4'][WAITING_FOR_OP].state = Error;
    stateLUT['4'][WAITING_FOR_OP].next_state = ERROR;
    stateLUT['5'][WAITING_FOR_OP].state = Error;
    stateLUT['5'][WAITING_FOR_OP].next_state = ERROR;
    stateLUT['6'][WAITING_FOR_OP].state = Error;
    stateLUT['6'][WAITING_FOR_OP].next_state = ERROR;
    stateLUT['7'][WAITING_FOR_OP].state = Error;
    stateLUT['7'][WAITING_FOR_OP].next_state = ERROR;
    stateLUT['8'][WAITING_FOR_OP].state = Error;
    stateLUT['8'][WAITING_FOR_OP].next_state = ERROR; 
    stateLUT['9'][WAITING_FOR_OP].state = Error;
    stateLUT['9'][WAITING_FOR_OP].next_state = ERROR;
    stateLUT['+'][WAITING_FOR_OP].next_state = WAITING_FOR_NUM;
    stateLUT['+'][WAITING_FOR_OP].state = WaitingForOp;
    stateLUT['-'][WAITING_FOR_OP].next_state = WAITING_FOR_NUM;
    stateLUT['-'][WAITING_FOR_OP].state = WaitingForOp;
    stateLUT['*'][WAITING_FOR_OP].next_state = WAITING_FOR_NUM;
    stateLUT['*'][WAITING_FOR_OP].state = WaitingForOp;
    stateLUT['/'][WAITING_FOR_OP].next_state = WAITING_FOR_NUM; 
    stateLUT['/'][WAITING_FOR_OP].state = WaitingForOp;
    stateLUT['^'][WAITING_FOR_OP].next_state = WAITING_FOR_NUM;
    stateLUT['^'][WAITING_FOR_OP].state = WaitingForOp;
    stateLUT['^'][WAITING_FOR_OP].next_state = ERROR;
    stateLUT['('][WAITING_FOR_OP].state = Error;
    stateLUT['('][WAITING_FOR_OP].next_state = ERROR;
    stateLUT['['][WAITING_FOR_OP].state = Error;
    stateLUT['['][WAITING_FOR_OP].next_state = ERROR;
    stateLUT['{'][WAITING_FOR_OP].state = Error;
    stateLUT['{'][WAITING_FOR_OP].next_state = ERROR; 
    stateLUT[')'][WAITING_FOR_OP].state = WaitingForOp;
    stateLUT[')'][WAITING_FOR_OP].next_state = WAITING_FOR_NUM;
    stateLUT[']'][WAITING_FOR_OP].state = WaitingForOp;
    stateLUT[']'][WAITING_FOR_OP].next_state = WAITING_FOR_NUM;
    stateLUT['}'][WAITING_FOR_OP].state = WaitingForOp;
    stateLUT['}'][WAITING_FOR_OP].next_state = WAITING_FOR_NUM; 
    
    stateLUT['#'][WAITING_FOR_NUM].state = DummyFunc;
    stateLUT['#'][WAITING_FOR_OP].next_state = FINISH;/*a function that colapses the calculator*/

    flag = TRUE;
    }
}

static void InitArithmeticOpsLUT(arith_op_t *arith_opsLUT)
{
    static int flag = FALSE; 

    if (!flag)
    {
        arith_opsLUT['+'].operation = Addition;
        arith_opsLUT['+'].precedence = ADDITION;
        arith_opsLUT['-'].operation = Subtraction;
        arith_opsLUT['-'].precedence = SUBTRACTION;
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
        
        arith_opsLUT['#'].operation = Addition;
        arith_opsLUT['#'].precedence = FINISH;

        flag = TRUE;
    }
}

static int ComparePrecendence(precedence_t before, precedence_t after)
{
    return (before - after);
}

static state_flag_t DummyFunc(calc_con_t *container, char **buffer)
{
    (void)(container);
    (void)(buffer);

    return (FINISH);
}




