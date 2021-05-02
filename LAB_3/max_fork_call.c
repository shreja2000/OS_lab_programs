#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
  int pid;
  int c=0;
  while(1){
    pid=fork();
    if(pid==0)
      exit(0);
    c++;
    if(pid<0){
      printf("Fork failed!!!!!\n");
      break;
    }
  }
  printf("Max processes: %d\n",c);
}
