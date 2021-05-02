#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define MAX 10000

void mergesort2w(int a[],int s,int e);
int a[MAX];

struct bounds{
    int beg,end;
};

//Runner code for merge sort
void *sort(void *ip){
    struct bounds *p=ip;
    mergesort2w(a,p->beg,p->end);

}

//merge function
void merge2w(int a[], int s, int e)
{
	int m=(s+e)/2;
	int x[m-s+1];
	int y[e-m];
	for(int i=s;i<=m;i++) x[i-s]=a[i];
	for(int i=m+1;i<=e;i++) y[i-m-1]=a[i];
	int i=0,j=0,k=s;
	while(i<m-s+1 && j<e-m)
	{
		if(x[i]<y[j])
			a[k++]=x[i++];
		else
			a[k++]=y[j++];
	}
	while(i<m-s+1) a[k++]=x[i++];
	while(j<e-m) a[k++]=y[j++];
}

//Merge sort function
void mergesort2w(int a[],int s,int e)
{
	pid_t rpid,lpid;
    if(s==e) return;
	int m=(s+e)/2;
    struct bounds p1,p2;
    p1.beg=s;
    p1.end=m;
    p2.beg=m+1;
    p2.end=e;
//Create threads and merge sort it in 2 threads
    pthread_t thread[2];
	pthread_create(&thread[0],NULL,sort,&p1);
	pthread_create(&thread[1],NULL,sort,&p2);
	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);
      
	merge2w(a,s,e);
}

int main(){

    int n;
//Inputs
    printf("Enter the size of the array:\n");
    scanf("%d",&n);
    printf("Enter the elements of the array:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);

    mergesort2w(a,0,n-1);

//Output
    printf("The sorted array:\n");
    for(int i=0;i<n;i++)
        printf("%d ",a[i]);

    printf("\n");

}
