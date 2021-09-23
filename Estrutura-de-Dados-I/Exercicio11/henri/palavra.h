#ifndef Palavra_h
#define Palavra_h
#include <stdio.h>

typedef struct palavra Palavra;

Palavra *inicPalavra(char *str);

Palavra *inserePalavralista(Palavra *lista, Palavra *p);

void imprimelista(Palavra *p);

void liberalistaPalavra(Palavra *pal);

char *retornaString(Palavra *pal);

void atualizaOcorrencias(Palavra *pal);

Palavra *buscaPalavra(Palavra *pal, char *string);

int contaPalavraslista(Palavra *p);

int retornaOcorrencias(Palavra *pal);

#endif