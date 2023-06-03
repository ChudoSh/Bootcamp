#make a funciton that makes a generic swap

void SwapGeneric(void *a, void *b, size_t size) /*O(1)*/
{
	char temp = '\0';
	
	assert(NULL != a);
	assert(NULL != b);
	
	while (0 < size)
	{
		 temp = *(char *)a; 
		 *(char *)a = *(char *)b;
		 *(char *)b = *temp;
		 
		 ++((char *)a);
		 ++((char *)b);
		 --(size);
	}
} 

typedef struct Queue
{
	stack_t *push;
	stack_t *pop;
}queue_t;


int EnQueue(queue *q, void *data) 
{
	assert(NULL != q);
	
	return (StackPush(q->push, data)); 
}

void *DeQueue(queue *q) 
{
	assert(NULL != q);
	
	if (StackIsEmpty(p->pop))
	{
		while (!StackIsEmpty(q->push))
		{
			StackPush(q->pop, StackPop(q->push)); 
		}
	}
	
	return (StackPop(q->pop)); 
}

typedef struct Bingo
{
	
};


