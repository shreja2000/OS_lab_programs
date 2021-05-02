#include<stdio.h>
//#include <sys/types.h> 
#include <unistd.h> 

int main(){
    int pid;
    printf("%d\n",pid);
    pid=fork();
    printf("%d\n",pid);

    if(pid<0)
        {printf("Fork failed\n");
    printf("%d\n",pid);
        }
    else if (pid==0)
        {printf("Child block\n");
    printf("%d\n",pid);
        }
    else if (pid>0)
        {printf("Parent block\n");
        printf("HI");
    printf("%d\n",pid);
        }
    return 0;
}