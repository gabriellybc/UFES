#include <stdio.h>
#include <stdlib.h>
#include "abb.h"

int main()
{
  // Criando alunos
  Aluno *gab = inicializaAluno(123, "Gabi", 5.3);
  Aluno *hen = inicializaAluno(456, "Henrique", 7.8);
  Aluno *isa = inicializaAluno(789, "Isa", 8.4);
  Aluno *con = inicializaAluno(951, "Jose", 3.7);
  Aluno *neu = inicializaAluno(357, "Neuzi", 8.8);

  Arv *a = abb_cria();
  a = abb_insere(a, gab);
  a = abb_insere(a, isa);
  a = abb_insere(a, hen);
  a = abb_insere(a, con);
  a = abb_insere(a, neu);

  abb_imprime(a);

  printf("\nAluno com matricula 951 pertence a arvore? %d", ((abb_busca(a, 123) != NULL) ? 1 : 0));

  printf("\nAluno com matricula 75319 pertence a arvore? %d\n", ((abb_busca(a, 123) != NULL) ? 1 : 0));

  a = abb_retira(a, 123);
  a = abb_retira(a, 951);
  a = abb_retira(a, 456);

  abb_imprime(a);

  abb_libera(a);

  destroiAluno(gab);
  destroiAluno(hen);
  destroiAluno(isa);
  destroiAluno(neu);
  destroiAluno(con);

  return 0;
}