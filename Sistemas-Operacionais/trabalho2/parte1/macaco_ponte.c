#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // Inclui a declaração da função sleep

#include "macaco_ponte.h"
#include "config.h"  // Inclui as constantes definidas

sem_t mutex;        // Semáforo para garantir acesso exclusivo à variável num_macacos_na_ponte
sem_t ponte;        // Semáforo que controla o acesso à ponte
sem_t mutex_gorila;       // Semáforo que controla o acesso à ponte pelos gorilas
sem_t mutex_margem1;      // Semáforo que controla o acesso à margem 1
sem_t mutex_margem2;      // Semáforo que controla o acesso à margem 2
sem_t sem_gorila;         // Semáforo para esperar todos os gorilas atravessarem antes de liberar outros macacos
int num_macacos_na_ponte = 0;  // Variável que armazena o número de macacos atualmente na ponte
int num_gorilas_esperando = 0;
int num_gorilas_atravessaram = 0;
int num_macacos_margem1 = 0;    

void* atravessa_ponte(void* args) {
    int* arg = (int*)args;
    int macaco_id = arg[0];
    int gorila = arg[1];

    if (gorila) {
        // Gorila
        printf("Gorila %d esperando para atravessar.\n", macaco_id);
        sem_wait(&mutex_gorila);
        num_gorilas_esperando++;
        sem_post(&mutex_gorila);

        sem_wait(&ponte);
        printf("Gorila %d começou a atravessar a ponte.\n", macaco_id);
        // Simula o tempo de travessia do gorila
        sleep(5);
        printf("Gorila %d terminou a travessia.\n", macaco_id);
        sem_wait(&mutex_gorila);
        num_gorilas_esperando--;
        num_gorilas_atravessaram++;

        if (num_gorilas_atravessaram == NUM_GORILAS) {
            // Último gorila terminou a travessia, libera outros macacos
            for (int i = 0; i < NUM_MACACOS; i++)
                sem_post(&sem_gorila);
            num_gorilas_atravessaram = 0; // Reinicia o contador de gorilas atravessados
        }

        sem_post(&mutex_gorila);

        sem_post(&ponte);
    } else {
        // Macaco
        int metade = NUM_MACACOS / 2;
        int margem = 0;
        if (macaco_id < metade)
            margem = 1;
        else
            margem = 2;

        if (margem == 1)
            printf("Macaco %d na margem 1, esperando para atravessar.\n", macaco_id);
        else
            printf("Macaco %d na margem 2, esperando para atravessar.\n", macaco_id);

        sem_wait(&sem_gorila);

        if (margem == 1){
            sem_wait(&mutex_margem1); 
        } else {
            sem_wait(&mutex_margem2);
        }
        
        printf("Macaco %d começou a atravessar a ponte.\n", macaco_id);

        // Simula o tempo de travessia do macaco
        sleep(5);

        printf("Macaco %d terminou a travessia.\n", macaco_id);

        sem_wait(&mutex);
        if (margem == 1) {
            num_macacos_margem1++;
        }

        sem_post(&mutex);

        if (margem ==1){
            if (num_macacos_margem1 >= NUM_MACACOS/2 -1){
                for (int i = 0; i < NUM_MACACOS/2+1; i++)
                    sem_post(&mutex_margem2); // Libera o acesso para a última macaco da margem 1
            }
        }
    }

    return NULL;
}

void inicializa_semaforos() {
    sem_init(&mutex, 0, 1);
    sem_init(&ponte, 0, 1);
    sem_init(&mutex_gorila, 0, 1);
    sem_init(&mutex_margem1, 0, NUM_MACACOS/2+1);
    sem_init(&mutex_margem2, 0, 0);
    sem_init(&sem_gorila, 0, 0);
}

void destroi_semaforos() {
    sem_destroy(&mutex);
    sem_destroy(&ponte);
    sem_destroy(&mutex_gorila);
    sem_destroy(&mutex_margem1);
    sem_destroy(&mutex_margem2);
    sem_destroy(&sem_gorila);
}