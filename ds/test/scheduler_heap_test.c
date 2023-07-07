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
	scheduler_t *scheduler = HSchedulerCreate();
	size_t test_count = 0;
	
	ilrd_uid_t id[6] = {0};
	
	printf("Scheduler basic functions tests\n");
	printf("_Line__Name____________Status_\n");
	
	Test(HSchedulerIsEmpty(scheduler), "IsEmpty", __LINE__);
	
	id[0] = HSchedulerAddTask(scheduler, FuncForTask, &test_count, 10, 1, NULL, NULL);
	id[1] = HSchedulerAddTask(scheduler, FuncForTask, &test_count, 15, 1, NULL, NULL);
	id[2] = HSchedulerAddTask(scheduler, FuncForTask, &test_count, 20, 1, NULL, NULL);
	id[3] = HSchedulerAddTask(scheduler, FuncForTask, &test_count, 25, 1, NULL, NULL);
	id[4] = HSchedulerAddTask(scheduler, FuncForTask, &test_count, 30, 1, (void (*)(void *))(HSchedulerStop), scheduler);
	id[5] = HSchedulerAddTask(scheduler, FuncForTask, &test_count, 35, 1, NULL, NULL);
	
	Test(6 == HSchedulerSize(scheduler), "AddTask & Size", __LINE__);
	
	HSchedulerRemoveTask(scheduler, id[5]);
	
	Test(5 == HSchedulerSize(scheduler), "Remove", __LINE__);

	HSchedulerRun(scheduler);
	
	Test(25 == test_count, "Scheduler Run", __LINE__);
	
	id[0] = HSchedulerAddTask(scheduler, FuncForTask, &test_count, 5, 1, NULL, NULL);
	id[1] = HSchedulerAddTask(scheduler, FuncForTask, &test_count, 6, 1, NULL, NULL);
	id[2] = HSchedulerAddTask(scheduler, FuncForTask, &test_count, 7, 1, NULL, NULL);
	id[3] = HSchedulerAddTask(scheduler, FuncForTask, &test_count, 8, 1, NULL, NULL);
	id[4] = HSchedulerAddTask(scheduler, FuncForTask, &scheduler, 9, 1, NULL, NULL);
	id[5] = HSchedulerAddTask(scheduler, FuncForTask, &test_count, 10, 1, NULL, NULL);
	
	HSchedulerClear(scheduler);
	
	Test(0 == HSchedulerSize(scheduler), "Clear", __LINE__);
	
	HSchedulerDestroy(scheduler);	
}

static int FuncToStop(void *data)
{
	HSchedulerStop((scheduler_t *)data);
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
	scheduler_t *moo = HSchedulerCreate();
	Test(0 == HSchedulerSize(moo), "Size 0", __LINE__);
	Test(HSchedulerIsEmpty(moo), "IsEmpty", __LINE__);
	Test(SUCCESS == HSchedulerRun(moo), "Run empty", __LINE__);
	HSchedulerDestroy(moo);
}

void SchedulerTest2()
{
	char *print = "Hi!";
	char *pront = "Bye!";
	ilrd_uid_t id4 = {0};
	scheduler_t *moo = HSchedulerCreate();
	Test(0 == HSchedulerSize(moo), "Size 0", __LINE__);
	
	HSchedulerAddTask(moo, PrintStuff, "Potato!", 10, 15, PrintStoff, pront);
	Test(1 == HSchedulerSize(moo), "Size 1", __LINE__);
	
	HSchedulerAddTask(moo, PrintStuff, print, 20, 0, PrintStoff, pront);
	Test(2 == HSchedulerSize(moo), "Size 2", __LINE__);
	
	HSchedulerAddTask(moo, StopRun, moo, 30, 0, PrintStoff, pront);
	Test(3 == HSchedulerSize(moo), "Size 3", __LINE__);
	
	id4 = HSchedulerAddTask(moo, PrintStuff, "Potato!", 40, 0, PrintStoff, pront);
	Test(4 == HSchedulerSize(moo), "Size 4", __LINE__);

	Test(!HSchedulerIsEmpty(moo), "Not empty", __LINE__);
	
	Test(STOPPED == HSchedulerRun(moo), "Run stopped", __LINE__);
	
	Test(1 == HSchedulerSize(moo), "Size after stop", __LINE__);
	
	Test(SUCCESS == HSchedulerRemoveTask(moo, id4), "remove", __LINE__);
	
	Test(0 == HSchedulerSize(moo), "Remove task", __LINE__);
	
	HSchedulerAddTask(moo, PrintStuff, "Potato!", 10, 15, PrintStoff, pront);
	HSchedulerAddTask(moo, PrintStuff, print, 20, 0, PrintStoff, pront);
	HSchedulerAddTask(moo, StopRun, moo, 30, 0, PrintStoff, pront);
	HSchedulerAddTask(moo, PrintStuff, "Potato!", 40, 0, PrintStoff, pront);
	Test(4 == HSchedulerSize(moo), "Add 4 tasks", __LINE__);
	
	HSchedulerClear(moo);
	Test(0 == HSchedulerSize(moo), "Clear", __LINE__);

	HSchedulerDestroy(moo);
}

void SchedulerTest3()
{
	char *pront = "Bye!";
	scheduler_t *moo = HSchedulerCreate();
		
	HSchedulerAddTask(moo, PrintStuffTwice, "Potato!", 10, 5, PrintStoff, pront);
	HSchedulerAddTask(moo, StopRun, moo, 20, 0, PrintStoff, pront);
	Test(STOPPED == HSchedulerRun(moo), "Several runs", __LINE__);
	
	HSchedulerDestroy(moo);
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
	HSchedulerStop((scheduler_t *)sched);
	return (DO_NOT_REPEAT);
}

