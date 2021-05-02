#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
pid_t pid;
int n;
printf("Enter the size of the sequence:");
printf("\n");
scanf("%d",&n);
while(n<0){
  printf("Enter a non negative number\n");
  scanf("%d",&n);
}
pid=fork();
if(pid==0){
    printf("***THIS IS THE CHILD BLOCK***\n");
    printf("Even sequence:\n");
    for(int i=0;i<n;i+=2)
        printf("%d ",i);
        printf("\n");

}
else{
    int status;
    wait(&status);
    printf("***THIS IS THE PARENT BLOCK***\n");
    printf("Odd sequence:\n");
    for(int i=1;i<n;i+=2)
        printf("%d ",i);
        printf("\n");
}
}
