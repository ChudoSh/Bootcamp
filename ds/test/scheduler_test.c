/*
Dev: BarSH
Rev: 
Status: Test impl.
Date: 19.5.23
*/

#include <stdio.h> /* printf */
#include <stddef.h> /*size_t*/

#include "scheduler.h"

#define SUCCESS (0)

void BasicFunctionTest();
static int FuncForTask(void *data);
static void CleanForTask(void *data);
static void Test(int val, const char *func, int line);
static int FuncToStop(void *data);

int main()
{	
	BasicFunctionTest();
	return (0);
}

void BasicFunctionTest()
{
	scheduler_t *scheduler = SchedulerCreate();
	size_t test_count = 0;
	char *done = "SchedulerRun \033[1;33mTask Finish\033[0m";
	char *run = "SchedulerRun \033[1;32mSuccess\033[0m";
	char *stop = "SchedulerRun \033[1;31mStopped\033[0m";
	
	ilrd_uid_t id[6] = {0};
	
	printf("Scheduler basic functions tests\n");
	printf("_Line__Name____________Status_\n");
	
	Test(SchedulerIsEmpty(scheduler), "Create & IsEmpty", __LINE__);
	
	id[0] = SchedulerAddTask(scheduler, FuncForTask, &test_count, 10, 1, CleanForTask, done);
	id[1] = SchedulerAddTask(scheduler, FuncForTask, &test_count, 11, 1, CleanForTask, done);
	id[2] = SchedulerAddTask(scheduler, FuncForTask, &test_count, 12, 1, CleanForTask, done);
	id[3] = SchedulerAddTask(scheduler, FuncForTask, &test_count, 13, 1, CleanForTask, done);
	id[4] = SchedulerAddTask(scheduler, FuncToStop, scheduler, 14, 1, CleanForTask, stop);
	id[5] = SchedulerAddTask(scheduler, FuncForTask, &test_count, 15, 1, CleanForTask, done);
	
	Test(6 == SchedulerSize(scheduler), "AddTask & Size", __LINE__);
	
	SchedulerRemoveTask(scheduler, id[5]);
	
	Test(5 == SchedulerSize(scheduler), "Remove", __LINE__);
	
	SchedulerRun(scheduler);
	
	Test(4 == test_count, "Scheduler Run", __LINE__);
	
	id[0] = SchedulerAddTask(scheduler, FuncForTask, run, 10, 1, CleanForTask, done);
	id[1] = SchedulerAddTask(scheduler, FuncForTask, run, 11, 1, CleanForTask, done);
	id[2] = SchedulerAddTask(scheduler, FuncForTask, run, 12, 1, CleanForTask, done);
	id[3] = SchedulerAddTask(scheduler, FuncForTask, run, 13, 1, CleanForTask, done);
	id[4] = SchedulerAddTask(scheduler, FuncToStop, scheduler, 14, 1, CleanForTask, stop);
	id[5] = SchedulerAddTask(scheduler, FuncForTask, run, 15, 1, CleanForTask, done);
	
	SchedulerClear(scheduler);
	
	Test(0 == SchedulerSize(scheduler), "Clear", __LINE__);
	
	SchedulerDestroy(scheduler);	
}

static int FuncToStop(void *data)
{
	SchedulerStop((scheduler_t *)data);
	return (1);
}

static int FuncForTask(void *data)
{
	++(*((size_t *)data));
	return (1);
}
static void CleanForTask(void *data)
{
	 return;
}

static void Test(int val, const char *func, int line)
{
	char str2[47];
	char temp[17] = {'\0'};
	sprintf(temp, " %d       ", line);
	strncpy(str2, temp, strlen(temp));
	sprintf(temp, "         ");
	sprintf(temp, " %s               ", func);
	strncpy(&str2[6], temp, strlen(temp));
	
	if(val)
	{
		strcpy(&str2[23], "\033[1;32msuccess\033[0m");
	}
	else
	{
		strcpy(&str2[23], "\033[1;31mfail\033[0m");
	}
	
	printf("%s\n", str2);
}

