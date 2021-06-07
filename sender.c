#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <stdlib.h>

int pid;
int num;
int bits[32];
int sign;
int success = 0;

void my_handler(int nsig) {
  success = 1;
}

int main(void) { 
  (void) signal(SIGUSR1, my_handler);

  printf("Snder ID: %d\n", getpid());
  printf("Receiver ID:\n");
  scanf("%d", &pid);

  while (!success);

  printf("Number:\n");
  scanf("%d", &num);

  sign = num < 0;
  if (sign) {
    num = num * (-1);
    num--;
  }
  bits[0] = sign;

  for (int i = 0; i < 31; ++i) {
    bits[31 - i] = sign ^ (num % 2);
    num /= 2;
  }

  for (int i = 0; i < 32; ++i) {
    if (bits[i])
      kill(pid, SIGUSR2);
    else
      kill(pid, SIGUSR1);
    success = 0;
    while(!success);
  }
  
  return 0;
}
