#include<stdio.h>
#include<unistd.h>
#include<string.h>


int main(){

    //Create two pipes for parent and child read and write.
    int p1fd[2],p2fd[2];
    //pid for forking
    int pid;
    //buf storage for I/P and O/P
    char p1wmsg[50],p2wmsg[50];
    char p1rmsg[50],p2rmsg[50];

    //input 
    printf("Enter the input string:\n");
    scanf("%s",p2wmsg);
    //creation and validation of pipe
    if(pipe(p1fd)==-1){
        printf("Unable to create pipe p1\n");
        return 1;
    }

    if(pipe(p2fd)==-1){
        printf("Unable to create pipe p2\n");
        return 1;
    }

    //fork
    pid=fork();
   
    //Validation of fork
    if(pid<0){
        printf("Unable to create fork!!!\n");
        return -1;
    }

    //parent process
    if(pid>0){
    //close unused pipes 
        close(p1fd[1]);
        close(p2fd[0]);
        
    //write into pipe2     
        write(p2fd[1],p2wmsg,sizeof(p2wmsg)+1);
    //read rev string from pipe1
        read(p1fd[0],p1rmsg,sizeof(p1rmsg)+1);
        printf("Reverse string in parent block:%s\n",p1rmsg);

    }

    //child process
    else if(pid==0){
    //close unused pipes 
        close(p1fd[0]);
        close(p2fd[1]);
    //read from pipe2
        read(p2fd[0],p2rmsg,sizeof(p2rmsg)+1);
    //program to reverse a string and add it to pipe1 write buffer.
    int n=strlen(p2rmsg);
    
    for(int i=0;i<n;i++){
        p1wmsg[i]=p2rmsg[n-1-i];
    }
    p1wmsg[n]='\0';

    //write into pipe1
        write(p1fd[1],p1wmsg,sizeof(p1wmsg)+1);
        printf("Reversed string in child block:%s\n",p1wmsg);

    }

    return 0;
    }