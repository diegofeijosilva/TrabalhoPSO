/* Arquivo: send.c (Roland Teodorowitsch; 2 set. 2013) */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msg.h"

int main(int argc, char *argv[])
{
	MSG_BUF msgp;
	int     msqid, msgsz = MSG_LEN;
	long    res;

	/* Obtem o numero da fila de mensagens. */
	msqid = msgget ( (key_t)IPC_KEY, 0 );
	if	(msqid==-1)  {
		fprintf(stderr,"Error in msgget(): %s\n",strerror(errno));
		exit (1);
	}
	printf("Client: queue %d located.\n", msqid);
	/* Monta a mensagem, definindo o seu tipo e o seu conteudo. */
	msgp.mtype = MSG_ID;
	if	(argc<2)
		strcpy ( msgp.mtext, "SEM TEXTO" );
	else
		if	( strlen(argv[1]) > 255 ) 
			strcpy ( msgp.mtext, "MENSAGEM MUITO GRANDE" );
		else
			strcpy ( msgp.mtext, argv[1] );
	/* Envia a mensagem. */
	res = msgsnd ( msqid, (struct msgbuf *)&msgp, msgsz, 0 );
	if	(res==-1)  {
		fprintf(stderr,"Error in msgsnd(): %s\n",strerror(errno));
		exit (1);
	}
	printf("Client: \"%s\" sent.\n",msgp.mtext);
	return 0;
}

