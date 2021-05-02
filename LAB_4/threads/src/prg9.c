#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int n;                          // size of fibonacci sequence.
int *fibseq;                    // array that holds the value of each fibonacci term.
int i;                          // counter for the threads.

void *runn(void *arg);

int main(int argc, char *argv[]){
    // valdiate num of args.
    if (argc != 2) {
        printf("format is:./a.out <intgervalue>\n");
        return -1;
    }                           
   // valdiate value of arg1.
    if (atoi(argv[1]) < 0){
        printf("%d must be>=0\n", atoi(argv[1]));
        return -1;
    }

    n = atoi(argv[1]);
    
    fibseq = (int *)malloc(n * sizeof(int));
    
    // set of thread attribute
    pthread_t *threads = (pthread_t *) malloc(n * sizeof(pthread_t));
    pthread_attr_t attr;        
    pthread_attr_init(&attr);

     // End of creating threads.
    for (i = 0; i < n; i++){
        pthread_create(&threads[i], &attr, runn, NULL);
    }                      

    int j;
    // End of wating the threads to exit.
    for (j = 0; j < n; j++){
        pthread_join(threads[j], NULL);
    }                      

    // printing fibseq.
    printf("The Fibonacci sequence.:");
    int k;

  // End of printing fibseq.
    for (k = 0; k < n; k++){
        printf("%d,", fibseq[k]);
    } 
     printf("\n");                       
    return 0;
}                               

void *runn(void *arg)
{
    if (i<= 0){
        fibseq[i] = 0;
    }                           // first fib term

    if (i == 1||i==2){
        fibseq[i] = 1;
    }
                               // second fib term
    else{
        fibseq[i] = fibseq[i - 1] + fibseq[i - 2];
    }                           
}                               