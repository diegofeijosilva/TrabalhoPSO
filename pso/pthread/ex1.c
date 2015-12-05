/* Arquivo: ex1.c (Roland Teodorowitsch; 17 set. 2013) */
#include <pthread.h>
#include <stdlib.h> 
#include <unistd.h>
#include <stdio.h>
 
void *minha_thread(void *arg)
{
	int i;

	for	( i=0; i<10; i++ ) {
		printf("+");
		fflush(stdout);
		sleep(1);
	} 
	return NULL;
}

int main(void)
{
	pthread_t mt;
	int i;

	if	( pthread_create( &mt, NULL, minha_thread, NULL) ) {
		fprintf(stderr,"Erro em pthread_create()\n");
		abort();
	}
	for	( i=0; i<10; i++ ) {
		printf("-");
		fflush(stdout);
		sleep(1);
	}
	if	( pthread_join ( mt, NULL ) ) {
		fprintf(stderr,"Erro em pthread_join()\n");
		abort();
	}
	return 0;
}
