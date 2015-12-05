all:		escreve le_inc	pipe_rd pipe_wr

escreve:	escreve.c
		@cc -o escreve escreve.c

le_inc:		le_inc.c
		@cc -o le_inc le_inc.c

pipe_rd:	pipe_rd.c
		@cc -o pipe_rd pipe_rd.c

pipe_wr:	pipe_wr.c
		@cc -o pipe_wr pipe_wr.c

clean:
		@rm -f escreve le_inc pipe_rd pipe_wr *~

info:
		@echo "(c) Roland Teodorowitsch (2 set. 2013)"

