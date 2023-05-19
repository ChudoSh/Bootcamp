/*
Dev: BarSH
Rev: 
Status: 
Date: 18.5.23
*/

#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <string.h> /* strcpy */
#include <time.h> /* time_t */
#include <stdlib.h>

#include "task.h"

#define SUCCESS (0)

struct some_struct
{
	int a;
	double b;
	void *c;
};

void BasicFunctionTest();
static int FuncForTask(void *data);
static void CleanForTask(void *data);
static void PrintUID(ilrd_uid_t uid);
static void Test(int val, const char *func, int line);

static void UnitTestCreateAndDestroy();
static void UnitTestChangeTime();
static void UnitTestCheckTasksAreDifferent();
static void	UnitTestRunWithCleanUp();

int HelloUser(void *user_name);
int StopOperation(void *scheduler);
int CreateStruct(void *some_struc);
void DestoryStruct(void *some_struc);

static void PrintMessage(const char *message);
static void PrintSuccess();
static void PrintFailure();
static void CheckSuccessOrFailure(int to_check);

int main()
{	
	BasicFunctionTest();
	UnitTestCreateAndDestroy();
	UnitTestChangeTime();
	UnitTestCheckTasksAreDifferent();
 	UnitTestRunWithCleanUp();
	return (0);
}

void BasicFunctionTest()
{
	char *stop = "Stopping";
	char *run = "Fucntion works";
	
	task_t *task1 = TaskCreate(FuncForTask, run, 5, 10, CleanForTask, stop);
	task_t *task2 = TaskCreate(FuncForTask, run, 10, 20, CleanForTask, stop);
	
	printf("Basic Functions tests\n");
	
	PrintUID(TaskGetUID(task1));
	
	printf("TaskGetTimeToRun: The time to run is :%ld\n",TaskGetTimeToRun(task1));
	printf("TaskGetTimeToRun: The time to run is :%ld\n",TaskGetTimeToRun(task2));
	
	Test(1 == TaskIsBefore(task1, task2), "TaskIsBefore", __LINE__);
	
	
	TaskUpdateTimeToRun(task1);
	printf("TaskUpdateTimeToRun: The time to run is  5 + 10:%ld\n",TaskGetTimeToRun(task1));
	
	TaskRun(task1);
	
	Test(0 == TaskIsMatch(task1, TaskGetUID(task2)), "TaskIsMatch", __LINE__);
	
	TaskDestroy(task1);
	TaskDestroy(task2);	
}

static int FuncForTask(void *data)
{
	printf("%s\n", (char *)data);
	return (0);
}
static void CleanForTask(void *data)
{
	printf("%s\n", (char *)data);
}

static void PrintUID(ilrd_uid_t uid)
{
	printf("This is the count of the uid: %lu \n", uid.counter);
	printf("This is the PID of the uid: %d \n", uid.pid);
	printf("This is the timestamp of the uid: %lu \n", uid.time);
	printf("This is the ip of the uid: %s \n", uid.ip);
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
static void UnitTestCreateAndDestroy()
{
	task_t *task = TaskCreate(&HelloUser, "Ido", 10, 0, NULL, NULL);
	PrintMessage("Testing Create and Destroy");

	printf("Verify correct uid\n");
	CheckSuccessOrFailure(!UIDIsSame(UIDBadUID,TaskGetUID(task)));

	printf("Verify time to run\n");
	CheckSuccessOrFailure(TaskGetTimeToRun(task) == time(NULL) + 10);

	printf("Run task\n");
	TaskRun(task); 

	TaskDestroy(task);
}

static void UnitTestChangeTime()
{
	task_t *task1 = TaskCreate(&HelloUser, "Ido", 10, 30, NULL, NULL);
	task_t *task2 = TaskCreate(&HelloUser, "Buddy", 30, 0, NULL, NULL);
	PrintMessage("Testing changing time");

	printf("Verify first task is before second: \n");
	CheckSuccessOrFailure(1 == TaskIsBefore(task1, task2));

	printf("Change tasks times: \n");
	TaskUpdateTimeToRun(task1);

	printf("Verify first task is after second: \n");
	CheckSuccessOrFailure(0 == TaskIsBefore(task1, task2));

	printf("Run tasks\n");
	TaskRun(task1); 
	TaskRun(task2); 

	TaskDestroy(task1);
	TaskDestroy(task2);
}

static void UnitTestCheckTasksAreDifferent()
{
	task_t *task1 = TaskCreate(&HelloUser, "Ido", 10, 30, NULL, NULL);
	task_t *task2 = TaskCreate(&HelloUser, "Buddy", 30, 0, NULL, NULL);
	PrintMessage("testing diffrent times");

	printf("Check first task is not second task: ");
	CheckSuccessOrFailure(0 == TaskIsMatch(task1, TaskGetUID(task2)));

	printf("Check first task is first task: ");
	CheckSuccessOrFailure(1 == TaskIsMatch(task1, TaskGetUID(task1)));

	TaskRun(task1); 
	TaskRun(task2); 

	TaskDestroy(task1);
	TaskDestroy(task2);
}

static void	UnitTestRunWithCleanUp()
{
	task_t *task = NULL;
	struct some_struct *some_struc = NULL;
	PrintMessage("testing run with cleanup");
	task = TaskCreate(&CreateStruct, &some_struc, 10, 0,
			 &DestoryStruct, &some_struc);

	printf("Run task\n");
	TaskRun(task); 

	TaskDestroy(task);
}

/*Operations*/
int HelloUser(void *user_name)
{
	printf("Hello %s!!!\n", (char *)user_name);
	
	return (SUCCESS);
}

int CreateStruct(void *some_struc)
{
	*(struct some_struct **)some_struc = malloc(sizeof(struct some_struct));
	if( NULL == some_struc)
	{
		return (DO_NOT_REPEAT);
	}

	printf("Struct created\n");

	return (REPEAT);
}

void DestoryStruct(void *some_struc)
{
	printf("Struct is destroyed\n");

	free(*(struct some_struct **)some_struc);
}


/*Used Functions*/
static void PrintMessage(const char *message)
{
	printf("\n\n\033[0;35m----- %s -----\033[0m\n", message);
}

static void PrintSuccess()
{
  	printf("\033[0;32m");
	printf("Success");
  	printf("\033[0m");
  	printf("\n");
}

static void PrintFailure()
{
	printf("\033[1;31m");
	printf("Failure");
  	printf("\033[0m");
  	printf("\n");
}

static void CheckSuccessOrFailure(int to_check)
{
	to_check ? PrintSuccess() : PrintFailure();
}



