/*
Dev: BarSH
Rev: YaronM
Date: 2.5.23
Status: Approved
*/

#include <stdio.h>
#include <stddef.h> /* size_t, NULL */
#include "queue.h" /*slist_t*/
/*
#define FALSE (0)
#define TRUE (1)
int detailed_test_summary_flag = 1;

void testQueueA(void);
int TestIsMatchForAddress(void *expected_val, void *recived_val, size_t ck_id);
int TestIsMatchForInt(int expected_val, int recived_val, size_t ck_id);
int TestIsMatchForSizeT(size_t expected_val, size_t recived_val, size_t ck_id);

int main(void)
{
	printf("\033[1;94m");
	printf("\n\n----------------------------------\n");
	printf("initating testing program by Eylon\n");
	printf("testing queue\n");
	printf("----------------------------------\n\n\n");
	printf("\033[0;97m");
	
	testQueueA();

	return (0);
}




void testQueueA(void)
{
	int arr[10] = {0,1,2,3,4,5,6,7,8,9};
	int arr_sec[10] = {100,101,102,103,104,105,106,107,108,109};
	int i;
	int num_of_errors = 0;
	queue_t *q_a = NULL;
	queue_t *q_b = NULL;
	
	printf("\033[1;97m");
	printf("initiate test for SList sequence A\n");
	printf("\033[0;97m");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("testing:queue(check also with vlg)\n");
	
	
	q_a = QCreate();
	q_b = QCreate();
	
	for (i = 0 ; i < 10 ; ++i)
	{
		num_of_errors += TestIsMatchForSizeT(i, QSize(q_a), 2000+i);
		num_of_errors += TestIsMatchForSizeT(i, QSize(q_b), 2010+i);
		QEnqueue(q_a, &arr[i]);
		QEnqueue(q_b, &arr_sec[i]);	
	}
	num_of_errors += TestIsMatchForInt(FALSE, QIsEmpty(q_a), 7770);
	num_of_errors += TestIsMatchForInt(FALSE, QIsEmpty(q_b), 7771);
	
	for (i = 0 ; i < 10 ; ++i)
	{
		num_of_errors += TestIsMatchForSizeT(10 - i, QSize(q_a), 92100+i);
		num_of_errors += TestIsMatchForSizeT(10 - i, QSize(q_b), 92110+i);
		num_of_errors += TestIsMatchForAddress((void *)&arr[i], QPeek(q_a),1000+i);
		num_of_errors += TestIsMatchForAddress((void *)&arr_sec[i], QPeek(q_b),1010+i);	
		QDequeue(q_a);
		QDequeue(q_b);	
	}
	
	num_of_errors += TestIsMatchForInt(TRUE, QIsEmpty(q_a), 7772);
	num_of_errors += TestIsMatchForInt(TRUE, QIsEmpty(q_b), 7773);
	
	for (i = 0 ; i < 10 ; ++i)
	{
		num_of_errors += TestIsMatchForSizeT(i, QSize(q_a), 2200+i);
		num_of_errors += TestIsMatchForSizeT(i, QSize(q_b), 2210+i);
		QEnqueue(q_a, &arr[i]);
		QEnqueue(q_b, &arr_sec[i]);	
	}
	
	num_of_errors += TestIsMatchForInt(FALSE, QIsEmpty(q_a), 7774);
	num_of_errors += TestIsMatchForInt(FALSE, QIsEmpty(q_b), 7775);
	
	num_of_errors += TestIsMatchForSizeT(10, QSize(q_a), 1);
	num_of_errors += TestIsMatchForSizeT(10, QSize(q_b), 2);
	QAppend(q_a, q_b);
	num_of_errors += TestIsMatchForSizeT(20, QSize(q_a), 3);
	num_of_errors += TestIsMatchForSizeT(0, QSize(q_b), 4);
	
	num_of_errors += TestIsMatchForInt(FALSE, QIsEmpty(q_a), 7776);
	num_of_errors += TestIsMatchForInt(TRUE, QIsEmpty(q_b), 7777);
	
	for (i = 0 ; i < 10 ; ++i)
	{
		num_of_errors += TestIsMatchForSizeT(20 - i, QSize(q_a), 2300+i);
		num_of_errors += TestIsMatchForAddress((void *)&arr[i], QPeek(q_a),1100+i);
		QDequeue(q_a);		
	}
	
	num_of_errors += TestIsMatchForInt(FALSE, QIsEmpty(q_a), 7778);
	
	for (i = 0 ; i < 10 ; ++i)
	{
		num_of_errors += TestIsMatchForSizeT(10 - i, QSize(q_a), 2310+i);
		num_of_errors += TestIsMatchForAddress((void *)&arr_sec[i], QPeek(q_a),1110+i);
		QDequeue(q_a);	
	}
	
	num_of_errors += TestIsMatchForInt(TRUE, QIsEmpty(q_a), 7779);
	
	QDestroy(q_a);
	QDestroy(q_b);
	
	if(num_of_errors == 0)
	{
		printf("\033[1;32m");
		printf("success test is done!\n");
		printf("\033[0;97m");
	}
	else
	{
		printf("\033[1;31m");
		printf("recived failures while checking capacity and size changes with ints\nnum of errors:%d\n",num_of_errors);
		printf("\033[0;97m");
	}
	printf("\033[1;97m");
	printf("testing done!\n\n\n");
	printf("\033[0;97m");
	

	
}


int TestIsMatchForAddress(void *expected_val, void *recived_val, size_t ck_id)
{
	if (expected_val == recived_val)
	{
		if(detailed_test_summary_flag == 1)
		{
			printf("\033[0;32m");
			printf("Success on Check ID %ld:",ck_id);
			printf("expected value %p ;",expected_val);
			printf("recived value %p \n",recived_val);
			printf("\033[0;97m");
		}
		return (0);
	}
	
	printf("\033[1;31m");
	printf("fail on Check ID %ld:",ck_id);
	printf("expected value %p ;",expected_val);
	printf("recived value %p \n",recived_val);
	printf("\033[0;97m");
	
	return (1);
}

int TestIsMatchForInt(int expected_val, int recived_val, size_t ck_id)
{
	if (expected_val == recived_val)
	{
		if(detailed_test_summary_flag == 1)
		{
			printf("\033[0;32m");
			printf("Success on Check ID %ld:",ck_id);
			printf("expected value %d ;",expected_val);
			printf("recived value %d \n",recived_val);
			printf("\033[0;97m");
		}
		return (0);
	}
	
	printf("\033[1;31m");
	printf("fail on Check ID %ld:",ck_id);
	printf("expected value %d ;",expected_val);
	printf("recived value %d \n",recived_val);
	printf("\033[0;97m");
	
	return (1);
}

int TestIsMatchForSizeT(size_t expected_val, size_t recived_val, size_t ck_id)
{
	if (expected_val == recived_val)
	{
		if(detailed_test_summary_flag == 1)
		{
			printf("\033[0;32m");
			printf("Success on Check ID %ld:",ck_id);
			printf("expected value %ld ;",expected_val);
			printf("recived value %ld \n",recived_val);
			printf("\033[0;97m");
		}
		return (0);
	}
	
	printf("\033[1;31m");
	printf("fail on Check ID %ld:",ck_id);
	printf("expected value %ld ;",expected_val);
	printf("recived value %ld \n",recived_val);
	printf("\033[0;97m");
	
	return (1);
}*/

int main()
{
	int x = 5; 
	float a = 6;
	double b = 7;
	char u = 'A';
	int y = 10;
	
	queue_t *queue1 = QCreate();
	queue_t *queue2 = QCreate();
	
	QEnqueue(queue1, &x);
	if (x == *((int*)QPeek(queue1)))
	{
		printf("Test 1 for Enqueue & Peek successful!\n");
	}
	else
	{
		printf("Test 1 for Enqueue & Peek failed\n");
	}
	
	
	QEnqueue(queue1, &a);
	if (x == *((int*)QPeek(queue1)))
	{
		printf("Test 2 for Enqueue & Peek successful!\n");
	}
	else
	{
		printf("Test 2 for Enqueue & Peek failed\n");
	}
	
	
	QEnqueue(queue1, &b);
	if (x == *((int*)QPeek(queue1)))
	{
		printf("Test 3 for Enqueue & Peek successful!\n");
	}
	else
	{
		printf("Test 3 for Enqueue & Peek failed\n");
	}
	
	
	QEnqueue(queue1, &u);
	if (x == *((int*)QPeek(queue1)))
	{
		printf("Test 4 for Enqueue & Peek successful!\n");
	}
	else
	{
		printf("Test 4 for Enqueue & Peek failed\n");
	}

	if (0 != QIsEmpty(queue2))
	{
		printf("Test for QIsEmpty successful!\n");
	}
	else
	{
		printf("Test for QIsEmpty failed\n");
	}
	
	QEnqueue(queue2, &y);
	if (y == *((int*)QPeek(queue2)))
	{
		printf("Test 5 for Enqueue & Peek successful!\n");
	}
	else
	{
		printf("Test 5 for Enqueue & Peek failed\n");
	}
	
	
	if (1 == QSize(queue2))
	{
		printf("Test for QSize successful!\n");
	}
	else
	{
		printf("Test for QSize failed\n");
	}

	QAppend(queue1, queue2);
	
	if (5 == QSize(queue1) && 1 == QIsEmpty(queue2))
	{
		printf("Test for QAppend successful!\n");
	}
	
	else
	{
		printf("Test for  QAppend failed\n");
	}
	
	
	QDestroy(queue1);
	QDestroy(queue2);

	return (0);
}
/*
void *Action(void *value1, void *value2)
{
	printf("The value is: %d\n", *(int *)value1);
	(void)value2;
	return value1;
}

void QCreateTest();
void QSizeTest();
void QIsEmptyTest();
void QPeekTest();
void QEnqueueTest();
void QEnqueueTest();
void QDequeueTest();
void QAppendTest();


int main()
{	
	QCreateTest();	
	QSizeTest();
	QIsEmptyTest();
	QPeekTest();
	QEnqueueTest();
	QDequeueTest();
	QAppendTest();
	return 0;
}

void QAppendTest()
{
	size_t size1 = 0;
	size_t size2 = 0;
	int value1 = 1;
	int value2 = 2;
	int value3 = 3;
	int value4 = 4;
	int value5 = 5;
	int value6 = 6;
	int value7 = 7;
	int value8 = 8;
	int value9 = 9;
	
	queue_t *queue1 = NULL;
	queue_t *queue2 = NULL;
	queue1 = SListCreate();
	queue2 = SListCreate();
	
	QEnqueue(queue1, (const void *)&value1);
	QEnqueue(queue1, (const void *)&value2);
	QEnqueue(queue1, (const void *)&value3);
	QEnqueue(queue1, (const void *)&value4);
	QEnqueue(queue1, (const void *)&value5);
	QEnqueue(queue2, (const void *)&value6);
	QEnqueue(queue2, (const void *)&value7);
	QEnqueue(queue2, (const void *)&value8);
	QEnqueue(queue2, (const void *)&value9);
	
	QAppend(queue1, queue2);
	
	size1 = QSize((const queue_t *)queue1);
	size2 = QSize((const queue_t *)queue2);
	
	SListForEach(SListBegin((const slist_t *)queue1), SListEnd((const slist_t *)queue1), Action, (void *)&value1);
	
	
	if(9 == size1 && 0 == size2)
	{
		printf("QAppendTest pass\n");
	}
	else
	{
		printf("Size is: %ld\n", size1);
		printf("Size is: %ld\n", size2);
		printf("QAppendTest fail\n");
	}
	SListDestroy(queue1);
	SListDestroy(queue2);
}



void QCreateTest()
{
	queue_t *queue = NULL;
	iter_t iterator1 = NULL;
	iter_t iterator2 = NULL;
	
	queue = SListCreate();
	iterator1 = SListBegin(queue);
	iterator2 = SListEnd(queue);
	if(iterator1 == iterator2)
	{
		printf("QCreateTest pass\n");
	}
	else
	{
		printf("QCreateTest fail\n");
	}
	
	
	SListDestroy(queue);

}



void QSizeTest()
{

	
	queue_t *queue = NULL;
	iter_t iterator1 = NULL;
	int value = 1;
	int value1 = 2;
	size_t size1 = 0;
	size_t size2 = 0;
	size_t size3 = 0;
	queue = SListCreate();
	iterator1 = SListBegin(queue);
	size1 = QSize((const queue_t *)queue);
	iterator1 = SListInsert(iterator1, (void *)&value);
	size2 = QSize((const queue_t *)queue);
	iterator1 = SListInsert(iterator1, (void *)&value1);
	size3 = QSize((const queue_t *)queue);
	if(0 == size1 && 1 == size2 && 2 == size3 )
	{
		printf("QSizeTest pass\n");
	}
	else
	{
		printf("Size is: %ld\n", size1);
		printf("Size is: %ld\n", size2);
		printf("Size is: %ld\n", size3);
		printf("QSizeTest fail\n");
	}
	
	
	SListDestroy(queue);
}



void QIsEmptyTest()
{

	queue_t *queue = NULL;
	iter_t iterator1 = NULL;
	int value = 1;
	int value1 = 2;
	int status1 = 0;
	int status2 = 0;
	int status3 = 0;
	queue = SListCreate();
	iterator1 = SListBegin(queue);
	status1 = QIsEmpty((const queue_t *)queue);
	iterator1 = SListInsert(iterator1, (void *)&value);
	status2 = QIsEmpty((const queue_t *)queue);
	iterator1 = SListInsert(iterator1, (void *)&value1);
	status3 = QIsEmpty((const queue_t *)queue);
	if(1 == status1 && 0 == status2 && 0 == status3 )
	{
		printf("QIsEmptyTest pass\n");
	}
	else
	{
		printf("Size is: %d\n", status1);
		printf("Size is: %d\n", status2);
		printf("Size is: %d\n", status3);
		printf("QIsEmptyTest fail\n");
	}
	
	
	SListDestroy(queue);
}






void QPeekTest()
{

	queue_t *queue = NULL;
	iter_t iterator1 = NULL;
	int value = 1;
	int value1 = 2;
	int value2 = 3;
	void *result1 = NULL;
	void *result2 = NULL;
	void *result3 = NULL;
	queue = SListCreate();
	
	iterator1 = SListEnd(queue);
	iterator1 = SListInsert(iterator1, (void *)&value);
	result1 = SListGet(SListBegin((const slist_t *)queue));
	
	iterator1 = SListEnd(queue);
	iterator1 = SListInsert(iterator1, (void *)&value1);
	result2 = SListGet(SListBegin((const slist_t *)queue));
	iterator1 = SListEnd(queue);
	iterator1 = SListInsert(iterator1, (void *)&value2);
	result3 = SListGet(SListBegin((const slist_t *)queue));
	if(value == *(int *)result1 && value == *(int *)result2 && value == *(int *)result3 )
	{
		printf("QPeekTest pass\n");
	}
	else
	{
		printf("Size is: %d\n", *(int *)result1);
		printf("Size is: %d\n", *(int *)result2);
		printf("Size is: %d\n", *(int *)result3);
		printf("QPeekTest fail\n");
	}
	
	
	SListDestroy(queue);
}



void QEnqueueTest()
{
	queue_t *queue = NULL;
	iter_t iterator1 = NULL;
	void * changed_value1 = NULL;
	void * changed_value2 = NULL;
	void * changed_value3 = NULL;


	int value1 = 2;
	int value2 = 3;
	int value3 = 4;
	int status1 = 1;
	int status2 = 1;
	int status3 = 1;
	queue = SListCreate();
	
	
	
	
	status1 = QEnqueue(queue, (const void *)&value1);
	status2 = QEnqueue(queue, (const void *)&value2);
	status3 = QEnqueue(queue, (const void *)&value3);
	
	
	iterator1 = SListBegin(queue);
	changed_value1 = SListGet(iterator1);
	iterator1 = SListNext(iterator1);
	
	changed_value2 = SListGet(iterator1);
	iterator1 = SListNext(iterator1);
	
	
	changed_value3 = SListGet(iterator1);
	if(4 == *(int *)changed_value3 && 3 == *(int *)changed_value2 && 2 == *(int *)changed_value1 && 0 == status1 && 0 == status2 && 0 == status3)
	{
		printf("QEnqueueTest pass\n");	
	}
	else
	{
		printf("QEnqueueTest pass\n");
	}
	
	SListDestroy(queue);
}



void QDequeueTest()
{
	queue_t *queue = NULL;
	iter_t iterator1 = NULL;
	void * changed_value1 = NULL;
	void * changed_value2 = NULL;
	


	int value1 = 2;
	int value2 = 3;
	int value3 = 4;
	
	queue = SListCreate();
	iterator1 = SListEnd(queue);
	iterator1 = SListInsert(iterator1, (void *)&value1);
	SListSet(iterator1, (void *)&value1);
	
	iterator1 = SListEnd(queue);
	iterator1 = SListInsert(iterator1, (void *)&value2);
	SListSet(iterator1, (void *)&value2);
	
	iterator1 = SListEnd(queue);
	iterator1 = SListInsert(iterator1, (void *)&value3);
	SListSet(iterator1, (void *)&value3);
	iterator1 = SListBegin(queue);
	
	changed_value1 = SListGet(iterator1);
	iterator1 = SListNext(iterator1);
	
	changed_value2 = SListGet(iterator1);
	iterator1 = SListNext(iterator1);
	
	
	
	
	QDequeue(queue);
	iterator1 = SListBegin((const slist_t *)queue);
	changed_value1 = SListGet(iterator1);
	QDequeue(queue);
	iterator1 = SListBegin((const slist_t *)queue);
	changed_value2 = SListGet(iterator1);
	
	if(4 == *(int *)changed_value2 && 3 == *(int *)changed_value1)
	{
		printf("QDequeueTest pass\n");	
	}
	else
	{
		printf("QDequeueTest pass\n");
	}
	
	SListDestroy(queue);
}*/

