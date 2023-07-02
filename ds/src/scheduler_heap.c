/*
Dev: BarSH
Rev: Michal
Status: Fixing
Date: 19.5.23
*/

#include <stdlib.h> /*malloc*/
#include <assert.h>/* assert */
#include <time.h> /* time */  
#include <stdio.h>


#include "scheduler_heap.h"


enum BOOLEAN/*change the name*/
{
	FALSE = 0,
	TRUE = 1
};

enum STATUS/*change the name*/
{
    ENQ_FAIL = -1,
    FAIL = -1,
	SUCCESS = 0
	
};

struct Scheduler
{
	pq_t *pqueue;
	int is_running;
	task_t *current_task;
	int current_occupied;
};

/*static void SetCurrentTask(scheduler_t *scheduler, task_t *task);*/
static int Compare_Time(const void *task1, const void *task2);
static int IsMatchUID(const void *task, const void *uid);

/*Create a scheduler*/
scheduler_t *HSchedulerCreate(void)
{
	scheduler_t *new_scheduler = NULL;
	
	new_scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (NULL == new_scheduler)
	{
		return (NULL);
	}
	
	new_scheduler->pqueue = PQHCreate(Compare_Time);
	if (NULL == new_scheduler->pqueue)
	{
		free(new_scheduler);
		return (NULL);
	}
	
	new_scheduler->is_running = STOPPED;
	new_scheduler->current_task = NULL;
	new_scheduler->current_occupied = FALSE;
	
	return (new_scheduler);	
}

/*Destroys a scheduler*/
void HSchedulerDestroy(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	HSchedulerClear(scheduler);
	
	PQHDestroy(scheduler->pqueue);
	
	free(scheduler);
}

/*Adds a new task*/
ilrd_uid_t HSchedulerAddTask(scheduler_t *scheduler, 
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
						 
	if (NULL == new_task)
	{
		return (UIDBadUID);
	}
						 
	if (ENQ_FAIL == PQHEnqueue(scheduler->pqueue, new_task))
	{
		TaskDestroy(new_task);
		return (UIDBadUID);
	}
	
	return (TaskGetUID(new_task));	
}

/*Removes a task*/
int HSchedulerRemoveTask(scheduler_t *scheduler, ilrd_uid_t uid)
{
	task_t *save = NULL;
	
	assert(NULL != scheduler);
	
	if (scheduler->current_occupied && TaskIsMatch(scheduler->current_task, uid))
	{
		TaskDestroy(scheduler->current_task);
		scheduler->current_occupied = FALSE;
		
		return (SUCCESS);
	}
	
	save = PQHErase(scheduler->pqueue, IsMatchUID, &uid);
	
	if (NULL != save)
	{
		TaskDestroy(save);
		return (SUCCESS);
		
	}
	
	return (FAIL);
}

/*Runs the schedule*/
int HSchedulerRun(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	scheduler->is_running = RUN;
	
	while (RUN == scheduler->is_running && !HSchedulerIsEmpty(scheduler))
	{
		if (!scheduler->current_occupied)
		{
			scheduler->current_task = PQHDequeue(scheduler->pqueue);
			scheduler->current_occupied = TRUE;
		}
		 
		/*while(sleep(TaskGetTimeToRun(scheduler->current_task) - time(NULL)));*/
		 
		if(!(scheduler->current_occupied))
		{
			continue;
		}

			
		if (REPEAT == TaskRun(scheduler->current_task))
		{
			TaskUpdateTimeToRun(scheduler->current_task);
			
			if (ENQ_FAIL == PQHEnqueue(scheduler->pqueue, 
									  scheduler->current_task))
			{	
				scheduler->is_running = ERROR;
				return (scheduler->is_running);	
			}
	
			scheduler->current_task = NULL;	
			scheduler->current_occupied = FALSE;
		}
		
		else
		{
			TaskDestroy(scheduler->current_task);
			scheduler->current_task = NULL;
			scheduler->current_occupied = FALSE;
		}		
	}
	
	return (scheduler->is_running);
}

/*Stops the scheduler*/
void HSchedulerStop(scheduler_t *scheduler)
{
	assert(NULL != scheduler);

	scheduler->is_running = STOPPED; 	
}

/*returns the number of tasks in the scheduler*/
size_t HSchedulerSize(const scheduler_t *scheduler)								
{
	assert(NULL != scheduler);
	
	if (scheduler->current_occupied)
	{
		return (PQHSize(scheduler->pqueue) + 1);
	} 
	
	return (PQHSize(scheduler->pqueue));
}

/*Is scheduler is empty*/
int HSchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	return (0 == HSchedulerSize(scheduler));
}

/*Clears the scheduler*/
void HSchedulerClear(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	if (scheduler->current_occupied)
	{
		TaskDestroy(scheduler->current_task);
		scheduler->current_task = NULL;
		scheduler->current_occupied = FALSE;
	}

	while (!HSchedulerIsEmpty(scheduler))
	{
		TaskDestroy((PQHDequeue(scheduler->pqueue)));
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
	
	return (TaskIsMatch((const task_t *)task, *((ilrd_uid_t *)uid)));
	
}

/*static void SetCurrentTask(scheduler_t *scheduler, task_t *task)
{
	assert(NULL != scheduler);
	
	scheduler->current_task = task;
}*/
