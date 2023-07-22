/*
Dev: BarSh
Rev: 
Date:
Status:
*/
#define __USE_POSIX199506L
#define _DEFAULT_SOURCE
#define _GNU_SOURCE
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

#define BUFFER_SIZE (100)
#define SEM_NAME ("/SemTheDog")
#define SEM_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
#define WD_PID ("ILRD_WD_PID")
#define WD_EXEC ("/home/barchik/Mygit/bar.shadkhin/utils/test/who_let_the_watchdog.out")
#define USER_EXEC ("/home/barchik/Mygit/bar.shadkhin/utils/test/watchdog_test.out")

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
    char *path;
}psched_t;

static sem_t *usr_sem = NULL;
static atomic_int flag_to_stop = FALSE;
static atomic_int counter = 0; 
pid_t wdg_pid = 0;
ilrd_uid_t task_uid = {0};
psched_t *psched = NULL;
pthread_t user_thread = 0;
static sigact_t sa_run = {NULL};
static sigact_t sa_stop = {NULL};
sigset_t *set = NULL;

/*Watchdog*/
static int WDUser(char **path);
static int WDProcess(char **path);
static void *WDThread(void *arg);
static int WDRevive();

/*Tasks*/
static int WDSender(void *arg);
static int WDChecker(void *arg);
static int WDStopper(void *arg);

/*Handlers*/
static void WDSigUser1Handler(int signal);
static void WDSigUser2Handler(int signal);

/*Static*/
static int WDPath_SchedCreate(char **path);
static void WDPath_SchedDestroy(void);
static int WDSigactInit(void);
static int WDSemInit(void);
static int WDPSchedRun(void);
static int WDIsWatchDog(void);
static int WDSetEnvVar(pid_t pid);
static int WDSetSigMask(int to_block);
static int WDGetEnvVar(void);

/******************************************************************************/
/*Spawns the watch dog*/
int WDStart(char **path)
{
    if (WDIsWatchDog())
    {
        printf("WD Process %d Start\n", getpid());
        return (WDProcess(path)); 
    }

    printf("User Process %d Start\n", getpid());
    return (WDUser(path)); 
}

/*Stops the watchdog*/
void WDStop(size_t timeout)
{
    time_t exit_time = time(NULL) + timeout;

    HSchedulerRemoveTask(psched->sched, task_uid);
    printf("WDChecker remove\n");

    while (!flag_to_stop && exit_time != time(NULL))
    {
        kill(wdg_pid, SIGUSR2);
    }

    WDPath_SchedDestroy();
    printf("User Sched destroyed\n");

    if (SUCCESS != pthread_join(user_thread, NULL))
    {
        printf("Failed to join the thread\n");
        return;
    }

    if (SUCCESS != sem_destroy(usr_sem))
    {
        printf("sem_clsoe fail..\n");
    }
    sem_unlink(SEM_NAME);

    if (time(NULL) < exit_time)
    {
        printf("Watchdog Process #%d stopped garcefully\n", wdg_pid);   
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
    /*psched init*/
    if (SUCCESS != WDPath_SchedCreate(path))
    {
        return (FAIL);
    }

    /*sigaction init*/
    if (SUCCESS != WDSigactInit())
    {
        return (FAILED_TO_CREATE_WATCHDOG);
    }

    /*sem init*/
    if (FAIL == WDSemInit())
    {
        return (FAILED_TO_CREATE_WATCHDOG);
    }
   
    /*user and watchdog init*/
    if (FAIL == WDGetEnvVar())
    { 
        /*forking*/
        wdg_pid = fork();
        if (FAIL == wdg_pid)
        {
            return (FAILED_TO_CREATE_CHILD_PROCESS);
        }

        if (0 == wdg_pid)
        {
            if (SUCCESS != WDSetEnvVar(getpid()))
            {
                return (FAILED_TO_CREATE_CHILD_PROCESS);
            }
            
            if (FAILED_TO_CREATE_CHILD_PROCESS == execl(WD_EXEC, psched->path))
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
        }
    }

    else if (getppid() == WDGetEnvVar())
    {
        wdg_pid = getppid();

        sem_post(usr_sem);
        if (SUCCESS != pthread_create(&user_thread, NULL, WDThread, psched))
        {
            printf("Failed to create the thread\n");
            return (FAILED_TO_CREATE_WATCHDOG);
        } 
    }

    if (SUCCESS != WDSetSigMask(FALSE))
    {
        return (FAILED_TO_CREATE_WATCHDOG);
    }

    return (WD_SUCCESS);   
}
static void *WDThread(void *arg)
{
    assert(NULL != arg);

    /*mask init*/
    if (SUCCESS != WDSetSigMask(TRUE))
    {
        printf("WDThread Fail..\n");
        return (NULL);
    }

    if (SUCCESS != WDPath_SchedCreate(&(psched->path)))
    {
        printf("WDThread Fail..\n");
        return (NULL);
    }

    if (SUCCESS != WDPSchedRun())
    {
        printf("WDThread Fail..\n");
        return (NULL);
    }

    return (NULL);
    (void)arg;
}

static int WDProcess(char **path)
{
    wdg_pid = getppid();
    /*sched create*/
    if (SUCCESS != WDPath_SchedCreate(path))
    {
        return (FAIL);
    }
    /*handlers init*/
    if (SUCCESS != WDSigactInit())
    {
        return (FAIL);
    }

    /*sem init*/
    if (SUCCESS != WDSemInit())
    {
        return (FAIL);
    }
    
    /*init sched*/
    sem_post(usr_sem);
    if (SUCCESS != WDPSchedRun())
    {
        return (FAILED_TO_CREATE_WATCHDOG);
    }
    
    WDPath_SchedDestroy();
    printf("WD Destroyed\n");

    if (SUCCESS != sem_close(usr_sem))
    {
        return (FAIL);
    }

    if (SUCCESS != unsetenv(WD_PID))
    {
        return (FAIL);
    }

    return (WD_SUCCESS);
}
static int WDRevive()
{
    pid_t revive_pid = 0;
    int is_current_proc_wd = WDIsWatchDog();
    
    revive_pid = fork();
    if (FAIL == revive_pid)
    {
        return (FAIL);
    }

    if (0 == revive_pid)/*Im the WD and I need to create a new user*/
    { 
        if (is_current_proc_wd)
        {
            wdg_pid = getppid();
            if (SUCCESS != WDSetEnvVar(wdg_pid))
            {
                printf("setenv fail..\n");
                return (FAILED_TO_CREATE_CHILD_PROCESS);
            } 

            printf("The path to the new user %s and the pid %d\n", psched->path, getpid());
            if (FAILED_TO_CREATE_CHILD_PROCESS == execl(USER_EXEC, psched->path))
            {
                perror("Execl FAIL\n");
                return (FAILED_TO_CREATE_CHILD_PROCESS);
            }
            printf("Dont Get Here\n");
        }
        else/*Im the user and I need to create a new WD*/
        {
            wdg_pid = getpid();
            if (SUCCESS != WDSetEnvVar(wdg_pid))
            {
                printf("setenv fail..\n");
                return (FAILED_TO_CREATE_CHILD_PROCESS);
            }

            printf("The path to the new wd %s and the pid %d\n", WD_EXEC, getpid());
            if(FAILED_TO_CREATE_CHILD_PROCESS == execl(WD_EXEC, psched->path))
            {
                perror("Execl FAIL\n");
                return (FAILED_TO_CREATE_CHILD_PROCESS);
            }
            printf("Dont Get Here\n");
        }
    }
    else
    {
        printf("Revive pid %d\n",revive_pid);
        wdg_pid = revive_pid;
    }
    
    sem_wait(usr_sem);
    
    return (WD_SUCCESS);

}

/*===============================TASKS========================================*/
/*Sends the signals accordignly*/
static int WDSender(void *arg)
{
    printf("Process %d Sent SIGUSR1 to %d\n", getpid(), wdg_pid);
    kill(wdg_pid, SIGUSR1);

    return (REPEAT);
    (void)arg;
}
/*Checks the counter, if counter is not 0, resert, else revive*/
static int WDChecker(void *arg)
{
    printf("Process %d Counter is %d \n", wdg_pid ,counter);
    if (0 != counter)
    {
        printf("Process %d Counter reset to 0 \n", getpid());
        counter = 0;
    }

    else/*Revive*/
    {
        WDRevive();   
    }
    
    return (REPEAT); 
    (void)arg;
}
/*Checks the flag, if true, send SIGUSR2*/
static int WDStopper(void *arg)
{
    if (flag_to_stop)
    {
        kill(wdg_pid, SIGUSR2);
        HSchedulerStop(psched->sched);
        printf("Process %d sent SIGUSR2\n", getpid());
        return (DO_NOT_REPEAT);
    }

    return (REPEAT);
    (void)arg;
}

/*===============================HANDLERS=====================================*/
/*Handler SIGUSR1*/
static void WDSigUser1Handler(int signal)
{
    printf("Process %d Counter increases\n",getpid());
    ++(counter);
    (void)signal;   
}

/*Handler SIGUSR1*/
static void WDSigUser2Handler(int signal)
{
    /* printf("Process %d Flag turns TRUE\n",getpid()); */
    flag_to_stop = TRUE;
    (void)signal;
}

/*===============================Static=======================================*/
static int WDPath_SchedCreate(char **path)
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
                  HSchedulerAddTask(psched->sched, WDSender, 
                                     psched, 1, 1, NULL, NULL)))
    {
        printf("Bad UID\n");
        return (FAIL);
    }

    if (NULL == getenv(WD_PID))
    {
        task_uid = HSchedulerAddTask(psched->sched, WDChecker, 
                                    psched, 5, 5, NULL, NULL);
        if (UIDIsSame(UIDBadUID, task_uid))
        {
            printf("WDChecker: Bad UID\n");
            return (FAIL);
        }
    }

    if (UIDIsSame(UIDBadUID, 
                  HSchedulerAddTask(psched->sched, WDChecker, 
                                    psched, 5, 5, NULL, NULL)))
    {
        printf("Bad UID\n");
        return (FAIL);
    }

    if (NULL != getenv(WD_PID))
    {
        if (UIDIsSame(UIDBadUID, 
                      HSchedulerAddTask(psched->sched, WDStopper, 
                                        psched, 1, 1, NULL, NULL)))
        {
            printf("Bad UID\n");
            return (FAIL);
        }
    }
    
    psched->path = *path;

    return (SUCCESS);
}

static void WDPath_SchedDestroy(void)
{
    HSchedulerDestroy(psched->sched);
    
    free(psched);
}

static int WDSigactInit(void)
{
    sa_run.sa_handler = WDSigUser1Handler;
    sa_stop.sa_handler = WDSigUser2Handler;
    
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
static int WDSemInit(void)
{
    usr_sem = sem_open(SEM_NAME, O_CREAT, SEM_PERMS, 0);
    if (SEM_FAILED == usr_sem)
    {
        printf("sem fail..\n");
        return (FAIL);
    }
    return (SUCCESS);
}

static int WDPSchedRun(void)
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
    
    return (SUCCESS);
}

static int WDIsWatchDog(void)
{
    return (getpid() == WDGetEnvVar());
}

static int WDGetEnvVar(void)
{
    if (NULL == getenv(WD_PID))
    {
        return (FAIL);
    }

    return (atoi(getenv(WD_PID)));
}

static int WDSetEnvVar(pid_t pid)
{
    char buffer[BUFFER_SIZE] = {'\0'};

    sprintf(buffer, "%d", pid);
    if (SUCCESS != setenv(WD_PID, buffer, 1))
    {
        printf("setenv fail..\n");
        return (FAILED_TO_CREATE_CHILD_PROCESS);
    }
    
    return (SUCCESS);
}

static int WDSetSigMask(int to_block)
{
    sigemptyset(set);
  
    if (to_block)
    {
        sigaddset(set, SIGUSR1); 
        sigaddset(set, SIGUSR2);  
    }
    
    if (SUCCESS != pthread_sigmask(SIG_BLOCK, set, NULL))
    {
        printf("mask fail..\n");
        return (FAILED_TO_CREATE_WATCHDOG);
    }
    
    return (SUCCESS);
}