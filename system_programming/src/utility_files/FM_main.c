#include <stdio.h>
#include <stdlib.h> 

#include "mapping.h"

int main(int argc, char *argv[], char *envp[])
{
    char** p_command_line_arguments = argv;
    char** p_environment_variables = envp;
    char *str = "FullMemory";
	int i = 0;
    i = AddOne(10);
    SuperMalloc();
    Funky();
    return 0;
}

