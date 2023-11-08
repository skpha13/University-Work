#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h> 
#include <semaphore.h>

sem_t sem;
unsigned int S, N, count = 0;
pthread_mutex_t mtx;

int init(int N) {
    S = 0;

    if(pthread_mutex_init(&mtx, NULL)) {
        perror(NULL);
        return errno;
    }

    if (sem_init(&sem, 0, S)) {
        perror(NULL);
        return errno;
    }   

    return 0;
}

int barrier_point() {
    // INTREBARE: daca toate thread urile doar cresc count ul atunci de ce avem nevoie de un mutex lock?
    // RASPUNS: chiar daca fac doar ++ la un contor daca facem 2 thread uri fiecare sa creasca intr un for de la 0 la 100000
        // atunci rezultatul nu va avea 200000, valoarea acceptata
    pthread_mutex_lock(&mtx);

    count++;
    if (count == N) {
        for (int i=0;i<N;i++) {
            if (sem_post(&sem)) {
                perror(NULL);
                return errno;
            }
        }
    }

    pthread_mutex_unlock(&mtx);

    if (sem_wait(&sem)) {
        perror(NULL);
        return errno;
    }
}

void * tfun(void *v) {
    int *tid = (int *) v;
    printf("%d reached the barrier\n", *tid);
    barrier_point();
    printf("%d passed the barrier\n", *tid);

    free(tid);
    return NULL;
}

int main(int argc, char *argv[]) {
    N = atoi(argv[1]);
    init(N);

    pthread_t *threads = malloc(N * sizeof(pthread_t));

    if (sem_init(&sem, 0, S)) {
        perror(NULL);
        return errno;
    }

    for (int i=0;i<N;i++) {
        int *tid = malloc(sizeof(int));
        *tid = i;

        if (pthread_create(&threads[i], NULL, tfun, tid)) {
            perror(NULL);
            return errno;
        }
    }

    for (int i=0;i<N;i++) {
        if (pthread_join(threads[i], NULL)) {
            perror(NULL);
            return errno;
        }
    }

    sem_destroy(&sem);

    return 0;
}