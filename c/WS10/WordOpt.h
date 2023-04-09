#ifndef __WORDOPT_H__
#define __WORDOPT_H__

#define ALIGN 8


typedef enum RESULT
{
    FAIL = -1,
    SUCCESS = 0, 
    ALIGNED, 
    UNALIGN     
}RESULT;

void *Memset(void *str, int c, size_t n);



#endif
