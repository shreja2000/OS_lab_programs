#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define max 100000

int isPrime(int n);

int main(){
  pid_t pid;
  int a[max],n;

  printf("Enter the size:\n");
  scanf("%d",&n);
  while(n<0){
    printf("Enter a non negative number\n");
    scanf("%d",&n);
  }

  for (int i = 0; i < n; i++) {
      a[i]=-1;
  }
  pid=fork();
  if(pid==0){
    printf("***THIS IS THE CHILD BLOCK***\n");
    printf("The fibonacci sequence of %d terms is:\n",n);
    a[0]=0;a[1]=1;a[2]=1;
    printf("%d %d %d ",a[0],a[1],a[2]);
    for (int i = 3; i < n; i++) {
      a[i]=a[i-1]+a[i-2];
      printf("%d ",a[i]);
    }
    printf("\n");
  }
  else{
      int status;
      wait(&status);
      printf("***THIS IS THE PARENT BLOCK***\n");
      printf("The prime number sequence till %d is \n",n);
      for(int i=1;i<n;i++){
        if(isPrime(i))
          printf("%d ",i);
      }
      printf("\n");
    }
}
int isPrime(int n)
{
    if (n <= 1)
        return 0;
    if (n <= 3)
        return 1;

    if (n % 2 == 0 || n % 3 == 0)
        return 0;

    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;

    return 1;
}
