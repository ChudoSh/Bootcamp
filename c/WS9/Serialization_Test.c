/*
Dev: BarSH
Rev: MariaP
Date: 11.4.23   
Status: Fixed & Approved
*/

#include <stdio.h>/*fopen*/
#include <assert.h> /*assert*/
#include <string.h>/*memcpy*/
#include <stdlib.h>/*malloc*/

#include "Serialization.h"

static void InitStudent(struct Student *stu)
{	
	assert(NULL != stu);
	
    memcpy(stu->first_name, "bar", NAME_LEN);
	memcpy(stu->last_name, "shadkhin", NAME_LEN);

	stu->grades.hum.literature = 85;
	stu->grades.hum.english = 62;
	stu->grades.hum.history = 77;

	stu->grades.real.math = 93;
	stu->grades.real.physics = 81;
	stu->grades.real.computer_science = 56;
	
	stu->grades.sports = 89.23;
}


int main()
{
    students foo;
    students bar;
    FILE *fp = NULL;
    
    InitStudent(&foo);
    
    	printf("Init check - The name of the student is %s %s\n", foo.first_name,foo.last_name);
    
    fp = fopen("oof.bin","wb");
    
    if(NULL == fp)
    {
        printf("File did not open properly");
        fclose(fp);
        return FAIL;
    }
    
    SaveStudent(&foo, fp);
    
    printf("Saved\n");
    
    fclose(fp);
    
    fp = fopen("oof.bin","rb");
   
    LoadStudent(&bar, fp);
    
    printf("Loaded\n");
    
    if(0 != fclose(fp))
    {
       printf("File did not close properly\n");
       return FAIL;
    }
   
    if(0 == memcmp(&bar,&foo,sizeof(foo)))
    {
        printf("Test memcmp for both structs - Success!\n");
    } 
    else
    {
        printf("Test memcmp for both structs failed..\n");
    } 
    
    
    return 0; 
}
