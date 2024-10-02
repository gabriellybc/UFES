#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/*
  Estrutura interna da celula da lista
*/
typedef struct Celula * celula;

/*
  Lista genérica com alocação dinâmica de memória que arnazema
  seu tamanho e a quantidade de eixos que a entrada tem
*/
struct Lista{
    celula prim, ult;
    unsigned int size;
    unsigned int qtdEixos;
};

/*
  Estrutura interna da celula da lista
*/
struct Celula{
    void* elem;
    celula prox;
};

/*
  Inicializa a lista
*/
lista lista_init(){
    lista l = malloc(sizeof(struct Lista));
    l->size = 0;
    l->qtdEixos = 0;
    l->prim = NULL;
    l->ult = NULL;
    return l;
}

//Função interna para inicializar a celula contendo um elemento elem
celula cel_init(void* elem){
    celula cel = malloc(sizeof(struct Celula));
    cel->elem = elem;
    cel->prox = NULL;
    return cel;
}

/*
  Insere o elemento elem na lista l
*/
void lista_insere(lista l, void* elem){
    celula toInsert = cel_init(elem);
    celula cel;

    l->size++;

    if(l->prim == NULL){
        l->prim = toInsert;
        l->ult = toInsert;
        return;
    }

    for(cel = l->prim; cel->prox; cel = cel->prox);
    cel->prox = toInsert;
    l->ult = toInsert;
}

/*
  Altera o valor da quantidade de eixos da lista l para qtdEixos
*/
void lista_setQtdEixos(lista l, unsigned int qtdEixos){
    l->qtdEixos = qtdEixos;
}

/*
  Libera a memória alocada pela lista (SEM liberar a memória do conteúdo)
*/
void lista_free(lista l){
    celula aux = NULL;

    if(l->prim){
        for(celula cel = l->prim; cel; cel = aux){
            aux = cel->prox;
            free(cel);
        }
    }
    free(l);
}

/*
  Função utilizada durante o debug para imprimir os dados de
  uma lista l.
  O ponteiro para função imprime é a função que imprime o
  conteúdo de cada elemento de l
*/
unsigned int lista_imprime(lista l, void imprime(void*, int)){
    unsigned int count = 0;
    if(l->prim){
        for(celula cel = l->prim; cel; cel = cel->prox){
            count++;
            imprime(cel->elem, l->qtdEixos);
        }
    }
    return count;
}

/*
  Função que insere cada elemento de uma lista l no array array, utilizando
  o ponteiro para função inserter e passando arvIdUpdater como argumento
  de inserter
*/
void lista_insertToArray(void* array, lista l, void inserter(void*, unsigned int, void*, void (*)(void*, unsigned int)),
                         void arvIdUpdater(void*, unsigned int)){
    unsigned int i = 0;
    for(celula cel = l->prim; cel; cel = cel->prox, i++){
        inserter(array, i, cel->elem, arvIdUpdater);
    }
}

/*
  Função para obter o tamanho de uma lista l
*/
unsigned int lista_getSize(lista l){
    return l->size;
}

/*
  Função para obter a quantidade de eixos de uma lista l
*/
unsigned int lista_getQtdEixos(lista l){
    return l->qtdEixos;
}