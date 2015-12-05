/* Arquivo: um.c (Roland Teodorowitsch; 28 ago. 2013) */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int	i,status;
	pid_t	num_proc;

	num_proc = fork();
	if	(num_proc==0)  {
		execl ("./dois", NULL, NULL);
		exit (1);
	}
	for	(i=0;i<30;++i)  {
		sleep(1);          /* Espera 1 segundo */
		printf("1");       /* Imprime "1" */
		fflush (stdout);   /* Limpa o buffer de saida */
	}
	wait(&status);
	printf("Filho terminou com estado: %d\n",WEXITSTATUS(status));
	return 0;
}
