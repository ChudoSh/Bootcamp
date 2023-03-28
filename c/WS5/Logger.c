#include<stdio.h>
#include<string.h>

#define CORS 5
#define SIZE 500
#define APPEND ""
#define RMVE "-remove"
#define COUT "-count"
#define EXIT "-exit"
#define STRT "<"
#define UNUSED(x) (void)(x)
#define CHECKFILE (file_name)(if(NULL!=file_name){return FAIL;})
	

typedef enum FILE_RESULT{
	SUCCESS = 0,
	FAIL,
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
    else
    {
        return Logger(argv[1]);
    }
	
	return SUCCESS; 
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
	if(0 == strncmp(str, flag, strlen(flag)))
	{
		return SUCCESS;
	}
	
	return FAIL; 
	
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
	int i  = 0; 
	
	FILE *fp = fopen(file_name, "r");
	UNUSED(str);
	
	c = getc(fp);
	
	while(EOF != c)
	{
		if('\n' == c)
		{
			++i;
		}
		c = getc(fp);	
	}
	
	printf("The number of lines is %d", i);
	
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
	
	if(0 != rename(file_name,"temp"))
	{
		return FAIL;
	}
	
	fp_original = fopen(file_name, "a+");
	fp_copy = fopen("temp","r");

	if (NULL == fp_original)
	{
	  
		perror("Invalid file.\n");
		  
		return FAIL;
	}
	
	if (NULL == fp_copy)
	{
		fclose(fp_original);
		  
		perror("Invalid file.\n");
		  
		return FAIL;
	}
	
	dummy = ++str; 
	
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
	
	remove("temp");
	
	if(0 != fclose(fp_original))
	{
		fclose(fp_copy);
		return FAIL;
	}
	if(0 != fclose(fp_copy))
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
	char str[SIZE];
	struct COR cor[CORS];
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
		
	return SUCCESS;	
}
