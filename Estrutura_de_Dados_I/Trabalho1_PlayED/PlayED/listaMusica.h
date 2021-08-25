//
// listaMusica.h
// Lista de Músicas Simplesmente Encadeada com Sentinela
//
// Criado por Gabrielly Cariman e Lucas Manfioletti em 02/08/21.
//
// Checagem de pré-condição deve ser feita pelo cliente.
//

#ifndef LISTAMUSICA_H_
#define LISTAMUSICA_H_
#include <stdbool.h>
#include "musica.h"

//Tipo Lista de musica (tipo opaco)
//Estrutura interna do tipo será definida na implementação do TAD
typedef struct listaMusica ListaMusica;

/*Inicializa uma estrutura de lista de músicas
 * inputs: nenhum
 * output: ponteiro para a lista de musicas inicializada
 * pre-condicao: nenhuma
 * pos-condicao: estrutura de lista de música de retorno inicializada existe, memória alocada
 */
ListaMusica *inicListaMusica();

/*Insere musica no final da lista
 * inputs: ponteiros para a lista de musicas e para a musica a ser inserida
 * output: nenhum
 * pre-condicao: a musica e lista existem, estão alocados e válidos
 * pos-condicao: a Musica music adicionada no fim da lista
 */
void insereMusica(ListaMusica *lista, Musica *music);

/*Imprime a lista de musicas
 * inputs: ponteiro para a lista de musica
 * output: nenhum
 * pre-condicao: lista existe está alocada e válida
 * pos-condicao: lista não é modificada
 */
void imprimeListaMusica(ListaMusica *lista);

/*Imprime a lista de musicas no arquivo txt
 * inputs: ponteiro para a lista de musica e ponteiro de char para o nome do arquivo
 * output: nenhum
 * pre-condicao: lista e nomeArquivo existem estão alocados e válidos. O nomeArquivo está no formato "nomePlaylist.txt"
 * pos-condicao: lista não é modificada e as musicas da lista estão adicionadas no arquivo txt
 */
void imprimeMusicasNoArquivo(ListaMusica *lista, char *nomeArquivo);

/*Retira a musica de determinado nome da lista de musicas
 * inputs: ponteiros para a lista de musicas e para o nome da musica
 * output: NULL, se a lista está vazia ou não encontrou a musica. Ou, a musica com o nome passado é retirada da lista
 * pre-condicao: lista e chave existem estão alocadas e válidas
 * pos-condicao: a lista não é alterada ou a musica com determinado nome é retirada da lista
 */
Musica *retiraMusica(ListaMusica *lista, char *chave);

/*Retorna a musica de determinado cantor da lista de musicas
 * inputs: ponteiros para a lista de musicas e para o nome do cantor da música
 * output: NULL, se a lista está vazia ou não encontrou a musica. Ou, a musica com o nome do cantor passado
 * pre-condicao: lista e chave existem estão alocadas e válidas
 * pos-condicao: lista não é modificada
 */
Musica *retornaMusicaCantor(ListaMusica *lista, char *cantor);

/*Retorna a musica de determinado nome da lista de musicas
 * inputs: ponteiros para a lista de musicas e para o nome da musica
 * output: NULL, se a lista está vazia ou não encontrou a musica. Ou, a musica com o nome passado
 * pre-condicao: lista e chave existem estão alocadas e válidas
 * pos-condicao: lista não é modificada
 */
Musica *retornaMusicaNomeLista(ListaMusica *lista, char *nome);

/*Retorna o nome do cantor da primeira musica da lista de musicas
 * inputs: ponteiro para a lista de musicas
 * output: NULL, se a lista está vazia. Ou, o nome do cantor da primeira musica da lista
 * pre-condicao: lista existe está alocada e válida
 * pos-condicao: lista não é modificada
 */
char *retornaPrimeiroCantor(ListaMusica *lista);

/*varre duas playlists e compara suas músicas
 * inputs: duas lista de músicas
 * output: numero de musicas que elas tem em comum
 * pre-condicao: listas de musicas existem estão alocadas
 * pos-condicao: listas de musicas não são modificadas
 */
int comparaMusicas(ListaMusica *listaP1, ListaMusica *listaP2);

/*Faz o marge de duas Listas de Musicas
 * inputs: duas listas de musicas
 * output: nenhum
 * pre-condicao: as listas de músicas existem estão alocadas e válida
 * pos-condicao: as Musicas que estavam na primeira lista, mas não na segunda foram adicionadas ao final da segunda lista e vice-versa. 
 */
void mergeListaMusica(ListaMusica *listaMusica1, ListaMusica *listaMusica2);

/*Libera memória alocada para a lista
 * inputs: ponteiro para a estrutura ListaMusica lista e booleano tudo
 * output: nenhum
 * pre-condicao: lista existe está alocada e válida e booleano tudo existe e é válido
 * pos-condicao: Se o booleano tudo for 0, libera apenas a memória alocada para a lista. Se ele for 1, além de liberar a memória da lista, libera também a de todas as músicas
 */
void liberaListaMusica(ListaMusica *lista, bool tudo);

#endif /*LISTAMUSICA_H_*/