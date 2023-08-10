#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

#include <pthread.h>

/*
 * Thread de um funcionário corintiano.
 * Cada corintiano terá um identificador de 1 a 10.
 */
void *thread_corintiano(void *id);

/*
 * Thread de um funcionário palmeirense.
 * Cada palmeirense terá um identificador de 1 a 10.
 */
void *thread_palmeirense(void *id);

#endif // FUNCIONARIOS_H
