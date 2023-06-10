


#include <assert.h>/*assert*/
#include <stdlib.h>/*malloc*/
#include <math.h> /*pow*/
#include <string.h> /*strlen*/

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
calculator_status_t current_calc_status = SUCCESS;

typedef state_flag_t (* transit_func)(calc_con_t * , char **);
typedef void (* arithmetics_func)(double * , double *);

typedef struct ParsingStacks
{
    stack_t *num_stack;
    stack_t *op_stack;
    char last_parantheses;
}calc_con_t;

typedef struct State
{
    transit_func transit_to;
    state_flag_t next_state;   
}state_t;

typedef struct ArithOperations
{
    arithmetics_func operation;
    precedence_t precedence;   
}arith_op_t;

state_t stateLUT[CHAR_TABLE][NUM_OF_STATES];
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
/*stateLUT['*'][WAITING_FOR_NUM].next_state = ERROR;
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
stateLUT['}'][WAITING_FOR_NUM].next_state = ERROR; */  
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
/*stateLUT['*'][WAITING_FOR_OP].next_state = WAITING_FOR_NUM;
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
stateLUT['}'][WAITING_FOR_OP].next_state = WAITING_FOR_NUM; */

/**************************************************************************/
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
/***************************************************************************/
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


static calculator_status_t InitCalculate(calc_con_t *container,
                                         const char *expression,
                                         double *result)
{   
    
}