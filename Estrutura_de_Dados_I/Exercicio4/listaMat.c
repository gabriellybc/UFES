#include "listaMat.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct cel Celula;

struct cel
{
  Matriz *mat;
  Celula *prox;
};

struct listmat // Sentinela
{
  Celula *Prim;
  Celula *Ult;
};

ListaMat *InicListaMat()
{
  ListaMat *listaMat = (ListaMat *)malloc(sizeof(ListaMat));

  if (!listaMat)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }

  listaMat->Prim = NULL;
  listaMat->Ult = NULL;

  return listaMat;
};

//No inicio
void InsereMatLista(ListaMat *listaMat, Matriz *mat)
{
  Celula *nova = (Celula *)malloc(sizeof(Celula));

  if (!nova)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }

  nova->mat = mat; //O nova->mat recebe a mat que eu quero incerir na lista

  nova->prox = listaMat->Prim; //Encadeando a nova celula na lista fazendo ela receber o endereço da antiga primeira celula que vai virar a segunda

  listaMat->Prim = nova; //Mudando a primeira celula da lista, o inicio da lista apontar pra nova e assim colocando ela no primeiro lugar da lista

  if (listaMat->Ult == NULL) //Caso a lista estivesse vazia
  {
    listaMat->Ult = nova; //A nova vai ser a primeira celula da lista
  }
};

void ImprimeListaMat(ListaMat *listaMat)
{
  Celula *p; //ponteiro auxiliar que aponta para um celula que já existe e já foi alocada anteriormente

  for (p = listaMat->Prim; p != NULL; p = p->prox)
  {
    imprimeMatriz(p->mat); //p anda em cada celula da lista
    printf("\n");
  }
};

Matriz *RetiraMatLista(ListaMat *listaMat, int posicaoMat)
{
  Celula *p = listaMat->Prim; //ponteiro auxiliar p apontando para a primeira celula da lista
  Matriz *mat;                //Variavel auxiliar de aluno para retornar ele.
  Celula *ant = NULL;         //Ponteiro auxiliar sempre na posição anterior ao p

  int posicao = 0;
  //Faz a busca
  while (p != NULL && posicao != posicaoMat)
  {
    ant = p;
    p = p->prox;
    posicao++;
  }

  //Lista vazia ou não encontrou a matriz
  if (p == NULL)
  {
    return NULL;
  }

  //Atribui a matriz de retorno
  mat = p->mat;

  //Se for a única celula da lista
  if (p == listaMat->Prim && p == listaMat->Ult)
    listaMat->Prim = listaMat->Ult = NULL; //Lista fica vazia
  else if (p == listaMat->Prim)            //Se for a primeira celula da lista
    listaMat->Prim = p->prox;
  else if (p == listaMat->Ult) //Se for a ultima Celula
  {
    listaMat->Ult = ant;
    ant->prox = NULL; // ou listaMat->Ult->prox = NULL;
  }
  else //caso comum
  {
    ant->prox = p->prox;
  }

  free(p); //Liberando apenas a célula da lista

  return mat; //Retornando o aluno
};

//Libera apenas a memoria da lista, as matrizes contiarão armazenadas
void LiberaListaMat(ListaMat *listaMat)
{
  Celula *p = listaMat->Prim; //ponteiro auxiliar recebendo a primeira celula da lista
  Celula *t;                  // outro ponteiro auxiliar

  while (p != NULL) //Enquanto não chegar ao final da lista
  {
    t = p->prox; //O ponteiro temporário aponta para a proxima célula
    free(p);
    p = t;
  }
  //Liberando a sentinela
  free(listaMat);
};