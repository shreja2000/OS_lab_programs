// (6) Given an input array use parent child relationship to sort the first half of array in ascending order and
// the trailing half in descending order (parent / child is ur choice)

//if its an odd sized array the first int(n/2) is sorted in ascending order by the child
//and the  rest is sorted in descending the parent process.

#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define max 100000

void sort(int a[max],int x,int y);

int main(){
  pid_t pid;
  int a[max],n;
  printf("Enter the n:\n");
  scanf("%d",&n);
  while(n<0){
    printf("Enter a non negative number \n");
    scanf("%d",&n);
  }
  for (int i = 0; i < n; i++)
    scanf("%d",&a[i]);
    pid=fork();
    if(pid==0){
      printf("***THIS IS THE CHILD BLOCK***\n");
      printf("The ascending order of %d terms is:\n",n/2);
      sort(a,0,n/2);
      //output in ascending order
      for(int i=0;i<n/2;i++){
        printf("%d ",a[i]);
      }
      printf("\n");
    }
    else{
        int status;//wait till child is done to terminate
        wait(&status);
        printf("***THIS IS THE PARENT BLOCK***\n");
        sort(a,(n/2)+1,n);
        //output in descending order
        int x=0;
        if(n%2==0){
          x=n/2-1;
          printf("The descending order of %d terms is:\n",n/2);
        }
        else{
          x=n/2;
          printf("The descending order of %d terms is:\n",n/2+1);
        }
        for(int i=0;i<=x;i++){
          printf("%d ",a[n-1-i]);
        }
     printf("\n");
}
}
//function to sort in ascending order
void sort(int a[max],int x,int y){
  for(int j=x;j<y;j++){
    for(int k=j;k<y;k++){
      if(a[k]<a[j]){
        a[k]=a[k]^a[j];
        a[j]=a[k]^a[j];
        a[k]=a[k]^a[j];
        }
      }
    }
}
