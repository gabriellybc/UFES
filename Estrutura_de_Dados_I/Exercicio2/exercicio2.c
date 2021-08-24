#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aluno
{
  char *nome;
  int matricula;
  float p1;
  float p2;
  float p3;
};
typedef struct aluno Aluno;

void imprime_aprovados(int n, Aluno **turma);
float media_turma(int n, Aluno **turma);
char *lenomeAluno(void);

int main()
{
  int n = 0;
  printf("Informe a quantidade de alunos: ");
  scanf("%d", &n);

  Aluno **turma = (Aluno **)malloc(n * sizeof(Aluno *));

  printf("Informaçoes sobre alunos: \n");
  Aluno *pAluno;
  for (int i = 0; i < n; i++)
  {
    pAluno = (Aluno *)malloc(sizeof(Aluno));

    pAluno->nome = lenomeAluno();

    printf("Informe a matricula: ");
    scanf("%d", &pAluno->matricula);

    printf("Informe a nota da prova 1: ");
    scanf("%f", &pAluno->p1);

    printf("Informe a nota da prova 2: ");
    scanf("%f", &pAluno->p2);

    printf("Informe a nota da prova 3: ");
    scanf("%f", &pAluno->p3);

    turma[i] = pAluno;
  }

  printf("\nDados de todos alunos: \n");
  for (int i = 0; i < n; i++)
  {
    printf("Nome: %s; Matricula: %d; P1: %0.2f; P2: %0.2f; P3: %0.2f\n", turma[i]->nome, turma[i]->matricula, turma[i]->p1, turma[i]->p2, turma[i]->p3);
  }

  imprime_aprovados(n, turma);

  printf("\nMedia da turma: %0.2f\n", media_turma(n, turma));

  for (int i = 0; i < n; i++)
  {
    free(turma[i]->nome);
    free(turma[i]);
  }
  free(turma);

  return 0;
}

char *lenomeAluno(void)
{
  // A função captura do teclado em uma memoria estatisca, faz a copia, retorna a copia em memoria dinamica e sai liberando a memoria estatica
  char nomeAluno[121];
  printf("\nDigite o nome: ");
  scanf(" %120[^\n]", nomeAluno);

  return strdup(nomeAluno);
}

void imprime_aprovados(int n, Aluno **turma)
{
  //Imprime na tela os alunos aprovados.
  printf("\nAprovados: \n");
  for (int i = 0; i < n; i++)
  {
    if ((turma[i]->p1 + turma[i]->p2 + turma[i]->p3 / 3) >= 5)
      printf("Nome: %s; Matricula: %d; P1: %0.2f; P2: %0.2f; P3: %0.2f\n", turma[i]->nome, turma[i]->matricula, turma[i]->p1, turma[i]->p2, turma[i]->p3);
  }
}

float media_turma(int n, Aluno **turma)
{
  float media = 0;
  for (int i = 0; i < n; i++)
    media += turma[i]->p1 + turma[i]->p2 + turma[i]->p3;
  return media / (n * 3);
}