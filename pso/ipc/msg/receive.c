/* Arquivo: receive.c (Roland Teodorowitsch; 2 set. 2013) */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msg.h"

int main(int argc,char *argv[])
{
	MSG_BUF msgp;
	int     msgsz=MSG_LEN,byterec,res,msqid,fim=0;

	/* Cria a fila de mensagens, com direitos de leitura e escrita (0x180) */
	/* para o dono (criador). */
	msqid = msgget ( (key_t)IPC_KEY, 0x180 | IPC_CREAT );
	if	(msqid==-1)  {
		fprintf(stderr,"Error in msgget(): %s\n",strerror(errno));
		exit(1);
	}
	printf("Server: queue %d created.\n", msqid);
	/* Entra em um laco de recebimento de mensagens. */
	while	(!fim)  {
		byterec = msgrcv ( msqid, (struct msgbuf *)&msgp, msgsz, 0, 0 );
		if	(byterec == -1)  {
			fprintf(stderr,"Error in msgrcv(): %s\n",strerror(errno));
			fim = 1;
		}
		else 	{
			printf("Server: \"%s\" received.\n", msgp.mtext);
			if	( strcmp(msgp.mtext,"fim") == 0 )
				fim = 1;
		}
	}
	/* Destroi a fila criada. */
	res = msgctl ( msqid, IPC_RMID, NULL );
	if	(res==-1)  {
		fprintf(stderr,"Error in msgctl(): %s\n",strerror(errno));
		exit(1);
	}
	return 0;
}

