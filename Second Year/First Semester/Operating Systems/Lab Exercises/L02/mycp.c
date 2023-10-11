#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char** argv) {
    int fd = open(argv[1],O_RDONLY);
    if(fd == -1) printf("%s\nError number: %i\n", "Failed to open first file", errno);

    int fd2 = open(argv[2],O_CREAT|O_WRONLY,S_IRWXU);
    if(fd2 == -1) printf("%s\nError number: %i\n", "Failed to open second file",errno);

    struct stat myStat; 
    stat(argv[1], &myStat);

    char readMsg[myStat.st_size];
    read(fd,readMsg,myStat.st_size); 
    write(fd2,readMsg,myStat.st_size);

    close(fd);
    close(fd2);
    return 0;
}