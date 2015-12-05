/* Arquivo: receive.c (Roland Teodorowitsch; 2 set. 2013) */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msg.h"

double fatorial(int n);

double fatorial(int n)
{
	double res=1.0;

	while	(n>=2)
		res *= n--;
	return res;
}

int main(int argc,char *argv[])
{
	RESP_BUF respmsg;
	REQ_BUF reqmsg;
	int     respsz=RESP_LEN,reqsz=REQ_LEN,byterec,res,msqid,fim=0;
	int     val;
	double  val_fat;

	msqid = msgget ( (key_t)IPC_KEY, 0x180 | IPC_CREAT );
	if	(msqid==-1)  {
		fprintf(stderr,"Error in msgget(): %s\n",strerror(errno));
		exit(1);
	}
	printf("Server: queue %d created.\n", msqid);
	while	(!fim)  {
		byterec = msgrcv ( msqid, (struct msgbuf *)&reqmsg, reqsz, REQ_ID, 0 );
		if	(byterec == -1)  {
			fprintf(stderr,"Error in msgrcv(): %s\n",strerror(errno));
			fim = 1;
		}
		else 	{
			bcopy((void *)reqmsg.mtext,(void *)&val,reqsz);
			printf("Server: \"%d\" received.\n", val);
			if	( val < 0 )
				fim = 1;
			else {
				val_fat = fatorial(val);
				respmsg.mtype = RESP_ID;
				bcopy((void *)&val_fat,(void *)respmsg.mtext,sizeof(double));
				res = msgsnd(msqid,(struct msgbuf *)&respmsg,respsz,0);
				if	(res==-1)  {
					fprintf(stderr,"Error in msgsnd(): %s\n",strerror(errno));
					exit (1);
				}
			}
		}
	}
	res = msgctl ( msqid, IPC_RMID, NULL );
	if	(res==-1)  {
		fprintf(stderr,"Error in msgctl(): %s\n",strerror(errno));
		exit(1);
	}
	return 0;
}

