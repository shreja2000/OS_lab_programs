#include<stdio.h>
#define max 100000

void sort(int a[max],int n);

int main(){
  int a[max],n;
  printf("Enter the n:\n");
  scanf("%d",&n);
  for (int i = 0; i < n; i++)
    scanf("%d",&a[i]);
    sort(a,n);
  for (int i = 0; i < n; i++)
      printf("%d ",a[i]);
  printf("\n");
}
void sort(int a[max],int n){
  for(int j=0;j<n;j++){
    for(int k=j;k<n;k++){
      if(a[k]<a[j]){
        a[k]=a[k]^a[j];
        a[j]=a[k]^a[j];
        a[k]=a[k]^a[j];
        }
      }
    }
}
