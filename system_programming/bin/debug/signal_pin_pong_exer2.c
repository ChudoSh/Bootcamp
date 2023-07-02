#include <sys/types.h>/*system*/
#include <unistd.h>/*system*/
#include <stdlib.h>/*fork*/
#include <string.h>/*strcmp*/
#include <stdio.h>/*scanf*/
#include <sys/types.h>/*wait*/
#include <sys/wait.h>/*wait*/
#include <sys/types.h>/*system*/
#include <errno.h>
#define __USE_POSIX
#include <signal.h>

#include <stdio.h>

typedef struct sigaction sigact_t;
static void PingPong2(int signal);

int main()
{
    sigact_t sa = {NULL};
    sa.sa_handler = &PingPong2;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    printf("This is main\n");

    sleep(20);
    printf("This was a nice sleep\n");
    kill(getppid(), SIGUSR2);
	
    return (0);
}
   
static void PingPong2(int signal)
{
    printf("This is pingpong\n");
    if (SIGUSR1 == signal)
    {
        printf("Parent serves to child1, Ping!\n"); 
    }

    else if (SIGUSR2 == signal)
    {
        printf("Child serves back to parent and scores, Pong!\n"); 
        printf("What a game!\n");
    }
}

