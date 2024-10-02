#ifndef TREE_H
#define TREE_H

#include "lista.h"
#include "array.h"
#include "ponto.h"
#include "distancia.h"

/*
  Função que gera a MST a partir do array de pontos e distâncias
  e remove as k-1 arestas
*/
void tree_make(array dists, array pts, unsigned int qtdToRemove);

/*
  Função que ordena o array de pontos pts de acordo com os grupos
  para impressão no arquivo de saída
*/
void tree_sort(array pts, unsigned int qtdGrupos);

#endif