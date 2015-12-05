/* Arquivo: dois.c (Roland Teodorowitsch; 28 ago. 2013) */
#include <stdio.h>
#include <unistd.h>

int main()
{
	int i;

	for	(i=0;i<30;++i)  {
		sleep(2);          /* Espera 2 segundos */
		printf("2");       /* Imprime "2" */
		fflush (stdout);   /* Limpa o buffer de saida */
	}
	printf("\n");
	return 0;
}

