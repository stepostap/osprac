#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(){
    printf("My pid = %d, my ppid = %d\n", (int)getpid(), (int)getppid());
    return 0;
}