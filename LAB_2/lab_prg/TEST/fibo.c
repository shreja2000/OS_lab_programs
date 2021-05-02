#include<stdio.h>
#include<time.h>
int fib(int n)
{
   if (n <= 1)
      return n;
   return fib(n-1) + fib(n-2);
}

int main ()
{

  clock_t begin = clock();

printf("%d\n", fib(9));
clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("%f\n", time_spent);
}
// #include<stdio.h>
// #include<stdlib.h>
// #define max 10000
//
// int main(){
// pid_t pid;
// int a[max];
// printf("Enter the size of the sequence:");
// printf("\n");
// scanf("%d",&n);
// for(int i =0;i<n;i++){
//     scanf("%d",&a[i]);
// }
// pid=fork();
// if(pid==0){
//     printf("***THIS IS THE CHILD BLOCK***\n");
//     for(int i=0;i<=n;i+=2)
//         fib+=;
//         printf("%d ",even_sum);
//         printf("\n");
//
// }
// else{
//     int status;
//     wait(&status);
//     printf("***THIS IS THE PARENT BLOCK***\n");
//     for(int i=1;i<n;i+=2)
//         odd_sum+=i;
//         printf("%d ",odd_sum);
//         printf("\n");
// }
// }
