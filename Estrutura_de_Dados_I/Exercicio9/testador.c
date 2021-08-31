#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

int main()
{
  // Criando alunos
  Aluno *gab = inicializaAluno(123, "Gabi", 5.3);
  Aluno *hen = inicializaAluno(456, "Henrique", 7.8);
  Aluno *isa = inicializaAluno(789, "Isa", 8.4);
  Aluno *con = inicializaAluno(951, "Jose", 3.7);
  Aluno *neu = inicializaAluno(357, "Neuzi", 8.8);

  Arv *a1 = arv_cria(hen, arv_criavazia(), arv_criavazia());
  Arv *a2 = arv_cria(isa, arv_criavazia(), arv_criavazia());
  Arv *a3 = arv_cria(hen, arv_criavazia(), a2);
  Arv *a4 = arv_cria(neu, arv_criavazia(), arv_criavazia());
  Arv *a5 = arv_cria(gab, a1, arv_criavazia());
  Arv *a6 = arv_cria(con, a4, a5);
  Arv *arv = arv_cria(gab, a3, a6);

  arv_imprime(arv);

  printf("\nAluno chamado Henrique pertence a arvore? %d", arv_pertence(arv, "Henrique"));

  printf("\nAluna chamado Gabi pertence a arvore? %d", arv_pertence(arv, "Gabi"));

  printf("\nQuantidade de folhas: %d", folhas(arv));

  printf("\nAltura da arvore: %d", altura(arv));

  printf("\nOcorrencias de Henrique: %d", ocorrencias(arv, "Henrique"));

  printf("\nOcorrencias de Gabi: %d\n", ocorrencias(arv, "Gabi"));

  arv_libera(arv);

  destroiAluno(gab);
  destroiAluno(hen);
  destroiAluno(isa);
  destroiAluno(neu);
  destroiAluno(con);

  return 0;
}