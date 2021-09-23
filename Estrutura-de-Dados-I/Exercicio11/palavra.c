#include "palavra.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Define o tipo opaco Palavra que tambem e' uma lista para tratamento de colisao
struct palavra
{
  char *string;
  int ocorrencias;
  struct palavra *prox;
};

Palavra *inicPalavra(char *str)
{
  Palavra *pal = (Palavra *)malloc(sizeof(Palavra));
  pal->string = strdup(str);
  pal->ocorrencias = 0;
  pal->prox = NULL;
  return pal;
}

char *retornaString(Palavra *pal)
{
  return pal->string;
}

void atualizaOcorrencias(Palavra *pal)
{
  pal->ocorrencias++;
}

int retornaOcorrencias(Palavra *pal)
{
  return pal->ocorrencias;
}

//busca a palavra na lista de colisoes
Palavra *buscaPalavra(Palavra *pal, char *string)
{
  Palavra *p;
  //busca na lista de colisao
  for (p = pal; p != NULL; p = p->prox)
  {
    if (strcmp(string, p->string) == 0)
      return p;
  }
  return NULL;
}

//Insere a palavra na primeira posicao
Palavra *inserePalavraLista(Palavra *lista, Palavra *p)
{
  p->prox = lista;
  return p;
}

// Retorna o numero de palavra da lista de colisoes
int contaPalavrasLista(Palavra *p)
{
  Palavra *pal;
  int i = 0;
  //procura na lista de colisao
  for (pal = p; pal != NULL; pal = pal->prox)
    i++;
  return i;
}

void imprimeLista(Palavra *p)
{
  Palavra *aux;
  for (aux = p; aux != NULL; aux = aux->prox)
    printf("String: %s - Ocorrencia: %d\n", aux->string, aux->ocorrencias);
}

void liberaListaPalavra(Palavra *pal)
{
  Palavra *aux = pal;
  Palavra *t;

  while (aux != NULL)
  {
    t = aux->prox;
    free(aux->string);
    free(aux);
    aux = t;
  }
}