#ifndef DISTANCIA_H
#define DISTANCIA_H
#include "ponto.h"


/*
  struct que armazena 2 pontos, a distância entre eles e uma
  variável do tipo char (utilizada como boolean) que indica
  se os 2 pontos estão conectados
*/
typedef struct Distancia * distancia;

/*
  Função utilizada para inicializar uma distância dados 2 pontos
  e a distância entre eles
*/
void* dist_init(float dist, void* p1, void* p2);

/*
  Função para obter a distância de uma distância dist (português chora nessa hora)
*/
float dist_getDist(distancia dist);

/*
  Função para liberar a memória alocada para uma distância dist
*/
void dist_free(void* dist);

/*
  Função utilizada no debug para imprimir os dados de uma distância dist.
  O argumento int é descartado, só está aqui para a função poder ser
  passada como ponteiro para a função array_imprime
*/
void dist_imprime(void* dist, int);

/*
  Função para comparar 2 distâncias comparando suas distâncias (Pleonasmo...)
*/
int dist_compare(const void* d1, const void* d2);

/*
  Função que obtem o 1o ponto de uma distância (ctrl + c)
*/
ponto dist_getP1(distancia d);

/*
  Função que obtem o 2o ponto de uma distância (ctrl + v)
*/
ponto dist_getP2(distancia d);

/*
  Função que conecta os 2 pontos de uma distância
*/
void dist_connect(distancia d);

/*
  Função que desconecta os 2 pontos de uma distância
*/
void dist_disconnect(distancia d);

/*
  Função que verifica se os 2 pontos de uma distância estão conectados
*/
char dist_isConnected(distancia d);

#endif