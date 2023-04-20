#include <stdio.h> 
#include <assert.h>

#define MAX2(a ,b) ((a >= b) ? a : b)
#define MAX3(a ,b, c) (MAX2(MAX2(a, b), c))

#define TO_LOWER(a) ((MAX3(a, 'A','Z')  == a) ? a - 32 : a) 

#define OFFSET(s,f) ((size_t)&f - (size_t)&s)

struct s
{
	int num;/*num num num num*/
	char ch1;/*ch1 [] [] []*/
	int *ptr;/*ptr ptr ptr ptr*/
	char ch2;/*ch2 [] [] []*/
};



/*typedef*/ struct /*With the typedef it wont work, we are missing struct name*/
{
	int num;/*num num num num*/
	char ch1;/*ch1 [] [] []*/

}s1;

union u
{
	int num; /*num/ch num/ch num/ch num/ch ch [] [] []*/	
	char ch1[5];	
};

int main()
{
	struct s1;
	
	s1.num = 5;
	s1.ch1 = 'a'; 
	
	
	printf("%d", s1.num);
	return 0;
}
