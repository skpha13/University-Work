#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <string.h>

void collatzConjecture(int n, char collatzResult[]) {
    char temp[20];
    snprintf(temp, sizeof(temp),"%i", n);
    strcat(collatzResult, temp);
    strcat(collatzResult, " ");
    if(n <= 1) return;
    if (n%2 == 0) collatzConjecture(n/2, collatzResult);
    else collatzConjecture(3*n+1, collatzResult);
}

int main(int argc, const char* argv[]) {
    pid_t firstParentProcess = getppid();
    pid_t firstChildProcess = getpid();
    printf("Starting Parent %i\n",firstChildProcess);

    char shm_name[] = "myshm"; 
    size_t shm_size = 10 * getpagesize();
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR );

    if (ftruncate(shm_fd, shm_size) == -1) {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }

    void * shm_ptr;
    shm_ptr = mmap(0, shm_size, PROT_READ, MAP_SHARED, shm_fd, 0);

    if (shm_ptr == MAP_FAILED) {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }

    for(int i=1;i<argc;i++) {
        pid_t pid = fork();
        if(pid < 0) 
            return errno;
        else if (pid == 0) {
            pid_t childPID = getpid();
            pid_t parentPID = getppid();

            char collatzResult[100];
            strcat(collatzResult, "\n");
            strcat(collatzResult, argv[i]);
            strcat(collatzResult, ": ");
            collatzConjecture(atoi(argv[i]),collatzResult);
            strcat(collatzResult, "\n");
            
            void * shm_ptr_child;
            shm_ptr_child = mmap(shm_ptr + 100 * (i-1), 100, PROT_WRITE, MAP_SHARED, shm_fd, 0);

            if (shm_ptr_child == MAP_FAILED) {
                perror(NULL);
                shm_unlink(shm_name);
                return errno;
            }

            write(shm_fd, collatzResult, 100);
            munmap(shm_ptr_child + 100 * (i-1), 100);


            printf("Done Parent %i Me %i\n",parentPID,childPID);
            exit(childPID);

            perror(NULL);
        }
    }

    for(int i=1;i<argc;i++) {
        wait(NULL);
    }

    char readMsg[shm_size];
    // doesnt work with read needs to be memcpy
    // read(shm_fd, readMsg, shm_size);
    memcpy(readMsg, shm_ptr, shm_size);

    // strcat places null after each string so we need to print what each childe wrote separately
    for(int i=1;i<argc;i++) {
        printf("%s\n", (char*)(shm_ptr + 100 * (i-1)));
    }

    munmap(shm_ptr, shm_size);
    printf("Done Parent %i Me %i\n",firstParentProcess,firstChildProcess);
    
    return 0;
}