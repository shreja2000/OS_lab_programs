#include<stdio.h>
#include<unistd.h>

int  main(){
//Create two pipes for parent and child read and write.
int p1fd[2],p2fd[2];
int ret1,ret2;
//pid for forking
int pid;
//buf storage for I/P and O/P
char p1wmsg[50],p2wmsg[50];
char p1rmsg[50],p2rmsg[50];

//input
printf("Enter the input string2:\n");
scanf("%s",p2wmsg);
printf("Enter the input string1:\n");
scanf("%s",p1wmsg);

//creation and validation of pipe
if((ret1=pipe(p1fd))==-1){
    printf("Unable to create pipe p1\n");
    return 1;
}

if((ret2=pipe(p2fd))==-1){
    printf("Unable to create pipe p2\n");
    return 1;
}

//fork
pid=fork();

//parent process
if(pid>0){
//close unused pipes 
    close(p1fd[1]);
    close(p2fd[0]);
    
//read string from pipe1
    read(p1fd[0],p1rmsg,sizeof(p1rmsg)+1);
    // printf("")
//concatenate 2 strings parent string +child string
    int m=0,n=0;
    while(p2wmsg[n]!='\0')
        n++;
    while(p1rmsg[m]!='\0')
        m++;
    for(int i=0;i<m;i++){
    p2wmsg[n+i]=p1rmsg[i];
}
p2wmsg[n+m]='\0';
printf("concat string @ parent printed:%s\n",p2wmsg);

//parent string written into pipe2 
    write(p2fd[1],p2wmsg,sizeof(p2wmsg)+1);

}
//child process
if(pid==0){
//close unused pipes 
    close(p1fd[0]);
    close(p2fd[1]);

//child string written into pipe1
    write(p1fd[1],p1wmsg,sizeof(p1wmsg)+1);

//read concat string from pipe2
    read(p2fd[0],p2rmsg,sizeof(p2rmsg)+1);

printf("concat string @ child printed:%s\n",p2rmsg);

}
}