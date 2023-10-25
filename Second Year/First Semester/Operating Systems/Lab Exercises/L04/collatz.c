#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>

void collatzConjecture(int n) {
    printf("%i ",n);
    if(n <= 1) return;
    if (n%2 == 0) collatzConjecture(n/2);
    else collatzConjecture(3*n+1);
}

int main(int argc, const char* argv[]) {
    pid_t pid = fork();
    if(pid < 0) 
        return errno;
    else if (pid == 0) {
        pid_t childPID = getpid();

        int n = atoi(argv[1]);
        printf("%i: ",n);
        collatzConjecture(n);

        printf("%s%i","\nChild PID = ",childPID);
        printf(" finished\n");
        // perror(NULL);
    }
    else {
        wait(NULL);
    }
    return 0;
}