/*
Dev: BarSH
Rev: 
Status: 
Date: 
*/
#include <sys/types.h> /*pid*/
#include <unistd.h> /*POSIX*/
#define __USE_POSIX
#define __USE_POSIX199309
#include <signal.h> /*signal*/
#include <pthread.h> /*pthread_t*/
#include <stdatomic.h> /*atomic*/
#include <assert.h> /*assert*/
#include <semaphore.h> /*sem_t*/
#include <stdio.h>/*printf*/
#include <fcntl.h>/*sem_open*/
#include <sys/stat.h> /*sem_open*/
#include <stdlib.h>/*malloc*/
#include <fcntl.h> /*O_CREA*/

#include "../../ds/include/scheduler_heap.h"

#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

typedef struct sigaction sigact_t;

enum BOOL
{
    FALSE, 
    TRUE
};

enum STATUS
{
    FAIL = -1, 
    SUCCESS
};

static int flag_to_stop = FALSE;
static atomic_int counter = 0;
static sem_t *wd_sem = NULL;
pid_t usr_proc = 0;

int Sender(void *arg);
int Checker(void *arg);
static void SigUser1Handler(int signal);
static void SigUser2Handler(int signal);

static sigact_t sa_run = {NULL};
static sigact_t sa_stop = {NULL};

typedef struct Path_Sched
{
    scheduler_t *sched;
    char **path;
}psched_t;

static psched_t *Path_SchedCreate(char **path);
static void Path_SchedDestroy(psched_t *psched);
   
int main()
{ 
    int sched_status = 0;
    psched_t *psched = Path_SchedCreate(NULL);
    if (NULL == psched)
    {
        printf("sched create fail..\n");
    }
   
    usr_proc = getppid();
    sa_run.sa_handler = SigUser1Handler;
    sa_stop.sa_handler = SigUser2Handler;

    if (0 != sigaction(SIGUSR2, &sa_stop, NULL))
    {
        printf("WD: sigaction USR2 failed..\n");
    }
    if (0 != sigaction(SIGUSR1, &sa_run, NULL))
    {
        printf("WD: sigaction USR1 failed..\n");
    }

    wd_sem = sem_open("/sem", O_CREAT, SEM_PERMS, 0);
    if (SEM_FAILED == wd_sem)
    {
        printf("WD: sem_open fail..\n");
    }
    
    if (UIDIsSame(UIDBadUID, 
                  HSchedulerAddTask(psched->sched, Sender, psched, 1, 1, NULL, NULL)))
    {
        printf("WD: Bad UID\n");
        return (FAIL);
    }
    if (UIDIsSame(UIDBadUID,
                  HSchedulerAddTask(psched->sched, Checker, psched, 1, 1, NULL, NULL)))
    {
        printf("WD: Bad UID\n");
        return (FAIL);
    }

    sem_post(wd_sem);
    sched_status = HSchedulerRun(psched->sched);
    if (ERROR == sched_status)
    {
        printf("WD: SchedRun regular error..\n");
    }
    else if(RUN == sched_status)
    {
        printf("WD: SchedRun run error..\n");
    }
    else
    {
        printf("WD: Sched Run stopped successfully\n");
    }
    
    Path_SchedDestroy(psched);
    printf("WD: Sched destroyed\n");

    kill(usr_proc, SIGUSR2);

    if (0 != sem_close(wd_sem))
    {
        printf("WD: sem_clsoe fail..\n");
    }

    return (0);
}
/********************************Tasks**************************************/
int Sender(void *arg)
{
    printf("WD: Sender run\n");
    kill(usr_proc, SIGUSR1);  

    return (REPEAT);
    (void)arg;
}

int Checker(void *arg)
{
    printf("WD: Current Counter is %d \n", counter);
    {   
        if (flag_to_stop)
        {
            printf("WD: Sender stops\n");
            HSchedulerStop(((psched_t *)arg)->sched);
            kill(usr_proc, SIGUSR2);
            return (DO_NOT_REPEAT); 
        }   
        else if (counter != 0)
        {
            printf("WD: Counter reset to 0\n");
            counter = 0;
        }
        else
        {
            (void)arg;
        } 
    }

    printf("WD: Chcker repeat\n");
    return (REPEAT);
    
}
/********************************Handlers**************************************/
static void SigUser1Handler(int signal)
{
    printf("WD: Counter increment\n");
    ++(counter); 
    (void)signal;   
}

static void SigUser2Handler(int signal) 
{
    printf("WD: Flag turns TRUE\n");
    flag_to_stop = TRUE;
    (void)signal;
}
/*============================================================================*/
static psched_t *Path_SchedCreate(char **path)
{
    psched_t *new_psched = (psched_t *)malloc(sizeof(psched_t)); 
    if (NULL == new_psched)
    {
        return (NULL);
    }

    new_psched->sched = HSchedulerCreate();
    if (NULL == new_psched->sched)
    {
        free(new_psched);
        return (NULL);
    }

    new_psched->path = path;

    return (new_psched);
}

static void Path_SchedDestroy(psched_t *psched)
{
    HSchedulerDestroy(psched->sched);
    
    free(psched);
}