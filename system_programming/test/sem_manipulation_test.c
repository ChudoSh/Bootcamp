/*
Dev: BarSh
Rev:
Status:
Date:
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>


int main()
{
    sem_t *sem = NULL;
    int time_to_run = 0;
    int value = 0; 
    int i = 0;
    char to_undo[20] = {'\0'};
    int amount_undo = 0;
    int to_change = 0;
    char manipulate[50] = {'\0'};

    printf("name thy semaphore\n");
    scanf("%s",manipulate);
    sem = sem_open(manipulate, O_CREAT ,0666, 0);
    if (SEM_FAILED == sem)
    {
        printf("failed to open\n");
        return (-1);
    }

    printf("Provide times to run\n");
    scanf("%d",&time_to_run);
    
    while (0 < time_to_run)
    {
        printf("manipulate thy semaphore: D, I, V, X\n");
        scanf("%s",manipulate);
        if (0 == strcmp(manipulate, "D"))
        {
            sem_getvalue(sem, &value);
            if (0 == value)
            {
                printf("semaphore is already locked\n");
            }

            else
            {
                printf("please enter amount to lock semaphore\n");
                scanf("%d", &to_change);

                printf("to undo? Y or N\n");
                scanf("%s", to_undo);

                if (0 == strcmp(to_undo, "Y"))
                {
                    amount_undo += to_change;
                }
               
                printf("locking semaphore by %d\n",to_change);
                for (i = 0; i < to_change; ++i)
                {
                    if (-1 == sem_wait(sem))
                    {
                        perror("wait");
                        return (-1);
                    }
                } 
                printf("semaphore is locked by the given amount\n");      
            } 
        }

        else if (0 == strcmp(manipulate, "I"))
        {
            sem_getvalue(sem, &value);
    
            printf("please enter amout to lock semaphore\n");
            scanf("%d", &to_change);

            printf("to undo? Y or N\n");
            scanf("%s", to_undo);

            if (0 == strcmp(to_undo, "Y"))
            {
                amount_undo -= to_change;
            }

            printf("locking semaphore by %d\n",to_change);
            for (i = 0; i < to_change; ++i)
            {
                if (-1 == sem_post(sem))
                {
                    perror("psoe");
                    return (-1);
                }
            }
            printf("semaphore is unlocked by the given amount\n");
        }

        else if (0 == strcmp(manipulate, "V"))
        {
            sem_getvalue(sem, &value);
            printf("semaphore value is %d:\n",value);
        }

        else if (0 == strcmp(manipulate, "X"))
        {
            for (i = 0;i < amount_undo; ++i)
            {
                if (-1 == sem_post(sem))
                {
                    perror("post");
                    return (-1);
                }
            }

            for (i = amount_undo; 0 > i ; ++i)
            {
                if (-1 == sem_wait(sem))
                {
                    perror("wait");
                    return (-1);
                }
            }

            if(-1 == sem_close(semaphor))
            {
                perror("sem_close");
                return (-1);
            }

            printf("semaphore is closed\n");
            return (0);
        }

        --(time_to_run);
    }

    return (-1);
}