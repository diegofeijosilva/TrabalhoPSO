/* Arquivo: pipe_rd.c (Roland Teodorowitsch; 2 set. 2013) */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
	int var;
	FILE *pipe;

	/* Inicia um processo e estabele um duto com este processo. O que o */
	/* processo imprimir na saída padrão poderá ser capturado através do duto. */
	pipe = popen ("./escreve","r");
	if	( pipe == NULL )  {   /* Verifica se popen() funcionou */
		fprintf(stderr,"Error in popen(): %s\n", strerror(errno));
		exit(1);
	}
	fscanf(pipe,"%d",&var);   /* Lê um valor do duto */
	printf("%d\n",var+1);     /* Imprime o valor lido mais um na saída */
	pclose(pipe);             /* Fecha do duto */
	return 0;
}

