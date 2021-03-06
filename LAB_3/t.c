#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<sys/types.h>
#define shmsize 100
#define shmmode (SHM_R|SHM_W)
#define shmkey (key_t)31

int main() {
    int shmid1, shmid2, pid, status;
    int *shmdata1, *shmdata2, *shmdata;
    int mtx1[10][10], mtx2[10][10];
    int i,j,k,r1,r2,c1,c2;
    struct shmd_ds *shmidds;
    shmid1 = shmget(shmkey,shmsize,shmmode|IPC_CREAT|IPC_EXCL);
    shmdata1 = (int*)shmat(shmid1,0,0);
    shmdata = shmdata1;
    printf("\nShmID: %d ShmData: %d \n",shmid1,*shmdata1);
    printf("Enter the rows and columns of matrix 1:");
    scanf("%d%d",&r1,&c1);
    printf("Enter the matrix 1: \n");
    for(i=0;i<r1;++i)
        for(j=0;j<c1;++j)
            scanf("%d",&mtx1[i][j]);
    printf("\nEnter the rows and columns of matrix 2:");
    scanf("%d%d",&r2,&c2);
    printf("Enter the matrix 2: \n");   
    for(i=0;i<r2;++i)
        for(j=0;j<c2;++j)
            scanf("%d",&mtx2[i][j]);   
    // printf("\n Hello,note this...");
    if(r2!=c1) {
        printf("\nCannot Multiply");
        return 0;
    }

    for(i=0;i<r1/2;i++)
        for(j=0;j<c1;j++) {
        *shmdata1 = 0;
        for(k=0;k<c1;k++)
            *shmdata1 += mtx1[i][k]*mtx2[k][j];
            shmdata1 += sizeof(int);
        }
    pid = fork();
    if(pid == 0) {
        for(i=r1/2;i<r1;i++)
            for(j=0;j<c2;j++) {
                *shmdata1 = 0;
                for(k=0;k<c1;k++)
                    *shmdata1 += mtx1[i][k]*mtx2[k][j];
                    shmdata1 += sizeof(int);
            }       
    }
    while((pid = wait(&status))!= -1);
    shmdata1 = shmdata;
    printf("\n\n\nResult from %d\n", getpid());
    for(i=0;i<r1;++i) {
        printf("\n");
        for(j=0;j<c2;j++,shmdata1+=sizeof(int))
            printf("%d ",*shmdata1);
    }
    shmdt((void*)shmdata1);
    shmdt((void*)shmdata2);
    shmctl(shmid1,IPC_RMID,shmidds);
    //shmctl(shmid2,IPC_RMID,shmidds);
    return 1;
} 