#include <stdio.h>

int Bursa(int *buy, int *sell, int *arr, size_t size)
{		
    size_t high = 0;
    size_t low = 0;
    int profit = 0; 
    
	if(NULL == arr)
	{
		return -1; 	
	}
  
	while(high < size)
	{
		 
		if(arr[low] > arr[high])
		{
		   low = high; 
		}
		
	    if((arr[high] - arr[low]) > profit)
		{
		    profit = (arr[high] - arr[low]); 
            *sell = high;
		    *buy = low;      	
		}
		
		++high;					
	}
	
	return profit;	
}


int main()
{
	int arr[4] = {3, 2, 100, 0}; 
	int buy = 0;
	int sell = 0;
	int result = Bursa(&buy, &sell, arr, 4);
	 
	printf("profit is %d ,to buy is at %d and to sell is at %d\n", result, buy, sell);
	
	
	return 0;
}
