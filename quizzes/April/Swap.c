
void SwapBit(int *a, int *b)
{
	assert(NULL != a);
	assert(NULL != b);
	
	if (*a == *b)
	{
		return;
	}
	
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void SwapTemp(int *a, int *b)
{
	int *temp = NULL;
	
	assert(NULL != a);
	assert(NULL != b);
	
	if (*a == *b)
	{
		return;
	}
	
	*temp = *a;
	*a = *b;
	*b = *temp;
}

void SwapArith(int *a, int *b)
{
	assert(NULL != a);
	assert(NULL != b);
	
	if (*a == *b)
	{
		return;
	}
	
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

