/*
Dev: BarSh
Rev: IdoI
Status: Approved
Date: 12.7.23
*/

#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <semaphore.h>
#include <string.h>

#include "slist.h"
#include "queue.h"

#define BUFF_SIZE (20)
#define COND (2)

enum EXER5
{
    READ,
    WRITE,
    NUM_OF_OPS
};


enum LOCKING
{
    LOCKED, 
    UNLOCKED
};

pthread_mutex_t mutex_exer2 = {0};
pthread_mutex_t mutex_exer3 = {0};
pthread_mutex_t mutex_exer4 = {0};

sem_t sem_exer3 = {0};
sem_t semEmpty_exer4 = {0};
sem_t semFull_exer4 = {0};


typedef struct FSQ
{
    int dirty_q[BUFF_SIZE];
    sem_t ops_count[NUM_OF_OPS];
    pthread_mutex_t mutex_op[NUM_OF_OPS];
    size_t read_index; 
    size_t write_index;
}fsq_t;

typedef struct BARRIER
{
    sem_t counter;
    pthread_mutex_t mutex; 
    pthread_cond_t cond;
}barrier_t;

barrier_t *barrier = {NULL};
fsq_t *fsq = {NULL};

enum STATUS
{
    FAIL = -1,
    SUCCESS
};

static int spinlock = UNLOCKED;

/*Exer 1*/
void Exer1(void);
void *Exer1Read(void *arg);
void *Exer1Write(void *arg);

/*Exer 2*/
void Exer2(void);
void *Exer2Read(void *arg);
void *Exer2Write(void *arg);

/*Exer 3*/
void Exer3(void);
void *Exer3Read(void *arg);
void *Exer3Write(void *arg);

/*Exer 4*/
void Exer4(void);
void *Exer4Read(void *arg);
void *Exer4Write(void *arg);

/*Exer 5*/
void Exer5(void);
void *Exer5Read(void *arg);
void *Exer5Write(void *arg);

/*Exer 6*/
void Exer6(void);
void *Exer6Read(void *arg); 
void *Exer6Write(void *arg);

static barrier_t *BarrierInit();
static void BarrierDestroy(barrier_t *barrier);

static fsq_t *FsqCreate();
static void FsqCDestroy();
static void FsqInsert(int value);
static int FsqRemove();

int main()
{
    Exer1();
    Exer2();
    Exer3();
    Exer4();
    Exer5();
    Exer6();

    return (0);   
}

/*
Exer 1: 
Description:
    Prints randon lower case letter of the alphabet BUFF_SIZE times

Implementation:
    1. Exer1 -> Creates Consumer & Producer threads and initiates them

    2. Producer -> Locks the string
                   Sets *string with a new char
                   Unlocks
    3. Consumer -> Locks the string
                   Prints string
                   Unlocks
                   
*/
void Exer1(void)
{
    pthread_t producer = 0; 
    pthread_t consumer = 0;
    char buffer[BUFF_SIZE] = {'\0'}; 

    if(0 != pthread_create(&producer, NULL, Exer1Write, buffer))
    {
        perror("producer");
    }
    if (0 != pthread_create(&consumer, NULL, Exer1Read, buffer))
    {
        perror("consumer");
    }

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);
    
}
void *Exer1Read(void *arg)
{   
    while (LOCKED == spinlock);

    spinlock = LOCKED;
    {
        printf("Exer 1:the new char for the password is: %s\n", (char *)arg);
    }
    spinlock = UNLOCKED; 

    return (NULL); 
       
}
void *Exer1Write(void *arg)
{   
    int i  = 0;
    char *runner = (char *)arg;
    
    while (LOCKED == spinlock);

    spinlock = LOCKED;
    {
        for (i = 0; i < BUFF_SIZE; ++i)
        {
            runner[i] = 'a' + (rand() % 26);
        }

        runner[i] = '\0';
    }
    spinlock = UNLOCKED;  

    return (NULL);
   
}

/*
Exer 2: 
Description:
    Prints randon lower case letter of the alphabet BUFF_SIZE times

Implementation:
    1. Exer2 -> Creates Consumer & Producer threads, a list and initiates them
    2. Producer -> Locks the list
                   Insert a random chars into the list
                   Unlocks

    3. Consumer -> Locks the list
                   Prints the value in the list
                   Removes it from the list
                   Unlocks
*/                  
void Exer2(void)
{
    pthread_t producer[BUFF_SIZE] = {0}; 
    pthread_t consumer[BUFF_SIZE] = {0};
    int i = 0; 

    slist_t *list = SListCreate();
    if (NULL == list)
    {
        perror("list create");
        return; 
    }

    if (0 != pthread_mutex_init(&mutex_exer2, NULL))
    {
        perror("mutex init");
        return; 
    }

    for (i = 0; i < BUFF_SIZE; ++i)
    {
        if (0 != pthread_create(&producer[i], NULL, Exer2Write, list))
        {
            perror("producer create");
        }
        if (0 != pthread_create(&consumer[i], NULL, Exer2Read, list))
        {
            perror("consumer create");
        }
    }
        
    for (i = 0; i < BUFF_SIZE; ++i)
    {
        if (0 != pthread_join(consumer[i], NULL))
        {
            perror("producer join");
        }
        if (0 != pthread_join(producer[i], NULL))
        {
            perror("consumer join");
        }
    }
  
    SListDestroy(list);
    pthread_mutex_destroy(&mutex_exer2);

}
void *Exer2Read(void *arg)
{   
    iter_t iter = NULL;
    char new_char = '\0';

    pthread_mutex_lock(&mutex_exer2);
    {
        iter = SListBegin((slist_t *)arg);
        new_char = (char)((size_t)SListGet(iter));

        if (0 != SListCount((slist_t *)arg))
        {
            printf("Exer 2:the new char for the password is: %c\n", new_char);
            
            if (NULL == SListRemove(iter))
            {
                perror("List remove");
                return (NULL);
            }
        }
    }
    pthread_mutex_unlock(&mutex_exer2);

    return (NULL); 
}
void *Exer2Write(void *arg)
{   
    char new_char = '\0';
    iter_t iter = NULL;
    
    pthread_mutex_lock(&mutex_exer2);
    {
        iter = SListBegin((slist_t *)arg);

        new_char = 'a' + rand() % BUFF_SIZE;

        if (NULL == SListInsert(iter, (void *)((size_t)new_char)))
        {
            perror("List insert");
            return (NULL);
        }
    }
    pthread_mutex_unlock(&mutex_exer2);

    return (NULL);     
}

/*
Exer 3: 
Description:
    Prints randon lower case letter of the alphabet BUFF_SIZE times

Implementation:
    1. Exer3 -> Creates Consumer & Producer threads, a list and initiates them

    2. Producer -> Locks the list
                   Insert a random chars into the list
                   Increases the sempahore
                   Unlocks

    3. Consumer -> Locks the list
                   Prints the value in the list
                   Removes the value from the list 
                   Decreases the sempahore
                   Unlocks
*/    
void Exer3(void)
{
    pthread_t producer[BUFF_SIZE] = {0}; 
    pthread_t consumer[BUFF_SIZE] = {0};
    int i = 0; 

    slist_t *list = SListCreate();
    if (NULL == list)
    {
        perror("list create");
        return; 
    }

    if (0 != pthread_mutex_init(&mutex_exer3, NULL))
    {
        perror("mutex init");
        return; 
    }

    if (0 != sem_init(&sem_exer3, 0, 0))
    {
        perror("semaphore init");
        return; 
    }


    for (i = 0; i < BUFF_SIZE; ++i)
    {
        if (0 != pthread_create(&producer[i], NULL, Exer3Write, list))
        {
            perror("producer create");
        }
        if (0 != pthread_create(&consumer[i], NULL, Exer3Read, list))
        {
            perror("consumer create");
        }
    }
        
    for (i = 0; i < BUFF_SIZE; ++i)
    {
        if (0 != pthread_join(consumer[i], NULL))
        {
            perror("producer join");
        }
        if (0 != pthread_join(producer[i], NULL))
        {
            perror("consumer join");
        }
    }
  
    SListDestroy(list);
    pthread_mutex_destroy(&mutex_exer3);
    sem_destroy(&sem_exer3);

}
void *Exer3Read(void *arg)
{   
    iter_t iter = NULL;
    char new_char = '\0';

    sem_wait(&sem_exer3);
    pthread_mutex_lock(&mutex_exer3);
    {
        iter = SListBegin((slist_t *)arg);
        new_char = (char)((size_t)SListGet(iter));

        printf("Exer 3:the new char for the password is: %c\n", new_char);
            
        if (NULL == SListRemove(iter))
        {
            perror("slist remove");
            return (NULL);
        }
    }
    pthread_mutex_unlock(&mutex_exer3);

    return (NULL); 
}
void *Exer3Write(void *arg)
{   
    char new_char = '\0';
    iter_t iter = NULL;
    
    sem_post(&sem_exer3);
    pthread_mutex_lock(&mutex_exer3);
    {
        iter = SListBegin((slist_t *)arg);

        new_char = 'a' + rand() % 25;

        if (NULL == SListInsert(iter, (void *)((size_t)new_char)))
        {
            perror("List insert");
            return (NULL);
        }
    }
    pthread_mutex_unlock(&mutex_exer3);

    return (NULL);     
}

/*
Exer 4: 
Description:
    Prints randon lower case letter of the alphabet BUFF_SIZE times

Implementation:
    1. Exer4 -> Creates Consumer & Producer threads, a queue and locks and initiates them
    2. Producer -> Decreases the Empty semaphore
                   Locks the list
                   Insert a random chars into the list
                   Increases the Full sempahore
                   Unlocks

    3. Consumer -> Decreases the Full semaphore
                   Locks the list
                   Prints the value in the list
                   Removes the value from the list 
                   increases the Empty sempahore
                   Unlocks
*/ 
void Exer4(void)
{
    pthread_t producer[BUFF_SIZE] = {0}; 
    pthread_t consumer[BUFF_SIZE] = {0};
    int i = 0; 

    queue_t *queue = QCreate();
    if (NULL == queue)
    {
        perror("queue create");
        return; 
    }

    if (0 != pthread_mutex_init(&mutex_exer4, NULL))
    {
        perror("mutex init");
        return; 
    }
    if (0 != sem_init(&semEmpty_exer4, 0, BUFF_SIZE))
    {
        perror("semaphore post init");
        return; 
    }
    if (0 != sem_init(&semFull_exer4, 0, 0))
    {
        perror("semaphore wait init");
        return; 
    }

    for (i = 0; i < BUFF_SIZE; ++i)
    {
        if (0 != pthread_create(&producer[i], NULL, Exer4Write, queue))
        {
            perror("producer create");
        }
        if (0 != pthread_create(&consumer[i], NULL, Exer4Read, queue))
        {
            perror("consumer create");
        }
    }
        
    for (i = 0; i < BUFF_SIZE; ++i)
    {
        if (0 != pthread_join(consumer[i], NULL))
        {
            perror("producer join");
        }
        if (0 != pthread_join(producer[i], NULL))
        {
            perror("consumer join");
        }
    }
  
    QDestroy(queue);
    pthread_mutex_destroy(&mutex_exer4);
    sem_destroy(&semEmpty_exer4);
    sem_destroy(&semFull_exer4);

}
void *Exer4Read(void *arg)
{   
    char new_char = '\0';

    sem_wait(&semFull_exer4);
    pthread_mutex_lock(&mutex_exer4);
    {
        new_char = (char)((size_t)QPeek((queue_t *)arg));

        printf("Exer 4:the new char for the password is: %c\n", new_char);  
        QDequeue((queue_t *)arg);
    }
    pthread_mutex_unlock(&mutex_exer4);
    sem_post(&semEmpty_exer4);

    return (NULL); 
}
void *Exer4Write(void *arg)
{
    char new_char = '\0';

    sem_wait(&semEmpty_exer4); 
    pthread_mutex_lock(&mutex_exer4);
    {
        new_char = 'a' + rand() % 25;

        if (-1 == QEnqueue((queue_t *)arg, (void *)((size_t)new_char)))
        {
            perror("QEnqueue");
            return (NULL);
        }
    }
    pthread_mutex_unlock(&mutex_exer4);
    sem_post(&semFull_exer4);

    return (NULL);     
}

/*
Exer 5: 
Description:
    Prints randon lower case letter of the alphabet BUFF_SIZE times

Implementation:
    1. Exer5 -> Creates Consumer & Producer threads, a queue and initiates them

    2. Producer -> Locks
                   Runs over the string
                   Insert a random chars into the list
                   Increases the barrier
                   Check the condition, if so then broadcast wait
                   Unlocks

    3. Consumer -> Decreases the barrier counter 
                   Checks if the condition is met, if so then broadcast signal 
                   Locks
                   Prints the value in the buffer
                   Unlocks
*/ 
void Exer5(void)
{
    pthread_t producer[BUFF_SIZE] = {0}; 
    pthread_t consumer[BUFF_SIZE] = {0};
    int i = 0; 

    fsq = FsqCreate();

    for (i = 0; i < BUFF_SIZE; ++i)
    { 
        if (0 != pthread_create(&producer[i], NULL, Exer5Write, &i))
        {
            perror("producer create");
        }

        if (0 != pthread_create(&consumer[i], NULL, Exer5Read, &i))
        {
            perror("consumer create");
        }
    } 


    for (i = 0; i < BUFF_SIZE; ++i)
    {
        if (0 != pthread_join(producer[i], NULL))
        {
            perror("producer join");
        } 

        if (0 != pthread_join(consumer[i], NULL))
        {
            perror("consumer join");
        }
    }

    FsqCDestroy();
    
}
void *Exer5Read(void *arg)
{  
    printf("The current int is %d\n", FsqRemove());

    return (NULL);
    (void)arg;
}
void *Exer5Write(void *arg)
{   
    int rand_val = rand() % 100;

    FsqInsert(rand_val);

    return (NULL);
    (void)arg;
}

/*
Exer 6: 
Description:
    Initiates a string up to a certain level indicatd by the barrier, then prints it all

Implementation:
    1. Exer6 -> Creates Consumer & Producer threads, a buffer and a barrier and initiates them

    2. Producer -> Locks
                   Runs over the string
                   Insert a random chars into the list
                   Increases the barrier
                   Check the condition, if so then broadcast wait
                   Unlocks

    3. Consumer -> Decreases the barrier counter 
                   Checks if the condition is met, if so then broadcast signal 
                   Locks
                   Prints the value in the buffer
                   Unlocks
*/ 
void Exer6(void)
{
    char buffer[BUFF_SIZE] = {'\0'};
    pthread_t producer = {0}; 
    pthread_t consumer[BUFF_SIZE] = {0};
    int i = 0; 

    barrier = BarrierInit();
    if (NULL == barrier)
    {
        perror("barrier init");
        return;
    }

    if (0 != pthread_create(&producer, NULL, Exer6Write, &buffer))
    {
        perror("producer create");
    }

    for (i = 0; i < BUFF_SIZE; ++i)
    { 
        if (0 != pthread_create(&consumer[i], NULL, Exer6Read, buffer))
        {
            perror("consumer create");
        }
    } 

    if (0 != pthread_join(producer, NULL))
    {
        perror("producer join");
    } 

    for (i = 0; i < BUFF_SIZE; ++i)
    {
        if (0 != pthread_join(consumer[i], NULL))
        {
            perror("consumer join");
        }
    }

    printf("Exer 6:the new string for the password is: %s\n", buffer);
  
    BarrierDestroy(barrier);
}
void *Exer6Read(void *arg)
{  
    int value = 0;
    
    sem_wait(&(barrier->counter));
    sem_getvalue(&(barrier->counter), &value);
    if (COND >= value)
    {
        pthread_cond_signal(&(barrier->cond));
    }

    pthread_mutex_lock(&(barrier->mutex));
    {  
        printf("Exer 6:the new char for the password is: %s\n", (char *)arg); 
    }
    pthread_mutex_unlock(&(barrier->mutex));

    return (NULL); 
}
void *Exer6Write(void *arg)
{
    char *runner = NULL;
    int i = 0; 
    int value = 0; 
    
    pthread_mutex_lock(&(barrier->mutex));
    {  
        runner = (char *)arg;
        
        while (i < BUFF_SIZE) 
        {   
            runner[i] = 'a' + (char)(rand() % 26);
            ++(i);

            sem_post(&(barrier->counter));
            sem_getvalue(&(barrier->counter), &value);
            if (COND < value)
            {
                printf("waiting..\n");
                pthread_cond_wait(&(barrier->cond), &(barrier->mutex));  
            } 
        }

        runner[i] = '\0';   
    }
    pthread_mutex_unlock(&(barrier->mutex));
    

    return (NULL);
}
/*============================================================================*/
static barrier_t *BarrierInit()
{
    barrier_t *new_barrier = (barrier_t *)malloc(sizeof(barrier_t));
    if (NULL == new_barrier)
    {
        return (NULL);
    }

    if (0 != pthread_mutex_init(&(new_barrier->mutex), NULL))
    {
        perror("mutex init");
        return (NULL); 
    }

    if (0 != sem_init(&(new_barrier->counter), 0, 0))
    {
        perror("semaphore init");
        return (NULL); 
    }

    if (0 != pthread_cond_init(&(new_barrier->cond), NULL))
    {
        perror("condition init");
        return (NULL); 
    }

    return (new_barrier);
}
static void BarrierDestroy()
{
    assert(NULL != barrier);

    pthread_mutex_destroy(&(barrier->mutex));
    sem_destroy(&(barrier->counter));
    pthread_cond_destroy(&(barrier->cond));

    free(barrier);
}
static fsq_t *FsqCreate()
{
    fsq_t *fsq = (fsq_t *)malloc(sizeof(fsq_t));

    if (0 != pthread_mutex_init(&(fsq->mutex_op[READ]), NULL))
    {
        perror("mutex read init");
        return (NULL); 
    }
    if (0 != pthread_mutex_init(&(fsq->mutex_op[WRITE]), NULL))
    {
        perror("mutex write init");
        return (NULL); 
    }

    if (0 != sem_init(&(fsq->ops_count[READ]), 0, 0))
    {
        perror("semaphore read init");
        return (NULL); 
    }

    if (0 != sem_init(&(fsq->ops_count[WRITE]), 0, BUFF_SIZE))
    {
        perror("semaphore write init");
        return (NULL); 
    }

    fsq->read_index = 0; 
    fsq->write_index = 0; 

    return (fsq);
}
static void FsqCDestroy()
{
    assert(NULL != fsq);

    pthread_mutex_destroy(&(fsq->mutex_op[READ]));
    pthread_mutex_destroy(&(fsq->mutex_op[WRITE]));
    sem_destroy(&(fsq->ops_count[READ]));
    sem_destroy(&(fsq->ops_count[WRITE]));

    free(fsq);
}
static void FsqInsert(int value)
{
    sem_wait(&(fsq->ops_count[WRITE]));
    pthread_mutex_lock(&(fsq->mutex_op[WRITE]));
    {
        fsq->dirty_q[fsq->write_index] = value;
        fsq->write_index = (fsq->write_index + 1) % BUFF_SIZE;
    }
    pthread_mutex_unlock(&(fsq->mutex_op[WRITE]));
    sem_post(&(fsq->ops_count[READ]));
}
static int FsqRemove()
{
    int value = 0; 
    
    sem_wait(&(fsq->ops_count[READ]));
    pthread_mutex_lock(&(fsq->mutex_op[READ]));
    {
        value = fsq->dirty_q[fsq->read_index];
        fsq->read_index = (fsq->read_index + 1) % BUFF_SIZE;
    }
    pthread_mutex_unlock(&(fsq->mutex_op[READ]));
    sem_post(&(fsq->ops_count[WRITE]));

    return (value);
}

