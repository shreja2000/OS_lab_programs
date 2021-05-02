#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
//#include<sys/
#include <unistd.h> 

int main(){
pid_t child,wpid;
int status=0;
//Father code (before child process starts)
for(int id=1;id<5;id++){
    if((child=fork())==0){
        printf("this is %d process",id);
        //child code
        exit(0);
    }
}
while((wpid=wait(&status))>0);
printf("hi\n");
}