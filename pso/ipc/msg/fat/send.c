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
	REQ_BUF	reqmsg;
	RESP_BUF respmsg;
	int     byterec, msqid, respsz = RESP_LEN, reqsz = REQ_LEN;
	int	val;
	double	val_fat;
	long    res;

	if	(argc!=2){
		fprintf(stderr,"%s: numero de parametros invalido\n",argv[0]);
		return 1;
	}
	msqid = msgget ( (key_t)IPC_KEY, 0 );
	if	(msqid==-1)  {
		fprintf(stderr,"Error in msgget(): %s\n",strerror(errno));
		exit (1);
	}
	printf("Client: queue %d located.\n", msqid);
	val = atoi(argv[1]);
	reqmsg.mtype = REQ_ID;
	bcopy((void *)&val,(void *)reqmsg.mtext,sizeof(int));
	res = msgsnd ( msqid, (struct msgbuf *)&reqmsg, reqsz, 0 );
	if	(res==-1)  {
		fprintf(stderr,"Error in msgsnd(): %s\n",strerror(errno));
		exit (1);
	}
	if	(val>=0) {
		byterec = msgrcv ( msqid, (struct msgbuf *)&respmsg, respsz, RESP_ID, 0 );
		if	(byterec == -1)  {
			fprintf(stderr,"Error in msgrcv(): %s\n",strerror(errno));
			exit (1);
		}
		bcopy((void *)respmsg.mtext,(void *)&val_fat,sizeof(double));
		printf("Client: \"%d\" sent and received \"%lf\".\n",val,val_fat);
	}
	return 0;
}

