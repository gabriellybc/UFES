#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listagen.h"

struct listagen
{
  void *item;
  ListaGen *prox;
};

//cria lista vazia
ListaGen *criaLista()
{
  return NULL;
}

//insere no inicio
ListaGen *insereLista(ListaGen *lista, void *item)
{
  ListaGen *nova = (ListaGen *)malloc(sizeof(ListaGen));
  nova->item = item;
  nova->prox = lista;
  return nova;
}

//retira
ListaGen *retiraLista(ListaGen *lista, int (*cb)(void *, void *), void *chave)
{
  ListaGen *p = lista;
  ListaGen *ant = NULL;

  //faz a busca (callback tem que retornar 0 quando forem iguais)
  while (p != NULL && cb(p->item, chave))
  {
    ant = p;
    p = p->prox;
  }

  //lista vazia ou nao encontrou o item
  if (p == NULL)
    return lista;

  //se for a primeira celula
  if (ant == NULL)
    lista = lista->prox;
  else
    ant->prox = p->prox;

  //libera a celula
  free(p);

  //retorna a nova lista
  return lista;
}

//funcao percorre que vai servir para fazer varias coisas na lista (quem define e' a funcao de callback)
int percorreLista(ListaGen *lista, int (*cb)(void *, void *), void *dado)
{
  ListaGen *p;
  for (p = lista; p != NULL; p = p->prox)
  {
    int r = cb(p->item, dado);
    if (r == 0)
      return r;
  }
  return 1;
}

//libera apenas celulas
void liberaLista(ListaGen *lista)
{
  ListaGen *p = lista;
  ListaGen *t;

  while (p != NULL)
  {
    t = p->prox;
    free(p);
    p = t;
  }
}