#include <pthread.h>
#include <stdlib.h>

#include "MonitorBanheiro.h"
#include "Funcionarios.h"
#include "config.h"

int main() {
    pthread_t corintianos[NUM_CORINTIANOS];
    pthread_t palmeirenses[NUM_PALMEIRENSES];
    int i;

    // Criando as threads dos corintianos
    for (i = 0; i < NUM_CORINTIANOS; i++) {
        int *corintiano_id = malloc(sizeof(int));
        *corintiano_id = i + 1;
        pthread_create(&corintianos[i], NULL, thread_corintiano, (void *)corintiano_id);
    }

    // Criando as threads dos palmeirenses
    for (i = 0; i < NUM_PALMEIRENSES; i++) {
        int *palmeirense_id = malloc(sizeof(int));
        *palmeirense_id = i + 1;
        pthread_create(&palmeirenses[i], NULL, thread_palmeirense, (void *)palmeirense_id);
    }

    // Aguardando as threads terminarem
    for (i = 0; i < NUM_CORINTIANOS; i++) {
        pthread_join(corintianos[i], NULL);
    }
    for (i = 0; i < NUM_PALMEIRENSES; i++) {
        pthread_join(palmeirenses[i], NULL);
    }

    return 0;
}
