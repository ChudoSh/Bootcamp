/*
Dev: BarSH
Rev: 
Status: Test impl.
Date: 19.5.23
*/

#include <stdlib.h> /*malloc*/
#include <assert.h>/* assert */
#include <time.h> /* time */  

#include "scheduler.h"

#define TRUE (1)
#define FALSE (0)


struct Scheduler
{
	pq_t *pqueue;
	int is_running;
};

static int Compare_Time(const void *task1, const void *task2);
static int IsMatchUID(const void *task, const void *uid);

scheduler_t *SchedulerCreate(void)
{
	scheduler_t *new_scheduler = NULL;
	
	new_scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (NULL == new_scheduler)
	{
		return (NULL);
	}
	
	new_scheduler->pqueue = PQCreate(&Compare_Time);
	if (NULL == new_scheduler->pqueue)
	{
		free(new_scheduler);
		return (NULL);
	}
	
	new_scheduler->is_running = SUCCESS;
	
	return (new_scheduler);	
}

void SchedulerDestroy(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	while (!PQIsEmpty(scheduler->pqueue))
	{
		TaskDestroy(PQDequeue(scheduler->pqueue));
	}
	
	PQDestroy(scheduler->pqueue);
	
	free(scheduler);
}


ilrd_uid_t SchedulerAddTask(scheduler_t *scheduler, 
							int (*op_func_t)(void *), 
					   		void *op_param, size_t delay_in_sec, 
					 		size_t interval_in_sec, 
					 		void (*task_cleanup)(void *),
					 		void *cleanup_param)
{
	task_t *new_task = NULL;
	
	assert(NULL != scheduler);
	assert(NULL != op_func_t);
	
	new_task = TaskCreate(op_func_t, op_param, delay_in_sec, interval_in_sec, 
						 task_cleanup, cleanup_param);
						 
	PQEnqueue(scheduler->pqueue, new_task);
	
	return (TaskGetUID(new_task));	
}

int SchedulerRemoveTask(scheduler_t *scheduler, ilrd_uid_t uid)
{
	assert(NULL != scheduler);

	 return (PQErase(scheduler->pqueue, IsMatchUID, &uid));
}

int SchedulerRun(scheduler_t *scheduler)
{
	task_t *handler = NULL;
	
	assert(NULL != scheduler);
	
	while (SUCCESS == scheduler->is_running && !SchedulerIsEmpty(scheduler))
	{
		handler = PQDequeue(scheduler->pqueue);
		
		sleep(TaskGetTimeToRun(handler) - time(NULL));	
			
		if (REPEAT == TaskRun(handler))
		{
			TaskUpdateTimeToRun(handler);
			
			if (-1 == PQEnqueue(scheduler->pqueue, handler))
			{
				scheduler->is_running = ERROR;
				TaskDestroy(handler);
			}
		}
		else
		{
			TaskDestroy(handler);
		}	
		
	}
	
	return (scheduler->is_running);
}

void SchedulerStop(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	scheduler->is_running = STOPPED;
}

size_t SchedulerSize(const scheduler_t *scheduler)								
{
	assert(NULL != scheduler);
	
	return (PQSize(scheduler->pqueue));
}

int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return (PQIsEmpty(scheduler->pqueue));
}

void SchedulerClear(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	while (!PQIsEmpty(scheduler->pqueue))
	{
		TaskDestroy(PQDequeue(scheduler->pqueue));
	}
}

/***************STATIC FUNCTIONS**********************************************/
static int Compare_Time(const void *task1, const void *task2)
{
	assert(NULL != task1);
	assert(NULL != task2);
	
	return (TaskGetTimeToRun((task_t *)task1) - 
				  TaskGetTimeToRun((task_t *)task2));
}

static int IsMatchUID(const void *task, const void *uid)
{
	assert(NULL != task);
	assert(NULL != uid);
	
	if (TaskIsMatch((const task_t *)task, *((ilrd_uid_t *)uid)))
	{
		TaskDestroy((task_t *)task);
		return (TRUE);
	}
	
	return (FALSE);
}

