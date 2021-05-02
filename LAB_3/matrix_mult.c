 #include <string.h>
 #include<stdio.h>
 #include<stdlib.h>
 #include <ctype.h>
 #include<unistd.h>
 #include<sys/wait.h>
 #include<sys/ipc.h>
 #include<sys/shm.h>

void multiply(int m1, int m2, int mat1[][m2], int n1, int n2, int mat2[][n2]) { 
	int x, i, j; 
	int res[m1][n2]; 
	for (i = 0; i < m1; i++) { 
		for (j = 0; j < n2; j++) { 
			res[i][j] = 0; 
			for (x = 0; x < m2; x++) { 
                pid_t pid;
                pid=fork();
                if(pid==0){
				*(*(res + i) + j) += *(*(mat1 + i) + x) * *(*(mat2 + x) + j); 
			}
            if(pid>0){
            int status;
            waitpid(pid,&status,0);
            exit(0);
            }
        } 
	} 
} 
		printf("\n"); 

	for (i = 0; i < m1; i++) { 
		for (j = 0; j < n2; j++) { 
			printf("%d ", *(*(res + i) + j)); 
		} 
		printf("\n"); 
	} 
} 

int* create_shm_array(int n,int m)
{
	key_t key = IPC_PRIVATE;
	int shm_id;
	size_t shm_size=sizeof(int)*m*n;
    shm_id=shmget(key,shm_size,IPC_CREAT | 0666);
    int x=shm_id;
	if(x==-1)
	{
		perror("shmget");
		exit(1);
	}

	int *shm_arr;
	if((shm_arr=shmat(shm_id,NULL,0))==(int *)-1)
	{
		perror("shmat");
		exit(1);
	}

	return shm_arr;
}
 
int main() 
{ 
    int r1,r2,c1,c2;
    printf("Enter the #rows and #cols of mat1:\n");
    scanf("%d %d",&r1,&c1);

    printf("Enter the #rows and #cols of mat2:\n");
    scanf("%d %d",&r2,&c2);
    
    int* shm_arr1=create_shm_array(r1*sizeof(int),c1*sizeof(int));
    int* shm_arr2=create_shm_array(r2*sizeof(int),c2*sizeof(int));
    
    printf("Enter the mat1 elements:\n");
    for(int i=0;i<r1;i++)
        for(int j=0;j<c1;j++)
            scanf("%d",&shm_arr1[i]);
    
    printf("Enter the mat1 elements:\n");    
    for(int i=0;i<r2;i++)
        for(int j=0;j<c2;j++)
            scanf("%d",&shm_arr2[i]);

	multiply(r1, c1, shm_arr1, r2, c2, shm_arr2); 
	return 0; 
} 