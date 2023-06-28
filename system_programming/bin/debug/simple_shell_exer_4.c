

#include <time.h>
#include <stdio.h>

int main()
{
	char *str = "banana";
	time_t deadline = time(NULL) + 20;
	
	*str = 'c';
	
	while (time(NULL) != deadline)
	{
		printf("This is exer4\n");
	}
	
	return (0);
	
}
