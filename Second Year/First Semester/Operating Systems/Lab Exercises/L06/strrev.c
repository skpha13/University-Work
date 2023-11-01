#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void * hello(void *v) {
    char *who = (char *) v;
    printf("Hello, %s!\n", who);
    return NULL;
}

void * reverse(void *v) {
    char *rev = (char *) v;
    char *returnString = (char *) malloc(strlen(rev)); 
    for(int i=strlen(rev)-1;i>=0;i--) {
        returnString[strlen(rev) - 1 - i] = rev[i];
    }
    returnString[strlen(rev)] = '\0';
    return returnString;
}

int main (int argc, char* argv[]) {
    // Hello World function
    /*
    pthread_t thr;
    if (pthread_create(&thr, NULL, hello, "world")) {
        perror(NULL);
        return errno;
    }

    void *result;
    if (pthread_join(thr, &result)) {
        perror(NULL);
        return errno;
    }
    */

   // Reverse function

    if (argc > 2) {
        printf("%s\n", "Wrong number of arguments");
        return 0;
    }

    pthread_t thr;
    if (pthread_create(&thr, NULL, reverse, argv[1])) {
        perror(NULL);
        return errno;
    }

    void *result;
    if (pthread_join(thr, &result)) {
        perror(NULL);
        return errno;
    }

    printf("%s\n",(char *) result);
    free(result);

    return 0;
}