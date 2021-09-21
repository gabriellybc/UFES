//
// abb.h
//
// Criado por Gabrielly Cariman em 29/08/21.
//
// Implementação de uma árvore binária de busca
//

#ifndef ABB_h
#define ABB_h

#include <stdbool.h>

typedef struct arv Arv;

#include "Aluno.h"

//Cria uma árvore vazia
Arv *abb_cria();

//retorna true se a árvore estiver vazia e false caso contrário
bool abb_vazia(Arv *a); //rebe a raíz da árvore

//imprime as informações dos nós da árvore
void abb_imprime(Arv *a); //rebe a raíz da árvore

// Se encontrar, retorna o nó que contém o aluno
// Se não encontrar, retorna NULL
Arv *abb_busca(Arv *r, int chave);

// Insere sempre como folha da arvore
Arv *abb_insere(Arv *a, Aluno *al);

Arv *abb_retira(Arv *r, int v);

//libera o espaço de memória ocupado pela árvore a
Arv *abb_libera(Arv *a); //rebe a raíz da árvore

#endif /*abb_h*/
