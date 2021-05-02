#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include<unistd.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N //the philosopher to the left of phnum
#define RIGHT (phnum + 1) % N //the philosopher to the right of phnum
//state in which the phil is in 
int state[N];
//the 5 philosophers
int phil[N] = {0, 1, 2, 3, 4};
//init semaphores
sem_t mutex;
sem_t S[N];

//if a phil is hungry and the left and the right phils 
//arent eating (left and right forks are free)
//change the state from hungry to eating of phnum
void test(int phnum){
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING){
        state[phnum] = EATING;

        sleep(2);//eat fir 2 secs

        printf("Philosopher %d takes fork %d and %d\n",
               phnum + 1, LEFT + 1, phnum + 1);

        printf("Philosopher %d is Eating\n", phnum + 1);

        //send signal that pnum is done 
        sem_post(&S[phnum]);
    }
}

void take_fork(int phnum){
    //if hungry enter the loop and put the phil in wait and set state as HUNGRY
    sem_wait(&mutex);

    state[phnum] = HUNGRY;

    printf("Philosopher %d is Hungry\n", phnum + 1);
    //test if left and right forks are free
    test(phnum);
    sem_post(&mutex);

    // if not free wait to be signalled
    sem_wait(&S[phnum]);

    sleep(1);
}

// put down forks
void put_fork(int phnum){
    //start of cs
    sem_wait(&mutex);

    // chnage the state to thinking
    state[phnum] = THINKING;

    printf("Philosopher %d putting fork %d and %d down\n",
           phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d is thinking\n", phnum + 1);
    //see if the left or the right neigbours want the forks
    test(LEFT);
    test(RIGHT);
    //end of cs
    sem_post(&mutex);
}

void *philospher(void *num){

    while (1){

        int *i = num;
        sleep(1);
        take_fork(*i);
        sleep(0);
        put_fork(*i);
    }
}

int main(){

    int i;
    pthread_t thread_id[N];

    // initialize the semaphores
    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);

    // create philosopher processes
    for (i = 0; i < N; i++){
        pthread_create(&thread_id[i], NULL,
                       philospher, &phil[i]);

        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    return 0;
}