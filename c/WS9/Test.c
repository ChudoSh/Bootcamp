/*
Dev: BarSH
Rev: AnnaBer
Date: 8.4.23   
Status: Approved
*/

#include <stdio.h>/*fopen*/
#include <assert.h> /*assert*/
#include <string.h>/*strcpy*/

#include "Serialization.h"

static void InitStudent(struct Student *stu)
{	
	assert(NULL != stu);
	
    strcpy(stu->first_name,"bar");
	strcpy(stu->last_name,"shadkhin");
	
	stu->grades.humane.literature = 85;
	stu->grades.humane.english = 62;
	stu->grades.humane.history = 77;

	stu->grades.real.math = 93;
	stu->grades.real.physics = 81;
	stu->grades.real.computer_science = 56;
	
	stu->grades.sports = 89.23;
}


int main()
{
    students foo = {0};
    students bar = {0};
    
    InitStudent(&foo);
  
    printf("Init check - The name of the student is %s %s\n", foo.first_name,foo.last_name);
    
    SaveStudent("BarTHEKIng",&foo);
    LoadStudent("BarTHEKIng",&bar);
    
    printf("Load and save check - The name of the student in  the new struct should be bar  %s\n", bar.first_name);
          
    if(0 == memcmp(&bar,&foo,sizeof(foo)))
    {
        printf("Test memcmp for both structs - Success!!!!!!!!!\n");
    }
    
    
    return 0; 
}
