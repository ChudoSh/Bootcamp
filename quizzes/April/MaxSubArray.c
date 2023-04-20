#include <stdio.h> 
#include <assert.h>

int MaxSumArray(int *arr, size_t size, int *start, int *end);

int main()
{
	int arr[9] = {3, 1, -3, 4, -1, 2, 3, -5, 4}; 
	int start = 0; 
	int end = 0; 
	int sum = MaxSumArray(arr, 9, &start, &end);
	
	printf("%d, %d, %d\n",sum, start, end);
		
	return 0;
}

int MaxSumArray(int *arr, size_t size, int *start, int *end)
{
	size_t runner = 0;
	int left_pos = 0; 
	int right_pos = 0;
	int check_sum = 0; 
	int max_sum = 0;
	
	assert(NULL != arr);
	assert(NULL != start); 
	assert(NULL != end);  
	
	while (0 > arr[runner])
	{
		++runner;
	}
	
	left_pos = runner; 
	right_pos = runner; 
	*start = runner;
	*end = runner;
	
	while (runner < size)
	{
		if (0 <= arr[runner]) 
		{ 
			right_pos = runner;
			
			if (arr[runner] >= check_sum + arr[runner])
			{
				check_sum = 0;
				left_pos = runner; 
			}
		}
		
		else
		{				
			max_sum = check_sum;
			*start = left_pos;
			*end = right_pos; 				
		}
		
		check_sum += arr[runner];
		++runner;		
	}
	
	if (max_sum < check_sum)
	{
		max_sum = check_sum;
		*start = left_pos;
		*end = right_pos; 	
	}
		
	return max_sum; 	
}


