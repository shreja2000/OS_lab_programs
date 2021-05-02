#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
pid_t pid;
int n,odd_sum=0,even_sum=0;
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
    printf("The even sum is:\n");
    for(int i=0;i<=n;i+=2)
        even_sum+=i;
        printf("%d ",even_sum);
        printf("\n");

}
else{
    int status;
    wait(&status);
    printf("***THIS IS THE PARENT BLOCK***\n");
    printf("The odd sum is:\n");
    for(int i=1;i<=n;i+=2)
        odd_sum+=i;
        printf("%d ",odd_sum);
        printf("\n");
}
}
