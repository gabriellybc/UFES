//
// arquivos.h
// TAD para a manibulação dos arquivos.
//
// Criado por Gabrielly Cariman e Lucas Manfioletti em 02/09/21.
//
// Checagem de pré-condição deve ser feita pelo cliente.
//

#ifndef ARQUIVOS_H_
#define ARQUIVOS_H_

#include "arvore.h"

/*Cria um vetor de inteiros com 256 elementos em que o índice é o código ASCII do caracter e o conteúdo é o número de vezes que ele aparece no arquivo passado
 * inputs: ponteiro para a string com o nome do arquivo que será campactado
 * output: ponteiro de vetor de inteiros que tem 256 elementos
 * pre-condicao: o ponteiro de char nomeArquivo existe está alocados e contém um nome de arquivo válido
 * pos-condicao: vetor de inteiros gerado com 256 elementos em que o índice do vetor é o código ASCII do caracter e o conteúdo é o número de vezes com que o caracter aparece no arquivo com o nome passado.
 */
int *repeticaoCaracteres(char *nomeArquivo);

/*Adiciona ao final do arquivo bonario os bytes do bitmap passado
 * inputs: ponteiro com estrutura bitmap e ponteiro para a string com o nome do arquivo
 * output: nenhum
 * pre-condicao: os ponteiros de bitmap e de char nomeArquivo existem estão alocados e são válidos
 * pos-condicao: o arquivo com o nome passado tem os bytes do bitmap adicionados no seu final
 */
void escreveBinario(bitmap *bm, char *nomeArquivo);

/*Modifica a string que define o formato do arquivo
 * inputs: string do nome do arquivo, e opcao de modificação(1 para compactação, e 2 para descompactação)
 * output: string com nome do arquivo no novo formato
 * pre-condicao: o nome do arquivo existe e opcao está definida
 * pos-condicao: a string passada é modificada para o .comp ou formato original, altrando sua parte final
 */
char *alteraFormato(char *nomeArquivo, int opcao);

/*Le quantidade de folhas e armazena a arvore do arquivo binario em uma estrutua Arvore
 * inputs: ponteiro para o nome do arquivo, para a posicao em bytes do fim da arvore no arquivo e quantidade de caracteres
 * output: ponteiro para a estrutura de arvore lida do arquivo binario
 * pre-condicao: lista, o nome do arquivo e qntCaracteresArquivo existe estão alocados e válidos
 * pos-condicao: a quantidade de folhas e' lida e a arvore lida do arquivo binario e'armazenada em uma estrutura arvore que e' retornada 
 */
Arv *leituraArvore(char *nomeArquivo, long *posicaoFimArv, long qntCaracteresArquivo);

/*Le quantidade de caracteres e armazena o valor no arquivo binario
 * inputs: ponteiro para o nome do arquivo antigo, para o arquivo novo e a quantidade de caracteres do arquivo
 * output: nenhum
 * pre-condicao: lista, o nome dos arquivos e qutCaracteres existem e sao validos
 * pos-condicao: a quantidade de caracteres do arquivo é obtida e gravada no arquivo binario
 */
void imprimeNumCaracteresBinario(char *nomeArquivo, char *nomeArquivoNovo, long qntCaracteres);

/*Calcula a quantidade de caracteres no arquivo
 * inputs: ponteiro para o nome do arquivo
 * output: valor da quantidade de caracteres
 * pre-condicao: nome dos arquivo existe
 * pos-condicao: a quantidade de caracteres do arquivo é obtida e retornada
 */
long calculaQuantidadeDeCaracteres(char *nomeArquivo);

/*Le a quantidade de caracteres do arquivo binário e restaura o arquivo original
 * inputs: ponteiro para o nome do arquivo antigo e arquivo novo, para a arvore usada no arquivo original, posição final de leitura do arquivo binário quantidade de caracteres
 * output: nenhum
 * pre-condicao: posição, arvore e o nome dos arquivos existem 
 * pos-condicao: o arquivo antigo é restaurado
 */
void imprimeArquivoOrignal(char *nomeArquivo, char *nomeArquivoNovo, Arv *arv, long posicaoFimArv, long qntCaracteresArquivo);

#endif /*ARQUIVOS_H_*/