/* Arquivo: msg.h (Roland Teodorowitsch; 2 set. 2013) */

#define IPC_KEY 1000

#define REQ_LEN  4
#define REQ_ID   1
typedef struct {
  long mtype;
  char mtext[REQ_LEN];
} REQ_BUF;

#define RESP_LEN  8
#define RESP_ID   2
typedef struct {
  long mtype;
  char mtext[RESP_LEN];
} RESP_BUF;


