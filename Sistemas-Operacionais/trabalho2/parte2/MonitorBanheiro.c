// MonitorBanheiro.c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "MonitorBanheiro.h"
#include "config.h"

pthread_mutex_t mutex;
pthread_cond_t corintianos_cond, palmeirenses_cond;
int num_corintianos = 0;
int num_palmeirenses = 0;
int num_corintianos_esperando = 0;

void initMonitor() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&corintianos_cond, NULL);
    pthread_cond_init(&palmeirenses_cond, NULL);
}

void corintianoQuerEntrar() {
    pthread_mutex_lock(&mutex);
    num_corintianos_esperando++;
    while (num_palmeirenses > 0 || num_corintianos >= MAX_CAPACITY) {
        pthread_cond_wait(&corintianos_cond, &mutex);
    }
    num_corintianos_esperando--;
    num_corintianos++;
    printf("Entrou corintiano! Corintianos: %d, Palmeirenses: %d\n", num_corintianos, num_palmeirenses);
    pthread_mutex_unlock(&mutex);
}

void corintianoSai() {
    pthread_mutex_lock(&mutex);
    num_corintianos--;
    printf("Saiu corintiano! Corintianos: %d, Palmeirenses: %d\n", num_corintianos, num_palmeirenses);
    pthread_cond_signal(&corintianos_cond);
    pthread_cond_signal(&palmeirenses_cond);
    pthread_mutex_unlock(&mutex);
}

void palmeirenseQuerEntrar() {
    pthread_mutex_lock(&mutex);
    while (num_corintianos_esperando > 0 || num_corintianos > 0 || num_palmeirenses >= MAX_CAPACITY) {
        pthread_cond_wait(&palmeirenses_cond, &mutex);
    }
    num_palmeirenses++;
    printf("Entrou palmeirense! Corintianos: %d, Palmeirenses: %d\n", num_corintianos, num_palmeirenses);
    pthread_mutex_unlock(&mutex);
}

void palmeirenseSai() {
    pthread_mutex_lock(&mutex);
    num_palmeirenses--;
    printf("Saiu palmeirense! Corintianos: %d, Palmeirenses: %d\n", num_corintianos, num_palmeirenses);
    pthread_cond_signal(&corintianos_cond);
    pthread_cond_signal(&palmeirenses_cond);
    pthread_mutex_unlock(&mutex);
}
