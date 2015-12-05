/* Arquivo: shmclient.c (Roland Teodorowitsch; 2 set. 2013) */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm.h"

int main(int argc, char *argv[])
{
	int shmid, res;
	char *mem;

	/* Obtem o identificador do segmento de memoria compartilhada. */
	shmid = shmget ( (key_t)IPC_KEY, 1024, 0x1c0 );
	if	(shmid == -1)  {
		fprintf(stderr,"Error in shmget(): %s\n",strerror(errno));
		exit(1);
	}
	/* Conecta o seg. de mem. compartilhada ao seg. de dados do processo. */
	mem = (char *)shmat( shmid, (char *)0, 0);
	if	(mem==(char *)-1)  {
		fprintf(stderr,"Error in shmat(): %s\n",strerror(errno));
		exit(1);
	}
	else  {
		if	(argc>1)  {
			if	(strlen(argv[1])>1023)
				strcpy(mem,"TEXTO MUITO GRANDE");
			else
				strcpy(mem,argv[1]);
		}
		else
			strcpy(mem,"SEM TEXTO");
		/* Desconecta o segmento compartilhado. */
		res = shmdt (mem);
		if	(res==-1)  {
			fprintf(stderr,"Error in shmdt(): %s\n",strerror(errno));
			exit(1);
		}
	}
	return 0;  
}

