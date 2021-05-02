#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>


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


void mergesort2w(int a[],int s,int e)
{
	pid_t rpid,lpid;
    if(s==e) return;
	int m=(s+e)/2;
    lpid=fork();
    if(lpid<0){
        printf("Left child fork failed\n"); 
        exit(0);}
    else if(lpid==0){
        mergesort2w(a,s,m);
        exit(0); }
    rpid=fork();
    if(rpid<0){
        printf("Right child fork failed\n");
        exit(0);}
    else if(rpid==0){ 
        mergesort2w(a,m+1,e);
        exit(0); }
	int status;
    waitpid(lpid,&status,0);
    waitpid(rpid,&status,0);

	merge2w(a,s,e);

}

int main(){
    int shm_id;
    key_t key =IPC_PRIVATE;

    int n;
    
    printf("Enter the size:\n");
    scanf("%d\n",&n);
    
    size_t shm_size=sizeof(int)*n;

    shm_id=shmget(key,shm_size,IPC_CREAT | 0666);
    if(shm_id==-1)
	{	perror("shmget");
    	exit(0);}
    
    int *shm_arr=shmat(shm_id,0,0);
    for(int i=0;i<n;i++)
        scanf("%d",&shm_arr[i]);
    
    mergesort2w(shm_arr,0,n-1);
    
    printf("The sorted array is:\n");
    for(int i=0;i<n;i++)
        printf("%d ",shm_arr[i]);  
    
    shmdt(shm_arr);
    shmctl(shm_id, IPC_RMID, NULL);

    printf("\n");
    return 0;

}
