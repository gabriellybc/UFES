#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ponto.h"

/*
  Estrutura ponto que armazena suas coordenadas, seu id,
  seu id de árvore, o id de árvore do seu pai e o tamanho da sua árvore
*/
struct Ponto{
    char* id;
    float* componentes;
    unsigned int arv_id;
    unsigned int arv_pid;
    unsigned int arv_size;
};

/*
  Função para criar os pontos a partir de um id, quantidade de eixos
  e das componentes da sua coordenada
*/
ponto ponto_init(char* id, float* componentes){
    ponto p = malloc(sizeof(struct Ponto));
    
    p->id = id;
    p->componentes = componentes;
    p->arv_id = 0;
    p->arv_pid = 0;
    p->arv_size = 1;
    return p;
}

/*
Função para calcular a distância euclidiana entre 2 pontos
*/
float ponto_distancia(void* p1, void* p2, int qtdEixos){
    float dist = 0;
    ponto pt1, pt2;

    pt1 = (ponto)p1;
    pt2 = (ponto)p2;

    for(int i = 0; i < qtdEixos; i++){
        dist += (pt2->componentes[i] - pt1->componentes[i]) * (pt2->componentes[i] - pt1->componentes[i]);
    }

    dist = sqrt(dist);
    return dist;
}

/*
Função para liberar a memória de um ponto
*/
void ponto_free(void* p){
    ponto pt = (ponto)p;
    free(pt->id);
    free(pt->componentes);
    free(pt);
}

/*
  Função usada no debug para imprimir os dados de um ponto
*/
void ponto_imprime(void* p, int m){
    ponto pt = (ponto)p;

    printf("Ponto %s:\n", pt->id);
    printf("Componentes: ");

    for(int i = 0; i < m; i++){
        printf("%.2lf\t", pt->componentes[i]);
    }
    printf("\n");
}

/*
  Função usada para obter o id de um ponto
*/
char* ponto_getId(ponto p){
    return p->id;
}

/*
  Função usada para obter o id de árvore de um ponto
*/
unsigned int ponto_getArvId(ponto p){
    return p->arv_id;
}

/*
  Função usada para setar o pai do ponto
  (seta o id de árvore do pai)
*/
void ponto_setArvPid(ponto p, unsigned int id){
    p->arv_pid = id;
}

/*
  Função usada para obter o id de árvore do pai do ponto
*/
unsigned int ponto_getArvPid(ponto p){
    return p->arv_pid;
}

/*
  Função usada pára inicializar os valores do id de árvore do ponto
  e do pai do ponto (valor = id)
*/
void ponto_setArvIds(void* pt, unsigned int id){
    ponto p = (ponto)pt;
    p->arv_id = id;
    p->arv_pid = id;
}

/*
  Função usada para setar o tamanho da árvore do ponto
*/
void ponto_setArvSize(ponto p, unsigned int size){
    p->arv_size = size;
}

/*
  Função usada ára obter o tamanho da árvore do ponto
*/
unsigned int ponto_getArvSize(ponto p){
    return p->arv_size;
}

/*
  Função usada para comparar 2 pontos pela ordem alfabética de seus ids
*/
int ponto_compare(const void* pt1, const void* pt2){
    ponto p1 = (ponto)pt1;
    ponto p2 = (ponto)pt2;
    return strcmp(p1->id, p2->id);
}