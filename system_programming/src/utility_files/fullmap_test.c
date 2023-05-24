#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h> 
void Test1(void);
void Test2(void);



int main()
{
	Test2();
    printf("------\n");    
	
	sleep(600);

	return (0);
}

/*void Test1(void)
{
	void *handle = NULL;
    void (*meh)(void);
    char *error;
    
    void *handle2 = NULL;
    void (*meh2)(void);
    char *error2;

    handle = dlopen ("./libglobal.so", RTLD_LAZY);
    if (!handle)
    {
        fputs (dlerror(), stderr);
        return;
    }

    meh = dlsym(handle, "foo");
    if ((error = dlerror()) != NULL)  
    {
        fputs(error, stderr);
        exit(1);
    }
    
    handle2 = dlopen ("./libglobal2.so", RTLD_LAZY);
    if (!handle2)
    {
        fputs (dlerror(), stderr);
        return;
    }

    meh2 = dlsym(handle2, "foo2");
    if ((error2 = dlerror()) != NULL)  
    {
        fputs(error2, stderr);
        exit(1);
    }

    (*meh)();
	dlclose(handle);
	(*meh2)();
	dlclose(handle2);
	PrintGlobalVariableAddress();
}*/

void Test2(void)
{
	void *handle = NULL;
    void (*meh)(void);
    char *error;

    handle = dlopen ("./libfullmap.so", RTLD_LAZY);
    if (!handle)
    {
        fputs (dlerror(), stderr);
        return;
    }

    meh = dlsym(handle, "PrintAddress");
    if ((error = dlerror()) != NULL)  
    {
        fputs(error, stderr);
        exit(1);
    }
	
	(*meh)(); 
	
	
}
