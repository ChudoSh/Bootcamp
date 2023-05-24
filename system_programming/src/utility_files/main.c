#include <stdio.h>

#include "globalvar"

void foo2()
{    
    PrintGlobalVariableAddress();
    foo();
}
