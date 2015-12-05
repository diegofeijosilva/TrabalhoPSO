/* Arquivo: ex2.c (Roland Teodorowitsch; 17 set. 2013) */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *soma_um(void *arg)
{
	static int val;

	val=*(int *) arg;
	printf("Thread %ld: valor recebido=%d\n", pthread_self(), val);
	val++;
	return (void *)&val;
}

int main()
{
	pthread_t t;
	int x=5, *px;

	printf("Thread %ld: valor enviado=%d\n", pthread_self(),x);
	pthread_create(&t, NULL, soma_um, (void *)&x);
	pthread_join(t, (void **)&px);
	printf("Thread %ld: valor recebido=%d\n", pthread_self(),*px);
	return 0;
}
