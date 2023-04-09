#include <stdio.h>/*fopen*/
#include <assert.h> /*assert*/
#include <string.h> /*strcpy*/

#include "Serialization.h"



RESULT SaveStudent(char *file_name,students *stu)
{	
    FILE *fp = fopen(file_name,"wb");

    assert(NULL != file_name || NULL != stu);
    
    if(NULL == fp)
    {
        perror("File did not open properly");
        return FAIL;   
    }
    
    if(1 != fwrite(stu, sizeof(*stu), 1, fp))
    {
        perror("Did not save the file");
        fclose(fp);
        return FAIL; 
    }
   
    return (EOF != fclose(fp)) ? SAVED : FAIL; 
}

RESULT LoadStudent(char *file_name, students *stu)
{	
    FILE *fp = fopen(file_name,"rb");

    assert(NULL != file_name || NULL != stu);
    
    if(NULL == fp)
    {
        perror("File did not open properly");
        return FAIL;   
    }
    
    if(1 != fread(stu, sizeof(*stu), 1, fp))
    {
        perror("Did not load the file");
        fclose(fp);
        return FAIL; 
    }
    
    return (EOF != fclose(fp)) ? LOADED : FAIL; 	
}



