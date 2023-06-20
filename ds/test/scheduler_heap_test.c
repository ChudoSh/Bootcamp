/*
Dev: BarSH
Rev: 
Status: Test impl.
Date: 19.5.23
*/

#include <stdio.h> /* printf */
#include <stddef.h> /*size_t*/

#include "scheduler_heap.h"

#define SUCCESS (0)

void BasicFunctionTest();
static int FuncForTask(void *data);
static void Test(int val, const char *func, int line);
static int FuncToStop(void *data);
static int PrintStuff(void *print_me);
static int PrintStuffTwice(void *print_me);
static void PrintStoff(void *print_me);
static int StopRun(void *sched);
static int UnAlive(void *kill_me);
void SchedulerTest1(); 
void SchedulerTest2(); 
void SchedulerTest3(); 


int main()
{
	BasicFunctionTest();
	/*SchedulerTest1();
	SchedulerTest2();
	SchedulerTest3();*/
	return (0);
}

void BasicFunctionTest()
{
	scheduler_t *scheduler = SchedulerCreate();
	size_t test_count = 0;
	
	ilrd_uid_t id[6] = {0};
	
	printf("Scheduler basic functions tests\n");
	printf("_Line__Name____________Status_\n");
	
	Test(SchedulerIsEmpty(scheduler), "IsEmpty", __LINE__);
	
	id[0] = SchedulerAddTask(scheduler, FuncForTask, &test_count, 10, 1, NULL, NULL);
	id[1] = SchedulerAddTask(scheduler, FuncForTask, &test_count, 15, 1, NULL, NULL);
	id[2] = SchedulerAddTask(scheduler, FuncForTask, &test_count, 20, 1, NULL, NULL);
	id[3] = SchedulerAddTask(scheduler, FuncForTask, &test_count, 25, 1, NULL, NULL);
	id[4] = SchedulerAddTask(scheduler, FuncForTask, &test_count, 30, 1, (void (*)(void *))(SchedulerStop), scheduler);
	id[5] = SchedulerAddTask(scheduler, FuncForTask, &test_count, 35, 1, NULL, NULL);
	
	Test(6 == SchedulerSize(scheduler), "AddTask & Size", __LINE__);
	
	SchedulerRemoveTask(scheduler, id[5]);
	
	Test(5 == SchedulerSize(scheduler), "Remove", __LINE__);

	SchedulerRun(scheduler);
	
	Test(25 == test_count, "Scheduler Run", __LINE__);
	
	id[0] = SchedulerAddTask(scheduler, FuncForTask, &test_count, 5, 1, NULL, NULL);
	id[1] = SchedulerAddTask(scheduler, FuncForTask, &test_count, 6, 1, NULL, NULL);
	id[2] = SchedulerAddTask(scheduler, FuncForTask, &test_count, 7, 1, NULL, NULL);
	id[3] = SchedulerAddTask(scheduler, FuncForTask, &test_count, 8, 1, NULL, NULL);
	id[4] = SchedulerAddTask(scheduler, FuncForTask, &scheduler, 9, 1, NULL, NULL);
	id[5] = SchedulerAddTask(scheduler, FuncForTask, &test_count, 10, 1, NULL, NULL);
	
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
	(*((size_t *)data)) += 5;
	return (1);
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
void SchedulerTest1()
{
	scheduler_t *moo = SchedulerCreate();
	Test(0 == SchedulerSize(moo), "Size 0", __LINE__);
	Test(SchedulerIsEmpty(moo), "IsEmpty", __LINE__);
	Test(SUCCESS == SchedulerRun(moo), "Run empty", __LINE__);
	SchedulerDestroy(moo);
}

void SchedulerTest2()
{
	char *print = "Hi!";
	char *pront = "Bye!";
	ilrd_uid_t id4 = {0};
	scheduler_t *moo = SchedulerCreate();
	Test(0 == SchedulerSize(moo), "Size 0", __LINE__);
	
	SchedulerAddTask(moo, PrintStuff, "Potato!", 10, 15, PrintStoff, pront);
	Test(1 == SchedulerSize(moo), "Size 1", __LINE__);
	
	SchedulerAddTask(moo, PrintStuff, print, 20, 0, PrintStoff, pront);
	Test(2 == SchedulerSize(moo), "Size 2", __LINE__);
	
	SchedulerAddTask(moo, StopRun, moo, 30, 0, PrintStoff, pront);
	Test(3 == SchedulerSize(moo), "Size 3", __LINE__);
	
	id4 = SchedulerAddTask(moo, PrintStuff, "Potato!", 40, 0, PrintStoff, pront);
	Test(4 == SchedulerSize(moo), "Size 4", __LINE__);

	Test(!SchedulerIsEmpty(moo), "Not empty", __LINE__);
	
	Test(STOPPED == SchedulerRun(moo), "Run stopped", __LINE__);
	
	Test(1 == SchedulerSize(moo), "Size after stop", __LINE__);
	
	Test(SUCCESS == SchedulerRemoveTask(moo, id4), "remove", __LINE__);
	
	Test(0 == SchedulerSize(moo), "Remove task", __LINE__);
	
	SchedulerAddTask(moo, PrintStuff, "Potato!", 10, 15, PrintStoff, pront);
	SchedulerAddTask(moo, PrintStuff, print, 20, 0, PrintStoff, pront);
	SchedulerAddTask(moo, StopRun, moo, 30, 0, PrintStoff, pront);
	SchedulerAddTask(moo, PrintStuff, "Potato!", 40, 0, PrintStoff, pront);
	Test(4 == SchedulerSize(moo), "Add 4 tasks", __LINE__);
	
	SchedulerClear(moo);
	Test(0 == SchedulerSize(moo), "Clear", __LINE__);

	SchedulerDestroy(moo);
}

void SchedulerTest3()
{
	char *pront = "Bye!";
	scheduler_t *moo = SchedulerCreate();
		
	SchedulerAddTask(moo, PrintStuffTwice, "Potato!", 10, 5, PrintStoff, pront);
	SchedulerAddTask(moo, StopRun, moo, 20, 0, PrintStoff, pront);
	Test(STOPPED == SchedulerRun(moo), "Several runs", __LINE__);
	
	SchedulerDestroy(moo);
}

static int PrintStuff(void *print_me)
{
	printf("%s\n", (char *)print_me);
	return (DO_NOT_REPEAT);
}

static int PrintStuffTwice(void *print_me)
{
	printf("%s\n", (char *)print_me);
	return (REPEAT);
}

static void PrintStoff(void *print_me)
{
	printf("%s\n", (char *)print_me);
}

static int UnAlive(void *kill_me)
{
	TaskDestroy((task_t *)kill_me);
	return (DO_NOT_REPEAT);
}

static int StopRun(void *sched)
{
	SchedulerStop((scheduler_t *)sched);
	return (DO_NOT_REPEAT);
}

