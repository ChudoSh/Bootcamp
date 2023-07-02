/*
Dev: BarSh
Rev:Ido I
Status: Approved
Date: 2.7.23
*/
#include <sys/types.h> /*pid*/
#include <unistd.h> /*POSIX*/
#include <stdio.h> /*printf*/
#include <stdlib.h>/*atoi*/

#define __USE_POSIX
#define __USE_POSIX199309
#include <signal.h>

static void Pong(int sig);

typedef struct sigaction sigact_t;
typedef union sigval sv_t;

int main(int argc, char *argv[])
{
    int pid = atoi(argv[1]);
    sigact_t sa = {NULL};
    size_t count = 20; 

    sa.sa_handler = Pong;
    sigaction(SIGUSR2, &sa, NULL);

    while (count)
    {
        sleep(1);
        kill(pid, SIGUSR1);
        pause();
        --(count);
    }
    
    return (0);
}

static void Pong(int signal)
{
    printf("Child served back to parent, Pong!\n"); 
    (void)signal; 
}
