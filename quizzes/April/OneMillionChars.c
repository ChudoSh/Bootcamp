#include <stdio.h>

#define ASCII_SIZE (256)

void OneMillionChars(char c);
int ReturnMaxOccurence(size_t *LUT);

int main()
{ 
	char arr[10] = {'a', 'b', 'c', 't', 'a', 'a', 'a', 'a', 'b', 0};
	int i = 0;
	
	while (i < 10)
	{
		OneMillionChars(arr[i]);
		++i;
	}

	return 0;

}

void OneMillionChars(char c)
{
	static size_t LUT[ASCII_SIZE] = {0};
	
	++LUT[(int)c];
	
	if (0 == (int)c)
	{
		printf("%d\n", ReturnMaxOccurence(LUT));	
	}
	
}

int ReturnMaxOccurence(size_t *LUT)
{
	size_t count = 0;
	int i = 0; 
	
	for (i = 0; i < ASCII_SIZE; ++i)
	{
		if (LUT[i] > count)
		{
			count = LUT[i];
		}
	}
	
	return count; 		
	
	
	
}
