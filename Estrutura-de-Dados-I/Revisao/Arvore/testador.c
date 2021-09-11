#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

int main()
{
  Arv *d = arv_cria('d', arv_criavazia(), arv_criavazia());

  Arv *b = arv_cria('b', arv_criavazia(), arv_criavazia());

  Arv *c = arv_cria('c', arv_criavazia(), d);

  Arv *a = arv_cria('a', b, c);

  printf("Tem c nela? %d\n", arv_pertence(a, 'c'));

  arv_imprime(a);

  printf("\nQuantidade de folhas: %d\n", folhas(a));

  printf("\nOcorrencias: %d\n", ocorrencias(a, 'a'));

  printf("\nInfo: %c\n", info(a));

  return 0;
}