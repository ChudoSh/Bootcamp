/*
Dev: BarSH
Rev: EtaiSH
Status: Approved
Date: 3.5.23
*/

#include <stdio.h> /*printf*/
#include <string.h> /*strncmp*/


#include "cbuffer.h"

static void UnitTest1();
static void UnitTest2();
static void UnitTest3();
static void UnitTest4();
static void UnitTest5();
static void UnitTest6();
static void UnitTest7();
static void UnitTest8();
static void UnitTest9();

static void PrintMessage(const char *message);
static void PrintSuccess();
static void PrintFailure();

int main()
{
	UnitTest1();
	UnitTest2();
	UnitTest3();
	UnitTest4();
	UnitTest5();
	UnitTest6();
	UnitTest7();
	UnitTest8();
	UnitTest9();

	return(0);
}


static void UnitTest1()
{
	cbuff_t *buff = NULL;
	size_t capacity = 1;	
	
	PrintMessage("Test Create and destroy:");

	buff = CBuffCreate(capacity);

	CBuffDestroy(buff);

	PrintSuccess();
}

static void UnitTest2()
{
	cbuff_t *buff = NULL;
	size_t capacity = 3;	
	
	PrintMessage("Test CBIsEmpty when empty, CBFreeSpace when empty, and CBCapacaity:");

	buff = CBuffCreate(capacity);

	(capacity == CBuffCapacity(buff)) ? PrintSuccess(): PrintFailure();
	(capacity == CBuffFreeSpace(buff)) ? PrintSuccess(): PrintFailure();
	CBuffIsEmpty(buff) ? PrintSuccess(): PrintFailure();

	CBuffDestroy(buff);
}

static void UnitTest3()
{
	cbuff_t *buff = NULL;
	size_t capacity = 1000;	
	const char *to_write = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	PrintMessage("Test CBWrite large buffer and CBFreeSpace when not empty, and CBCapacaity:");

	buff = CBuffCreate(capacity);
	printf("CBWrite:");
	10 == CBuffWrite(buff, to_write, 10) ? PrintSuccess():PrintFailure();

	printf("CBCapacity:");
	1000 == CBuffCapacity(buff) ? PrintSuccess():PrintFailure();
	printf("CBFreeSpace:");
	1000-10 == CBuffFreeSpace(buff) ? PrintSuccess():PrintFailure();
	printf("CBIsEmpty:");
	CBuffIsEmpty(buff) ? PrintFailure():PrintSuccess();

	CBuffDestroy(buff);
}

static void UnitTest4()
{
	cbuff_t *buff = NULL;
	size_t capacity = 5;	
	const char *to_write = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	PrintMessage("Test CBWrite small buffer :");

	buff = CBuffCreate(capacity);
	printf("CBWrite:");
	5 == CBuffWrite(buff, to_write, 10) ? PrintSuccess():PrintFailure();

	CBuffDestroy(buff);
}

static void UnitTest5()
{
	cbuff_t *buff = NULL;
	size_t capacity = 5;	
	const char *to_write = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	PrintMessage("Test CBWrite Full buffer :");

	buff = CBuffCreate(capacity);

	printf("First write:");
	5 == CBuffWrite(buff, to_write, 10) ? PrintSuccess():PrintFailure();
	printf("Second write(full buffer):");
	-1 == CBuffWrite(buff, to_write, 10) ? PrintSuccess():PrintFailure();

	CBuffDestroy(buff);
}

static void UnitTest6()
{
	cbuff_t *buff = NULL;
	size_t capacity = 100;
	const char *to_write = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char dest[100] = "\0";

	PrintMessage("Test CBRead large buffer:");

	buff = CBuffCreate(capacity);

	CBuffWrite(buff, to_write, 30);
	printf("Read gives:");	
	10 == CBuffRead(buff, dest, 10) ? PrintSuccess():PrintFailure();
	printf("Check destination recived:");	
	strncmp(dest, to_write, 10) ? PrintFailure() : PrintSuccess();

	CBuffDestroy(buff);
}

static void UnitTest7()
{
	cbuff_t *buff = NULL;
	size_t capacity = 100;
	const char *to_write = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char dest[100] = "\0";

	PrintMessage("Test size after read:");

	buff = CBuffCreate(capacity);

	CBuffWrite(buff, to_write, 30);
	CBuffRead(buff, dest, 5);
	printf("Check free space:");	
	100-25 == CBuffFreeSpace(buff) ? PrintSuccess():PrintFailure();

	CBuffDestroy(buff);
}

static void UnitTest8()
{
	cbuff_t *buff = NULL;
	size_t capacity = 100;
	char dest[100] = "\0";

	PrintMessage("Test Read from empty:");

	buff = CBuffCreate(capacity);

	printf("Read from empty:");	
	-1 == CBuffRead(buff, dest, 10) ? PrintSuccess():PrintFailure();


	CBuffDestroy(buff);
}

static void UnitTest9()
{
	cbuff_t *buff = NULL;
	size_t capacity = 5;
	char dest[100] = "\0";	
	const char *to_write = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	PrintMessage("Test CBRead small buffer :");

	buff = CBuffCreate(capacity);
	5 == CBuffWrite(buff, to_write, 5) ? PrintSuccess():PrintFailure();
	printf("Read from small:");	
	5 == CBuffRead(buff, dest, 10) ? PrintSuccess():PrintFailure();
	printf("Read from emptied:");	
	-1 == CBuffRead(buff, dest, 10) ? PrintSuccess():PrintFailure();
	printf("%s\n", dest);
	
	CBuffDestroy(buff);
}

static void PrintMessage(const char *message)
{
	printf("\n----- %s -----\n", message);
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
