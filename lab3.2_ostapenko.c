#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();
    if (pid == -1) {
        printf("Error in creating project.");
    } else if (pid == 0) {
        printf("Child process, ID: %d\n", (int)getpid());
        printf("Child, I am your father! ID: %d\n", (int)getppid());
        exit(0);
    } else {
        printf("Parent, ID: %d\n", (int)getpid());
        printf("Child's ID: %d\n", (int)pid);
    }
    return 0;
}