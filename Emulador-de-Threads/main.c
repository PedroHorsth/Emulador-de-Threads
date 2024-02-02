#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "threads.h"

#define NUM_THREADS 4
#define RECURSOS 3

int disponivel[RECURSOS];
int maximo[NUM_THREADS][RECURSOS];
int alocado[NUM_THREADS][RECURSOS];
int falta[NUM_THREADS][RECURSOS];
pthread_mutex_t mutex;

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < RECURSOS; ++i) {
        disponivel[i] = 0;
    }

    leitura_maxima("recursomax.txt");

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_funcao, (void *)&thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
