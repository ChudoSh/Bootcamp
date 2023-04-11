#include <stdio.h>/*fopen*/
#include <assert.h> /*assert*/
#include <string.h> /*strcpy*/

#include "Serialization.h"


static RESULT SaveReal(students *stu, FILE *fp)
{  
    fwrite(&(stu->grades.real.math), sizeof(float), ELEM, fp);
    fwrite(&(stu->grades.real.physics), sizeof(float), ELEM, fp);
    fwrite(&(stu->grades.real.computer_science), sizeof(float), ELEM, fp);
    
    return SAVED;
}

static RESULT LoadHumane(students *stu, FILE *fp)
{
    fread(&(stu->grades.hum.literature), sizeof(float), ELEM, fp);
    fread(&(stu->grades.hum.english), sizeof(float), ELEM, fp);
    fread(&(stu->grades.hum.history), sizeof(float), ELEM, fp);   
    
    return LOADED;                
}

static RESULT LoadReal(students *stu, FILE *fp)
{
    fread(&(stu->grades.real.math), sizeof(float), ELEM, fp);
    fread(&(stu->grades.real.physics), sizeof(float), ELEM, fp);
    fread(&(stu->grades.real.computer_science), sizeof(float), ELEM, fp);
    
    return LOADED;
}

static RESULT SaveHumane(students *stu, FILE *fp)
{
    fwrite(&(stu->grades.hum.literature), sizeof(float), ELEM, fp);
    fwrite(&(stu->grades.hum.english), sizeof(float), ELEM, fp);
    fwrite(&(stu->grades.hum.history), sizeof(float), ELEM, fp); 
    
    return SAVED; 
}

static RESULT SaveGrades(students *stu, FILE *fp)
{
    SaveHumane(stu, fp);
    SaveReal(stu, fp);
    
    fwrite(&(stu->grades.sports), sizeof(float), ELEM, fp);
    
    return SAVED;
}
static RESULT LoadGrades(students *stu, FILE *fp)
{
    LoadHumane(stu, fp);
    LoadReal(stu, fp);
    
    fread(&(stu->grades.sports), sizeof(float), ELEM, fp);
    
    return LOADED;
}


RESULT SaveStudent(students *stu ,FILE *fp)
{	
    assert(NULL != stu);
    
    fwrite(stu->first_name, sizeof(char), NAME_LEN, fp);
	fwrite(stu->last_name, sizeof(char), NAME_LEN, fp);
	
    SaveGrades(stu, fp);
  
    return SAVED; 
}

RESULT LoadStudent(students *stu, FILE *fp)
{	
    assert(NULL != stu);
    
    fread(stu->first_name, sizeof(char), NAME_LEN, fp);
	fread(stu->last_name, sizeof(char), NAME_LEN, fp);
	
    LoadGrades(stu, fp);
    
    return LOADED; 	
}



