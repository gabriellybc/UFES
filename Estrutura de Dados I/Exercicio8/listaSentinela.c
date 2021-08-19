#include "listaSentinela.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct cel Celula;

struct cel
{
  Aluno *al;
  Celula *prox;
};

struct lista // Sentinela
{
  Celula *Prim;
  Celula *Ult;
};

Lista *InicLista()
{
  Lista *lista = (Lista *)malloc(sizeof(Lista));

  if (!lista)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }

  lista->Prim = NULL;
  lista->Ult = NULL;

  return lista;
};

//No Inicio
void InsereLista(Lista *Lista, Aluno *al)
{
  Celula *nova = (Celula *)malloc(sizeof(Celula));

  if (!nova)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }

  nova->al = al; //O nova->al recebe a al que eu quero incerir na lista

  nova->prox = Lista->Prim; //Encadeando a nova celula na lista fazendo ela receber o endereço da antiga primeira celula que vai virar a segunda

  Lista->Prim = nova; //Mudando a primeira celula da lista, o inicio da lista apontar pra nova e assim colocando ela no primeiro lugar da lista

  if (Lista->Ult == NULL) //Caso a lista estivesse vazia
  {
    Lista->Ult = nova; //A nova vai ser a primeira celula da lista
  }
};

//No Final
void InsereListaUlt(Lista *Lista, Aluno *al)
{
  Celula *nova = (Celula *)malloc(sizeof(Celula));

  if (!nova)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }

  nova->al = al; //O nova->al recebe a al que eu quero incerir na lista
  nova->prox = NULL;

  if (Lista->Ult == NULL) //Caso a lista estivesse vazia
  {
    Lista->Prim = Lista->Ult = nova; //A nova vai ser a primeira e a ultima celula da lista
    return;
  }

  Lista->Ult->prox = nova; //Encadeando a nova celula na lista, encadeando a antiga ultima celula com a nova

  Lista->Ult = nova; //Mudando a ultima celula da lista, o final da lista aponta pra nova e assim colocando ela no ultimo lugar da lista
};

void ImprimeLista(Lista *Lista)
{
  Celula *p; //ponteiro auxiliar que aponta para um celula que já existe e já foi alocada anteriormente

  for (p = Lista->Prim; p != NULL; p = p->prox)
  {
    imprimeAluno(p->al); //p anda em cada celula da lista
    printf("\n");
  }
};

Aluno *RetiraLista(Lista *Lista, int pos)
{
  Celula *p = Lista->Prim; //ponteiro auxiliar p apontando para a primeira celula da lista
  Aluno *al;               //Variavel auxiliar de aluno para retornar ele.
  Celula *ant = NULL;      //Ponteiro auxiliar sempre na posição anterior ao p

  int posicao = 0;
  //Faz a busca
  while (p != NULL && posicao != pos)
  {
    ant = p;
    p = p->prox;
    posicao++;
  }

  //Lista vazia ou não encontrou a Aluno
  if (p == NULL)
  {
    return NULL;
  }

  //Atribui a Aluno de retorno
  al = p->al;

  //Se for a única celula da lista
  if (p == Lista->Prim && p == Lista->Ult)
    Lista->Prim = Lista->Ult = NULL; //Lista fica vazia
  else if (p == Lista->Prim)         //Se for a primeira celula da lista
    Lista->Prim = p->prox;
  else if (p == Lista->Ult) //Se for a ultima Celula
  {
    Lista->Ult = ant;
    ant->prox = NULL; // ou Lista->Ult->prox = NULL;
  }
  else //caso comum
  {
    ant->prox = p->prox;
  }

  free(p); //Liberando apenas a célula da lista

  return al; //Retornando o aluno
};

//Libera apenas a memoria da lista, as Alunoes contiarão armazenadas
void LiberaLista(Lista *Lista)
{
  Celula *p = Lista->Prim; //ponteiro auxiliar recebendo a primeira celula da lista
  Celula *t;               // outro ponteiro auxiliar

  while (p != NULL) //Enquanto não chegar ao final da lista
  {
    t = p->prox; //O ponteiro temporário aponta para a proxima célula
    free(p);
    p = t;
  }
  //Liberando a sentinela
  free(Lista);
};