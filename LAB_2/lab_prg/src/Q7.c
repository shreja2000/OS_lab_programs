#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

#define max 100000

void binary_search (int [], int, int, int);

int main (){
int a[max],n=0,key=0;
printf("Enter the n:\n");
scanf("%d",&n);
while(n<0){
  printf("Enter a non negative number\n");
  scanf("%d",&n);
}
if(!n) return 0;
for (int i = 0; i < n; i++)
  scanf("%d",&a[i]);
  printf("Enter the key:\n");
  scanf("%d",&key);
binary_search(a, 0, n, key);
return 0;
}
void binary_search (int a[], int beg, int end, int key)
{
  int mid = (end + beg)/2;
  if(beg > end)
  {
    return;
  }
  if(beg == end){
    if(a[mid] == key)
    {
      printf("Key found at address: %d\n", mid);
    }
    return;
  }
  if(beg+1 == end){
    binary_search(a, beg, beg, key);
    binary_search(a, end, end, key);
  }
  if(a[mid] == key){
    printf("Key found at address: %d\n", mid);
  }
  pid_t pid = fork();
  if(pid == 0)
  {
    binary_search(a, beg, mid-1, key);
  }
  else
  {
    binary_search(a, mid+1, end, key);
  }
}
//3, 1, 5, 2, 5, 2, 6, 4, 7, 9, 5, 3, 5
