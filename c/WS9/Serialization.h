#ifndef __SERIALIZATION_H__
#define __SERIALIZATION_H__

#define NAME_LEN 50


typedef enum RESULT
{
	FAIL = -1,
	SAVED = 0,
	LOADED = 1,
	ELEM = 1
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
}humane;

typedef struct Grades
{	
	humane hum; 
	reals real;
	float sports;
}grades;

typedef struct Student
{
	grades grades; 
	char first_name[NAME_LEN];
	char last_name[NAME_LEN];	
}students;


/*
Description:Saves a student into a file .
arguments:
    *file_name 	 - A valid file name pointer.
	*stu 	 - A valid address of a Student.
return: Returns 1 if it succeeded and 0 if Failed.
*/
RESULT SaveStudent(students *stu, FILE *fp);

/*
Description:Loads a student from a file into a new Student type.
arguments:
	*file name - A valid file name pointer.		
	*stu 	 - A valid address of a Student.
return: Returns 1 if it succeeded and 0 if Failed.
*/
RESULT LoadStudent(students *stu, FILE *fp);

#endif /*__SERIALIZATION_H__
*/


