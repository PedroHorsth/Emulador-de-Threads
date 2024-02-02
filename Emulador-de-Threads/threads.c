#include <stdio.h>
#include <unistd.h>
#include "threads.h"

void leitura_maxima(char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        for (int j = 0; j < RECURSOS; ++j) {
            fscanf(arquivo, "%d", &maximo[i][j]);
        }
    }

    fclose(arquivo);
}

void ler_dados(char *nome_arquivo, int thread_id) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    while (fscanf(arquivo, "%*s %d", &alocado[thread_id][0]) != EOF) {
        for (int i = 1; i < RECURSOS; ++i) {
            fscanf(arquivo, "%*s %d", &alocado[thread_id][i]);
        }

        sleep(alocado[thread_id][0]);

        pthread_mutex_lock(&mutex);
        int seguro = seseguro(thread_id);
        if (seguro) {
            recurso_alocado(thread_id);
        } else {
            printf("Estado inseguro! Thread %d aguardando.\n", thread_id);
        }
        pthread_mutex_unlock(&mutex);
    }

    fclose(arquivo);
}

int seseguro(int thread_id) {
    for (int i = 0; i < RECURSOS; ++i) {
        if (falta[thread_id][i] > disponivel[i]) {
            return 0;
        }
    }
    return 1;
}

void recurso_alocado(int thread_id) {
    for (int i = 0; i < RECURSOS; ++i) {
        disponivel[i] -= alocado[thread_id][i];
        falta[thread_id][i] = 0;
    }
}

void *thread_funcao(void *arg) {
    int thread_id = *(int *)arg;
    char nome_arquivo[10];
    sprintf(nome_arquivo, "%d.txt", thread_id);

    read_thread_data(nome_arquivo, thread_id);

    printf("Thread %d terminou a execucao.\n", thread_id);

    pthread_exit(NULL);
}
