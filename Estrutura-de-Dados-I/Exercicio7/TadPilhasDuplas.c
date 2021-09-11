#include "TadPilhasDuplas.h"
#include <stdio.h>
#include <stdlib.h>

#define MaxTam 10

typedef struct indicepilha IndicePilha;

struct indicepilha
{
  int Topo, Base;
};

struct pilhadupla
{
  Item *item[MaxTam];
  IndicePilha Pilha1, Pilha2;
};

// Inicializa a estrutura pilha
PilhaDupla *inicPilhaDupla(void)
{
  PilhaDupla *p = (PilhaDupla *)malloc(sizeof(PilhaDupla));
  p->Pilha1.Base = 0;
  p->Pilha1.Topo = -1; //cresce para a direita
  p->Pilha2.Base = MaxTam - 1;
  p->Pilha2.Topo = MaxTam; //cresce para a esquerda
  return p;
}

//inclui na pilha1
void pushPilha1(PilhaDupla *p, Item *item)
{
  if (!p || p->Pilha1.Topo == (p->Pilha2.Topo - 1) || !item)
  {
    printf("\nPilha cheia ou item invalido");
    return;
  }
  p->item[p->Pilha1.Topo + 1] = item;
  p->Pilha1.Topo++;
}

//inclui na pilha1
void pushPilha2(PilhaDupla *p, Item *item)
{
  if (!p || p->Pilha1.Topo == (p->Pilha2.Topo - 1) || !item)
  {
    printf("\nPilha cheia ou item invalido");
    return;
  }
  p->item[p->Pilha2.Topo - 1] = item;
  p->Pilha2.Topo--;
}

//retira da pilha1
Item *popPilha1(PilhaDupla *p)
{
  if (!p || p->Pilha1.Topo == -1)
  {
    printf("\nPilha vazia!!!");
    return NULL;
  }
  Item *item = p->item[p->Pilha1.Topo];
  p->Pilha1.Topo--;
  return item;
}

//retira da pilha2
Item *popPilha2(PilhaDupla *p)
{
  if (!p || p->Pilha2.Topo == MaxTam)
  {
    printf("\nPilha vazia!!!");
    return NULL;
  }
  Item *item = p->item[p->Pilha2.Topo];
  p->Pilha2.Topo++;
  return item;
}

// imprime do topo para a base
void imprimePilha1(PilhaDupla *p)
{
  int i;
  if (!p)
    return;
  printf("\n----------- Pilha1 ------------\n");
  for (i = (p->Pilha1.Topo); i >= 0; i--)
    printf("%d\n", *p->item[i]);
}

// imprime do topo para a base
void imprimePilha2(PilhaDupla *p)
{
  int i;
  if (!p)
    return;
  printf("\n----------- Pilha2 ------------\n");
  for (i = (p->Pilha2.Topo); i <= MaxTam - 1; i++)
    printf("%d\n", *p->item[i]);
}

void destroiPilhaDupla(PilhaDupla *p)
{
  if (!p)
    return;
  free(p);
}