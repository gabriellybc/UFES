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

  Arv *a = arv_cria();
  abb_insere(a, gab);
  abb_insere(a, isa);
  abb_insere(a, hen);
  abb_insere(a, con);
  abb_insere(a, neu);

  arv_imprime(a);

  printf("\nAluno com matricula 951 pertence a arvore? %d", ((abb_busca(a, 123) != NULL) ? 1 : 0));

  printf("\nAluno com matricula 75319 pertence a arvore? %d", ((abb_busca(a, 123) != NULL) ? 1 : 0));

  abb_retira(a, 123);
  abb_retira(a, 951);
  abb_retira(a, 456);

  arv_libera(a);

  destroiAluno(gab);
  destroiAluno(hen);
  destroiAluno(isa);
  destroiAluno(neu);
  destroiAluno(con);

  return 0;
}