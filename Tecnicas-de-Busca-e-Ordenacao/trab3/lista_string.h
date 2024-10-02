#ifndef LISTA_STRING_H
#define LISTA_STRING_H

typedef struct lista_string Lista_string;

#include "string.h"

Lista_string *iniciar_lista_string();

void inserir_lista_string(Lista_string *lista_string, String *pag);

void inserir_lista_string_ult(Lista_string *lista_string, String *pag);

unsigned int get_tamanho_lista_string(Lista_string *lista_string);

void liberar_lista_string(Lista_string *lista_string);

void imprimir_lista_string(Lista_string *lista_string);


#endif
