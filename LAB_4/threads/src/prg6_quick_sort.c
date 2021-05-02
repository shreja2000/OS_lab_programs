#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define MAX 10000

void *runner(void *param);

int n,arr[MAX],k;

struct bounds
{
	int b,e,k;
};

//Function for swap
void swap(int* a, int* b) 
{ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
} 

//Function for partition
int partition(int arr[], int low, int high) 
{ 
    int pivot = arr[high];    
    int i = (low - 1);   
  
    for (int j = low; j <= high- 1; j++) 
    { 
       if (arr[j] < pivot) 
        { i++;     
          swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i+1],&arr[high]); 
    return i+1; 
} 

//Function of quick sort  
void quicksort(int arr[], int low, int high,int k) 
{ 
    if (high>low) 
    { 
        int q = partition(arr, low, high);  

				struct bounds p,r;
				p.b=low;p.e=q-1;p.k=k;
				r.b=q+1;r.e=high;r.k=k;
				pthread_t thread[2];
				pthread_create(&thread[0],NULL,runner,&p);
				pthread_create(&thread[1],NULL,runner,&r);
				pthread_join(thread[0],NULL);
				pthread_join(thread[1],NULL);

    } 
} 

int main(int argc,char *argv[])
{
//Inputs	
    printf("Enter the size of the array:\n");
    scanf("%d",&n);
    printf("Enter the elements of the array:\n");
	for(int i=0;i<n;i++)
		scanf("%d",&arr[i]);
	k=n;

	quicksort(arr,0,n-1,k);

//Output
	printf("The sorted array:\n");
	for(int i=0;i<k;++i)
		printf("%d ",arr[i]); 
		printf("\n");

	return 0;
}

void *runner(void *param)
{
	struct bounds* p=(struct bounds*)param;
	quicksort(arr,p->b,p->e,p->k); 
}