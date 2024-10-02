#ifndef ARRAY_H
#define ARRAY_H
#include "lista.h"

//Array genérico com quantidade de elementos inseridos e quantidade de eixos
typedef struct Array * array;

//Função para inicializar um array de tamanho size (não pode ser expandido)
array array_init(unsigned int size);

/*
  Função para copiar uma lista e converter para array.
  O ponteiro para função arvIdUpdater é para caso o array for ser utilizado
  como base para uma floresta, inicializar os ids das árvores
*/
array array_copyFromList(lista l, void arvIdUpdater(void*, unsigned int));

//Função para inserir um elemento no array a
void array_insere(array a, void* elem);

/*
  Função para liberar a memória alocada a um array a
  O ponteiro para função limpador é a função que irar
  liberar a memória do conteúdo de cada elemento de a,
  caso seja NULL, só será liberada a memória usada pelo array
*/
void array_free(array a, void limpador(void*));

/*
  Função utilizada durante o debug para imprimir os dados de
  um array a.
  O ponteiro para função imprime é a função que imprime o
  conteúdo de cada elemento de a
*/
unsigned int array_imprime(array a, void imprime(void*, int));

/*
  Função usada para ordenar um array a de acordo com um comparador comparator
  Implementação: Quick Sort
*/
void array_sort(array a, int comparator(const void*, const void*));


//Função para obter o tamanho (quantidade de elementos inseridos) de um array a
unsigned int array_getSize(array a);

//Função para obter um elemento em determinada posição pos de um array a
void* array_getElem(array a, unsigned int pos);

/*
  Função que recebe um array de pontos pts, calcula as distâncias entre os pontos usando calcDistancia,
  inicializa as distâncias usando distInit, as coloca em um novo array (alocação de memória) e o retorna
*/
array array_calcDist(array pts, float calcDistancia(void*, void*, int), void* distInit(float, void*, void*));

/*
  Função que recebe um array a, cria um novo array (alocação de memória) de tamanho qtdElem baseado em a,
  seleciona os elementos de a usando identifier e passando elemParaComparar como parâmetro de identifier,
  os coloca no novo array e o retorna
*/
array array_getTipoElem(array a, void* identifier(void*, void*, array), void* elemParaComparar, unsigned int qtdElem);

/*
  Função que copia os elementos de um grupo (array fonte) para o array dest (ja inicializado).
  sizes é um vetor contendo o tamanho de cada grupo, sendo que sizes[0] = 0 e
  index é o índice (1o grupo, 2o grupo, etc) (1o grupo = 0, 2o grupo = 1, etc) do grupo
*/
void array_copyFromGrupo(array dest, array fonte, unsigned int* sizes, unsigned int index);

/*
  Função que cria um array (alocação de memória) de tamanho qtd,
  "pula" os elementos do array a de acordo com os valores de sizes (pegando o 1o elemento),
  insere os 1os elementos no array e o retorna
*/
array array_getInterv(array a, unsigned int* sizes, unsigned int qtd);

/*Função que pega um array a, previamente ordenado, de forma que tenha um grupo após o outro
  sequencialmente (ordem dos grupos aleatória) e que cada grupo já esteja ordenado internamente,
  utiliza o array grupos como uma "máscara" de ordenação (o array grupo contém os 1os elementos
  de cada grupo), e ordena o array a de acordo com o array grupo.
  O vetor sizes é o tamanho de cada grupo no posicionamento do array a e o vetor sizesOrdenados
  é o tamanho de cada grupo no posicionamento do array grupos
*/
void array_sortGrupos(array a, array grupos, unsigned int* sizes, unsigned int* sizesOrdenados);

//Função que copia totos os elementos do array fonte para o array dest
void array_copyFromArray(array dest, array fonte);

//Função que retorna a quantidade de eixos de um array
unsigned int array_getQtdEixos(array a);

#endif