/* Arquivo: waittest.c (Roland Teodorowitsch; 2 set. 2013) */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
	pid_t num_proc, filho;
	int status;

	num_proc = fork();
	if	(num_proc==0)  {
		printf("Filho: meu pid eh %u\n",getpid());
		printf("Filho: o pid do pai eh %u\n",getppid());
		fflush(stdout);
		sleep(5);   
		exit(5);
	}
	printf("Pai: o meu pid eh %u\n",getpid());
	printf("Pai: o pid do filho eh %u\n",num_proc);
	fflush(stdout);
	sleep(10);
	filho=wait(&status);
	printf("Pai: filho %u terminou com estado %d\n",filho,WEXITSTATUS(status));
	return 0;
}

