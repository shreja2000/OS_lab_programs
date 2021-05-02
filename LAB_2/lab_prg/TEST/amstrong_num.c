#include<stdio.h>
#include<stdlib.h>
#define MAX 1000000
#define CUBE(a) ((a)*(a)*(a))
int main(){
    int n,a[MAX],b[MAX],k=0;
    for(int i=0;i<100;i++){
        a[i]=-1;
        b[i]=-1;
    }
    scanf("%d",&n);
    
     for(int i=0;i<n;i++){
        int k=i;
        int j=0;
        while(k){
            a[j]=k%10;
            k=k/10;
            j++;
        }

        
        int sum=0;
        for(int l=0;l<j;l++){
            sum+= CUBE(a[l]);
            a[l]=-1;
        }
        if(sum==i){
            printf("%d:%d\n",sum,i);
            b[i]=1;
        }    
     }
     printf("the amstrong numbers are:\n");
     for(int i=0;i<n;i++){
     if(b[i]==1){

            printf("%d ",i);}
        
     }
    printf("\n");
}