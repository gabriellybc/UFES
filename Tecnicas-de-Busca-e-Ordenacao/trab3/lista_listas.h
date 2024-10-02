#ifndef LISTA_LISTAS_H
#define LISTA_LISTAS_H

typedef struct lista_listas Lista_listas;

#include "lista.h"

Lista_listas *iniciar_lista_listas();

void inserir_lista_listas(Lista_listas *lista_listas, Lista *pag);

void inserir_lista_listas_ult(Lista_listas *lista_listas, Lista *pag);

unsigned int get_tamanho_lista_listas(Lista_listas *lista_listas);

void liberar_lista_listas(Lista_listas *lista_listas);

void imprimir_lista_listas(Lista_listas *lista_listas);

Pagina **listas_para_array(Lista_listas *lista_listas, unsigned int *tamanho);

#endif
