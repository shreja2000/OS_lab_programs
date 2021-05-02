#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    int i = 0;
    pid_t pid, pid1, pid2;
    pid = fork(); //gives child 2 of 1
    printf("1  2\n");
    i += 4;
    if (pid != 0)
    {
        pid1 = fork(); //gives child 3 of 1
        while (i > 0)
        {
            printf(" ");
            i--;
        }
        printf("1  3\n");
        if (pid1 == 0)
            fork(); //gives 7 child of 3
    }
    else
    {
        pid = fork(); //gives 4 child of 2
        if (pid != 0)
        {
            pid1 = fork(); //gives 5 child of 2
            if (pid1 != 0)
            {
                pid2 = fork(); //gives 6 child of 2
            }
            else
            {
                fork(); //gives 9 child of 5
            }
        }
        else
        {
            fork(); //gives 8 child of 4
            printf("hi\n");
        }
    }
}