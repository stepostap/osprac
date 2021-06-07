#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <stdlib.h>

int i = 31;
int res = 0;
int sign;
int pid;

void my_handler(int nsig) {
  if (i == 31)
    sign = nsig == 12;
  else {
    res <<= 1;
    if (sign ^ (nsig == 12))
      res++;
  }
  i--;
  kill(pid, SIGUSR1);
}

int main(void) {
  (void) signal(SIGUSR1, my_handler);
  (void) signal(SIGUSR2, my_handler);

  printf("Receiver ID: %d\n", getpid());
  printf("Sender ID:\n");
  scanf("%d", &pid);

  kill(pid, SIGUSR1);

  while(i >= 0);

  if (sign)
    res = (res + 1) * (-1);
  printf("Number = %d\n", res);

  return 0;
}
