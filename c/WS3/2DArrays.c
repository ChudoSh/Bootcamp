/*******

Dev: BarSH
Rev: EtaiSH
Status: Approved
Date: 26.3.23

*******/


#include <stdio.h>/*printf*/

void Sum2DArray(int a[][2], int *sum);

int main()
{	 
	int arr[4][2] = {{2,3},{5,6}, {2,6}, {2,45}};
    int sum[4] = {0};
    int i = 0;

	Sum2DArray(arr, sum);

    for(i = 0; i < 4;++i)
    {
        printf("%d\n", sum[i]);
    }
    
	return 0;
}


void Sum2DArray(int a[][2], int sum[])
{
	int i = 0;
	int j = 0;
	
	if(NULL != sum)
	{
		for(i = 0; i < 4; ++i)
		{
			for(j = 0; j < 2; ++j)
			{
				sum[i] += a[i][j];		
			}
		}
	}
}



