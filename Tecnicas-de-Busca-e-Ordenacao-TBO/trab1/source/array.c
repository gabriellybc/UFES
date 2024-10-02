#include <stdio.h>
#include <stdlib.h>
#include "array.h"

//Partição utilizada pelo Quick Sort
#define PARTITION lomutoPartition //lomutoPartition ou hoarePartition

//Array genérico com quantidade de elementos inseridos e quantidade de eixos
struct Array{
    void** array;
    unsigned int qtdInseridos;
    unsigned int qtdEixos;
    //qtdEixos: Utilizado para calcular distância entre pontos e no debug para imprimir os dados de um ponto
};

//Função para inicializar um array de tamanho size (não pode ser expandido)
array array_init(unsigned int size){
    array a = malloc(sizeof(struct Array));
    a->array = malloc(size*sizeof(void*));
    if (!a->array) {
        printf("** Erro: Memoria Insuficiente **");
        exit;
    }
    a->qtdInseridos = 0;
    a->qtdEixos = 0;
    return a;
}

//Função interna utilizada por array_copyFromList para inserir um elemento no array ary
void inserter(void* ary, unsigned int pos, void* elem, void arvIdUpdater(void*, unsigned int)){
    array a = (array)ary;
    a->array[pos] = elem;
    a->qtdInseridos++;
    arvIdUpdater(elem, pos);
}

/*
  Função para copiar uma lista e converter para array.
  O ponteiro para função arvIdUpdater é para caso o array for ser utilizado
  como base para uma floresta, inicializar os ids das árvores
*/
array array_copyFromList(lista l, void arvIdUpdater(void*, unsigned int)){
    array a = array_init(lista_getSize(l));
    a->qtdEixos = lista_getQtdEixos(l);
    lista_insertToArray(a, l, inserter, arvIdUpdater);
    return a;  
}

//Função para inserir um elemento no array a
void array_insere(array a, void* elem){
    a->array[a->qtdInseridos] = elem;
    a->qtdInseridos++;
}

/*
  Função para liberar a memória alocada a um array a
  O ponteiro para função limpador é a função que irar
  liberar a memória do conteúdo de cada elemento de a,
  caso seja NULL, só será liberada a memória usada pelo array
*/
void array_free(array a, void limpador(void*)){
    if(limpador != NULL){
        for(int i = 0; i < a->qtdInseridos; i++){
            limpador(a->array[i]);
        }
    }
    free(a->array);
    free(a);
}

/*
  Função utilizada durante o debug para imprimir os dados de
  um array a.
  O ponteiro para função imprime é a função que imprime o
  conteúdo de cada elemento de a
*/
unsigned int array_imprime(array a, void imprime(void*, int)){
    unsigned int qtd = 0;

    for(int i = 0; i < a->qtdInseridos; i++){
        qtd++;
        imprime(a->array[i], a->qtdEixos);
    }
    return qtd;
}

//Função interna para trocar 2 elementos de um array a de posição
void swap(array a, unsigned int pos1, unsigned int pos2){
    void* aux = a->array[pos1];
    a->array[pos1] = a->array[pos2];
    a->array[pos2] = aux;
}

//Função interna que faz a Partição de Lomuto do Quick Sort
unsigned int lomutoPartition(array a, unsigned int left, unsigned int right, int comparator(const void*, const void*)){
    void* pivot = a->array[left];
    unsigned int i = left;

    for(unsigned int j = left+1; j <= right; j++){
        if(comparator(pivot, a->array[j]) > 0){
            i++;
            swap(a, i, j);
        }
    }
    swap(a, left, i);
    return i;
}

//Função interna que faz a Partição de Hoare do Quick Sort
unsigned int hoarePartition(array a, unsigned int left, unsigned int right, int comparator(const void*, const void*)){
    void* pivot = a->array[left];
    unsigned int i = left + 1;
    unsigned int j = right;
    char flag = 0;

    while(i <= j){
        for(; i <= j; i++){
            if(comparator(pivot, a->array[i]) < 0){
                break;
            }
        }

        for(; i<= j; j--){
            if(comparator(pivot, a->array[j]) > 0){
                break;
            }
        }
        if(i < j){
            swap(a, i, j);
        }
    }
    swap(a, left, j);
    return j;
}

//Função interna utilizada pelo Quick Sort para pegar a mediana do 1o, do meio e último elementos, evitando
//cair no pior caso.
unsigned int pickPivotIndex(array a, unsigned int left, unsigned int right, int comparator(const void*, const void*)){
    unsigned int mid = (left + right)/2;

    if(comparator(a->array[left], a->array[right]) < 0){
        if(comparator(a->array[left], a->array[mid]) < 0){
            if(comparator(a->array[mid], a->array[right]) < 0){
                return mid;
            }
            return right;
        }
        return left;
    } else if(comparator(a->array[right], a->array[mid]) < 0){
        if(comparator(a->array[mid], a->array[left])){
            return mid;
        }
        return left;
    }
    return right;
}

//Função interna com implementação do Quick Sort para a struct Array.
//O índice do pivot é escolhido usando a media do 1o, do meio e últimos elementos, para evitar
//cair no pior caso.
void quickSort(array a, unsigned int left, unsigned int right, int comparator(const void*, const void*),
               unsigned int partition(array, unsigned int, unsigned int, int comparator(const void*, const void*))){
    
    if(left < right){
        unsigned int pivotIndex = pickPivotIndex(a, left, right, comparator);
        swap(a, left, pivotIndex);
        
        pivotIndex = partition(a, left, right, comparator);
        if(pivotIndex > 0){
            quickSort(a, left, pivotIndex-1, comparator, partition);
        } else{
            quickSort(a, left, 0, comparator, partition);
        }
        quickSort(a, pivotIndex+1, right, comparator, partition);
    }

}

/*
  Função usada para ordenar um array a de acordo com um comparador comparator
  Implementação: Quick Sort
*/
void array_sort(array a, int comparator(const void*, const void*)){
    //Como qtdInseridos é unsigned int, se for 0, teria -1 como parâmetro, que é um valor muito alto
    if(a->qtdInseridos > 0){
        quickSort(a, 0, a->qtdInseridos-1, comparator, PARTITION);
    } else{
        quickSort(a, 0, 0, comparator, PARTITION);
    }
    
}

//Função para obter o tamanho (quantidade de elementos inseridos) de um array a
unsigned int array_getSize(array a){
    return a->qtdInseridos;
}

//Função para obter um elemento em determinada posição pos de um array a
void* array_getElem(array a, unsigned int pos){
    return a->array[pos];
}

//Função interna que calcula a quantidade de distâncias dado uma quantidade de pontos
unsigned int calcQtdDistancias(unsigned int qtdPontos){
    if(qtdPontos > 2){
        //Quantidade de distâncias = num de "lados/vertices" + num de "diagonais"
        return qtdPontos + (qtdPontos * (qtdPontos - 3))/2;
    } else if(qtdPontos < 2){
        return 0;
    }
    return 1;
}

/*
  Função que recebe um array de pontos pts, calcula as distâncias entre os pontos usando calcDistancia,
  inicializa as distâncias usando distInit, as coloca em um novo array (alocação de memória) e o retorna
*/
array array_calcDist(array pts, float calcDistancia(void*, void*, int), void* distInit(float, void*, void*)){
    array dists = array_init(calcQtdDistancias(pts->qtdInseridos));
    unsigned int qtdEixos = pts->qtdEixos;
    for(int i = 0; i < pts->qtdInseridos; i++){
        void* p1 = pts->array[i];
        for(int j = i+1; j < pts->qtdInseridos; j++){
            void* p2 = pts->array[j];
            void* d = distInit(calcDistancia(p1, p2, qtdEixos), p1, p2);

            array_insere(dists, d);
        }
    }
    return dists;
}

/*
  Função que recebe um array a, cria um novo array (alocação de memória) de tamanho qtdElem baseado em a,
  seleciona os elementos de a usando identifier e passando elemParaComparar como parâmetro de identifier,
  os coloca no novo array e o retorna
*/
array array_getTipoElem(array a, void* identifier(void*, void*, array), void* elemParaComparar, unsigned int qtdElem){
    array toReturn = array_init(qtdElem);
    unsigned int k = 0;
    toReturn->qtdEixos = a->qtdEixos;

    for(unsigned int i = 0; i < a->qtdInseridos; i++){
        if(identifier(a->array[i], elemParaComparar, a)){
            toReturn->array[k] = a->array[i];
            toReturn->qtdInseridos++;
            k++;
        }
    }
    return toReturn;
}

/*
  Função que copia os elementos de um grupo (array fonte) para o array dest (ja inicializado).
  sizes é um vetor contendo o tamanho de cada grupo, sendo que sizes[0] = 0 e
  index é o índice (1o grupo, 2o grupo, etc) (1o grupo = 0, 2o grupo = 1, etc) do grupo
*/
void array_copyFromGrupo(array dest, array fonte, unsigned int* sizes, unsigned int index){
    unsigned int j = 0;
    dest->qtdEixos = fonte->qtdEixos;

    for(unsigned int i = 0; i <= index; i++){
        j += sizes[i];
    }

    for(unsigned int i = 0; i < fonte->qtdInseridos; i++){
        dest->array[j+i] = fonte->array[i];
        dest->qtdInseridos++;
    }
}

/*
  Função que cria um array (alocação de memória) de tamanho qtd,
  "pula" os elementos do array a de acordo com os valores de sizes (pegando o 1o elemento),
  insere os 1os elementos no array e o retorna
*/
array array_getInterv(array a, unsigned int* sizes, unsigned int qtd){
    unsigned int index = 0;
    array toReturn = array_init(qtd);
    toReturn->qtdEixos = a->qtdEixos;

    for(unsigned int i = 0; i < qtd; i++){
        index += sizes[i];
        toReturn->array[i] = a->array[index];
        toReturn->qtdInseridos++;
    }
    return toReturn;
}

/*Função que pega um array a, previamente ordenado, de forma que tenha um grupo após o outro
  sequencialmente (ordem dos grupos aleatória) e que cada grupo já esteja ordenado internamente,
  utiliza o array grupos como uma "máscara" de ordenação (o array grupo contém os 1os elementos
  de cada grupo), e ordena o array a de acordo com o array grupo.
  O vetor sizes é o tamanho de cada grupo no posicionamento do array a e o vetor sizesOrdenados
  é o tamanho de cada grupo no posicionamento do array grupos
*/
void array_sortGrupos(array a, array grupos, unsigned int* sizes, unsigned int* sizesOrdenados){
    array aux = array_init(a->qtdInseridos);
    unsigned int index = 0, index2 = 0;
    for(unsigned int i = 0, j = 0; (i <= grupos->qtdInseridos) && (j < grupos->qtdInseridos); i++){
        index += sizes[i];
        if(a->array[index] == grupos->array[j]){
            index2 += sizesOrdenados[j];
            for(unsigned int k = 0; k < sizesOrdenados[j+1]; k++){
                aux->array[index2 + k] = a->array[index + k];
            }
            j++;
            i = -1;
            index = 0;
        }
    }

    array_copyFromArray(a, aux);
    array_free(aux, NULL);
}

//Função que copia totos os elementos do array fonte para o array dest
void array_copyFromArray(array dest, array fonte){
    dest->qtdEixos = fonte->qtdEixos;
    for(unsigned int i = 0; i < dest->qtdInseridos; i++){
        dest->array[i] = fonte->array[i];
    }
}

//Função que retorna a quantidade de eixos de um array
unsigned int array_getQtdEixos(array a){
    return a->qtdEixos;
}