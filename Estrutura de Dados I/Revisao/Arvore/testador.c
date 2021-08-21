#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

int main()
{
  Arv *b = arv_cria('b', arv_criavazia(), arv_criavazia());

  Arv *c = arv_cria('c', arv_criavazia(), arv_criavazia());

  Arv *a = arv_cria('a', b, c);

  printf("Tem c nela? %d\n", arv_pertence(a, 'c'));

  arv_imprime(a);
}