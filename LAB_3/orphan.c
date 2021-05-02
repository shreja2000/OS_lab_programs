#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    pid_t pid;
    pid=fork();
    if(pid==0){
        printf("____This is the child process____\n");
        sleep(10);
        printf("%d this is an orphan process now__\n",getpid());
    }
    else if(pid>0){
        printf("___This is the parent process____\n");
    }
    else{
        printf("Fork failed\n");
    }
    return 0;
}