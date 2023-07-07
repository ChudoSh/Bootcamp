#include <stdio.h> /*printf*/
#include <unistd.h> /*printf*/
#include <pthread.h> /*pthread_create, pthread_attr_init, pthread_attr_destroy, pthread_attr_setdetachstate*/
#include <stdlib.h>

#define NUM_OF_THREADS (5)
#define NUM_OF_VARS (10000)

char global_array[NUM_OF_VARS] = {0};
__thread char thread_local_array[NUM_OF_VARS] = {0};


enum status
{
    SUCCESS,
    FAIL
};

static void InitThreads(pthread_t *threads, size_t threads_num);
static void JoinThreads(pthread_t *threads, size_t threads_num, void *res);

static void *MemRoutine(void *arg);

int main()
{
    char local_vars[NUM_OF_VARS] = {0};
    pthread_t threads[NUM_OF_THREADS] = {0};
    void *res_array[NUM_OF_THREADS] = {NULL};

    sleep(10);

    printf("main thread\n");
    printf("local var(start): %p\nlocal var(end): %p\n", 
          (void *)&local_vars[0], (void *)&local_vars[NUM_OF_VARS - 1]);


    InitThreads((pthread_t *)threads, NUM_OF_THREADS);

    JoinThreads((pthread_t *)threads, NUM_OF_THREADS, &res_array);

    return (SUCCESS);
}

static void InitThreads(pthread_t *threads, size_t threads_num)
{
    size_t i = 0;

    for(i = 0; i < threads_num; ++i)
    {
        while(SUCCESS != pthread_create(threads + i, NULL, &MemRoutine, (void *)i));
    }
}

static void JoinThreads(pthread_t *threads, size_t threads_num, void *res)
{
    size_t i = 0;

    for(i = 0; i < threads_num; ++i)
    {
        if(SUCCESS != pthread_join(*(threads + i), (void **)res))
        {
            printf("FAIL at %lu\n", i);
        }
    }
}

static void *MemRoutine(void *arg)
{
    size_t thread_index = (size_t)arg;
    char local_vars[NUM_OF_VARS] = {0};
    char *heap_vars = NULL;
    int *small_heap_vars = NULL;

    heap_vars = (char *)malloc(NUM_OF_VARS);
    if(NULL == heap_vars)
    {
        return (NULL);
    }

    small_heap_vars = (int *)malloc(sizeof(int));
    if(NULL == heap_vars)
    {
        free(heap_vars);
        return (NULL);
    }


    sleep(thread_index);
    printf("thread %lu\n", thread_index);
    printf("local var(start): %p\nlocal var(end): %p\n", 
          (void *)&local_vars[0], (void *)&local_vars[NUM_OF_VARS - 1]);
    printf("heap var(start): %p\nheap var(end): %p\n", 
          (void *)&heap_vars[0], (void *)&heap_vars[NUM_OF_VARS - 1]);
        printf("small heap var: %p\n", (void *)small_heap_vars);
    printf("global var(start): %p\nglobal var(end): %p\n", 
          (void *)&global_array[0], (void *)&global_array[NUM_OF_VARS - 1]);
    printf("TLS var(start): %p\nTLS var(end): %p\n", 
          (void *)&thread_local_array[0], 
          (void *)&thread_local_array[NUM_OF_VARS - 1]);

    free(heap_vars);
    free(small_heap_vars);

    return (NULL);
}
