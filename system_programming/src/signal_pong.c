/*
Dev: BarSh
Rev: Ido I
Status: Approved
Date: 2.7.23
*/
#include <sys/types.h> /*pid*/
#include <unistd.h> /*POSIX*/
#include <stdio.h> /*printf*/
#include <stdlib.h>/*atoi*/
#define __USE_POSIX
#define __USE_POSIX199309
#include <signal.h> /*signal*/


typedef struct sigaction sigact_t;
static void Ping(int signo, siginfo_t *siginfop, void *context);

int main(int argc, char *argv[])
{ 
    sigact_t sa = {NULL};
    size_t count = 20; 

    sa.sa_sigaction = Ping;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);

    printf("PID:%d\n", getpid());/*is printf signal?*/

    while (count)
    {
        pause();
        --(count);
    }

    return (0);
}

static void Ping(int signo, siginfo_t *siginfop, void *context)
{
   if (siginfop != NULL)
   {
        printf("Parent served to it's child, Ping!\n");
        kill(siginfop->si_pid, SIGUSR2);
   } 

   (void)signo;
   (void)context;    
}

/* Exer 1,2
    char *arg[20] = {"./a.out", NULL};
    pid_t child = 0;
    sigact_t sa = {NULL};
    sa.sa_handler = &PingPong;
    sigaction(SIGUSR2, &sa, NULL);
 
    child = fork();
    if (0 > child) 
    {
        perror("The fork outta here");
        exit(1);
    }

    if (0 != child) 
    {
        while (1)
        {
            sleep (5);
            kill(child, SIGUSR1);
            waitpid(child, NULL, WUNTRACED); 
        }
    }

    else
    {
        if (-1 == execvp("./a.out", arg))
        {
            perror("execvp error");
        }

        exit(0);
    }

    return (0);
*/