// Implementação de uma fila circular usando vetor simples de

#include "Fila.h"

#define TAM 4

struct fila
{
  int ini; //indice do ínicio da fila
  int n;   //numero de alunos na fila
  Aluno *alunos[TAM];
};

Fila *inicFila(void)
{
  Fila *f = (Fila *)malloc(sizeof(Fila));
  f->ini = 0;
  f->n = 0;
  return f;
};

//Insere sempre no final da fila
void insereFila(Fila *f, Aluno *al)
{
  if (!f || f->n >= TAM)
  {
    printf("\nFila invalida ou cheia!\n");
    return;
  }
  //Achando o final da fila circular
  int pos = (f->ini + f->n) % TAM;
  //Inserindo no final
  f->alunos[pos] = al;
  //incrementa número de alunos
  f->n++;
};

//Retira sempre no iniio da fila
Aluno *retiraFila(Fila *f)
{
  if (!f || f->n == 0)
  {
    printf("\nFila invalida ou vazia!\n");
    return NULL;
  }
  Aluno *al = f->alunos[f->ini];

  //faz o incremento circular do indice do iniio
  f->ini = (f->ini + 1) % TAM;

  f->n--;

  return al;
};

//Imprime do iniio ao fim da fila
void imprimeFila(Fila *f)
{
  int i;
  int pos = 0;

  if (!f)
    return;

  for (int i = 0; i < f->n; i++)
  {
    pos = (f->ini + i) % TAM;
    imprimeAluno(f->alunos[pos]);
  }
};

//Libera a memoria da fila, mas não dos alunos
void destroiFila(Fila *f)
{
  if (!f)
    return;

  free(f);
};
