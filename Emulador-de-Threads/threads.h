#ifndef THREADS_H
#define THREADS_H

void leitura_maxima(char *nome_arquivo);
void ler_dados(char *nome_arquivo, int thread_id);
int seseguro(int thread_id);
void recurso_alocado(int thread_id);
void *thread_funcao(void *arg);

#endif
