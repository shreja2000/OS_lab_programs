#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>


int sum=0;
//returns a to the power of b
int power(int a,int b ){
    int pow=1;
    while(b){
        pow*=a;
        b--;
    }
    return pow;
}

//runner code for the threads declared
void *runner( void *param){

    int *num= (int *) param;

    int c=0,temp=*num;
    while(temp){
        temp=temp/10;
        c++;
    }
    temp=*num;
    sum=0;
    while(temp){
        int x=temp%10;
        sum+=power(x,c);
        temp=temp/10;
    }
    if(sum==*num)
        printf("%d ",*num);
    pthread_exit(0);


}


int main(int argc,char * argv[]){
//validations of argc and argv
    if(argc!=2){
        fprintf( stderr, "Please enter valid arguments\n" );
        exit(0);
    }
    //threads instantiation
    pthread_t thread;
    pthread_attr_t attr;
    printf("The amstrong numbers below the value of %d\n",atoi(argv[1]));
    for(int i=0;i<atoi(argv[1]);i++){
        
        pthread_attr_init(&attr);
        pthread_create(&thread,&attr,runner,&i);
        pthread_join(thread,NULL);
        
        
    }
    printf("\n");
    
return 0;
}