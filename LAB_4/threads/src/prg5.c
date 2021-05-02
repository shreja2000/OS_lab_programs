#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define MAX 10000

//init n as a global variable 
int n;

//function for sort
void sort(int *arr){
    for(int i=0;i<n;i++)
        for(int j=i;j<n;j++)
            if((arr[i]>arr[j])){
                int temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        
}

//Runner code for finding mean
void *mean(void *ip){
    int *arr =ip;
    double sum=0;
    for(int i=0;i<n;i++){
        sum+=arr[i];
    }
    sum=sum/n;
    printf("The mean is %lf\n",sum);

    pthread_exit(0);


}

//Runner code for finding median
void *median(void *ip){
    int *arr=ip;
    double  median;
    if(n%2==0)
        median =1.0*(arr[n/2]+arr[(n/2)-1])/2;
    else
        median =1.0*arr[n/2];

    printf("The median is %lf\n",median);

    pthread_exit(0);
}

//Runner code for finding mode
void *mode(void *ip){
    int *arr =ip;
    int max_val=0,max=0;
    for(int i=0;i<n;i++){
        int c=0;
        for(int j=i;j<n;j++){
            if(arr[i]==arr[j])
                c++;
        }
        if(c>max){
            max=c;
            max_val=arr[i];
        }

    }

    printf("The mode is %d that repeats %d  times \n",max_val,max);

    pthread_exit(0);

}

int main(){

    //Inputs
    printf("Enter the size of the array:\n");
    scanf("%d",&n);
    int a[MAX];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    
    //sort the array
    sort(a);
    
    //implement threads for mean median and mode calculation
    pthread_t thread[3];
    pthread_attr_t attr[3];
    
    pthread_attr_init(&attr[0]);
    pthread_attr_init(&attr[1]);
    pthread_attr_init(&attr[2]);

    pthread_create(&thread[0],&attr[0],mode,&a);
    pthread_create(&thread[1],&attr[1],median,&a);
    pthread_create(&thread[2],&attr[2],mean,&a);


	pthread_join(thread[0],NULL);
	pthread_join(thread[1],NULL);
	pthread_join(thread[2],NULL);

}