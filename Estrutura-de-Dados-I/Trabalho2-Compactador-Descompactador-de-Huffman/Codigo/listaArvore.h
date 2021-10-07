//
// listaArvore.h
// Lista de Arvores Duplamente Encadeada com Sentinela
//
// Criado por Gabrielly Cariman e Lucas Manfioletti em 02/09/21.
//
// Checagem de pré-condição deve ser feita pelo cliente.
//

#ifndef LISTAARVORE_H_
#define LISTAARVORE_H_

#include <stdbool.h>
#include "arquivos.h"

//Tipo Lista de arvores(tipo opaco)
//Estrutura interna do tipo será definida na implementação do TAD
typedef struct listaArvore ListaArvore;

/*Inicializa uma estrutura de lista de arvores
 * inputs: nenhum
 * output: ponteiro para a lista de arvores inicializada
 * pre-condicao: nenhuma
 * pos-condicao: estrutura de lista de arvore de retorno inicializada existe, memória alocada
 */
ListaArvore *inicListaArvore();

/*Insere uma arvore na lista de forma ordenada crescente de acordo com o peso da arvore
 * inputs: ponteiros para a lista de arvores e para a arvore a ser inserida
 * output: nenhum
 * pre-condicao: a arvore e a lista existem, estão alocados e válidos e booleano inicio existe e é válido
 * pos-condicao: a arvore é adicionada na posição em que ela fique ordenada de forma crescente na lista. Se o booleano inicio for 1, a verificação da ordenação da lista será feita do final para o inicio. Se ele for 0, uma verificação será feita para definir a posicao de inicio.
 */
void insereArvoreOrdenada(ListaArvore *lista, Arv *arv, bool final);

/*Define a lista de arvores passada, de forma crescente, com arvores criadas com caracteres do vetor de inteiros diferentes de zero
 * inputs: ponteiros para a lista de arvores e para o vetor de inteiros, repeticoes
 * output: quantidade de caracteres diferentes
 * pre-condicao: o ponteiro de inteiros repeticoes e a lista existem, estão alocados e válidos
 * pos-condicao: para os elementos do vetor de inteiros que tiverem o conteúdo diferente de zero, será criada uma arvore que tem como info o caracter com o índice do vetor de inteiro que representada o código ASCII do caracter e como peso o mesmo valor que o conteúdo deste índice. Essa arvore criada será adicionda de forma ordenada, seguindo a ordem crescente dos pesos das arvores, na lista de arvores passada.
 */
int defineListaArvore(ListaArvore *lista, int *repeticoes);

/*Retira a arvore de determinado posição da lista de arvores
 * inputs: ponteiros para a lista de arvores e inteiro com a posição da arvore na lista
 * output: NULL, se a lista está vazia ou não encontrou a arvore. Ou, a arvore com a posição passada é retirada da lista
 * pre-condicao: lista existe está alocada e válida e posicao existe e é válida
 * pos-condicao: a lista não é alterada ou a arvore de terminada posição é retirada da lista
 */
Arv *retiraArvore(ListaArvore *lista, int posicao);

/*Retetorna a arvore de determinado posição da lista de arvores
 * inputs: ponteiros para a lista de arvores e inteiro com a posição da arvore na lista
 * output: NULL, se a lista está vazia ou não encontrou a arvore. Ou, a arvore com a posição passada é retornada da lista
 * pre-condicao: lista existe está alocada e válida e posicao existe e é válida
 * pos-condicao: a lista não é alterada
 */
Arv *retornaArvore(ListaArvore *lista, int posicao);

/*Cria uma única arvore com a lista de arvores
 * inputs: ponteiros para a lista de arvores
 * output: NULL, se a lista está vazia ou não encontrou a arvore. Ou, a arvore montada com as demais lista passada
 * pre-condicao: lista existe está alocada
 * pos-condicao: a lista não é alterada e uma arvore é criada
 */
Arv *codificaArvore(ListaArvore *lista);

/*Imprime a lista de arvores
 * inputs: ponteiro para a lista de arvore
 * output: nenhum
 * pre-condicao: lista existe está alocada e válida
 * pos-condicao: lista não é modificada
 */
void imprimeListaArvore(ListaArvore *lista);

/*Imprime a quantidade de folhas e a primeira arvore da lista no arquivo binario
 * inputs: ponteiro para a lista de arvore e para o nome do arquivo
 * output: nenhum
 * pre-condicao: lista e o nome do arquivo existe estão alocados e válidos
 * pos-condicao: lista e o nome do arquivo não são modificados e o arquivo com o nome pasado binario tem a quantidade de folhas e a arvore adicionadas ao seu final 
 */
void imprimeArvoreBinario(ListaArvore *lista, char *nomeArquivo);

/*Libera memória alocada para a lista
 * inputs: ponteiro para a estrutura ListaArvore lista e booleano tudo
 * output: nenhum
 * pre-condicao: lista existe está alocada e válida
 * pos-condicao: libera a memória alocada para a lista e também a de todas as arvores
 */
void liberaListaArvore(ListaArvore *lista);

#endif /*ListaArvore_H_*/