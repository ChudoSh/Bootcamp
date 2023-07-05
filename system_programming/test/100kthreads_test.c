/*
Dev: BarSh
Rev:
Status:
Date:
*/
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define NUM_THREADS (6)
#define ARR_SIZE (100000)
#define DIVISOR_NUM (0x77ffffff)

int arr[ARR_SIZE] = {0};

static void *SetSumOfDivisors(void *arg);
static void *SetArray(void *arg);
static void *SetSumOfDivisorsSingle(void *arg);
static int Exer1();
static int Exer2();
static int Exer3();
static int Exer4();
static int Exer5();

int main()
{  
    /*Exer1();
    Exer2();
    Exer3();*/
    Exer4();
    Exer5();

    return (0); 
}

static int Exer1()
{
    pthread_t new_thread[NUM_THREADS] = {0};
    size_t i = 0;

    for (i = 0; i <= ARR_SIZE; ++i)
    {
        pthread_create(&new_thread[i], NULL, SetArray,(void *)i);
    }

    return (0);
}

static int Exer2()
{
    pthread_t new_thread[NUM_THREADS] = {0};
    size_t i = 0;
    time_t stop = time(NULL) + 20;

    for (i = 0; i < ARR_SIZE; ++i)
    {
        while (0 != pthread_create(&new_thread[i], NULL, SetArray,(void *)i)
               && stop != time(NULL));
    }

    for (i = 0; i < ARR_SIZE; ++i)
    {
        pthread_detach(new_thread[i]);         
    }

    return (0);
}

static int Exer3()
{
    pthread_t new_thread[65530] = {0};
    size_t i = 0;
    time_t stop = time(NULL) + 20;

    for (i = 0; i < 65530; ++i)
    {
        while (0 != pthread_create(&new_thread[i], NULL, SetArray,(void *)i)
               && stop != time(NULL));
    }

    for (i = 0; i < 65530; ++i)
    {
        pthread_detach(new_thread[i]);         
    }

    return (0);
}


static int Exer4()
{
    pthread_t new_thread[NUM_THREADS] = {0};
    size_t i = 0;
    size_t thread_res = 0;
    size_t generic_sum = 0;
    time_t start = time(NULL);

    for (i = 0; i < NUM_THREADS; ++i)
    {
        while (0 != pthread_create(&new_thread[i], NULL,
                                   SetSumOfDivisors,
                                   (void *)i));
    }

    for (i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(new_thread[i], ((void *)&thread_res));

        generic_sum += thread_res;
    }

    printf("exer 4 the sum is: %lu, it takes %ld seconds to calculate\n", 
            generic_sum, time(NULL) - start);

    return (0);
}

static int Exer5()
{
    pthread_t new_thread = {0};
    size_t generic_sum = 0;
    time_t start = time(NULL);

    while (0 != pthread_create(&new_thread, NULL,
                                   SetSumOfDivisorsSingle,
                                   (void *)generic_sum));
                                   
    pthread_join(new_thread, ((void *)&generic_sum));
    
    printf("exer 5 the sum is: %lu, it takes %ld seconds to calculate\n", 
            generic_sum, time(NULL) - start);

    return (0);
}

static void *SetArray(void *arg)
{
    int i = (int)arg;

    arr[i] = i;

    return (NULL);
}

static void *SetSumOfDivisors(void *arg)
{
    size_t sum = 0;
    size_t begin = (size_t)arg * (DIVISOR_NUM / NUM_THREADS);
    size_t end = ((size_t)arg + 1) * (DIVISOR_NUM / NUM_THREADS);
    size_t i = 0;

    if (begin > DIVISOR_NUM)
    {
        return (NULL);
    }

    if (end > DIVISOR_NUM)
    {
        end = DIVISOR_NUM + 1;
    }

    for (i = begin + 1; i <= end; ++i)
    {
        if (0 == (DIVISOR_NUM % i))
        {
            sum += i;
        }
    }

    return ((void *)sum);
}

static void *SetSumOfDivisorsSingle(void *arg)
{   
    size_t i = 0; 
    size_t sum = 0;  

    #pragma omp parallel for
    for (i = 1 ; i < DIVISOR_NUM; ++i)
    {
        if (0 == (DIVISOR_NUM % i))
        {
            sum += i;
        }
    }

    return ((void *)sum);
}