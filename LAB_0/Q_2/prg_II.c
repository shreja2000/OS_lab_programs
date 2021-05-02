#include<stdio.h>
#include<stdlib.h>
//input validation error msgs
char err[]="Too less or too may arguments\nUsage:\n./mysort  <ascd/dscd> <sizeof(input_arr)> <input_arr[0:size-1]>\n1 for ascd\n0 for dscd\n";
char err1[]="Invalid value\n1 for ascd\n0 for dscd";
int main(int argc,char *argv[]){
    int i,j,k,max,a[100],size,flag;
     if(argc==2||argc==1||argc==0){
        printf("%s",err);
        printf("\n");
        exit(-1); 
    }
    size=atoi(argv[2]);

    if (argc!=size+3)
    {
        printf("%s",err);
        printf("\n");
        exit(-1);
    }
   
    flag=atoi(argv[1]);
    if(flag!=1&&flag!=0){
        printf("%s",err1);
        printf("\n");
        exit(-1);
    }
    printf("the sorted array is:");
    for(i=0;i<size;i++){
        a[i]=atoi(argv[i+3]);
    }
    max=a[0];

        for(j=0;j<size;j++){
            for(k=j;k<size;k++){
                if(a[k]<a[j]){
                    a[k]=a[k]^a[j];
                    a[j]=a[k]^a[j];
                    a[k]=a[k]^a[j];
                    
                }
            }
        }
        

    for(int i=0;i< size;i++){
        if(flag==1){
            printf("%d ",a[i]);
        }
        else{
            printf("%d ",a[size-1-i]);
        }
    }
    printf("\n");
}
    
