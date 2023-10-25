#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>


int main() {
    pid_t pid = fork();
    if(pid < 0) 
        return errno;
    else if (pid == 0) {
        pid_t childPID = getpid();
        pid_t parentPID = getppid();
        printf("%s%i","Child PID = ",childPID);
        printf("\n");
        printf("%s%i","Parent PID = ",parentPID);
        printf("\n");

        char *argv[] = {"ls", NULL};
        execve("/usr/bin/ls",argv,NULL);
        perror(NULL);
    }
    else {
        wait(NULL);
    }
    return 0;
}