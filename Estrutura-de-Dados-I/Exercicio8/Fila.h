#ifndef Fila_H_
#define Fila_H_

#include <stdio.h>
#include <stdlib.h>
#include "Aluno.h"

typedef struct fila Fila;

Fila *inicFila(void);

//Insere sempre no final da fila
void insereFila(Fila *f, Aluno *al);

//Retira sempre no inicio da fila
Aluno *retiraFila(Fila *f);

//Imprime do inicio ao fim da fila
void imprimeFila(Fila *f);

//Libera a memoria da fila, mas não dos alunos
void destroiFila(Fila *f);

#endif // Fila_H_