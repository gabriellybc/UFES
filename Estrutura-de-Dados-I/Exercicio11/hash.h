#ifndef HASH_H_
#define HASH_H_

#include "palavra.h"

//Define o tipo opaco que contem a Hash
typedef struct hash Hash;

Hash *inicHash(int tamanhoHash);

//Faz acesso a hash realizando 2 possíveis operações:
//1) insercao, caso a palavra nao esteja na hash
//2) incremento de ocorrenciia, caso a palavra ja esteja na hash
Palavra *acessa(Hash *h, char *string);

void imprimeHash(Hash *h);

void liberaHash(Hash *h);

#endif /*HASH_H_*/