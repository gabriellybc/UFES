#include "Fila.h"
#include "listaSentinela.h"

struct fila
{
  Lista *lista;
};

Fila *inicFila(void)
{
  Fila *f = (Fila *)malloc(sizeof(Fila));
  f->lista = InicLista();
  return f;
};

//Insere sempre no final da fila
void insereFila(Fila *f, Aluno *al)
{
  if (!f)
  {
    printf("\nFila invalida!\n");
    return;
  }
  InsereListaUlt(f->lista, al);
};

//Retira sempre no iniio da fila
Aluno *retiraFila(Fila *f)
{
  if (!f)
  {
    printf("\nFila invalida\n");
    return NULL;
  }
  Aluno *al = RetiraLista(f->lista, 0);
  return al;
};

//Imprime do iniio ao fim da fila
void imprimeFila(Fila *f)
{
  if (!f)
    return;

  ImprimeLista(f->lista);
};

//Libera a memoria da fila, mas não dos alunos
void destroiFila(Fila *f)
{
  if (!f)
    return;
  LiberaLista(f->lista);
  free(f);
};
