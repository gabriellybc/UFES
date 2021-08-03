#include "ListaHet.h"
#include <stdio.h>
#include <stdlib.h>

#define PROF 0
#define ALU 1

typedef struct cel Celula;

struct cel
{
  Celula *prox;
  void *item;
  int tipo;
};

// Sentinela
struct listhet
{
  Celula *Prim;
  Celula *Ult;
};

ListaHet *InicListaHet(void)
{
  ListaHet *lista = (ListaHet *)malloc(sizeof(ListaHet));

  if (!lista)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }

  lista->Prim = NULL;
  lista->Ult = NULL;

  return lista;
};

//No inicio
void InsereAluno(ListaHet *lista, Aluno *al)
{
  Celula *nova = (Celula *)malloc(sizeof(Celula));

  if (!nova)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }

  nova->item = al; //O nova->item recebe o aluno que eu quero inserir na lista

  nova->tipo = ALU;

  nova->prox = lista->Prim; //Encadeando a nova celula na lista fazendo ela receber o endereço da antiga primeira celula que vai virar a segunda

  lista->Prim = nova; //Mudando a primeira celula da lista, o inicio da lista apontar para a nova e assim colocando ela no primeiro lugar da lista

  if (lista->Ult == NULL) //Caso a lista estivesse vazia
  {
    lista->Ult = nova; //A nova vai ser a primeira celula da lista
  }
};

//No inicio
void InsereProfessor(ListaHet *lista, Professor *prof)
{
  Celula *nova = (Celula *)malloc(sizeof(Celula));

  if (!nova)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }

  nova->item = prof; //O nova->item recebe o professor que eu quero inserir na lista

  nova->tipo = PROF;

  nova->prox = lista->Prim; //Encadeando a nova celula na lista fazendo ela receber o endereço da antiga primeira celula que vai virar a segunda

  lista->Prim = nova; //Mudando a primeira celula da lista, o inicio da lista apontar para a nova e assim colocando ela no primeiro lugar da lista

  if (lista->Ult == NULL) //Caso a lista estivesse vazia
  {
    lista->Ult = nova; //A nova vai ser a primeira celula da lista
  }
};

void ImprimeListaHet(ListaHet *lista)
{
  Celula *p; //ponteiro auxiliar que aponta para um celula que já existe e já foi alocada anteriormente

  for (p = lista->Prim; p != NULL; p = p->prox)
  {
    // Se for aluno, impreme aluno
    if (p->tipo == ALU)
    {
      printf("ALUNO: ");
      imprimeAluno(p->item); //p anda em cada celula da lista
    }
    if (p->tipo == PROF)
    {
      printf("PROFESSOR: ");
      imprimeProfessor(p->item); //p anda em cada celula da lista
      // Aqui acontece uma conversão de tipo implicita, o void pointer é convertido para o tipo Professor implicitamente. Nesse caso é o downcasting (menos especifico para mais especifico).
    }
  }
};

float ValorChurrasco(ListaHet *lista)
{
  Celula *p = lista->Prim;
  float valor = 0.0;

  while (p != NULL)
  {
    if (p->tipo == PROF)
      valor = valor + 0.02 * retornaSalario(p->item);
    if (p->tipo == ALU)
      valor = valor + 30.0;
    p = p->prox;
  }
  return valor;
}

//Libera apenas a memoria da lista
void LiberaListaHet(ListaHet *lista)
{
  Celula *p = lista->Prim; //ponteiro auxiliar recebendo a primeira celula da lista
  Celula *t;               // outro ponteiro auxiliar

  while (p != NULL) //Enquanto não chegar ao final da lista
  {
    t = p->prox; //O ponteiro temporário aponta para a proxima célula
    free(p);
    p = t;
  }
  //Liberando a sentinela
  free(lista);
};