//
// arvore.h
// Arvore Binaria
//
// Criado por Gabrielly Cariman e Lucas Manfioletti em 02/09/21.
//
// Checagem de pré-condição deve ser feita pelo cliente.
//

#ifndef ARVORE_H_
#define ARVORE_H_

#include <stdbool.h>
#include "bitmap.h"

//Tipo Arv (tipo opaco)
//Estrutura interna do tipo sera definida na implementação do TAD
typedef struct arv Arv;

/*Inicializa uma estrutura arvore vazia
 * inputs: nenhum
 * output: ponteiro para a arvore inicializada
 * pre-condicao: nenhuma
 * pos-condicao: estrutura arvore de retorno inicializada existe, memória alocada
 */
Arv *arvCriaVazia();

/*Inicializa a estrutura arvore com todos os campos definidos 
 * inputs: nenhum
 * output: ponteiro para a arvore inicializada
 * pre-condicao: nenhuma
 * pos-condicao: estrutura arvore de retorno inicializada existe, memória alocada. Arvore tem os campos info, peso, temCaracter, arv esq e dir definidos
 */
Arv *arvCria(char c, int qnt, bool tem, Arv *e, Arv *d);

/*Indica se uma árvore e' ou nao vazia
 * inputs: ponteiro para a arvore
 * output: booleano, true se a arvore estiver vazia, false caso contrario
 * pre-condicao: arvore existe está alocada e válida
 * pos-condicao: arvore não é modificada
 */
bool arvVazia(Arv *a);

/*Retorna o campo peso da arvore
 * inputs: ponteiro para a arvore
 * output: o valor do peso da arvore
 * pre-condicao: arvore existe está alocada e válida
 * pos-condicao: arvore não é modificada
 */
int retornaPeso(Arv *a);

/*Retorna o campo info da arvore
 * inputs: ponteiro para a arvore
 * output: o char do campo info da arvore
 * pre-condicao: arvore existe está alocada e válida
 * pos-condicao: arvore não é modificada
 */
char retornaInfo(Arv *a);

/*Retorna o campo temCaracter da arvore
 * inputs: ponteiro para a arvore
 * output: o booleano do campo temCaracter da arvore
 * pre-condicao: arvore existe está alocada e válida
 * pos-condicao: arvore não é modificada
 */
bool retornaTemCaracter(Arv *a);

/*Retorna  o campo arv esq da arvore
 * inputs: ponteiro para a arvore
 * output: ponteiro para a arv esq da arvore
 * pre-condicao: arvore existe está alocada e válida
 * pos-condicao: arvore não é modificada
 */
Arv *retornaArvEsq(Arv *a);

/*Retorna  o campo arv dir da arvore
 * inputs: ponteiro para a arvore
 * output: ponteiro para a arv dir da arvore
 * pre-condicao: arvore existe está alocada e válida
 * pos-condicao: arvore não é modificada
 */
Arv *retornaArvDir(Arv *a);

/*Imprime a arvore
 * inputs: ponteiro para a arvore
 * output: nenhum
 * pre-condicao: estrutura arvore existe está alocada e válida
 * pos-condicao: estrutura arvore não é modificada
 */
void arvImprime(Arv *a);

/*A arvore e' percorrida recursivamente e o devido bit e' armazenado ao final do bitmap
 * inputs: ponteiro para a arvore e para o bitmap
 * output: nenhum
 * pre-condicao: estrutura arvore e bitmap existe estao alocados e validos
 * pos-condicao: estrutura arvore não é modificada. A arvore e' percorrida recursivamente, todos os nos sao visitados e o devido bit e' armazenado ao final do bitmap. Nos nao folhas armazenam o bit 0 e nos folhas armazenam o bit 1 seguido por 8 bits que representam o valor do caracter do campo info.
 */
void arvBinario(Arv *a, bitmap *bm);

/*Retorna a altura da arvore
 * inputs: ponteiro para a arvore
 * output: inteiro com o valor da altura da arvore
 * pre-condicao: arvore existe está alocada e válida
 * pos-condicao: arvore não é modificada e o valor da altura da arvore e' calculado
 */
int arvAltura(Arv *a);

/*Retorna o numero total de nos de uma arvore binaria cheia
 * inputs: ponteiro para a arvore
 * output: inteiro com o valor maximo de nos da arvore
 * pre-condicao: arvore existe está alocada e válida
 * pos-condicao: arvore não é modificada e o valor maximo de nos da arvore e' calculado
 */
int arvNos(Arv *a);

/*Retorna a quantidade de folhas de uma árvore binaria
 * inputs: ponteiro para a arvore
 * output: inteiro com a quantidade de folhas da arvore
 * pre-condicao: arvore existe está alocada e válida
 * pos-condicao: arvore não é modificada e a quantidade de folhas da arvore e' calculado
 */
int arvFolhas(Arv *a);

/*Armazena a arvore do arquivo binario em uma estrutua Arvore
 * inputs: ponteiros para a arvore (a), o bitmap com o bytes lidos (bm), a quantidade de folhas atuais (folhasAtuais), a flag que fala se a arvore ja terminou (flagFolhasMax), o index que diz a posicao do bitmap que esta sendo lida (i), para a posicao no arquivo (arq), a quantidade de leituras feitas (leituras) e a posicao em bytes do final da arvore no arquivo (posicao). Alem disso, tem o inteiro totalFolhas que armazena a quantidade de folhas lida do arquivo
 * output: ponteiro para a estrutura de arvore lida do arquivo binario
 * pre-condicao: todos os inputs existem estão alocados e validos, menos a arvore (a) que sera alocada diretamente dentro da funcao
 * pos-condicao: a arvore lida do arquivo binario e'armazenada em uma estrutura arvore que e' retornada 
 */
Arv *redefineArvore(Arv *a, bitmap *bm, int totalFolhas, int *folhasAtuais, bool *flagFolhasMax, int *i, FILE *arq, int *leituras, long *posicao);

/*Retorna o caracter passado por um bitmap
 * inputs: ponteiros para a arvore, o bitmap com o bytes lidos, e ponteiro de indice de leitura do bitmap
 * output: caracter de uma parcela do bitmap
 * pre-condicao: todos os inputs existem estão alocados e validos
 * pos-condicao: a função navega pela arvore de acordo com os valores do bitmap até encontar um nó folha, e retorna o caracter associado
 */
char retornaCaracter(bitmap *bm, Arv *a, int *indice);

/*Libera memória alocada para a arvore
 * inputs: ponteiro para a arvore
 * output: nenhum
 * pre-condicao: arvore existe está alocada e valida
 * pos-condicao: toda a memoria alocada para a arvore é liberada
 */
Arv *arvLibera(Arv *a);

#endif /*ARVORE_H_*/