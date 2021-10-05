#ifndef listagen_h
#define listagen_h

#include <stdio.h>

typedef struct listagen ListaGen;

// cria lista vazia
ListaGen *criaLista();

//insere no inicio
ListaGen *insereLista(ListaGen *lista, void *item);

//retira
ListaGen *retiraLista(ListaGen *lista, int (*cb)(void *, void *), void *chave);

//funcao percorre que vai servir para fazer varias coisas na lista (quem define e' a funcao de callback)
int percorreLista(ListaGen *lista, int (*cb)(void *, void *), void *dado);

//libera apenas celulas
void liberaLista(ListaGen *lista);

#endif //listagen_h