#ifndef LISTAHET_H_
#define LISTAHET_H_

#include <stdio.h>
#include "Aluno.h"
#include "Professor.h"

typedef struct listhet ListaHet;

ListaHet *InicListaHet(void);

void InsereAluno(ListaHet *lista, Aluno *al);

void InsereProfessor(ListaHet *lista, Professor *prof);

void ImprimeListaHet(ListaHet *lista);

float ValorChurrasco(ListaHet *lista);

void LiberaListaHet(ListaHet *ListaHet);

#endif // ListaHet_H_
