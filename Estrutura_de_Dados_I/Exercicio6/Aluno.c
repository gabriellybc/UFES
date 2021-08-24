#include "Aluno.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Tipo Aluno (tipo opaco)
//Estrutura interna do tipo deve ser definida na implementação do TAD
struct aluno
{
  int mat;
  char *nome;
  float CR;
};

/*Inicializa um Aluno*/
Aluno *inicializaAluno(int mat, char *nome, float CR)
{
  Aluno *al = (Aluno *)malloc(sizeof(Aluno));
  if (!al)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }
  al->mat = mat;
  al->CR = CR;
  al->nome = strdup(nome);
  return al;
};

/*Imprime o Aluno*/
void imprimeAluno(Aluno *al)
{
  printf("mat: %d, nome: %s, CR: %.2f\n", al->mat, al->nome, al->CR);
};

/*Retorna a matricula do Aluno*/
int retornaMat(Aluno *al)
{
  return al->mat;
};

/*Retorna nome do Aluno*/
char *retornaNomeAlunoAluno(Aluno *al)
{
  return al->nome;
};

/*Retorna CR do Aluno*/
float retornaCR(Aluno *al)
{
  return al->CR;
};

/*Libera memória alocada para Aluno*/
void destroiAluno(Aluno *al)
{
  free(al->nome);
  free(al);
};
