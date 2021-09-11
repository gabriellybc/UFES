//
// playlist.h
//
// Criado por Gabrielly Cariman e Lucas Manfioletti em 02/08/21.
//
// Checagem de pré-condição deve ser feita pelo cliente.
//

#ifndef PLAYLIST_H_
#define PLAYLIST_H_
#include <stdbool.h>
#include "listaMusica.h"

//Tipo playlist (tipo opaco)
//Estrutura interna do tipo sera definida na implementação do TAD
typedef struct playlist Playlist;

/*Inicializa a estrutura Playlist
 * inputs: nenhum
 * output: ponteiro para a playlist inicializada
 * pre-condicao: nenhuma
 * pos-condicao: estrutura de playlist de retorno inicializada existe, memória alocada
 */
Playlist *inicializaPlaylist();

/*Modifica o campos nomePlaylist de playlist
 * inputs: a playlist e a string contendo o nome da playlist
 * output: nenhum
 * pre-condicao: playlist existe, a string está no formato "nomePlaylist.txt"
 * pos-condicao: elemento nomePlaylist da playlist modificado
 */
void defineNomePlaylist(Playlist *playlist, char *leitura);

/*Modifica o campo listaMusica de playlist
 * inputs: ponteiro para a playlist e para a lista com todas a músicas
 * output: nenhum
 * pre-condicao: estrutura playlist já existe está alocada e válida e tem já tem nome definido, existe uma arquivo de nome "nomePlaylist.txt" no mesmo diretório. Estrutura de ListaMusica todasMusicas existe está alocada e válida
 * pos-condicao: campo listaMusica de playlist e lista todasMusicas modificados
 */
void defineListaMusica(Playlist *playlist, ListaMusica *todasMusicas);

/*Inicializa a estrutura Playlist com nome
 * inputs: ponteiro de char com o nome do cantor
 * output: ponteiro para a playlist inicializada com o campo nomePlaylist preenchido com string cantor
 * pre-condicao: string cantor existe está alocado e válido
 * pos-condicao: estrutura de playlist de retorno inicializada existe, memória alocada com campo nomePlaylist preenchido com string cantor
 */
Playlist *criaPlaylistPorCantor(char *cantor);

/*Retorna o nome da playlist
 * inputs: ponteiro para a playlist
 * output: o nome da playlist
 * pre-condicao: a estrutura playlist e seu campo nomePlaylist existem estão alocados e válidos
 * pos-condicao: a estrutura playlist não é modificada
 */
char *retornaNomePlaylist(Playlist *playlist);

/*Retorna a listaMusica da playlist
 * inputs: ponteiro para a playlist
 * output: a estrutura a listaMusica da playlist da playlist
 * pre-condicao: a estrutura playlist e seu campo listaMusica existem estão alocados e válidos
 * pos-condicao: a estrutura playlist não é modificada
 */
ListaMusica *retornaListaMusica(Playlist *playlist);

/*Imprime a Playlist
 * inputs: ponteiro para a playlist
 * output: nenhum
 * pre-condicao: estrutura playlist existe está alocada e válida
 * pos-condicao: estrutura playlist não é modificada
 */
void imprimePlaylist(Playlist *playlist);

/*Imprime a playlist no arquivo txt
 * inputs: ponteiro para a playlist e ponteiro de char para o nome da pessoa
 * output: nenhum
 * pre-condicao: já existe uma pasta com o nomePessoa no mesmo diretório. Playlist e nomePessoa existem estão alocados e válidos
 * pos-condicao: playlist não é modificada. Um arquivo de nome "nomePlaylist.txt" com a lista de músicas é criado no diretório de nome "nomePessoa"
 */
void imprimePlaylistNoArquivo(Playlist *playlist, char *nomePessoa);

/*Libera memória alocada para a Playlist
 * inputs: ponteiro para a estrutura playlist e booleano tudo
 * output: nenhum
 * pre-condicao: playlist existe está alocada e válida e booleano tudo existe e é válido
 * pos-condicao: Se o booleano tudo for 1, toda a memória alocada para a playlist e todos os seus campos são liberados. Caso ele seja 0, apenas a memória alocada para as músicas da listaMusica de playlist não vai ser liberada
 */
void deletaPlaylist(Playlist *playlist, bool tudo);

#endif /*PLAYLIST_H_*/
