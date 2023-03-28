

#include<stdio.h>

void Print(int input);

typedef void (*func_print)(int);

struct print_me
{
	int input;
	func_print output; 
};

int main()
{
	struct print_me printing[10] = {0};
	int i = 0; 
	
	for (i = 0; i < 10; ++i)
	{
		printing[i].input = i;
		printing[i].output = Print; 
		printing[i].output(printing[i].input); 
		
	}
	
	return 0;
}

void Print(int input)
{
	printf("%d\n", input);
}


