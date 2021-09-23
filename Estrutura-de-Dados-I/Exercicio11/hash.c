#include "hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Define o tipo opaco que contem a Hash
struct hash
{
  Palavra **vet;
  int tamanhoHash;
};

//Funcao da Hash
static int hash(char *s, int tamanhoHash)
{
  int i, total = 0;
  for (i = 0; s[i] != '\0'; i++)
    total += s[i];
  return (total % tamanhoHash);
}

Hash *inicHash(int tamanhoHash)
{
  int i;
  //inicializa o tipo opaco
  Hash *h = (Hash *)malloc(sizeof(Hash));
  h->tamanhoHash = tamanhoHash;
  //inicializa o vetor da Hash
  h->vet = (Palavra **)malloc(tamanhoHash * sizeof(Palavra *));
  //vamos iniciar a tabela com NULL (importante valor de comparação na busca)
  for (i = 0; i < tamanhoHash; i++)
    h->vet[i] = NULL;
  return h;
}

//Faz acesso a hash realizando 2 possíveis operações:
//1) insercao, caso a palavra nao esteja na hash
//2) incremento de ocorrencia, caso a palavra ja esteja na hash
Palavra *acessa(Hash *h, char *string)
{
  Palavra *p;

  //aplica funcao de hash
  int indice = hash(string, h->tamanhoHash);

  p = buscaPalavra(h->vet[indice], string);

  //atualiza ocorrencia
  if (p)
    return p;

  //caso não tenha encontrado na tabela (p e' NULL), insere a nova palavra não

  //cria palavra
  p = inicPalavra(string);

  //insere na Hash
  h->vet[indice] = inserePalavraLista(h->vet[indice], p);

  return p;
}

void imprimeHash(Hash *h)
{
  int i;
  for (i = 0; i < h->tamanhoHash; i++)
  {
    if (h->vet[i])
    {
      printf("\nPosicao vet[%d]: \n", i);
      imprimeLista(h->vet[i]);
    }
  }
}

void liberaHash(Hash *h)
{
  int i;
  for (i = 0; i < h->tamanhoHash; i++)
    liberaListaPalavra(h->vet[i]);
  free(h->vet);
  free(h);
}
