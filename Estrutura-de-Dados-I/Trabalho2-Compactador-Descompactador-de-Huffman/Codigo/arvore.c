#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"

//Tipo arv (tipo opaco)
struct arv
{
  unsigned char info; //campo de char
  int peso;
  bool temCaracter;
  struct arv *esq; // ponteiro para a esquerda
  struct arv *dir; // ponteiro para a direita
};

// Cria uma árvore vazia
Arv *arvCriaVazia()
{
  return NULL;
}

//Cria uma arvore com todos os campos definidos
Arv *arvCria(unsigned char c, int qnt, bool tem, Arv *sae, Arv *sad)
{
  Arv *p = (Arv *)malloc(sizeof(Arv)); //malloc para criar o novo no, p aponta para o novo no
  p->info = c;
  p->peso = qnt;
  p->temCaracter = tem;
  p->esq = sae;
  p->dir = sad;
  return p;
}

//Indica se uma árvore e' ou nao vazia
bool arvVazia(Arv *a)
{
  return a == NULL; //Se a raiz for nula, então ela é vazia
}

//Retorna o campo peso da arvore
int retornaPeso(Arv *a)
{
  if (arvVazia(a))
    return 0;
  return a->peso;
}

//Retorna o campo info da arvore
unsigned char retornaInfo(Arv *a)
{
  if (arvVazia(a))
    return '\0';
  return a->info;
}

//Retorna o campo temCaracter
bool retornaTemCaracter(Arv *a)
{
  if (arvVazia(a))
    return 0;
  return a->temCaracter;
}

//Retorna o campo arv esq da arvore
Arv *retornaArvEsq(Arv *a)
{
  if (arvVazia(a))
    return NULL;
  return a->esq;
}

//Retorna o campo arv dir da arvore
Arv *retornaArvDir(Arv *a)
{
  if (arvVazia(a))
    return NULL;
  return a->dir;
}

//Percorre recursivamente a árvore, visitando todos os nós e imprimindo sua informação
void arvImprime(Arv *a)
{
  printf("<");
  if (!arvVazia(a))
  {
    printf("%c", a->info); //mostra raiz
    arvImprime(a->esq);    //mostra sae
    arvImprime(a->dir);    //mostra sad
  }
  printf(">");
}

//A arvore e' percorrida recursivamente e o devido bit e' armazenado ao final do bitmap
void arvBinario(Arv *a, bitmap *bm)
{
  if (retornaTemCaracter(a)) //caso base
  {
    bitmapAppendLeastSignificantBit(bm, 1);
    bitmap *bin = dec2bin(retornaInfo(a));
    for (int i = 0; i < 8; i++)
      bitmapAppendLeastSignificantBit(bm, bitmapGetBit(bin, i));
    bitmapLibera(bin);
    return;
  }
  bitmapAppendLeastSignificantBit(bm, 0);
  arvBinario(a->esq, bm);
  arvBinario(a->dir, bm);
}

static int max2(int a, int b)
{
  return (a > b) ? a : b; // Se a for maior que b, então retorna a. Caso contrário, retorna b
}

//Retorna a altura da arvore
int arvAltura(Arv *a)
{
  if (arvVazia(a)) //Condição de parada: Se a árvore estiver vazia
    return -1;     //Retorna -1
  else             //Caso contrário (árvore não vazia)
  {
    return 1 + max2(arvAltura(a->esq), arvAltura(a->dir));
  }
}

//Retorna o numero total de nos de uma arvore cheia
int arvNos(Arv *a)
{
  int nos = 1, altura = arvAltura(a);
  for (int i = 0; i < altura + 1; i++)
    nos *= 2;
  return nos - 1; //nos = 2^(altura+1) - 1
}

//Retorna a quantidade de folhas de uma arvore binaria
int arvFolhas(Arv *a)
{
  int qnt_folhas;
  if (arvVazia(a)) //caso base
    return 0;
  qnt_folhas = arvFolhas(a->esq) + arvFolhas(a->dir);
  qnt_folhas = (qnt_folhas == 0) ? 1 : qnt_folhas; //Se qnt_folhas for igual a zero, retorna 1. Caso contrário, retorna qnt_folhas
  return qnt_folhas;
}

//Armazena a arvore do arquivo binario em uma estrutua Arvore
Arv *redefineArvore(Arv *a, bitmap *bm, int totalFolhas, int *folhasAtuais, bool *flagFolhasMax, int *i, FILE *arq, int *leituras, long *posicao)
{
  if (*flagFolhasMax) //Se atingir o numero max de folhas
    return NULL;

  if (*i == 100000) //Se chegou ao final da leitura
  {
    bitmapLibera(bm);
    bm = bitmapInit(100000 * 8);
    fread(bitmapGetContents(bm), sizeof(char), 100000, arq); //le novamente
    (*leituras)++;
    *i = 0;
  }

  a = arvCria('\0', 0, 0, arvCriaVazia(), arvCriaVazia());

  if (bitmapGetBit(bm, *i) == 1) // no folha
  {
    bitmap *bin = bitmapInit(8);
    for (int j = 0; j < 8; j++) //pega o binario do caracter
    {
      (*i)++;
      bitmapAppendLeastSignificantBit(bin, bitmapGetBit(bm, *i));
    }
    unsigned char caracter = bin2dec(bin);
    bitmapLibera(bin);
    a->info = caracter;
    a->temCaracter = 1;
    (*folhasAtuais)++;
    if (*folhasAtuais == totalFolhas)
    {
      *flagFolhasMax = 1;
      // diminui a posicao atual de leitura pelo o que faltava ler para encontrar a posicao atual real do final da arvore
      *posicao = ((*leituras - 1) * 100000) + ((*i / 8) + 1);
    }
    else
      (*i)++; //Incrementa o index para analisar o prox bit
    return a;
  }

  (*i)++; //Incrementa o index para analisar o prox bit

  a->esq = redefineArvore(a->esq, bm, totalFolhas, folhasAtuais, flagFolhasMax, i, arq, leituras, posicao);

  a->dir = redefineArvore(a->dir, bm, totalFolhas, folhasAtuais, flagFolhasMax, i, arq, leituras, posicao);

  return a; //retorna a arvore completa
}

//Retorna o caracter passado por um bitmap
unsigned char retornaCaracter(bitmap *bm, Arv *a, int *indice)
{
  unsigned int bit = bitmapGetBit(bm, *indice);
  //faz a função recursivamente de acordo com o bitmap, até encontar um nó folha(com caracter)
  if (retornaTemCaracter(a)) //caso base
    return retornaInfo(a);

  if ((int)bit == 0)
  {
    (*indice)++;
    retornaCaracter(bm, retornaArvEsq(a), indice);
  }
  else
  {
    (*indice)++;
    retornaCaracter(bm, retornaArvDir(a), indice);
  }
}

//Libera o espaço de memória ocupado pela árvore6
Arv *arvLibera(Arv *a)
{
  //Se a árvore não estiver vazia, entra aqui
  if (!arvVazia(a)) //Caso base: árvore estar vazia
  {
    //Chamando recursivamente para sae
    arvLibera(a->esq); //libera sae
    //Chamando recursivamente para sad
    arvLibera(a->dir); //libera sad
    free(a);           //libera raiz
  }
  return NULL; //Se a árvore estiver vazia, retorna NULL
}