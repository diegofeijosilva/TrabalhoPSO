/* Arquivo: sem.c (Roland Teodorowitsch; 2 set. 2013) */
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#if !defined(__GNU_LIBRARY__) || defined(_SEM_SEMUN_UNDEFINED)
/* union semun deve ser definida manualmente */
union semun {
	int val;                  /* valor para SETVAL */
	struct semid_ds *buf;     /* buffer para IPC_STAT, IPC_SET */
	unsigned short *array;    /* array para GETALL, SETALL */
	struct seminfo *__buf;    /* Específico para o Linux: buffer para IPC_INFO */
};
#endif

#define gotoxy(A,B)   printf("%c[%d;%dH",27,B,A);
#define clrscr()      { printf("%c[H%c[2J",27,27); fflush(stdout); }

void p(int semid)
{
	int res;
	struct sembuf sops;

	sops.sem_num = 0;
	sops.sem_op = -1;
	sops.sem_flg = 0;
	res = semop (semid,&sops,1);
	if	(res==-1)  {
		fprintf(stderr,"Error in semop(): %s\n",strerror(errno));
		exit(1);
	}
}

void v(int semid)
{
	int res;
	struct sembuf sops;

	sops.sem_num = 0;
	sops.sem_op = 1;
	sops.sem_flg = 0;
	res = semop (semid,&sops,1);
	if	(res==-1)  {
		fprintf(stderr,"Error in semop(): %s\n",strerror(errno));
		exit(1);
	}
}

int main()
{
	pid_t filho;
	int   res,k,semid;

	clrscr();
	semid = semget ( IPC_PRIVATE, 1, 0x1C0 );
	if	(semid==-1)  {
		fprintf(stderr,"Error in semget(): %s\n",strerror(errno));
		exit(1);
	}
	res = semctl (semid,0,SETVAL,(union semun)(int)1);
	if	(res == -1)  {
		fprintf(stderr,"Error in semctl(semid,0,SETVAL,1): %s\n",strerror(errno));
		exit(1);
	}
	filho = fork();
	if	(filho==0)  {
		p(semid);
		gotoxy(10,5);
		printf("PROCESSO FILHO:");
		fflush(stdout);
		v(semid);
		while	(1)
			for	(k=0;k<100000;++k)  {
				p(semid);
				gotoxy(40,5);
				printf("%06d",k);
				fflush(stdout);
				v(semid);
			}
	}
	p(semid);
	gotoxy(10,3);
	printf("PROCESSO PAI:");
	fflush(stdout);
	v(semid);
	for	(k=0;k<50000;++k)  {
		p(semid);
		gotoxy(40,3);
		printf("%06d",k);
		fflush(stdout);
		v(semid);
	}
	kill ( filho, SIGKILL );
	res = semctl (semid,0,IPC_RMID,0);
	if	(res == -1)  {
		fprintf(stderr,"Error in semctl(semid,0,IPC_RMID,0): %s\n",strerror(errno));
		exit(1);
	}
	gotoxy(1,7);
	return 0;
}

