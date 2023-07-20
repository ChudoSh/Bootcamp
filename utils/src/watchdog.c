/*
Dev: BarSh
Rev: 
Date:
Status:
*/
#define __USE_POSIX199506L
#define _DEFAULT_SOURCE
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

#define BUFFER_SIZE (50)
#define SEM_NAME ("/LockTheDog")
#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
#define WD_PID ("ILRD_WD_PID")
#define WD_DIR ("/home/barchik/Mygit/bar.shadkhin/utils/test/who_let_the_watchdog.out")

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

typedef struct Path_Sched
{
    scheduler_t *sched;
    char **path;
}psched_t;

static sem_t *usr_sem = NULL;
static atomic_int flag_to_stop = FALSE;
static atomic_int counter = 0; 
pid_t wdg_pid = 0;
pid_t usr_pid = 0;
psched_t *psched = NULL;
pthread_t user_thread = 0;
static sigact_t sa_run = {NULL};
static sigact_t sa_stop = {NULL};

/*Watchdog*/
static int WDUser(char **path);
static int WDProcess(char **path);
static void *WDThread(void *arg);

/*Tasks*/
static int Sender(void *arg);
static int Checker(void *arg);
static int Stopper(void *arg);

/*Handlers*/
static void SigUser1Handler(int signal);
static void SigUser2Handler(int signal);

/*Static*/
static int Path_SchedCreate(char **path);
static void Path_SchedDestroy();
static int SigactInit();
static int SemInit();
static int PSchedRun();

/******************************************************************************/
/*Spawns the watch dog*/
int WDStart(char **path)
{
    /* pid_t to_compare = (NULL != getenv(WD_PID)) ? atoi(getenv(WD_PID)) : 0;

    if (to_compare != (int)getpid())
    {
        printf("WD - Process %d Start\n", getpid());
        return (WDProcess(path)); 
    }
    
    printf("WD - User %d Start\n", getpid());
    return (WDUser(path)); */
    
    if (NULL == path)
    {
        printf("WD - Process %d Start\n", getpid());
        return (WDProcess(path));
    }

    printf("WD - User %d Start\n", getpid());
    return (WDUser(path));
}

/*Stops the watchdog*/
void WDStop(size_t timeout)
{
    time_t exit_time = time(NULL) + timeout;

    kill(wdg_pid, SIGUSR2);
    kill(usr_pid, SIGUSR2);

    printf("WDStop signals sent\n");
    counter = 0;

    while(exit_time > time(NULL) && !flag_to_stop);

    if (SUCCESS != pthread_join(user_thread, NULL))
    {
        printf("Failed to join the thread\n");
        return;
    } 

    sem_unlink(SEM_NAME);
    if (SUCCESS != sem_destroy(usr_sem))
    {
        printf("sem_clsoe fail..\n");
    }

    if (SUCCESS != unsetenv(WD_PID))
    {
        printf("unsetenv fail..\n");
    }
    
    if (time(NULL) < exit_time)
    {
        printf("Watchdog Process #%d stopped garcefully\n",wdg_pid);   
    }
    else
    {
        printf("Watchdog stop delayed..\n");
    }

    return;

}
/********************************User and WD***********************************/
static int WDUser(char **path)
{ 
    sigset_t set = {0};
    char buffer[BUFFER_SIZE] = {'\0'}; 

    /*psched init*/
    if (SUCCESS != Path_SchedCreate(path))
    {
        return (FAIL);
    }

    /*sigaction init*/
    if (SUCCESS != SigactInit())
    {
        return (FAILED_TO_CREATE_WATCHDOG);
    }

    /*sem init*/
    if (FAIL == SemInit())
    {
        return (FAILED_TO_CREATE_WATCHDOG);
    }
    
   
    /*user and watchdog init*/
    if (NULL == getenv(WD_PID))
    { 
        /*forking*/
        wdg_pid = fork();
        if (FAIL == wdg_pid)
        {
            return (FAILED_TO_CREATE_CHILD_PROCESS);
        }

        if (0 == wdg_pid)
        {
            sprintf(buffer, "%d", wdg_pid);
            if (SUCCESS != setenv(WD_PID, buffer, 0))
            {
                printf("USR: setenv fail..\n");
                return (FAILED_TO_CREATE_CHILD_PROCESS);
            }

            if(FAILED_TO_CREATE_CHILD_PROCESS == execl(WD_DIR, *path))
            {
                return (FAILED_TO_CREATE_CHILD_PROCESS);
            }

            printf("Dont get here\n");  
        } 
        else
        {
            sem_wait(usr_sem);
            if (SUCCESS != pthread_create(&user_thread, NULL, WDThread, psched))
            {
                printf("Failed to create the thread\n");
                return (FAILED_TO_CREATE_WATCHDOG);
            }

            sigemptyset(&set);
            if (SUCCESS != pthread_sigmask(SIG_BLOCK, &set, NULL))
            {
                printf("mask fail..\n");
                return (FAILED_TO_CREATE_WATCHDOG);
            }
        }
    }

    else 
    {
        sem_post(usr_sem);
        if (SUCCESS != pthread_create(&user_thread, NULL, WDThread, psched))
        {
            printf("Failed to create the thread\n");
            return (FAILED_TO_CREATE_WATCHDOG);
        } 

        sigemptyset(&set);
        if (SUCCESS != pthread_sigmask(SIG_BLOCK, &set, NULL))
        {
            printf("mask fail..\n");
            return (FAILED_TO_CREATE_WATCHDOG);
        }
    
    }

    return (WD_SUCCESS);   
}
static void *WDThread(void *arg)
{
    sigset_t set = {0};
    wdg_pid = getpid();

    assert(NULL != arg);

    /*mask init*/
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGUSR2);
    if (SUCCESS != pthread_sigmask(SIG_BLOCK, &set, NULL))
    {
        printf("mask fail..\n");
    }

    if (SUCCESS != Path_SchedCreate(((psched_t *)arg)->path))
    {
        printf("WDThread Fail..\n");
    }

    if (SUCCESS != PSchedRun())
    {
        printf("WDThread Fail..\n");
    }

    return (NULL);
}
static int WDProcess(char **path)
{
    wdg_pid = getppid();
    /*sched create*/
    if (SUCCESS != Path_SchedCreate(path))
    {
        return (FAIL);
    }
    /*handlers init*/
    if (SUCCESS != SigactInit())
    {
        return (FAIL);
    }
    
    /*sem init*/
    if (SUCCESS != SemInit())
    {
        return (FAIL);
    }
    
    /*init sched*/
    sem_post(usr_sem);
    printf("sem unlocked\n");
    if (SUCCESS != PSchedRun())
    {
        return (FAILED_TO_CREATE_WATCHDOG);
    }

    if (SUCCESS != sem_close(usr_sem))
    {
        return (FAIL);
    }

    return (WD_SUCCESS);
}
/********************************TASKS*****************************************/
/*Sends the signals accordignly*/
static int Sender(void *arg)
{
    printf("Process %d Sent SIGUSR1\n", getpid());
    kill(wdg_pid, SIGUSR1);

    return (REPEAT);
    (void)arg;
}
/*Checks the counter, if counter is not 0, resert, else revive*/
static int Checker(void *arg)
{
    printf("Process %d Counter is %d \n", getpid(),counter);
    if (0 != counter)
    {
        printf("Process %d Counter reset to 0 \n", getpid());
        counter = 0;
    }

    else/*Revive*/
    {
        (void)arg;
    }
   
    return (REPEAT); 
}
/*Checks the flag, if true, send SIGUSR2*/
static int Stopper(void *arg)
{
    if (flag_to_stop)
    {
        kill(wdg_pid, SIGUSR2);
        HSchedulerStop(((psched_t *)arg)->sched);
        printf("Process %d sent SIGUSR2\n", getpid());
        return (DO_NOT_REPEAT);
    }

    return (REPEAT);
}

/********************************HANDLERS**************************************/
/*Handler SIGUSR1*/
static void SigUser1Handler(int signal)
{
    printf("Process %d Counter increases\n",getpid());
    ++(counter);
    (void)signal;   
}

/*Handler SIGUSR1*/
static void SigUser2Handler(int signal)
{
    printf("Process %d Flag turns TRUE\n",getpid());
    flag_to_stop = TRUE;
    (void)signal;
}

/*===============================Static=======================================*/
static int Path_SchedCreate(char **path)
{
    psched = (psched_t *)malloc(sizeof(psched_t)); 
    if (NULL == psched)
    {
        printf("Process SchedCreate");
        return (FAIL);
    }

    psched->sched = HSchedulerCreate();
    if (NULL == psched->sched)
    {
        free(psched);
        printf("Process SchedCreate");
        return (FAIL);
    }

     if (UIDIsSame(UIDBadUID, 
                  HSchedulerAddTask(psched->sched, Sender, 
                                     psched, 1, 1, NULL, NULL)))
    {
        printf("Bad UID\n");
        return (FAIL);
    }

    if (UIDIsSame(UIDBadUID, 
                  HSchedulerAddTask(psched->sched, Checker, 
                                    psched, 1, 2, NULL, NULL)))
    {
        printf("Bad UID\n");
        return (FAIL);
    }

    if (UIDIsSame(UIDBadUID, 
                  HSchedulerAddTask(psched->sched, Stopper, 
                                    psched, 1, 1, NULL, NULL)))
    {
        printf("Bad UID\n");
        return (FAIL);
    }


    psched->path = path;

    return (SUCCESS);
}

static void Path_SchedDestroy()
{
    HSchedulerDestroy(psched->sched);
    
    free(psched);
}

static int SigactInit()
{
    sa_run.sa_handler = SigUser1Handler;
    sa_stop.sa_handler = SigUser2Handler;
    
    if (SUCCESS != sigaction(SIGUSR1, &sa_run, NULL))
    {
        printf("sigaction failed..\n");
        return (FAIL);
    }
    if (SUCCESS != sigaction(SIGUSR2, &sa_stop, NULL))
    {
        printf("sigaction failed..\n");
        return (FAIL);
    }

    return (SUCCESS);
}
static int SemInit()
{
    usr_sem = sem_open(SEM_NAME, O_CREAT, SEM_PERMS, 0);
    if (SEM_FAILED == usr_sem)
    {
        printf("sem fail..\n");
        return (FAIL);
    }
    return (SUCCESS);
}

static int PSchedRun()
{
    int status = 0; 

    status = HSchedulerRun(psched->sched);
    if (ERROR == status)
    {
        printf("SchedRun regular error..\n");
        return (FAIL);
    }
    else if (RUN == status)
    {
        printf("SchedRun run error..\n");
        return (FAIL);
    }
    
    Path_SchedDestroy(psched);
    printf("Process %d Sched destroyed\n",getpid());

    return (SUCCESS);
}