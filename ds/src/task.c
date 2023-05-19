/*
Dev: BarSH
Rev: 
Status: 
Date: 18.5.23
*/
#include <stdlib.h> /* malloc */
#include <time.h> /* time_t */
#include <assert.h> /*assert*/

#include "task.h"

struct Task 
{
	ilrd_uid_t task_id;
	int (*op_func)(void *); 
	void *op_param;
	time_t time_to_run;
	size_t interval_in_sec;
	void (*task_cleanup)(void *);
	void *cleanup_param;
};

task_t *TaskCreate(int (*op_func)(void *), void *param, 
				   size_t delay_in_sec, size_t interval_in_sec, 
				   void (*task_cleanup)(void *), void *cleanup_param)
{
	task_t *new_task = NULL;
	
	assert(NULL != op_func);
	
	new_task = (task_t *)malloc(sizeof(task_t));
	if (NULL == new_task)
	{
		return (NULL);
	}
	
	new_task->task_id = UIDCreate();
	if (UIDIsSame(UIDBadUID, TaskGetUID(new_task)))
	{
		free(new_task);
		return (NULL);
	}
	
	new_task->op_func = op_func; 
	new_task->op_param = param;
	new_task->time_to_run = time(NULL) + (time_t)delay_in_sec;
	new_task->interval_in_sec = interval_in_sec;
	new_task->task_cleanup = task_cleanup;
	new_task->cleanup_param = cleanup_param;
	
	return (new_task);
	
}

void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	
	free(task);
}

ilrd_uid_t TaskGetUID(const task_t *task)
{
	assert(NULL != task);
	
	return (task->task_id);
}

time_t TaskGetTimeToRun(const task_t *task)
{
	assert(NULL != task);
	
	return (task->time_to_run);
}

int TaskUpdateTimeToRun(task_t *task)
{
	assert(NULL != task);
	
	task->time_to_run += (time_t)task->interval_in_sec;
	
	return (REPEAT);
}

int TaskRun(task_t *task)
{
	int to_repeat = REPEAT; 
	
	assert(NULL != task);
	
	to_repeat = task->op_func(task->op_param);
	
	if (NULL != task->task_cleanup)
	{
		task->task_cleanup(task->cleanup_param);	
	}
	
	return (to_repeat);
}

int TaskIsBefore(const task_t *to_check, const task_t *check_against)
{
	assert(NULL != to_check);
	assert(NULL != check_against);
	
	return (TaskGetTimeToRun(to_check) <  TaskGetTimeToRun(check_against));
}

int TaskIsMatch(const task_t *task1, ilrd_uid_t uid)
{
	assert(NULL != task1);
	
	return (UIDIsSame(TaskGetUID(task1), uid)); 
}


