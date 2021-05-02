#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
//init semaphores
sem_t x,y;
//create threads
pthread_t tid;
pthread_t writerthreads[100],readerthreads[100];
//tracking number of readers
int readercount = 0;

//reader thread
void *reader(void* param){
    
    sem_wait(&x);
    readercount++;

    //if a reader is reading put the writer on wait
    if(readercount==1)
        sem_wait(&y);
    sem_post(&x);

    printf("%d reader is inside\n",readercount);
    usleep(3);
    sem_wait(&x);
    readercount--;
    if(readercount==0){
        sem_post(&y);
    }
    sem_post(&x);
    printf("%d Reader is leaving\n",readercount+1);
    return NULL;
}

void *writer(void* param){
    printf("Writer is trying to enter\n");
    sem_wait(&y);
    printf("Writer has entered\n");
    sem_post(&y);
    printf("Writer is leaving\n");
    return NULL;
}

int main(){
    
    int num_readers;
    //user input number of readers
    printf("Enter the number of readers:");
    scanf("%d",&num_readers);
    printf("\n");
    
    int n1[num_readers];

    sem_init(&x,0,1);
    sem_init(&y,0,1);

    for(int i=0;i<num_readers;i++){
        pthread_create(&writerthreads[i],NULL,reader,NULL);
        pthread_create(&readerthreads[i],NULL,writer,NULL);
    }

    for(int i=0;i<num_readers;i++){
        pthread_join(writerthreads[i],NULL);
        pthread_join(readerthreads[i],NULL);
    }

}