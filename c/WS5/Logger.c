/**********
Dev: BarSH
Rev: DanielHA
Date: 28.3.23
Status: Approved
***********/

#include<stdio.h> /*printf*/	
#include<string.h> /*strncmp*/

#define CORS 5
#define SIZE 500
#define APPEND ""
#define RMVE "-remove\n"
#define COUT "-count\n"
#define EXIT "-exit\n"
#define STRT "<"
#define UNUSED(x) (void)(x)
	

typedef enum FILE_RESULT{
	FAIL = -1,
	SUCCESS = 0,
	REMOVED,
	TERMINATED
}FILE_RESULT;

typedef FILE_RESULT(*Compare)(char*, char*);
typedef FILE_RESULT(*Operation)(char*, char*);

typedef struct COR 
{	
	char* flag;
	Compare cmp;
	Operation opt;
}COR;


FILE_RESULT Cmp(char *str, char *flag);
FILE_RESULT CmpToStrt(char *str, char *flag);
FILE_RESULT DoNothing(char *str, char *flag);


FILE_RESULT OptRmve(char *file_name, char *str);
FILE_RESULT OptCout(char *file_name, char *str);
FILE_RESULT OptExit(char *file_name, char *str);
FILE_RESULT OptToStrt(char *file_name, char *str);
FILE_RESULT Append(char *file_name, char *str);
FILE_RESULT Logger(char *file_name);


void InitCOR(struct COR *cor);

/*********************/
int main(int argc, char *argv[])
{
		
	if(NULL == argv[1] || argc > 2)
    {
        perror("No file entered.\n");
        return FAIL;
    }
    
    return Logger(argv[1]);
    
	
}
/*******************/

void InitCOR(struct COR *cor)
{	
	cor[0].flag = RMVE;
	cor[1].flag = COUT;
	cor[2].flag = EXIT;
	cor[3].flag = STRT;
	cor[4].flag = APPEND;
		
	cor[0].cmp = Cmp;
	cor[1].cmp = Cmp;
	cor[2].cmp = Cmp;
	cor[3].cmp = CmpToStrt;
	cor[4].cmp = DoNothing;
		
	cor[0].opt = OptRmve;
	cor[1].opt = OptCout;
	cor[2].opt = OptExit;
	cor[3].opt = OptToStrt;
	cor[4].opt = Append;
}

FILE_RESULT Cmp(char *str, char *flag)
{
	if(NULL == str)
	{
		return FAIL;
	}
	
	if(SUCCESS != strcmp(str, flag))
	{
		return FAIL;
	}
	
	return SUCCESS; 
	
}

FILE_RESULT OptRmve(char *file_name, char *str)
{	
	UNUSED(str);
	
	if(NULL == file_name)
	{
		return FAIL;
	}
	
	if(SUCCESS != remove(file_name))
	{
		perror("Error with removing the file.\n");
		return	FAIL;
	}
	
	printf("File was removed from directory.\n");
	
	return REMOVED;	
}

FILE_RESULT OptCout(char *file_name, char *str)
{
	char c = '\0'; 
	size_t i  = 0; 
	
	FILE *fp = fopen(file_name, "r");
	UNUSED(str);
	
	while(EOF != c)
	{
		c = getc(fp);
		
		if('\n' == c)
		{
			++i;
		}	
	}
	
	printf("The number of lines is %lu", i);
	
	if(SUCCESS != fclose(fp))
	{
		perror("Error with closing the file.\n");
		return FAIL;	
	}
	
	return SUCCESS;
}

FILE_RESULT OptExit(char *file_name, char *str)
{		
	UNUSED(file_name);
	UNUSED(str);	
	
	printf("Program has ended.\n");	
	
	return TERMINATED;	
}

FILE_RESULT CmpToStrt(char *str, char *flag)
{
	if(NULL == str)
	{
		return FAIL;
	}
	if(*str == *flag)
	{
		return SUCCESS;
	}
	return FAIL; 
}

FILE_RESULT OptToStrt(char *file_name, char *str)
{	 
	FILE *fp_original;
	FILE *fp_copy;
	char c = '\0';
	const char *dummy = NULL;
	
	if(SUCCESS != rename(file_name,"temp"))
	{
		return FAIL;
	}
	
	fp_original = fopen(file_name, "a+");

	if (NULL == fp_original)
	{
		perror("Invalid file.\n");
		return FAIL;
	}
	
	fp_copy = fopen("temp","r");
	
	if (NULL == fp_copy)
	{
		fclose(fp_original);  
		perror("Invalid file.\n");
		return FAIL;
	}
	
	dummy = str + 1; /*Removed the small sign*/
	
	while (*dummy != '\0')
	{
		fputc(*dummy, fp_original);
		++dummy;
	}
	
	c = fgetc(fp_copy);
	
	while (c != EOF)
	{
		fputc(c, fp_original);
		c = fgetc(fp_copy);
	}
	
	
	if(SUCCESS != remove("temp"))
	{
		fclose(fp_original);
		fclose(fp_copy);
		return FAIL;
	}
	
	if(SUCCESS != fclose(fp_original))
	{
		fclose(fp_copy);
		return FAIL;
	}
	
	if(SUCCESS != fclose(fp_copy))
	{
		return FAIL;
	}
	
	printf("The given string was added to the BEGINNING of the file: %s\n", str);
	
	return SUCCESS;
}

FILE_RESULT Append(char *file_name, char* str)
{	

	FILE *fp = fopen(file_name, "a+");

	if(NULL == fp)
	{
		perror("File did not open.\n");
		return FAIL;
	}
	
	if(EOF == fputs(str, fp))
	{
		perror("String wasnt printed.\n");
		fclose(fp);
		return FAIL;
	}

	if(SUCCESS != fclose(fp))
	{
		perror("Error with closing the file.\n");
		return FAIL;	
	}
	
	printf("The given string was added to the END of the file: %s\n", str);
	
	return SUCCESS;
}

FILE_RESULT DoNothing(char *file_name, char *str)
{		
	UNUSED(file_name);
	UNUSED(str);	
	return SUCCESS;	
}

FILE_RESULT Logger(char* file_name)
{
	char str[SIZE] = {0};
	COR cor[CORS] = {0};
	int i = 0;
	int termination = SUCCESS; 
	
	InitCOR(cor);
	
	if(NULL == file_name)
	{
		perror("Invalid file name.\n");
		return FAIL;
	}
	
	printf("Please enter a string to add to the file up to 500 characters.\nTo stop appending please enter '-exit'.\n");
		
	while(SUCCESS == termination)
	{
		fgets(str, SIZE, stdin);
		
		for(i = 0; i < CORS; ++i)
		{
			if(SUCCESS == cor[i].cmp(str, cor[i].flag))
			{	
				termination	= cor[i].opt(file_name, str);
				break;
			}
				
		}	
	}
		
	return (FAIL != termination) ? SUCCESS : FAIL;	
}
