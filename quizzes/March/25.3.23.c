#include <stdio.h>

int IsSumFound(int *start, int *end, int sum, int *arr, size_t size)
{		

	if(NULL == start || NULL == end)
	{
		return 0; 	
	}
	
	start = arr; 
	end = (arr + size) - 1;
 
	
	
	while(start != end)
	{
		if (sum < (*start + *end))
		{
			--end;
		}
		
		else if (sum > (*start + *end))
		{
			++start; 
		}
		
		else
		{
			return 1;
		}
	}
	
	return 0;
	
}


int main()
{
	int arr[6] = {2, 8, 12, 15, 17, 19};
	int sum = 14; 
	int *start = arr;
	int *end = arr;
	
	if(IsSumFound(start,end,sum,arr,6))
	{
		printf("Success\n");
	}
	else
	{
		printf("Fail\n");
		
	}
	
	return 0;

}
