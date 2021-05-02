#include <sys/types.h>
#include <sys/wait.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<time.h>

 size_t fibonacci( size_t n );
int main(){
  clock_t begin = clock();
  printf("%ld\n", fibonacci(10));
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("%f\n", time_spent);

}
size_t fibonacci( size_t n )
{
	pid_t pid1, pid2;
	size_t fib;
	int status;

	switch ( n )
	{
		case 0:	 return 0;
		case 1:	 //FALLTHRU
		case 2:	 return 1;
		default: break;
	}

	pid1 = fork();

	if ( pid1 == 0 ) exit( fibonacci( n - 1 ));

	pid2 = fork();

	if ( pid2 == 0 ) exit( fibonacci( n - 2 ));

	if ( waitpid( pid1, &status, 0 ) == -1 ) err( 1, "waitpid" );

	fib = WEXITSTATUS( status );

	if ( waitpid( pid2, &status, 0 ) == -1 ) err( 1, "waitpid" );

	return fib + WEXITSTATUS( status );
}
