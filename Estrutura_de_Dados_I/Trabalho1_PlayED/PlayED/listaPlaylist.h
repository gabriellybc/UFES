//
// listaPlaylist.h
// Lista de Playlists Simplesmente Encadeada com Sentinela
//
// Criado por Gabrielly Cariman e Lucas Manfioletti em 02/08/21.
//
// Checagem de pré-condição deve ser feita pelo cliente.
//

#ifndef LISTAPLAYLIST_H_
#define LISTAPLAYLIST_H_
#include <stdbool.h>
#include "playlist.h"

//Tipo Lista de playlist (tipo opaco)
//Estrutura interna do tipo será definida na implementação do TAD
typedef struct listaPlaylist ListaPlaylist;

/*Inicializa uma estrutura de lista de playlists
 * inputs: nenhum
 * output: ponteiro para a lista de playlists
 * pre-condicao: nenhuma
 * pos-condicao: estrutura de lista de playlists de retorno inicializada existe, memória alocada
 */
ListaPlaylist *inicListaPlaylist();

/*Insere Playlist no final da lista
 * inputs: ponteiro para a lista de Playlists e para a Playlist a ser inserida
 * output: nenhum
 * pre-condicao: a Playlist e lista de Playlists existem, estão alocados e válidos
 * pos-condicao: a Playlist adicionada no fim da lista
 */
void inserePlaylist(ListaPlaylist *lista, Playlist *playlist);

/*Imprime a lista de Playlists
 * inputs: ponteiro para a lista de Playlist
 * output: nenhum
 * pre-condicao: lista existe está alocada e válida
 * pos-condicao: lista não é modificada
 */
void imprimeListaPlaylist(ListaPlaylist *lista);

/*Imprime a lista de playlist no arquivo txt
 * inputs: ponteiro para a lista de playlist e ponteiro de char para o nome da pessoa
 * output: nenhum
 * pre-condicao: lista de Playlist e nomePessoa existem estão alocados e válidos
 * pos-condicao: lista de playlist não é modificada
 */
void imprimeListaPlaylistNoArquivo(ListaPlaylist *lista, char *nomePessoa);

/*Retira a Playlist de determinado nome da lista de Playlists
 * inputs: ponteiro para a lista de Playlists e para o nome da Playlist
 * output: NULL, se a lista está vazia ou não encontrou a playlist. Ou, a playlist com o nome passado é retirada da lista
 * pre-condicao: lista e chave existem estão alocadas e válidas
 * pos-condicao: a lista não é alterada ou a Playlist com determinado nome é retirada da lista
 */
Playlist *retiraPlaylist(ListaPlaylist *lista, char *chave);

/*Retorna a Playlist de determinado nome da lista de Playlists
 * inputs: ponteiro para a lista de Playlists e para o nome da Playlist
 * output: NULL, se a lista está vazia ou não encontrou a playlist. Ou, a playlist com o nome passado 
 * pre-condicao: lista e chave existem estão alocadas e válidas
 * pos-condicao: lista não é modificada
 */
Playlist *retornaPlaylist(ListaPlaylist *lista, char *nome);

/*Modifica o campo listaMusica de todas as playlist da lista
 * inputs: ponteiro para a lista de playlist e para a lista com todas a músicas
 * output: nenhum
 * pre-condicao: estruturas lista de playlist e  playlist da lista já existem estão alocadas e válidas e as playlists já tem nome definido. Estrutura de ListaMusica todasMusicas existe está alocada e válida
 * pos-condicao: campo listaMusica de todas as playlist da lista e lista todasMusicas modificados
 */
void defineTodasListaMusica(ListaPlaylist *lista, ListaMusica *todasMusicas);

/*Inicializa uma outra estrutura de lista de playlists que separa as músicas por cantor
 * inputs: ponteiro para a listaAntiga de playlists antiga e para a quantidade de playlists
 * output: ponteiro para a lista de playlists nova gerada
 * pre-condicao: listaAntiga existe está alocada e válida e preenchida com playlists com nomes de estilos musicais 
 * pos-condicao: estrutura de lista de playlists de retorno inicializada existe, memória alocada e possui as mesmas músicas da lista1. Porém, as músicas são separadas por cantor, em que cada playlist tem o nome de um cantor e o seu campo listaMusica é preenchido apenas pelas músicas do cantor com o mesmo nome da playlist
 */
ListaPlaylist *reInicListaPlaylist(ListaPlaylist *listaAntiga, int *qtdPlaylists);

/*Imprime o nome de cada playlist da lista de playlist entre ';' no arquivo played-refatorada.txt
 * inputs: ponteiro para a lista de playlist
 * output: nenhum
 * pre-condicao: lista de playlist existe está alocada e válida
 * pos-condicao: lista de playlist não é modificada. O nome das playlists da lista de playlist é adicionado ao arquivo played-refatorada.txt separados por ';'
 */
void refatoraNomePlaylist(ListaPlaylist *lista);

/*varre uma lista de playlists e compara suas músicas
 * inputs: duas listas de playlists
 * output: numero de musicas que elas tem em comum
 * pre-condicao: lista de playlist existe está alocada
 * pos-condicao: lista de playlist não é modificada.
 */
int comparaPlaylist(ListaPlaylist *playlistP1, ListaPlaylist *playlistP2);

/*Faz o marge de duas Listas de Playlists
 * inputs: duas listas de playlists
 * output: nenhum
 * pre-condicao: as listas de playlists existem estão alocadas e válida
 * pos-condicao: as Musicas que estavam na primeira lista, mas não na segunda foram adicionadas ao final da segunda lista e vice-versa em todas as playlists das listas. 
 */
void mergePlaylists(ListaPlaylist *listaPlaylist1, ListaPlaylist *listaPlaylist2);

/*Libera memória alocada para a lista
 * inputs: ponteiro para a estrutura ListaPlaylist lista e booleano tudo
 * output: nenhum
 * pre-condicao: lista existe está alocada e válida e booleano tudo existe e é válido
 * pos-condicao: Se o booleano tudo for 1, toda a memória alocada para a lista para os seus campos são liberados. Caso ele seja 0, apenas a memória alocada para as músicas da listaMusica de cada playlist não vai ser liberada
 */
void liberaListaPlaylist(ListaPlaylist *lista, bool tudo);

#endif