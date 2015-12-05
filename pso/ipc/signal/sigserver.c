/* Arquivo: sigserver.c (Roland Teodorowitsch; 2 set. 2013) */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void sig_handler(int val)
{
	printf("Server: signal %d received.\n", val);
}


int main(int argc, char *argv[])
{
	int i;
	void (*oldsighand)(int);

	printf("Server: PID=%d\n",getpid());
	for	(i=1;i<32;++i)  {
		if	( (i!=SIGKILL) && (i!=SIGSTOP) )  {
			oldsighand = signal ( i, sig_handler );
			if	( oldsighand == SIG_ERR )  {
				fprintf(stderr,"Error in signal(): %s\n",strerror(errno));
				return 1;
			}
		}
	}
	while (1)
		  pause(); /* Bloqueia o processo ate' que um sinal seja recebido. */ 
	return 0;
}
