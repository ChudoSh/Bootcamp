#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

int main()
{
        void *handle = NULL;
        int (*meh)(int);
        char *error;

        handle = dlopen ("foo.so", RTLD_LAZY);
        if (!handle)
        {
            fputs (dlerror(), stderr);
            return (1);
        }

        meh = dlsym(handle, "foo");
        
        if ((error = dlerror()) != NULL)  
        {
            fputs(error, stderr);
            exit(1);
        }

        printf ("%d\n", (*meh)(5));
        dlclose(handle);
        
        return (0);
}
