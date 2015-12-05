/* Arquivo: shmserver.c (Roland Teodorowitsch; 2 set. 2013) */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm.h"

int main()
{
	int shmid, res;
	char *mem;

	/* Cria um segmento de memoria compartilhada. */
	shmid = shmget ( (key_t)IPC_KEY, 1024, IPC_CREAT | IPC_EXCL | 0x1c0 );
	if	(shmid == -1)  {
		fprintf(stderr,"Error in shmget(): %s\n",strerror(errno));
		exit(1);
	}
	printf("SHMID = %d\n",shmid);
	/* Conecta o seg. de mem. compartilhada ao seg. de dados do processo. */
	mem = (char *)shmat( shmid, (char *)0, 0);
	if	(mem==(char *)-1)  {
		fprintf(stderr,"Error in shmat(): %s\n",strerror(errno));
	}
	else  {
		strcpy(mem,"TEXTO INICIAL");
		while	(strcmp(mem,"FIM")!=0)  {
			printf("Server tem texto: %s\n",mem);
			sleep(1);
		}
		/* Desconecta o segmento compartilhado. */
		res = shmdt (mem);
		if	(res==-1)
			fprintf(stderr,"Error in shmdt(): %s\n",strerror(errno));
	}
	res = shmctl ( shmid, IPC_RMID, (struct shmid_ds *)0);  
	if	(res == -1)  {
		fprintf(stderr,"Error in shmctl()\n");
		return 1;
	}
	return 0;  
}

