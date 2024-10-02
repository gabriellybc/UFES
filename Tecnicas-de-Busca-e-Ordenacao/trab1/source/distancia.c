#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "distancia.h"

/*
  struct que armazena 2 pontos, a distância entre eles e uma
  variável do tipo char (utilizada como boolean) que indica
  se os 2 pontos estão conectados
*/
struct Distancia{
    float dist;
    ponto p1, p2;
    char connected;
};

/*
  Função utilizada para inicializar uma distância dados 2 pontos
  e a distância entre eles
*/
void* dist_init(float dist, void* p1, void* p2){
    distancia d = malloc(sizeof(struct Distancia));
    d->dist = dist;
    d->p1 = (ponto)p1;
    d->p2 = (ponto)p2;
    d->connected = 0;
    return d;
}

/*
  Função para obter a distância de uma distância dist (Português chora nessa hora)
*/
float dist_getDist(distancia dist){
    return dist->dist;
}

/*
  Função para liberar a memória alocada para uma distância dist
*/
void dist_free(void* dist){
    free(dist);
}

/*
  Função utilizada no debug para imprimir os dados de uma distância dist.
  O argumento int é descartado, só está aqui para a função poder ser
  passada como ponteiro para a função array_imprime
*/
void dist_imprime(void* dist, int){
    distancia d = (distancia)dist;

    printf("Distancia entre os pontos %s e %s: %.2lf\n", ponto_getId(d->p1), ponto_getId(d->p2), d->dist);
}

/*
  Função para comparar 2 distâncias comparando suas distâncias (Pleonasmo...)
*/
int dist_compare(const void* d1, const void* d2){
    distancia dist1 = (distancia)d1;
    distancia dist2 = (distancia)d2;
    if(dist1->dist < dist2->dist){
        return -1;
    }
    if(dist1->dist > dist2->dist){
        return 1;
    }
    return 0;
}

/*
  Função que obtem o 1o ponto de uma distância (ctrl + c)
*/
ponto dist_getP1(distancia d){
    return d->p1;
}

/*
  Função que obtem o 2o ponto de uma distância (ctrl + v)
*/
ponto dist_getP2(distancia d){
    return d->p2;
}

/*
  Função que conecta os 2 pontos de uma distância
*/
void dist_connect(distancia d){
    d->connected = 1;
}

/*
  Função que desconecta os 2 pontos de uma distância
*/
void dist_disconnect(distancia d){
    d->connected = 0;
}

/*
  Função que verifica se os 2 pontos de uma distância estão conectados
*/
char dist_isConnected(distancia d){
    return d->connected;
}