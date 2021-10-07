#include <stdio.h>
#include <stdlib.h>
#include "codificacao.h"

//Tipo codifucacao (tipo opaco)
struct cod
{
  char caracter;
  bitmap *bm;
};

//Inicializa a estrutura Codificacao
Codificacao *inicCodificacao(char caracter, bitmap *bm)
{
  Codificacao *cod = (Codificacao *)malloc(sizeof(Codificacao));
  if (!cod)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }
  cod->caracter = caracter;
  cod->bm = bm;
  return cod;
}

//Retorna o caracter (caracter) da codificacao
char retornaCaracterCodificacao(Codificacao *codificacao)
{
  return codificacao->caracter;
}

//Retorna o bitmap da codificacao
bitmap *retornaBitmapCodificacao(Codificacao *codificacao)
{
  return codificacao->bm;
}

//Imprime a codificacao
void imprimeCodificacao(Codificacao *codificacao)
{
  printf("%c\n", codificacao->caracter);
  for (int i = 0; i < bitmapGetLength(codificacao->bm); i++)
    printf("bit #%d = %0x\n", i, bitmapGetBit(codificacao->bm, i));
}

//Libera memória alocada para a codificacao
void liberaCodificacao(Codificacao *codificacao)
{
  bitmapLibera(codificacao->bm);
  free(codificacao);
}