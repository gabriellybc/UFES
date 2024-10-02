#ifndef LISTA_H
#define LISTA_H

/*
  Lista genérica com alocação dinâmica de memória que arnazema
  seu tamanho e a quantidade de eixos que a entrada tem
*/
typedef struct Lista * lista;

/*
  Inicializa a lista
*/
lista lista_init();

/*
  Insere o elemento elem na lista l
*/
void lista_insere(lista l, void* elem);

/*
  Altera o valor da quantidade de eixos da lista l para qtdEixos
*/
void lista_setQtdEixos(lista l, unsigned int qtdEixos);

/*
  Libera a memória alocada pela lista (SEM liberar a memória do conteúdo)
*/
void lista_free(lista l);

/*
  Função utilizada durante o debug para imprimir os dados de
  uma lista l.
  O ponteiro para função imprime é a função que imprime o
  conteúdo de cada elemento de l
*/
unsigned int lista_imprime(lista l, void imprime(void*, int));

/*
  Função que insere cada elemento de uma lista l no array array, utilizando
  o ponteiro para função inserter e passando arvIdUpdater como argumento
  de inserter
*/
void lista_insertToArray(void* array, lista l, void inserter(void*, unsigned int, void*, void (*)(void*, unsigned int)),
                         void arvIdUpdater(void*, unsigned int));

/*
  Função para obter o tamanho de uma lista l
*/
unsigned int lista_getSize(lista l);

/*
  Função para obter a quantidade de eixos de uma lista l
*/
unsigned int lista_getQtdEixos(lista l);

#endif