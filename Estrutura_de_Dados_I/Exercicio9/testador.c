#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

int main()
{
  // Criando alunos
  Aluno *al1 = inicializaAluno(123, "Aluno1", 5.3);
  Aluno *al2 = inicializaAluno(456, "Aluno2", 7.8);
  Aluno *al3 = inicializaAluno(789, "Aluno3", 8.4);
  Aluno *al4 = inicializaAluno(951, "Aluno4", 3.7);

  Arv *d = arv_cria(al1, arv_criavazia(), arv_criavazia());

  Arv *b = arv_cria(al2, arv_criavazia(), arv_criavazia());

  Arv *c = arv_cria(al3, arv_criavazia(), d);

  Arv *a = arv_cria(al4, b, c);

  printf("Tem al3 nela? %d\n", arv_pertence(a, "Aluno3"));

  arv_imprime(a);

  printf("\n\n");

  arv_imprime_graficamente(a);

  return 0;
}