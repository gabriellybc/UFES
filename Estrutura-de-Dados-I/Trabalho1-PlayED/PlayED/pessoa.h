//
// pessoa.h
//
// Criado por Gabrielly Cariman e Lucas Manfioletti em 02/08/21.
//
// Checagem de pré-condição deve ser feita pelo cliente.
//

#ifndef PESSOA_H_
#define PESSOA_H_
#include <stdbool.h>

//Tipo pessoa (tipo opaco)
//Estrutura interna do tipo será definida na implementação do TAD
typedef struct pessoa Pessoa;

#include "listaPessoa.h"
#include "listaPlaylist.h"

/*Inicializa a estrutura pessoa com nome e amizades alocados
 * inputs: string alocada dinamicamente com o nome da pessoa
 * output: ponteiro para a pessoa e inicializada com nome e amizades definidos
 * pre-condicao: string existe está alocada e válida
 * pos-condicao: estrutura pessoa de retorno inicializada e campo amizades existem, memória alocada e tem nome definido
 */
Pessoa *inicializaPessoa(char *nome);

/*Insere uma pessoa na lista de amigos da outra, de forma recíproca
 * inputs: as duas pessoas amigas
 * output: nenhum
 * pre-condicao: pessoas existem
 * pos-condicao: elemento amizades modificado
 */
void adAmigo(Pessoa *pessoa1, Pessoa *pessoa2);

/*Modifica os campo numeroPlaylists e listaPlaylist de Pessoa
 * inputs: a pessoa e a string lida contendo o nome da pessoa, o número de playlists e o nome de cada playlist
 * output: nenhum
 * pre-condicao: pessoa existe e já tem nome definido, a string está no formato "numeroPlaylists;nomePlaylist1;nomePlaylist2"
 * pos-condicao: elementos numeroPlaylists e listaPlaylist da pessoa modificados
 */
void definePlaylists(Pessoa *pessoa, char *leitura);

/*Retorna o nome da pessoa
 * inputs: ponteiro para a pessoa
 * output: o nome da pessoa
 * pre-condicao: pessoa existe está alocada e válida
 * pos-condicao: pessoa não é modificada
 */
char *retornaNomePessoa(Pessoa *pessoa);

/*Retorna o campo listaPlaylist da pessoa
 * inputs: ponteiro para a pessoa
 * output: o campo listaPlaylist da pessoa
 * pre-condicao: pessoa existe está alocada e válida
 * pos-condicao: pessoa não é modificada
 */
ListaPlaylist *retornaListaPlaylistPessoa(Pessoa *pessoa);

/*Retorna o campo amizades da pessoa
 * inputs: ponteiro para a pessoa
 * output: o campo amizades da pessoa
 * pre-condicao: pessoa existe está alocada e válida
 * pos-condicao: pessoa não é modificada
 */
ListaPessoa *retornaListaAmizades(Pessoa *pessoa);

/*Imprime a pessoa
 * inputs: ponteiro para a pessoa
 * output: nenhum
 * pre-condicao: estrutura pessoa existe está alocada e válida
 * pos-condicao: estrutura pessoa não é modificada
 */
void imprimePessoa(Pessoa *pessoa);

/*Imprime a lista de playlists da pessoa no arquivo txt
 * inputs: ponteiro para a pessoa
 * output: nenhum
 * pre-condicao: pessoa existe está alocada e válida
 * pos-condicao: pessoa não é modificada. Uma pasta é criada com o nome da pessoa e arquivos txt com a lista de playlists da pessoa são criados dentro da pasta
 */
void imprimePlaylistPessoaNoArquivo(Pessoa *pessoa);

/*Modifica o campo listaMusica de todas as playlist da listaPlaylist da pessoa
 * inputs: ponteiro para a pessoa e para a lista com todas a músicas
 * output: nenhum
 * pre-condicao: estruturas lista de playlist e  playlist da listaPlaylist da pessoa já existem estão alocadas e válidas e as playlists já tem nome definido. Estrutura de ListaMusica todasMusicas existe está alocada e válida
 * pos-condicao: campo listaMusica de todas as playlist da listaPlaylist da pessoa e lista todasMusicas modificados
 */
void carregaPlaylists(Pessoa *pessoa, ListaMusica *todasMusicas);

/*Inicializa uma outra estrutura de listaPlaylists que separa as músicas por cantor da pessoa
 * inputs: ponteiro a pessoa
 * output: nenhum
 * pre-condicao: listaPlaylist da pessoa existe está alocada e válida e preenchida com playlists com nomes de estilos musicais 
 * pos-condicao: estrutura listaPlaylists modificada com uma lista nova que existe e possui as mesmas músicas da lista antiga. Porém, as músicas são separadas por cantor, em que cada playlist tem o nome de um cantor e o seu campo listaMusica é preenchido apenas pelas músicas do cantor com o mesmo nome da playlist. ListaPlaylist antiga é liberada, menos as suas músicas. 
 */
void reInicListaPlaylistPessoa(Pessoa *pessoa);

/*Imprime o nome da pessoa e sua quantida de playlists separados por ';' no arquivo played-refatorada.txt
 * inputs: ponteiro para a pessoa
 * output: nenhum
 * pre-condicao: pessoa existe está alocada e válida e contém os seus campos já preenchidos 
 * pos-condicao: pessoa não é modificada. O nome da pessoa e sua quantidade de playlists é adicionado ao arquivo played-refatorada.txt separados por ';'
 */
void refatoraPessoa(Pessoa *pessoa);

/*Libera memória alocada para a pessoa
 * inputs: ponteiro para a estrutura pessoa e booleano tudo
 * output: nenhum
 * pre-condicao: pessoa existe está alocada e válida e booleano tudo existe e é válido
 * pos-condicao: Se o booleano tudo for 1, toda a memória alocada para a pessoa e todos os seus campos são liberados, mas o campo amizades libera apenas as Celulas da lista. Caso ele seja 0, a memória alocada para as músicas não vai ser liberada, fora o que já foi descrito anteriormente.
 */
void deletaPessoa(Pessoa *pessoa, bool tudo);

#endif