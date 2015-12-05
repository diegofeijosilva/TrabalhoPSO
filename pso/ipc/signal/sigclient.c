/* Arquivo: sigclient.c (Roland Teodorowitsch; 2 set. 2013) */
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int res,pid,sig;

	if	(argc<3)  {
		fprintf(stderr,"Syntax: %s <pid> <signal>\n",argv[0]);
		return(1);
	}
	pid = atoi (argv[1]);
	sig = atoi (argv[2]);
	res = kill ( pid, sig );
	if	( res == -1 )  {
		fprintf(stderr,"Error in kill(): %s\n",strerror(errno));
		return (1);
	}
	printf("Client: signal %d sent to process %d.\n",sig,pid);
	return 0;
}

