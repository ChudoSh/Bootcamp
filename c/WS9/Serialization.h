#ifndef __SERIALIZATION_H__
#define __SERIALIZATION_H__

#define NAME_LEN 50


typedef enum RESULT
{
	FAIL = -1,
	SAVED = 0,
	LOADED
}RESULT;


typedef struct RealGrades
{	
	float math; 
	float computer_science;
	float physics;
}reals;

typedef struct HumaneGrades
{	
	float literature; 
	float english;
	float history;
}humanes;

typedef struct Grades
{	
	humanes humane; 
	reals real;
	float sports;
}gardes;

typedef struct Student
{
	gardes grades; 
	char first_name[NAME_LEN];
	char last_name[NAME_LEN];	
}students;


/*
Description:Saves a student into a file .
arguments:
	*num 	 - A valid address of a Student.
return: Returns 1 if it succeeded and 0 if it Failed.
*/
RESULT SaveStudent(char *file_name,students *stu);

/*
Description:Loads a student from a file into a new Student type.
arguments:
	*file name - A valid file name.		
	*num 	 - A valid address of a Student.
return: Returns 1 if it succeeded and 0 if it Failed.
*/
RESULT LoadStudent(char *file_name,students *stu);

#endif /*__SERIALIZATION_H__
*/


