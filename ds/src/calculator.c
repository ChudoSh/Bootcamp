
/*
Dev: BarSH
Rev: OlegV
Status: Approved
Date: 24.6.23
*/
#include <assert.h>/*assert*/
#include <stdlib.h>/*malloc*/
#include <math.h> /*pow*/
#include <string.h> /*strlen*/
#include <stdio.h> /*strlen*/

#include "calculator.h"

#define UNUSED(X) (void)X

enum BOOL
{
    FALSE = 0,  
    TRUE = 1 
};

typedef enum STATES_FLAG
{ 
    WAITING_FOR_NUM, 
    WAITING_FOR_OP,
    NUM_OF_STATES = 2,
    FINISH,
    ERROR
}state_flag_t;

typedef enum OP_STATE
{ 
    OP_ADD,
    OP_COLLAPES,
    OP_PARENTH_CLOSE,
    NUM_OF_OP_STATES = 3
}op_state_t;

typedef double (*arith_func_t)(double *, double *);

typedef struct operator
{
	char operator;
    int assoc;
	arith_func_t operation;
    
}operator_t;

typedef struct ParsingStacks
{
    stack_t *num_stack;
    stack_t *op_stack;
}calc_con_t;

typedef calculator_status_t (* transit_func)(calc_con_t * ,void *);

/*=====Container==========*/
static calc_con_t *CreateContainer(const char *expression);
static void DestroyContainer(calc_con_t *container);
stack_t *GetNumStack(calc_con_t *container);
stack_t *GetOpStack(calc_con_t *container);

/*========Arithmetics======*/
static double Addition(double *dest, double *to_add);
static double Subtraction(double *dest, double *to_add);
static double Multiplication(double *dest, double *to_add);
static double Division(double *dest, double *to_add);
static double Power(double *dest, double *to_add);

/*========Parser========*/
typedef enum TYPE
{
    NUMBER = 0,
    ADD_OP,
    SUB_OP,
    MULTI_OP,
    DIV_OP,
    PARENTH,
    POW,
    NUM_OF_TYPES = 8,
    OP_ERROR = -1,
    END = 7
}type_t;

typedef type_t (* parser_t)(const char *, void *, char**);
type_t OpParse(const char *str, void *result, char** end);
type_t NumParse(const char *str, void *result, char** end);

/*========States======*/
static calculator_status_t NumberAdded(calc_con_t *container, void* num);
static calculator_status_t OpHandle(calc_con_t *container, void *op);
static calculator_status_t OpAdded(calc_con_t *container, void *op);
static calculator_status_t Errorhandle(calc_con_t *container, void *op);
static calculator_status_t OpCollapes(calc_con_t *container, void *op);
static calculator_status_t OpCollapesParenth(calc_con_t *container, void *op);
static calculator_status_t Calculate(calc_con_t *container, void *op);

/*=====Global LUTS======*/
int levels[7][6] = 
{   
    {OP_ADD, OP_ADD, OP_ADD, OP_ADD, OP_ADD},
    {OP_ADD, OP_ADD, OP_ADD, OP_ADD, OP_ADD},
    {OP_ADD, OP_ADD, OP_PARENTH_CLOSE, OP_PARENTH_CLOSE, OP_PARENTH_CLOSE},
    {OP_ADD, OP_ADD, OP_ADD, OP_COLLAPES, OP_COLLAPES,OP_COLLAPES},
    {OP_ADD, OP_ADD, OP_ADD, OP_ADD, OP_COLLAPES,OP_COLLAPES},
    {OP_ADD,OP_ADD,OP_ADD,OP_ADD,OP_COLLAPES},
    {OP_ADD,OP_ADD,OP_ADD,OP_ADD,OP_ADD}
};

transit_func op_handlers[NUM_OF_OP_STATES] = 
{
    OpAdded,
    OpCollapes,
    OpCollapesParenth
};

transit_func stack_operation_table[NUM_OF_STATES][NUM_OF_TYPES] = 
{
    {
        NumberAdded,
        Errorhandle,
        Errorhandle,
        Errorhandle,
        Errorhandle,
        OpHandle,
        Errorhandle,
        Errorhandle,
    },
    {
        Errorhandle,
        OpHandle,
        OpHandle,
        OpHandle,
        OpHandle,
        OpHandle,
        OpHandle,
        OpHandle
    }
};


state_flag_t transition_table[NUM_OF_STATES][NUM_OF_TYPES] = 
{
    {
        WAITING_FOR_OP,
        ERROR,
        ERROR,
        ERROR,
        ERROR,
        WAITING_FOR_NUM,
        ERROR,
        ERROR
    },
    {
        ERROR,
        WAITING_FOR_NUM,
        WAITING_FOR_NUM,
        WAITING_FOR_NUM,
        WAITING_FOR_NUM,
        WAITING_FOR_OP,
        WAITING_FOR_NUM,
        FINISH,
    }
};

static void InitLuts();

parser_t parsers[NUM_OF_STATES] = {NumParse, OpParse};
int symbols[256]= {0};
char parenth[256]= {0};
arith_func_t operations[256]= {0};
int associtation[256]= {0};
type_t op_lut[256] = {OP_ERROR};


/******************************************************************************/
calculator_status_t Calculator(const char *expression, double *result)
{
    char *str = NULL;
    char *runner = NULL;
    void *data = NULL;
    calc_con_t *container = NULL;
    state_flag_t state = WAITING_FOR_NUM;
    calculator_status_t status = SUCCESS;
    type_t type = 0;

    assert(NULL != expression);
    assert(NULL != result);
    
    *result = 0; 
    
    container = CreateContainer(expression);
    if(NULL == container)
    {
        return (MEMORY_ALLOC_ERR);
    }

    data = malloc(sizeof(double));
    if(NULL == data)
    {
        DestroyContainer(container);
        return (MEMORY_ALLOC_ERR);
    }

    InitLuts();

    runner = (char *)expression;

    while(state < NUM_OF_STATES && status == SUCCESS)
    {
        str = runner;
        type = parsers[state](str, data, &runner);
        status = stack_operation_table[state][type](container, data);
        state = transition_table[state][type];
    }

    if(status == SUCCESS)
    {
        *result = *(double *)StackPeek(GetNumStack(container));
    }

    free(data);
    DestroyContainer(container);

    return (status);
}

/**************************static functions************************************/
static calculator_status_t Calculate(calc_con_t *container, void *op)
{
    double val1 = 0;
    double val2 = 0;
	int symbol_prec1 = 0;
    int symbol_prec2 = 0; 
    operator_t *new_op = op; 

    symbol_prec1 = symbols[(int)new_op->operator] + new_op->assoc;
    symbol_prec2 = (int)symbols[(int)((operator_t *)StackPeek(GetOpStack(container)))->operator];

    while(levels[symbol_prec1][symbol_prec2])
    {
       
        val1 = *(double *)StackPeek(GetNumStack(container));
        StackPop(GetNumStack(container));
        val2 = *(double *)StackPeek(GetNumStack(container));
        StackPop(GetNumStack(container));

        if(((operator_t *)StackPeek(GetOpStack(container)))->operator == '/' && val1 == 0)
        {
            return (MATH_ERR);
        }

  
        val1 = ((operator_t *)StackPeek(GetOpStack(container)))->operation(&val2, &val1);
        
        StackPop(GetOpStack(container));
        StackPush(GetNumStack(container), &val1);

        symbol_prec2 = (int)symbols[(int)((operator_t *)StackPeek(GetOpStack(container)))->operator];
    }

    if('\0' == new_op->operator && '#' != ((operator_t *)StackPeek(GetOpStack(container)))->operator)
    {
        return (SYNTAX_ERR);
    }

    return (SUCCESS);
}

static calculator_status_t NumberAdded(calc_con_t *container, void *num)
{  
    StackPush(GetNumStack(container), num);

    return (SUCCESS);
}
static calculator_status_t OpHandle(calc_con_t *container, void *op)
{    
    calculator_status_t status = SUCCESS;
    int symbol_prec1 = 0;
    int symbol_prec2 = 0;
    operator_t oper;

    oper.operator = *(char *)op;
    oper.operation = operations[(int)*(char *)op];
    oper.assoc = associtation[(int)*(char *)op];

    symbol_prec1 = (int)symbols[(int)oper.operator];
    symbol_prec2 = (int)symbols[(int)(((operator_t *)StackPeek(GetOpStack(container)))->operator)];

	status = op_handlers[levels[symbol_prec1][symbol_prec2]](container, &oper);

    return (status);

}

static calculator_status_t OpAdded(calc_con_t *container, void *op)
{
    StackPush(GetOpStack(container), (operator_t *)op);

    return (SUCCESS);
}

static calculator_status_t OpCollapes(calc_con_t *container, void *op)
{
    operator_t *new_op = op; 
    
    if(SUCCESS != Calculate(container, new_op))
    {
        return (MATH_ERR);
    }
    
    StackPush(GetOpStack(container), op);

    return (SUCCESS);
}

static calculator_status_t OpCollapesParenth(calc_con_t *container, void *op)
{
    operator_t *new_op = op; 

    if(SUCCESS != Calculate(container, new_op))
    {
        return (MATH_ERR);
    }

    if(new_op->operator != 
       parenth[(int)((operator_t *)StackPeek(GetOpStack(container)))->operator])
    {
        return (SYNTAX_ERR);
    }

    StackPop(GetOpStack(container));

    return (SUCCESS);
}

static calculator_status_t Errorhandle( calc_con_t *container, void *op)
{
    return (SYNTAX_ERR);

    UNUSED(container);
    UNUSED(op);
}


static calc_con_t *CreateContainer(const char *expression)
{
    calc_con_t *container = NULL;
    operator_t oper;
    
    assert(NULL != expression);
    assert(0 < strlen(expression));

    container = (calc_con_t *)malloc(sizeof(calc_con_t));
    if (NULL == container)
    {
        return (NULL);
    }

    container->num_stack = StackCreate(strlen(expression),  sizeof(double));
    if (NULL == container->num_stack)
    {
        free(container);
        return (NULL);
    }

    container->op_stack = StackCreate((strlen(expression)), sizeof(operator_t));
    if (NULL == container->op_stack)
    {   
        StackDestroy(container->num_stack);
        free(container); 
        return (NULL);
    }

    oper.operator = '#';
    StackPush(GetOpStack(container), &oper);

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
static double Addition(double *dest, double *to_add)
{
    return ((*dest) + (*to_add));
}
static double Subtraction(double *dest, double *to_subtract)
{
    return ((*dest) - (*to_subtract));
}
static double Multiplication(double *dest, double *to_mulitply)
{
    return ((*dest) * (*to_mulitply));
}
static double Division(double *dest, double *to_divide)
{
    if(0 == to_divide)
    {
        return (MATH_ERR);
    }

    return ((*dest) / (*to_divide));
}

static double Power(double *dest, double *to_raise)
{
    size_t i = 0;
    double base = *dest;
    double power = *to_raise;
    double result = 0;

    if (power < 0)
    {
        base = 1/base;
        power = -power;
    }

    for (i = 0; i < power; ++i)
    {
        result += (base * power);
    }

    return (result);
}


type_t OpParse(const char *str, void *result, char** end)
{
    op_lut['+'] = ADD_OP;
    op_lut['-'] = SUB_OP;
    op_lut['*'] = MULTI_OP;
    op_lut['/'] = DIV_OP;
    op_lut['^'] = DIV_OP;
    op_lut['}'] = PARENTH;
    op_lut[']'] = PARENTH;
    op_lut[')'] = PARENTH;
    
    op_lut['\0'] = END;

    *(char *)result = *(char *)str;
    ++(*end);
    return (op_lut[(int)*str]);

    
}

type_t NumParse(const char *str, void *result, char** end)
{
    type_t type = NUMBER;
    *end = (char *)str;

    op_lut['('] = PARENTH;
    op_lut['['] = PARENTH;
    op_lut['{'] = PARENTH;

    assert(NULL != str);

    *(double *)result = strtod(str, end);

    if(*end == (char *)str)
    {
        *(char *)result =  *(char *)str;
        type = op_lut[(int)**end];
        ++(*end);
        return type;
    }

    return (NUMBER);
}

static void InitLuts()
{
    symbols['#'] = 0;

    symbols['('] = 1;
    symbols['['] = 1;
    symbols['{'] = 1;
    
    symbols[')'] = 2;
    symbols[']'] = 2;
    symbols['}'] = 2;

    symbols['\0'] = 3;
    symbols['+'] = 3;
    symbols['-'] = 3;

    symbols['*'] = 4;
    symbols['/'] = 4;

    symbols['^'] = 5;
    
    operations['+'] = Addition;
    operations['-'] = Subtraction;

    operations['*'] = Multiplication;
    operations['/'] = Division;
    
    operations['^'] = Power;

    associtation['^'] = 1;


    parenth['['] = ']';
    parenth['('] = ')';
    parenth['{'] = '}';

}








