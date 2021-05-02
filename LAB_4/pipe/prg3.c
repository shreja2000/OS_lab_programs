#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(){

//Create two pipes for parent and child read and write.
int p1fd[2],p2fd[2];
int ret1,ret2;
//pid for forking
int pid;
//buf storage for I/P and O/P
char p1wmsg[50],p2wmsg[50];
char p1rmsg[50],p2rmsg[50];

//input
int s,e;
printf("Enter the input string:\n");
scanf("%s",p2wmsg);
int n=0;
while(p2wmsg[n]!='\0')
    n++;
printf("Enter the start and end index of sub_string[0-%d]:\n",n-1);
scanf("%d %d",&s,&e);
//Validation of the input 
while(s<0 || e>n-1){
    printf("Enter values within the range specified!!!\n");
    scanf("%d %d",&s,&e);
    }
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
    
//parent string written into pipe2 
    write(p2fd[1],p2wmsg,sizeof(p2wmsg)+1);

//sub string reading from pipe1
    read(p1fd[0],p1rmsg,sizeof(p1rmsg)+1);

    //Prints the sub-string from [start_index,end_index]
    printf("sub-string @ parent printed:%s\n",p1rmsg);

}

//child process
if(pid==0){
//close unused pipes 
    close(p1fd[0]);
    close(p2fd[1]);

//read string from pipe2
    read(p2fd[0],p2rmsg,sizeof(p2rmsg)+1);
//generate the sub_string
//prints the substring of index [s,e] 
//thats is s and e inclusive 
    int j=0; 
    for(int i=s;i<=e;i++){
        p1wmsg[j]=p2rmsg[i];
        j++;
    }
    p1wmsg[j]='\0';

//sub string written into pipe1
    write(p1fd[1],p1wmsg,sizeof(p1wmsg)+1);

    printf("sub-string @ child printed:%s\n",p1wmsg);

}
}