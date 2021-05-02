#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

//prime number check
void *prime_no(void *value){

int *n=(int*) value;
int flag=1;
// Corner case
    if (*n <= 1)
        flag=0;
 
// Check from 2 to n-1
    for (int i = 2; i < *n; i++)
        if (*n % i == 0)
            flag=0;
 
    if(flag)
        printf("%d ",*n);
}
int main(int argc,char *argv[]){
    //validations of argc and argv
    if(argc!=2){
        fprintf( stderr, "Please enter valid arguments\n" );
        exit(0);
    }
    //threads instantiation
    pthread_t thread;
    pthread_attr_t attr;
    printf("The prime numbers below the value of %d\n",atoi(argv[1]));
    for(int i=0;i<atoi(argv[1]);i++){
        
        pthread_attr_init(&attr);
        pthread_create(&thread,&attr,prime_no,&i);
        pthread_join(thread,NULL);
        
        
    }
    printf("\n");
    
return 0;


}