#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

struct cont{
    int arr[20][2],beg,end,key;
};

pthread_t thread[1000];
int x=0;


void *bin_search(void *param){
    struct cont *a=param;
    int end =a->end,beg=a->beg;
    int mid = (beg+end)/2;

    if(beg>end)
        return 0;
    
    if(beg == end){
        if(a->arr[mid][0]==a->key)
            a->arr[mid][1]=1;
        return 0;
    }

    if(beg+1==end){
        a->beg=a->end;
        pthread_create(&thread[x],NULL,bin_search,a);
        x++;
        a->beg=a->end=end;
        
        pthread_create(&thread[x], NULL, bin_search, a);
        x++;
        a->beg=beg;
        a->end=end;
    }
    if(a->arr[mid][0] == a->key){
        a->arr[mid][1] = 1;
    }
    a->end = mid-1;
    bin_search(a);
    pthread_create(&thread[x], NULL, bin_search, a);x++;
    a->beg = mid+1;
    a->end = end;
    bin_search(a);
    pthread_create(&thread[x], NULL, bin_search, a);x++;
}
int main (){
    struct cont *a = (struct cont *)malloc(sizeof(struct cont));
    
    int n;
    printf("Enter size of array\n");
    scanf("%d", &n);
    printf("Enter elements of array:\n");
    
    for(int i=0; i<n; i++)
        scanf("%d", &a->arr[i][0]);
    printf("Enter key to search for:\n");
        scanf("%d", &a->key);
        a->end = n;
        a->beg = 0;
    bin_search(a);
    
    for(int i=0; i<x; i++)
        pthread_join(thread[i],NULL);

    for(int i=0; i<n; i++)
        if(a->arr[i][1] == 1)
    printf("Key found at address: %d\n", i);
    
    return 0;
}