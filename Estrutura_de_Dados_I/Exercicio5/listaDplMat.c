#include "listaDplMat.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct cel Celula;

struct listdplmat // Sem Sentinela
{
  Matriz *mat;
  ListaDplMat *prox;
  ListaDplMat *ant;
};

ListaDplMat *InicListaDplMat()
{
  return NULL;
};

//No inicio
ListaDplMat *InsereMatLista(ListaDplMat *listaDplMat, Matriz *mat)
{
  ListaDplMat *nova = (ListaDplMat *)malloc(sizeof(ListaDplMat));
  nova->mat = mat;
  nova->ant = NULL;
  nova->prox = listaDplMat;

  if (listaDplMat != NULL)
    listaDplMat->ant = nova;

  return nova;
};

void ImprimeListaMat(ListaDplMat *listaDplMat)
{
  ListaDplMat *p; //ponteiro auxiliar que aponta para um celula que já existe e já foi alocada anteriormente

  for (p = listaDplMat; p != NULL; p = p->prox)
  {
    imprimeMatriz(p->mat); //p anda em cada celula da listaDpl
    printf("\n");
  }
};

static ListaDplMat *Busca(ListaDplMat *listaDplMat, int posicaoMat)
{
  ListaDplMat *p = listaDplMat;
  int posicao = 0;
  //faz a busacao
  while (p != NULL && posicao != posicaoMat)
  {
    p = p->prox;
    posicao++;
  }
  return p;
}

ListaDplMat *RetiraMatLista(ListaDplMat *listaDplMat, int posicaoMat)
{
  ListaDplMat *p = Busca(listaDplMat, posicaoMat);

  //ListaDpl vazia ou não encontrou a matriz
  if (p == NULL)
    return listaDplMat;

  if (p->prox == NULL && p->ant == NULL)
  { //Unico elemento
    free(p);
    return NULL;
  }

  // testa se é o primeiro elemento
  if (p == listaDplMat)
    listaDplMat = p->prox;
  else if (p->prox == NULL) //ultimo elemento
    p->ant->prox = NULL;    // p->ant->prox = NULL;
  else
  { // Caso comum
    p->ant->prox = p->prox;
    p->prox->ant = p->ant;
  }
  free(p);            //Liberando apenas a célula da listaDpl
  return listaDplMat; //Retornando a lista
};

//Libera apenas a memoria da listaDpl, as matrizes contiarão armazenadas
void LiberaListaMat(ListaDplMat *listaDplMat)
{
  ListaDplMat *p = listaDplMat; //ponteiro auxiliar recebendo a listaDpl
  ListaDplMat *t;               // outro ponteiro auxiliar

  while (p != NULL) //Enquanto não chegar ao final da listaDpl
  {
    t = p->prox; //O ponteiro temporário aponta para a proxima célula
    free(p);
    p = t;
  }
};