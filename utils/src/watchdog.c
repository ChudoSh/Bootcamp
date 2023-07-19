/*
Dev: BarSh
Rev: 
Date:
Status:
*/
#define _DEFAULT_SOURCE
#define __USE_POSIX199506L
#include <sys/types.h> /*pid*/
#include <unistd.h> /*POSIX*/
#include <signal.h> /*signal*/
#include <pthread.h> /*pthread_t*/
#include <semaphore.h> /*sem_t*/
#include <stdatomic.h> /*atomic*/
#include <assert.h> /*assert*/
#include <time.h>/*time_t*/
#include <stdio.h>/*printf*/
#include <unistd.h>/*execve*/
#include <fcntl.h>/*sem_open*/
#include <sys/stat.h>/*sem_open*/
#include <fcntl.h>/*O_CREA*/
#include <stdlib.h> /*getenv*/
#include <bits/sigthread.h> /*pthread_sigmask*/

#include "../include/watchdog.h"

#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
#define WD_PID ("ILRD_WD_PID")

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

static void *ThreadSchedInit(void *arg);
static void SigUser1Handler(int signal);
static void SigUser2Handler(int signal);
static int Sender(void *arg);
static int Checker(void *arg);

static sem_t *usr_sem = NULL;
static int flag_to_stop = FALSE;
static atomic_int counter = 0; 
pid_t wdg_pid = 0; /*env var*/
pthread_t user_thread = 0;
static sigact_t sa_run = {NULL};
static sigact_t sa_stop = {NULL};


typedef struct Path_Sched
{
    scheduler_t *sched;
    char **path;
}psched_t;

static psched_t *Path_SchedCreate(char **path);
static void Path_SchedDestroy(psched_t *psched);
/*static int WDUser(char **path);
static int WDApp(char **path);*/

/******************************************************************************/
/*Spawns the watch dog*/
int WDStart(char **path)
{ 
    sigset_t set = {0};
    char buffer[50] = {'\0'}; 
    psched_t *psched = Path_SchedCreate(path); 
    if (NULL == psched)
    {
        return (FAIL);
    }
    /*if (NULL == path)
    {
        return WDAppProc();
    }
    else
    {
        return WDClientProc(*path);
    }*/

    /*sigaction init*/
    sa_run.sa_handler = SigUser1Handler;
    sa_stop.sa_handler = SigUser2Handler;
    
    if (SUCCESS != sigaction(SIGUSR1, &sa_run, NULL))
    {
        printf("USR: sigaction USR1 failed..\n");
    }
    if (SUCCESS != sigaction(SIGUSR2, &sa_stop, NULL))
    {
        printf("USR: sigaction USR2 failed..\n");
    }

    /*sem init*/
    usr_sem = sem_open("/sem", O_CREAT, SEM_PERMS, 0);
    if (SEM_FAILED == usr_sem)
    {
        printf("USR: sem_open fail..\n");
    }
    sem_unlink("/sem");
   
    

    /*forking*/
    wdg_pid = fork();
    if (FAIL == wdg_pid)
    {
        return (FAILED_TO_CREATE_CHILD_PROCESS);
    }

    if (0 == wdg_pid)
    {
        execle("./test/who_let_the_watchdog.out",*path);
    }

    else 
    {
        sprintf(buffer, "%d", wdg_pid);
        if (SUCCESS != setenv(WD_PID, buffer, 0))
        {
            printf("USR: setenv fail..\n");
        }

        sem_wait(usr_sem);
        if (SUCCESS != pthread_create(&user_thread, NULL, ThreadSchedInit, psched))
        {
            printf("Failed to create the thread\n");
            return (FAILED_TO_CREATE_WATCHDOG);
        }

        sigemptyset(&set);
        if (SUCCESS != pthread_sigmask(SIG_BLOCK, &set, NULL))
        {
            printf("Mask fail..\n");
        }   
    }

    return (WD_SUCCESS);   
}

/*Stops the watchdog*/
void WDStop(size_t timeout)
{
    time_t exit_time = time(NULL) + timeout;

    kill(wdg_pid, SIGUSR2);
    kill(getpid(), SIGUSR2);

    printf("USR: WDStop signals sent\n");

    while(exit_time > time(NULL) && !flag_to_stop);

    if (time(NULL) < exit_time)
    {
        printf("USR: watchdog stopped garcefully\n");   
    }
    else
    {
        printf("USR: watchdog stop delayed..\n");
    }

    if (SUCCESS != pthread_join(user_thread, NULL))
    {
        printf("Failed to join the thread\n");
        return;
    } 

    if (SUCCESS != sem_destroy(usr_sem))
    {
        printf("USR: sem_clsoe fail..\n");
    }

    return;

}
/********************************THREAD FUNC***********************************/

static void *ThreadSchedInit(void *arg)
{
    int sched_status = 0;
    sigset_t set = {0};

    assert(NULL != arg);

    /*mask init*/
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);
    if (SUCCESS != pthread_sigmask(SIG_BLOCK, &set, NULL))
    {
        printf("Mask fail..\n");
    }

    if (UIDIsSame(UIDBadUID, 
                  HSchedulerAddTask(((psched_t *)arg)->sched, Sender, 
                                     (psched_t *)arg, 1, 1, NULL, NULL)))
    {
        printf("USR: Bad UID\n");
        return (NULL);
    }

    if (UIDIsSame(UIDBadUID, 
                  HSchedulerAddTask(((psched_t *)arg)->sched, Checker, 
                                    (psched_t *)arg, 1, 1, NULL, NULL)))
    {
        printf("USR: Bad UID\n");
        return (NULL);
    }

    sched_status = HSchedulerRun(((psched_t *)arg)->sched);
    if (ERROR == sched_status)
    {
        printf("SchedRun regular error..\n");
    }
    else if (RUN == sched_status)
    {
        printf("SchedRun run error..\n");
    }
    else
    {
        printf("USR: Sched Run stopped successfully\n");
    }
    
    Path_SchedDestroy(((psched_t *)arg));
    printf("USR: Sched destroyed\n");

    return (NULL);
}
/********************************TASKS*****************************************/
/*Sends the signals accordignly*/
static int Sender(void *arg)
{
    printf("USR: Sent SIGUSR1\n");
    kill(atoi(getenv(WD_PID)), SIGUSR1);

    return (REPEAT);
    (void)arg;
}
/*Checks the counter, if counter is not 0, resert, else revive*/
static int Checker(void *arg)
{
    printf("USR: Current Counter is %d \n", counter);
    if (flag_to_stop)
    {
        printf("USR: Sent SIGUSR2\n");
        kill(atoi(getenv(WD_PID)), SIGUSR2);
        HSchedulerStop(((psched_t *)arg)->sched);
        return (DO_NOT_REPEAT); 
    }

    else if (0 != counter)
    {
        printf("USR: Counter reset to 0 \n");
        counter = 0;
    }

    else/*Revive*/
    {
        (void)arg;
    }
   
    return (REPEAT); 
}

/********************************HANDLERS**************************************/
/*Handler SIGUSR1*/
static void SigUser1Handler(int signal)
{
    printf("USR: Counter increases\n");
    ++(counter);
    (void)signal;   
}

/*Handler SIGUSR1*/
static void SigUser2Handler(int signal)
{
    printf("USR: Flag turns TRUE\n");
    flag_to_stop = TRUE;
    (void)signal;
}

/*===============================Static=======================================*/
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