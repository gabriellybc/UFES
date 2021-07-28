#ifndef LISTADPLMAT_H_
#define LISTADPLMAT_H_

// funções de criação, inserção, retirada, impressão e liberação de memória; o retira só vai fazer sentido considerando a posição da matriz na lista.

#include "matriz.h"

typedef struct listdplmat ListaDplMat;

ListaDplMat *InicListaDplMat();

ListaDplMat *InsereMatLista(ListaDplMat *listaDplMat, Matriz *mat);

void ImprimeListaMat(ListaDplMat *listaMDplat);

ListaDplMat *RetiraMatLista(ListaDplMat *listaDplMat, int posicaoMat);

void LiberaListaMat(ListaDplMat *listaDplMat);

#endif // LISTADPLMAT_H_
