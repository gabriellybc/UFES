//
// musica.h
//
// Criado por Gabrielly Cariman e Lucas Manfioletti em 02/08/21.
//
// Checagem de pré-condição deve ser feita pelo cliente.
//

#ifndef MUSICA_H_
#define MUSICA_H_
#include <stdbool.h>

//Tipo musica (tipo opaco)
//Estrutura interna do tipo sera definida na implementação do TAD
typedef struct musica Musica;

/*Inicializa a estrutura musica
 * inputs: nenhum
 * output: ponteiro para a musica inicializada
 * pre-condicao: nenhuma
 * pos-condicao: estrutura musica de retorno inicializada existe, memória alocada
 */
Musica *inicializaMusica();

/*Copia um string para outra alocada dinamicamente
 * inputs: string leitura e inteiro tamanho.
 * output: ponteiro para a nova string alocada dinamicamente.
 * pre-condicao: string leitura existe e int tamanho diferente de 0.
 * pos-condicao: cópia da string alocada dinamicamente.
 */
char *duplica(char *leitura, int tamanho);

/*Modifica os campos nomeMusica e cantor de Musica
 * inputs: a musica e a string lida contendo o nome e o cantor
 * output: nenhum
 * pre-condicao: musica existe, a string está no formato "nomeMusica - Cantor"
 * pos-condicao: elementos nomeMusica e cantor da musica modificados
 */
void defineMusica(Musica *musica, char *leitura);

/*Retorna o nome da musica
 * inputs: ponteiro para a musica
 * output: o nome da musica
 * pre-condicao: musica existe está alocada e válida
 * pos-condicao: musica não é modificada
 */
char *retornaNomeMusica(Musica *musica);

/*Retorna o nome do cantor ou banda da musica
 * inputs: ponteiro para a musica
 * output: o nome do cantor ou banda da musica
 * pre-condicao: musica existe está alocada e válida
 * pos-condicao: musica não é modificada
 */
char *retornaCantor(Musica *musica);

/*Imprime a musica
 * inputs: ponteiro para a musica
 * output: nenhum
 * pre-condicao: estrutura musica existe está alocada e válida
 * pos-condicao: estrutura musica não é modificada
 */
void imprimeMusica(Musica *musica);

/*Retorna uma string da musica no formato para o arquivo
 * inputs: ponteiro para a musica
 * output: string com o formato "nomeMusica - Cantor"
 * pre-condicao: musica existe está alocada e válida
 * pos-condicao: musica não é modificada
 */
char *musicaParaArquivo(Musica *musica);

/*Libera memória alocada para a musica
 * inputs: ponteiro para a musica
 * output: nenhum
 * pre-condicao: musica existe está alocada e válida
 * pos-condicao: toda a memória alocada para a musica é liberada
 */
void deletaMusica(Musica *musica);

#endif /*MUSICA_H_*/
