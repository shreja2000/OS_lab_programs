#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include<math.h>

#define max 100000

// int power(int x, unsigned int y)
// {
// 	if (y == 0)
// 		return 1;
// 	if (y % 2 == 0)
// 		return power(x, y / 2) * power(x, y / 2);
// 	return x * power(x, y / 2) * power(x, y / 2);
// }

int main (){
	int n=0,a[max];
	for(int i=0;i<max;i++){
		a[i]=-1;
	}
	printf("Enter the number\n");
	scanf("%d",&n);
	while(n<0){
	  printf("Enter a non negative number\n");
	  scanf("%d",&n);}


	for(int i=0; i<=n; i++){
		int sum = 0;
		int k = i;
		int c = 0,c1=c,x=i;
		while (x) {
			c++;
			x= x/10;
		}
    if(c1!=c){
      printf("%d",c);
    }
		while (k)
		{
			pid_t pid = vfork();
			if(pid == 0){
				int digit = k%10;
				sum =sum+pow(digit,c);
				exit(0);
			}
			else{
				k = k/10;
			}
		}
		if(sum == i){
			a[i]=sum;
	}
}
	printf("The amstrong numbers are less than %d :\n",n+1);
	for(int i=0;a[i]<=n;i++){
		if(a[i]!=-1 && a[i]>=0)
			printf("%d ",i);
	}
	printf("\n");
	return 0;
}
