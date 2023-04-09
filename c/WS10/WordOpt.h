#ifndef __WORDOPT_H__
#define __WORDOPT_H__

#define ALIGN sizeof(size_t)



typedef enum RESULT
{
    FAIL = -1,
    SUCCESS = 0, 
    ALIGNED    
}RESULT;

void *Memset(void *str, int c, size_t n);


#endif
