#ifndef hash_h
#define hash_h

#include <stdio.h>

#include "palavra.h"

typedef struct hash Hash;

Hash *inicHash(int tamanho);

Palavra *acessa(Hash *h, char *string);

int contaPalavras(Hash *h);

void imprimeHash(Hash *h);

void liberaHash(Hash *h);

#endif