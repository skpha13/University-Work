#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

struct args {
    int *matrix1,*matrix2;
    int rows,cols, rowMultiplied, columnMultiplied;
};

void printMatrix(int *m, int rows, int cols) {
    for(int i=0;i<rows;i++) {
        for(int j=0;j<cols;j++)
            printf("%i ", m[i * cols + j]); 
        printf("\n");
    }
}

void * multiplyRowWithColumn(void *v) {
    struct args *arg = v;
    int *result = malloc(sizeof(int));
    *result = 0;
    for(int j=0;j<arg->cols;j++) {
        *result += arg->matrix1[arg->rowMultiplied * arg->cols + j] * 
                               arg->matrix2[j * arg->cols + arg->columnMultiplied];    
    }
    return result;
}

int main (int argc, char* argv[]) {
    int rows = 3;
    int cols = 3;
    int *matrix1 = malloc((rows * cols) * sizeof(int));
    int *matrix2 = malloc((rows * cols) * sizeof(int));
    int *resultingMatrix = malloc((rows * cols) * sizeof(int));

    for(int i=0;i<rows*cols;i++) matrix1[i] = i+1;
    for(int i=0;i<rows*cols;i++) matrix2[i] = i+1;

    struct args arguments = {matrix1,matrix2,rows,cols,0,0};

    pthread_t thr;
    for(int i=0;i<rows;i++) {
        for(int j=0;j<cols;j++) {
            arguments.rowMultiplied = i;
            arguments.columnMultiplied = j;

            if (pthread_create(&thr, NULL, multiplyRowWithColumn, &arguments)) {
                perror(NULL);
                return errno;
            }

            void *result;
            if (pthread_join(thr, &result)) {
                perror(NULL);
                return errno;
            }
            resultingMatrix[i * cols + j] = *((int*)result);

            free(result);
        }
    }

    printMatrix(resultingMatrix,rows,cols);
    free(matrix1);
    free(matrix2);
    free(resultingMatrix);
    return 0;
}