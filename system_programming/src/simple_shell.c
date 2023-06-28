/*
Dev: BarSh
Rev:
Status:
Date: 28.6.23
*/

#include <assert.h>/*assert*/

#include "simple_shell.h"


enum STATUS
{
    FAIL = -1, 
    SUCCESS = 0
};

/*============================================================================*/
/*Creates a new process*/
int CreateProcess()
{
    pid_t child = 0;
    int wait_status = WNOHANG;
    char sys_call[10] = "start";
    char command[10] =  {'\0'};
    
    while (0 != strcmp(sys_call, "exit"))
    {
        printf("Curernt process:%d\n", getpid());
        printf("Enter a system call: fork or system; enter exit to stop.\n");
        scanf("%s", sys_call);

        if (0 == strcmp(sys_call, "system"))
        {
            scanf("%s", command);
            if (-1 == system(command))
            {
                return (FAIL);
            }
        }

        else if (0 == strcmp(sys_call, "fork"))
        {
            child = fork();
            if (0 != child)
            { 
                waitpid(child, &wait_status, WUNTRACED);
                printf("status terminated with the status: %d\n", wait_status);
            }
            else
            {
                /*printf("Enter path for the command:\n");
                scanf("%s", path);*/
                printf("Enter new command:\n");
                scanf("%s", command);

                execl("/bin/sh","sh","-c", command,(char*)NULL);
                exit(0);
            }
        }         
    }

    return (SUCCESS);
}