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
    for(int i=1;i<argc;i++) {
        pid_t pid = fork();
        if(pid < 0) 
            return errno;
        else if (pid == 0) {
            pid_t childPID = getpid();
            pid_t parentPID = getppid();

            printf("%s%i","Starting Parent = ",parentPID);
            printf("\n");

            printf("%s: ",argv[i]);
            collatzConjecture(atoi(argv[i]));

            printf("\n");

            exit(childPID);
            perror(NULL);
        }
        else {
            wait(NULL);
        }
    }
    
    return 0;
}