/* Arquivo: msg.h (Roland Teodorowitsch; 2 set. 2013) */

#define IPC_KEY 123

#define MSG_LEN  256
#define MSG_ID     1

typedef struct {
  long mtype;
  char mtext[MSG_LEN];
} MSG_BUF;

