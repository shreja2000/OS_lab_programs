#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
#include<sys/sysinfo.h>

// #define N 10000

typedef struct par
{
	int a,b;
}par;

void* monte_carlo_runner(void* _param);
int randrange(int a, int b);

int main()
{
//Inputs	
	int r,n,*circle,tot_circle=0;
    printf("Enter the range of values to choose from:\n");
	scanf("%d",&r);
    printf("Enter the number of iterations:\n");
	scanf("%d",&n);
    int N=get_nprocs_conf();
	
    
    long double pi;
	par param[N];
	pthread_t thread[N];
	pthread_attr_t attr[N];

	for(int i=0;i<N;i++)
	{
		param[i].a=r;
		param[i].b=n/N+(n%N>i?1:0);
		pthread_attr_init(&attr[i]);
		pthread_create(&thread[i],&attr[i],monte_carlo_runner,&param[i]);
	}
	printf("generating %d points totally\n\n",n);

	for(int i=0;i<N;i++)
	{
		pthread_join(thread[i],(void*)&circle);
		tot_circle+=*circle;
		free(circle);
	}
	
	pi=((long double)tot_circle)/n*4;
	printf("out of the %d random points generated, %d were found to be inside the circle\n",n,tot_circle);
	printf("pi value obtained %Lf\n",pi);
	printf("error = %Lf percent\n",(pi-M_PI)*100);

	return 0;
}

int randrange(int a, int b)
{
	return a+rand()%(b-a+1);
}

void* monte_carlo_runner(void* _param)
{
	par param=*(par*)_param;
	int x,y,r=param.a,count=param.b,*circle=(int*)malloc(4);
	long rsq=r*r;
	srand(time(0));
	for(int i=0;i<count;i++)
	{
		x=randrange(0,r);
		y=randrange(0,r);
		if(x*x+y*y<=rsq)
			*circle=*circle+1;
	}
	pthread_exit((void*)circle);
}