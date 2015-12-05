all:		sigclient sigserver

sigclient:	sigclient.c
		@cc -o sigclient sigclient.c

sigserver:	sigserver.c
		@cc -o sigserver sigserver.c

clean:
		@rm -f sigserver sigclient *~

info:
		@echo "(c) Roland Teodorowitsch (2 set. 2013)"
