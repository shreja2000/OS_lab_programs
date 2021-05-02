#include <stdio.h>
#include <sys/wait.h>
#include <pthread.h>
#define N 5
void *producer(void *args);
void *consumer(void *args);
int buf[N];
int in = 0, out = 0,counter=0;
int flag[] = {0, 0};
int turn = 0;
// acquire lock
void lock(int id)
{
	// set the flag to let the other thread know that this thread wants to acquire a lock
	flag[id] = 1;
	// give the other thread a chance first
	turn = 1 - id;
	// wait till the other thread finishes
	while (flag[1 - id] == 1 && turn == 1 - id)
		;
}
// release lock
void unlock(int id)
{
	// set the flag to let the other thread know that this thread does not need the lock anymore
	flag[id] = 0;
}

int main(){
	pthread_t tid[2];
	pthread_create(&tid[0], NULL, producer, NULL);
	pthread_create(&tid[1], NULL, consumer, NULL);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	return 0;
}

void *producer(void *args){
	int data = 3, i = 0;
	while (i < 10){
		lock(0);
		buf[in] = data;
		printf("producing data to index %d\n", in);
		in = (in + 1) % N;
		i++;
		counter++;
		unlock(0);
	}
	pthread_exit(0);
}
void *consumer(void *args){
	int data, i = 0;
	while (i < 10){
		while(counter==0);
		lock(1);
		data = buf[out];
		printf("consuming data at index %d\n", out);
		out = (out + 1) % N;
		i++;
		counter--;
		unlock(1);
	}
	pthread_exit(0);
}
