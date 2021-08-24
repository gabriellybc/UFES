#ifndef listaSentinela_H_
#define listaSentinela_H_

#include "Aluno.h"

typedef struct lista Lista;

Lista *InicLista();

void InsereLista(Lista *lista, Aluno *al);

void InsereListaUlt(Lista *Lista, Aluno *al);

void ImprimeLista(Lista *Lista);

Aluno *RetiraLista(Lista *Lista, int pos);

void LiberaLista(Lista *Lista);

#endif // listaSentinela_H_
