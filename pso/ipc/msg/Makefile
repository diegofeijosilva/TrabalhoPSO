all:		receive send

receive:	receive.c msg.h
		@cc -o receive receive.c

send:		send.c msg.h
		@cc -o send send.c

clean:
		@rm -f send receive *~

info:
		@echo "(c) Roland Teodorowitsch (2 set. 2013)"
