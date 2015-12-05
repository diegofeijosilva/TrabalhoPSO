/* Arquivo: ptrace.c (Roland Teodorowitsch; 2 set. 2013) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ptrace.h>

int main()
{
	pid_t p;
	int   x,status;
	long  val='A';

	p = fork();
	if	(p==0)  {
		ptrace(PTRACE_TRACEME,0,NULL,NULL);
		/* FILHO */
		for	(x=0;x<10;++x)  {
			printf("%c\n",(int)val);
			sleep(1);
		}
		exit(0);
	}
	/* PAI */
	sleep(5);
	kill(p,SIGUNUSED);
	wait(&status);
	val = ptrace(PTRACE_PEEKDATA,p,(void *)&val,NULL);
	++val;
	ptrace(PTRACE_POKEDATA,p,(void *)&val,(void *)val);
	ptrace(PTRACE_CONT,p,31,NULL);
	wait(&status);
	return 0;
}
