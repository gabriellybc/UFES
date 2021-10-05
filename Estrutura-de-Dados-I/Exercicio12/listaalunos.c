#include "listaalunos.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct cr
{
  float CR; //CR acumulado
  int n;    //numero de alunos
};

//definindo as funcoes de callback
// --------------------------------------------------------------
//comparacao
static int comparacaoMat(void *aluno1, void *aluno2)
{
  Aluno *a1 = (Aluno *)aluno1;
  Aluno *a2 = (Aluno *)aluno2;

  //retorna 0 se forem iguais
  if (retornaMat(a1) == retornaMat(a2))
    return 0;

  //retorna 1 se forem diferentes
  return 1;
}

//impressao (compativel com callback de percorre)
static int imprime(void *aluno, void *dado)
{
  imprimeAluno(aluno);
  return 1; //para continuar no loop
}

//acumula CRs
static int acumula(void *aluno, void *dado)
{
  struct cr *acumulado = (struct cr *)dado;
  acumulado->CR += retornaCR(aluno);
  acumulado->n++;
  return 1; //continuar percurso na percorre
}
// --------------------------------------------------------------

//retira o aluno com a matricula dada
ListaGen *retiraAluno(ListaGen *lista, int matricula)
{
  return retiraLista(lista, comparacaoMat, &matricula);
}

//verifica se o aluno esta na lista
int pertenceAluno(ListaGen *lista, int matricula)
{
  return percorreLista(lista, comparacaoMat, &matricula);
}

//imorime a lista de alunos
void imprimeListaAlunos(ListaGen *lista)
{
  percorreLista(lista, imprime, NULL);
}

//calcula media de CRs da turma
float mediaTurma(ListaGen *lista)
{
  struct cr *acumulado = (struct cr *)malloc(sizeof(struct cr));
  acumulado->CR = 0.0;
  acumulado->n = 0;
  percorreLista(lista, acumula, acumulado);
  float media = acumulado->CR / acumulado->n;
  free(acumulado);
  return media;
}