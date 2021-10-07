//
// codificacao.h
// TAD para a Tabela de Codificao
//
// Criado por Gabrielly Cariman e Lucas Manfioletti em 13/09/21.
//
// Checagem de pré-condição deve ser feita pelo cliente.
//

#ifndef CODIFICACAO_H_
#define CODIFICACAO_H_

#include "bitmap.h"

//Tipo Codificacao (tipo opaco)
//Estrutura interna do tipo sera definida na implementação do TAD
typedef struct cod Codificacao;

/*Inicializa a estrutura codificacao
 * inputs: nenhum
 * output: ponteiro para a codificacao inicializada
 * pre-condicao: nenhuma
 * pos-condicao: estrutura codificacao de retorno inicializada existe, memória alocada
 */
Codificacao *inicCodificacao(char caracter, bitmap *bm);

/*Retorna o caracter (caracter) da codificacao
 * inputs: ponteiro para a codificacao
 * output: o caracter (caracter) da codificacao
 * pre-condicao: codificacao existe está alocada e válida
 * pos-condicao: codificacao não é modificada
 */
char retornaCaracterCodificacao(Codificacao *codificacao);

/*Retorna o bitmap da codificacao
 * inputs: ponteiro para a codificacao
 * output: ponteiro para o bitmap da codificacao
 * pre-condicao: codificacao existe está alocada e válida
 * pos-condicao: codificacao não é modificada
 */
bitmap *retornaBitmapCodificacao(Codificacao *codificacao);

/*Imprime a codificacao
 * inputs: ponteiro para a codificacao
 * output: nenhum
 * pre-condicao: estrutura codificacao existe está alocada e válida
 * pos-condicao: estrutura codificacao não é modificada
 */
void imprimeCodificacao(Codificacao *codificacao);

/*Libera memória alocada para a codificacao
 * inputs: ponteiro para a codificacao
 * output: nenhum
 * pre-condicao: codificacao existe está alocada e válida
 * pos-condicao: toda a memória alocada para a codificacao é liberada
 */
void liberaCodificacao(Codificacao *codificacao);

#endif /*CODIFICACAO_H_*/