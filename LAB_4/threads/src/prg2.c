#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

#define MAX 10000

struct array_def{
    int arr[MAX];
    int size;

};

void sort(int size,int *arr){
    for(int i=0;i<size;i++)
        for(int j=i;j<size;j++)
            if((arr[i]>arr[j])){
                int temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        
}

void *runner_ascd(void *param){
    struct array_def *ascd=param;
    int n=ascd->size;
    
    sort(n,ascd->arr);

    printf("\nThe array in ascending order\n");
    for(int i=0;i<n;i++){
        printf("%d ",ascd->arr[i]);
    }
    printf("\n");
    
    pthread_exit(0);

}

void *runner_dscd(void *param){
    struct array_def *dscd=param;
    int n=dscd->size;
    printf("\nThe array in descending order:\n");
    sort(n,dscd->arr);

    for(int i=n-1;i>=0;i--){
        printf("%d ",dscd->arr[i]);
    }
    printf("\n");
    
    pthread_exit(0);
} 

int main(int argc,char *argv[]){
    
    int x;
    printf("Enter the size of the array:\n");
    scanf("%d",&x);

    struct array_def *ascd=(struct array_def *)malloc(x*sizeof(int)+1);
    struct array_def *dscd=(struct array_def *)malloc(x*sizeof(int)+1);

    ascd->size=dscd->size=x;


    printf("Enter the array elements:\n");
    for(int i=0;i<x;i++){
        scanf("%d",&ascd->arr[i]);
        dscd->arr[i]=ascd->arr[i];
    }
    printf("\n");
    pthread_t thread[2];
    pthread_attr_t attr[2];
    
    pthread_attr_init(&attr[0]);
    pthread_attr_init(&attr[1]);

    pthread_create(&thread[0],&attr[0],runner_ascd,ascd);
    pthread_create(&thread[1],&attr[1],runner_dscd,dscd);


	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);






}