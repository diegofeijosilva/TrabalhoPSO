/* Arquivo: ex3.c (Roland Teodorowitsch; 17 set. 2013) */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

void *soma_um(void *arg)
{
	long val;

	val=*(long *) arg;
	printf("Thread %ld: valor recebido=%ld\n", pthread_self(), val);
	val++;
	return (void *)val;
}

int main()
{
	pthread_t t[NUM_THREADS];
	int i;
	long x[NUM_THREADS], *px;

	for	(i=0;i<NUM_THREADS;++i)  {
		x[i] = i*10;
		printf("Thread %ld: valor enviado=%ld\n", pthread_self(),x[i]);
		if	(pthread_create(&(t[i]), NULL, soma_um, (void *)&(x[i])) != 0)
			exit(1);
	}
	for	(i=0;i<NUM_THREADS;++i)  {
		pthread_join(t[i], (void **)&px);
		printf("Thread %ld: valor recebido=%ld\n", pthread_self(),(long)px);
	}
	return 0;
}

