#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h> 

#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;
pthread_mutex_t mtx, mtxFor;

struct args {
    int value;
};

void * decrease_count(void *v) {
    struct args *arg = v;
    int *result = malloc(sizeof(int));
    pthread_mutex_lock(&mtx);
    if (available_resources < arg->value) {
        *result = -1;
        return result;
    } else {
        available_resources -= arg->value;
        *result = 0;
    }
    pthread_mutex_unlock(&mtx);

    printf("Got %i resources %i remaining\n",arg->value,available_resources);
    return result;
}

void * increase_count(void *v) {
    struct args *arg = v;
    int *result = malloc(sizeof(int));

    pthread_mutex_lock(&mtx);
    available_resources += arg->value;
    *result = 0;
    pthread_mutex_unlock(&mtx);

    printf("Released %i resources %i remaining\n",arg->value,available_resources);
    return result;
}

int main(int argc, char *argv[]) {

    if(pthread_mutex_init(&mtx, NULL)) {
        perror(NULL);
        return errno;
    }

    if(pthread_mutex_init(&mtxFor, NULL)) {
        perror(NULL);
        return errno;
    }

    struct args arguments = {0};
    struct args arg_values[] = {2,2,1,3,2};
    pthread_t *threads = malloc(10 * sizeof(int));

    for (int i=0;i<5;i++) {
        pthread_t threads[i];
        arguments = arg_values[i];
        // void *result;

        if (pthread_create(&threads[i], NULL, decrease_count, &arguments)) {
            perror(NULL);
            return errno;
        }        

        if (pthread_create(&threads[i], NULL, increase_count, &arguments)) {
            perror(NULL);
            return errno;
        }
        
        // free(result);
    }

    for(int i=0;i<5;i++) {
        if (pthread_join(threads[i], NULL)) {
            perror(NULL);
            return errno;
        }


        if (pthread_join(threads[i], NULL)) {
            // perror(NULL);
            return errno;
        }
    }

    pthread_mutex_destroy(&mtx);
    return 0;
}