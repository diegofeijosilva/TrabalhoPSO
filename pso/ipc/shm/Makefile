all:		shmserver shmclient

shmserver:	shmserver.c shm.h
		@cc -o shmserver shmserver.c

shmclient:	shmclient.c shm.h
		@cc -o shmclient shmclient.c

clean:
		@rm -f shmclient shmserver *~

info:
		@echo "(c) Roland Teodorowitsch (2 set. 2013)"

