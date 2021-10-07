//
// listaCodificacao.h
// Lista de Codificacoes Duplamente Encadeada com Sentinela
//
// Criado por Gabrielly Cariman e Lucas Manfioletti em 02/09/21.
//
// Checagem de pré-condição deve ser feita pelo cliente.
//

#ifndef LISTACODIFICACAO_H_
#define LISTACODIFICACAO_H_

#include "codificacao.h"
#include "listaArvore.h"

//Tipo Lista de Codificacao (tipo opaco)
//Estrutura interna do tipo será definida na implementação do TAD
typedef struct listaCodificacao ListaCodificacao;

/*Inicializa uma estrutura de lista de músicas
 * inputs: nenhum
 * output: ponteiro para a lista de Codificacoes inicializada
 * pre-condicao: nenhuma
 * pos-condicao: estrutura de lista de música de retorno inicializada existe, memória alocada
 */
ListaCodificacao *inicListaCodificacao();

/*Insere uma Codificacao na lista de forma ordenada crescente de acordo com tamanho do bitmap
 * inputs: ponteiros para a lista de codificacoes e para a Codificacao a ser inserida
 * output: nenhum
 * pre-condicao: a Codificacao e a lista existem, estão alocados e válidos
 * pos-condicao: a Codificacao é adicionada na posição em que ela fique ordenada de forma crescente na lista
 */
void insereCodificacaoOrdenada(ListaCodificacao *lista, Codificacao *cod);

/*Imprime a lista de Codificacoes
 * inputs: ponteiro para a lista de Codificacao
 * output: nenhum
 * pre-condicao: lista existe está alocada e válida
 * pos-condicao: lista não é modificada
 */
void imprimeListaCodificacao(ListaCodificacao *lista);

/*Retorna a Codificacao com determinado caracter (info) da lista de Codificacoes
 * inputs: ponteiro para a lista de Codificacoes e o caracter da Codificacao
 * output: NULL, se a lista está vazia ou não encontrou a Codificacao. Ou, a Codificacao com o caracter passado
 * pre-condicao: lista e chave existem estão alocadas e válidas
 * pos-condicao: lista não é modificada
 */
Codificacao *retornaCodificacao(ListaCodificacao *lista, char caracter);

/*Define toda a tabela de Codificacoes do arquivo
 * inputs: ponteiros para a lista de codificacoes e para a lista de arvores
 * output: nenhum
 * pre-condicao: as listas existem, estão alocados e válidos
 * pos-condicao: a lista de codificoes contem toda a tabela de codificacoes do arquivo de forma ordenadas
 */
void tabelaCodificacao(ListaCodificacao *listaCod, ListaArvore *listaArv);

/*grava a codificacao no arquivo binario
 * inputs: ponteiro para lista e para o nome dos arquivos
 * output: nenhum
 * pre-condicao: lista e os nomes dos arquivos existem
 * pos-condicao: lista e os nomes dos arquivos não são modificados e o arquivo com o nome passado ".comp" tem a codificação gravada ao seu final
 */
void imprimeCodificacaoBinario(ListaCodificacao *lista, char *nomeArquivo, char *nomeArquivoComp);

/*Libera memória alocada para a lista
 * inputs: ponteiro para a estrutura ListaCodificacao lista e booleano tudo
 * output: nenhum
 * pre-condicao: lista existe está alocada e válida e booleano tudo existe e é válido
 * pos-condicao: Se o booleano tudo for 0, libera apenas a memória alocada para a lista. Se ele for 1, além de liberar a memória da lista, libera também a de todas as músicas
 */
void liberaListaCodificacao(ListaCodificacao *lista);

#endif /*LISTACODIFICACAO_H_*/