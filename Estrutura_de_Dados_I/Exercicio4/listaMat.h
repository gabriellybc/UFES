#ifndef LISTAMAT_H_
#define LISTAMAT_H_

// funções de criação, inserção, retirada, impressão e liberação de memória; o retira só vai fazer sentido considerando a posição da matriz na lista.

#include "matriz.h"

typedef struct listmat ListaMat;

ListaMat *InicListaMat();

void InsereMatLista(ListaMat *listaMat, Matriz *mat);

void ImprimeListaMat(ListaMat *listaMat);

Matriz *RetiraMatLista(ListaMat *listaMat, int posicaoMat);

void LiberaListaMat(ListaMat *listaMat);

#endif // LISTAMAT_H_
