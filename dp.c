#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
typedef bool semaphore;
semaphore chopsticks[5];
bool phil_status[5];
int initialise()
{
    int i;
    for (i = 0; i < 5; i++)
    {
        chopsticks[i] = 1;
        phil_status[i] = 1;
    }
}
int wait(semaphore S)
{
    if (S != 1)
    {
        //Chopstick is not available
        return (0);
    }
    else
    {
        //Chopstick is available but we are locking it
        S = 0;
        return S;
    }
}
int signal(semaphore S)
{
    if (S == 1)
    {
        //Chopstick is available
        return 1;
    }
    else
    {
        S = 1;
        return 1;
    }
}
int main()
{
    int i, j, k, l, m, n;
    initialise();
    char c;
    srand(time(0));
    //printf(" Thinking - 1, Eating - 0\n");
    for (j = 0; j < 2; j++)
    {
        i = rand() % 5;
        printf("\n Philosopher %d is hungry.", i + 1);
        chopsticks[i] = wait(chopsticks[i]);
        chopsticks[(i + 1) % 5] = wait(chopsticks[(i + 1) % 5]);
        if (chopsticks[(i + 1) % 5] == 0 && chopsticks[i] == 0)
        {
            printf("\n Philosopher %d is eating.", i + 1);
            phil_status[i] = 0;
        }
        printf("\n\n Philosophers' Status : ");
        for (n = 0; n < 5; n++)
        {
            if (phil_status[n] == 1)
                printf("\n Philosopher %d - Thinking", n + 1);
            else
                printf("\n Philosopher %d - Eating", n + 1);
        }
        printf("\n");
        for (k = 0; k < 2; k++)
        {
            l = rand() % 5;
            printf("\n\tPhilosopher %d is hungry.", l + 1);
            if (chopsticks[l] == 0 || chopsticks[(l + 1) % 5] == 0)
            {
                printf("\n\tPhilosopher %d cannot eat as chopsticks not available.\n", l + 1);
                c = getchar();
                continue;
            }
            chopsticks[l] = wait(chopsticks[l]);
            chopsticks[(l + 1) % 5] = wait(chopsticks[(l + 1) % 5]);
            if (chopsticks[l] == 0 && chopsticks[(l + 1) % 5] == 0)
            {
                printf("\n\tPhilosopher %d is eating.", l + 1);
                phil_status[l] = 0;
                printf("\n\n\tPhilosophers' Status : ");
                for (n = 0; n < 5; n++)
                {
                    if (phil_status[n] == 1)
                        printf("\n\tPhilosopher %d - Thinking", n + 1);
                    else
                        printf("\n\tPhilosopher %d - Eating", n + 1);
                }
                printf("\n");
                chopsticks[l] = signal(chopsticks[l]);
                chopsticks[(l + 1) % 5] = signal(chopsticks[(l + 1) % 5]);
                printf("\n\tPhilosopher %d has finished eating.\n", l + 1);
                phil_status[l] = 1;
            }
            c = getchar();
        }
        chopsticks[i] = signal(chopsticks[i]);
        chopsticks[(i + 1) % 5] = signal(chopsticks[(i + 1) % 5]);
        printf("\n Philosopher %d has finished eating.\n", i + 1);
        phil_status[i] = 1;
        c = getchar();
    }
}
