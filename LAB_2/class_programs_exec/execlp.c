# include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/wait.h>

int main ()
{
pid_t pid;
pid = fork();
if (pid == 0)
{
  execlp("ls", "ls", NULL);
}
else
{
wait (NULL); 
printf("Parent Process gets the control \n");
printf ("Parent Has waited for Child to Complete\n");
}
return 0;
}
