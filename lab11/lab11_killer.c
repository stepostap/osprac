#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

//Killer
struct request {
    long mtype;
    struct {
      pid_t pid;
      float message;
    } info;
  } requestbuf;

int main(void)
{
  
  char pathname[]="server.c";
  key_t  key;
  int i,len, maxlen, msqid;
  long j;

  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }
  if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
    printf("Can\'t get msqid\n");
    exit(-1);
  }
  
  requestbuf.mtype = 2;
  requestbuf.info.pid = getpid();
  requestbuf.info.message = 0;
  len = sizeof(requestbuf.info);

  if (msgsnd(msqid, (struct request *) &requestbuf, len, 0) < 0) {
    printf("Can\'t send messages to queue\n");
    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
    exit(-1);
  }

  printf("Killer\tI killed a server\n");

  return 0;
}