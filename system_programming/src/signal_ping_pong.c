#include "signal_ping_pong.h"

#include <string.h>

static void PingPong(int signal);

typedef struct sigaction sigact_t;
 
void TableTennis()
{
    pid_t child = 0;
    sigact_t sa = {NULL};
    sa.sa_handler = &PingPong;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
 
    child = fork();
    if (0 > child) 
    {
        perror("The fork outta here");
        exit(1);
    }

    if (0 != child) 
    {
        raise(SIGUSR1);  
    }
    else
    { 
        raise(SIGUSR2);
        exit(0);
    } 
}
 
static void PingPong(int signal)
{
    if (SIGUSR1 == signal)
    {
        printf("Parent serves to child, Ping!\n"); 
    }
    else if(SIGUSR2 == signal)
    {
        printf("Child serves back parent and scores, Pong!\n"); 
        printf("What a game!\n");
    }
}
