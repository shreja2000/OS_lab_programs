 #include <string.h>
 #include<stdio.h>
 #include<stdlib.h>
 #include<ctype.h>
 #include<unistd.h>
 #include<sys/wait.h>
 #include<sys/ipc.h>
 #include<sys/shm.h>

 #define MAX 10000 
 
 char* create_shm_array(int size)
{
	key_t key = IPC_PRIVATE;

	int shm_id;
	size_t shm_size=size*sizeof(char);
	if((shm_id=shmget(key,shm_size,IPC_CREAT | 0666))==-1)
	{
		perror("shmget");
		exit(1);
	}

	char *shm_arr;
	if((shm_arr=shmat(shm_id,NULL,0))==(int *)-1)
	{
		perror("shmat");
		exit(1);
	}

	return shm_arr;
}

int check(char *s,char c)
{
    int count=0;
        for(int i=0;s[i];i++){
            if(s[i]==c)
  			count++;
		}
    return count;
	 
}
int main()
{
	int count;  
    char *shm_arr=create_shm_array(MAX*sizeof(char));
    
    printf("Enter the string : ");
    gets(shm_arr);

    for(int i=0;shm_arr[i];i++)
        if(shm_arr[i]=tolower(shm_arr[i]));
    
        printf("\n");
    
    for(char c='a';c<='z';c++){
        pid_t pid;
        pid=fork();
        if(pid==0){
        count=check(shm_arr,c);
        if(count){
        printf("[%c]",c);
        for(int i=0;i<count;i++){
            printf("*");
            
        }
        printf("\n");
        }}
        if(pid>0){
            int status;
            waitpid(pid,&status,0);
            exit(0);
        }
        
    }
 
	return 0;
 }