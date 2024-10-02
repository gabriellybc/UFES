#ifndef LISTA_H
#define LISTA_H

typedef struct lista Lista;

#include "pagina.h"

Lista *iniciar_lista();

void inserir_lista(Lista *lista, Pagina *pag);

void inserir_lista_ult(Lista *lista, Pagina *pag);

unsigned int get_tamanho_lista(Lista *lista);

void imprimir_lista(Lista *lista);

Pagina *retirar_lista(Lista *lista, int pos);

void liberar_lista(Lista *lista);

Pagina **lista_para_array(Lista *lista, unsigned int *tamanho);

Pagina **lista_para_array_imprimir(Lista *lista, unsigned int tamanho);

double lista_pagerank(Lista *lista);

void liberar_lista_stop_word(Lista *lista);

Pagina *get_ultima_pagina(Lista *lista);

void imprimir_lista_saida(Lista *lista);

#endif
