#include <pthread.h>

#include "macaco_ponte.h"
#include "config.h"  // Inclui as constantes definidas

int main() {
    int i;
    pthread_t macacos[NUM_MACACOS + NUM_GORILAS];
    int macaco_args[NUM_MACACOS + NUM_GORILAS][NUM_GORILAS];

    inicializa_semaforos();

    // Adiciona os gorilas com IDs começando a partir do número total de macacos
    for (i = 0; i < NUM_GORILAS; i++) {
        macaco_args[NUM_MACACOS + i][0] = NUM_MACACOS + i + 1;
        macaco_args[NUM_MACACOS + i][1] = 1; // O segundo argumento é 1 para indicar que é um gorila
        pthread_create(&macacos[NUM_MACACOS + i], NULL, atravessa_ponte, &macaco_args[NUM_MACACOS + i]);
    }

    // Adiciona os macacos com IDs de 1 até NUM_MACACOS
    for (i = 0; i < NUM_MACACOS; i++) {
        macaco_args[i][0] = i + 1;
        macaco_args[i][1] = 0; // O segundo argumento é 0 para indicar que é um macaco
        pthread_create(&macacos[i], NULL, atravessa_ponte, &macaco_args[i]);
    }

    // Aguarda o término das threads
    for (i = 0; i < NUM_MACACOS + 2; i++) {
        pthread_join(macacos[i], NULL);
    }

    destroi_semaforos();

    return 0;
}