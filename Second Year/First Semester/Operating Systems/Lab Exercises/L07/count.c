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
pthread_mutex_t mtx;

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
    printf("Got %i resources %i remaining\n",arg->value,available_resources);
    pthread_mutex_unlock(&mtx);

    return result;
}

void * increase_count(void *v) {
    struct args *arg = v;
    int *result = malloc(sizeof(int));

    pthread_mutex_lock(&mtx);
    available_resources += arg->value;
    *result = 0;
    printf("Released %i resources %i remaining\n",arg->value,available_resources);
    pthread_mutex_unlock(&mtx);

    return result;
}

int main(int argc, char *argv[]) {

    if(pthread_mutex_init(&mtx, NULL)) {
        perror(NULL);
        return errno;
    }

    struct args arguments = {0};
    struct args arg_values[] = {2,2,1,3,2};
    pthread_t *threads = malloc(10 * sizeof(pthread_t));

    for (int i=0;i<5;i++) {
        arguments = arg_values[i];
        int hasOcupiedResources = 0;

        if (pthread_create(&threads[i], NULL, decrease_count, &arguments)) {
            perror(NULL);
            return errno;
        }

        if (pthread_join(threads[i], NULL)) {
            perror(NULL);
            return errno;
        }

        if (pthread_create(&threads[i], NULL, increase_count, &arguments)) {
            perror(NULL);
            return errno;
        }

    }

    pthread_mutex_destroy(&mtx);
    return 0;
}