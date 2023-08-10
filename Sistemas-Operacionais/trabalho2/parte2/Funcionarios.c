// Funcionarios.c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "MonitorBanheiro.h"
#include "config.h"

pthread_mutex_t mutex;
pthread_cond_t corintianos_cond; 
pthread_cond_t palmeirenses_cond;

void *thread_corintiano(void *arg) {
    int *id = (int *)arg;

    while (1) {
        corintianoQuerEntrar();
        printf("Eu sou corintiano-%d: ... UFA! Entrei no banheiro!\n", *id);
        sleep(3);

        corintianoSai();
        printf("Eu sou corintiano-%d: ... Estou aliviado! Vou trabalhar!\n", *id);
        sleep(5);
    }

    return NULL;
}

void *thread_palmeirense(void *arg) {
    int *id = (int *)arg;

    while (1) {
        palmeirenseQuerEntrar();
        printf("Eu sou palmeirense-%d: ... UFA! Entrei no banheiro!\n", *id);
        sleep(3);

        palmeirenseSai();
        printf("Eu sou palmeirense-%d: ... Estou aliviado! Vou trabalhar!\n", *id);
        sleep(5);
    }

    return NULL;
}

int main() {
    initMonitor(); // Inicializa o Monitor

    pthread_t corintianos[NUM_CORINTIANOS];
    pthread_t palmeirenses[NUM_PALMEIRENSES];
    int ids[NUM_CORINTIANOS + NUM_PALMEIRENSES];

    // Criar threads dos corintianos
    for (int i = 0; i < NUM_CORINTIANOS; i++) {
        ids[i] = i + 1;
        pthread_create(&corintianos[i], NULL, thread_corintiano, &ids[i]);
    }

    // Criar threads dos palmeirenses
    for (int i = 0; i < NUM_PALMEIRENSES; i++) {
        ids[NUM_CORINTIANOS + i] = i + 1;
        pthread_create(&palmeirenses[i], NULL, thread_palmeirense, &ids[NUM_CORINTIANOS + i]);
    }

    // Aguardar threads terminarem
    for (int i = 0; i < NUM_CORINTIANOS; i++) {
        pthread_join(corintianos[i], NULL);
    }

    for (int i = 0; i < NUM_PALMEIRENSES; i++) {
        pthread_join(palmeirenses[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&corintianos_cond);
    pthread_cond_destroy(&palmeirenses_cond);

    return 0;
}
