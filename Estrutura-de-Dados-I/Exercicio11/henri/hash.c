#include "hash.h"

#include <stdlib.h>
#include <string.h>

#include "palavra.h"

struct hash
{
  Palavra **vet;
  int tamanho;
};

static int hash(char *s, int tamanho)
{
  int i;
  int total = 0;
  for (i = 0; s[i] != '\0'; i++)
    total += s[i];
  return (total % tamanho);
}

Hash *inicHash(int tamanho)
{
  int i;

  Hash *h = (Hash *)malloc(sizeof(Hash));
  h->tamanho = tamanho;

  h->vet = (Palavra **)malloc(tamanho * sizeof(Palavra *));

  for (i = 0; i < tamanho; i++)
    h->vet[i] = NULL;
  return h;
}

Palavra *acessa(Hash *h, char *string)
{
  Palavra *p;

  int indice = hash(string, h->tamanho);
  p = buscaPalavra(h->vet[indice], string);

  if (p)
    return p;

  p = inicPalavra(string);

  h->vet[indice] = inserePalavralista(h->vet[indice], p);
  return p;
}

void imprimeHash(Hash *h)
{
  int i;
  for (i = 0; i < h->tamanho; i++)
  {
    printf("\nPosição vet[%d]: \n ", i);
    imprimelista(h->vet[i]);
  }
}

void liberaHash(Hash *h)
{
  int i;
  for (i = 0; i < h->tamanho; i++)
    liberalistaPalavra(h->vet[i]);
  free(h->vet);
  free(h);
}