/* Arquivo: pipe_wr.c (Roland Teodorowitsch; 2 set. 2013) */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
	FILE *pipe;

	/* Inicia um processo e estabele um duto com este processo. O processo */
	/* receberá o que se enviar para o duto como se fosse a entrada padrão. */
	pipe = popen("./le_inc","w");
	if	( pipe == NULL )  {   /* Verifica se popen() funcionou */
		fprintf(stderr,"Error in popen(): %s\n", strerror(errno));
		exit(1);
	}
	fprintf(pipe,"15\n");   /* Envia um valor para o duto */
	pclose(pipe);               /* Fecha o duto */
	return 0;
}

