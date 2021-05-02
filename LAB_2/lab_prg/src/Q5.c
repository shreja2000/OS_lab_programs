// (5) Ascending Order sort within Parent and Descending order sort (or vice versa) within the child
// process of an input array. (u can view as two different outputs –first entire array is asc order sorted in op
// and then the second part desc order output)

#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define max 100000

void sort(int a[max],int n);

int main(){
  pid_t pid;
  int a[max],n;
  printf("Enter the n:\n");
  scanf("%d",&n);
  while(n<0){
    printf("Enter a non negative number\n");
    scanf("%d",&n);
  }
  for (int i = 0; i < n; i++)
    scanf("%d",&a[i]);
    pid=fork();
    if(pid==0){
      printf("***THIS IS THE CHILD BLOCK***\n");
      printf("The ascending order of %d terms is:\n",n);
      sort(a,n);
      //output in ascending order
      for(int i=0;i< n;i++){
        printf("%d ",a[i]);
      }
      printf("\n");
    }
    else{
        int status;//wait till child is done to terminate
        wait(&status);
        printf("***THIS IS THE PARENT BLOCK***\n");
        printf("The descending order of %d terms is:\n",n);
        sort(a,n);
        //output in descending order
        for(int i=0;i< n;i++){
          printf("%d ",a[n-1-i]);
        }
     printf("\n");
}
}
//function to sort in ascending order
void sort(int a[max],int n){
  for(int j=0;j<n;j++){
    for(int k=j;k<n;k++){
      if(a[k]<a[j]){
        a[k]=a[k]^a[j];
        a[j]=a[k]^a[j];
        a[k]=a[k]^a[j];
        }
      }
    }
}
