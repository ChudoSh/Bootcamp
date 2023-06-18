#ifndef __PARSER_H__
#define __PARSER_H__

#include <stddef.h> /* size_t */

typedef enum RET_TYPE
{
    ERR,
    NUM,
    ADD_SUB,
    DIV_MULTI,
    OPEN_BRACKET,
    CLOSE_BRACKET,
    POW,
    END,
    NUM_OF_RETS
}ret_type_t;

void LutInit();
ret_type_t ParseWNum(const char *str, double *num, char **buffer);
ret_type_t ParseWOp(const char *str, double *num, char **buffer);

#endif /*__PARSE_H__*/
