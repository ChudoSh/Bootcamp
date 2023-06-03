/* This is was correct
LIFO
Push    O(1) 
Pop     O(1)
Peek    O(1)
*/

/* {}, [], () */
/* {ahua */
/* ({]) */
/*[]{[}]*/
/* []][{}<> */
int IsParsAreBalance(char *str)
{

}

/*Why i cant dereference a void pointer?*/
void *Memcpy(void *dest, void *src, size_t size)/*To copy memory by word size or byte size*/
{
    unsigned char *runner_dest = NULL; 
    unsigned char *runner_src = NULL;
    
    assert(NULL != dest);
    assert(NULL != src);
    
    runner = dest; 
    
    while (0 < size)
    {
        *runner_dest = *((unsigned char *)runner_src); 
        
        ++(runner);
        ++(src);
        --(size);
    }
    
    return (dest);
}



int main()
{
    size_t *ptr = NULL;/*Initializing a size_t pointer to NULL*/
    char *my_str = "hello";/*Initializng a str (char *) to "hello"*/
    
    strncpy(ptr, my_str, 4);/*assert(NULL != dest), also it's a size_t*/
    strncpy(&ptr, my_str, 4);/*Wont work, pointer to pointert*/
}


/*The build process?*/

