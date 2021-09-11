//
// listaPessoa.h
// Lista de Pessoas Simplesmente Encadeada com Sentinela
//
// Criado por Gabrielly Cariman e Lucas Manfioletti em 02/08/21.
//
// Checagem de pré-condição deve ser feita pelo cliente.
//

#ifndef LISTAPESSOA_H_
#define LISTAPESSOA_H_
#include <stdbool.h>
#include "listaMusica.h"

//Tipo Lista de pessoas (tipo opaco)
//Estrutura interna do tipo será definida na implementação do TAD
typedef struct listaPessoa ListaPessoa;

#include "pessoa.h"

/*Inicializa uma estrutura de lista de pessoas
 * inputs: nenhum
 * output: ponteiro para a lista de pessoas
 * pre-condicao: nenhuma
 * pos-condicao: estrutura de lista de pessoas de retorno inicializada existe, memória alocada
 */
ListaPessoa *inicListaPessoa();

/*Insere pessoa no final da lista
 * inputs: ponteiro para a lista de pessoas e a pessoa a ser inserida
 * output: nenhum
 * pre-condicao: a pessoa e lista de pessoas existem, estão alocados e válidos
 * pos-condicao: a pessoa adicionada no fim da lista
 */
void inserePessoa(ListaPessoa *lista, Pessoa *people);

/*Le as pessoas do arquivo e cria pessoas na lista de pessoas
 * inputs: o ponteiro para a estrutura lista de pessoas
 * output: nenhum
 * pre-condicao: as pessoas da lista existem e já tem nome definido
 * pos-condicao: pessoas são criadas e adicionadas em listaPessoa
 */
void lePessoas(ListaPessoa *lista);

/*Imprime a lista de Pessoas
 * inputs:  ponteiro para a lista de Pessoa
 * output: nenhum
 * pre-condicao: lista existe está alocada e válida
 * pos-condicao: lista não é modificada
 */
void imprimeListaPessoa(ListaPessoa *lista);

/*Imprime a lista de playlist de todas as pessoas da listaPessoa no arquivo txt
 * inputs: ponteiro para a lista de pessoas
 * output: nenhum
 * pre-condicao: lista de pessoa tem pessoas com lista de Playlists alocados e válidos
 * pos-condicao: lista de pessoa não é modificada
 */
void imprimeTodasPlaylistsNoArquivo(ListaPessoa *lista);

/*Retira a Pessoa de determinado nome da lista de Pessoas
 * inputs: lista de Pessoas e o nome da Pessoa
 * output: NULL, se a lista está vazia ou não encontrou a pessoa. Ou, a Pessoa retirada da lista
 * pre-condicao: lista e chave existem
 * pos-condicao: a lista não é alterada ou a Pessoa com determinado nome é retirada da lista
 */
Pessoa *retiraPessoa(ListaPessoa *lista, char *chave);

/*Retorna a Pessoa de determinado nome da lista de Pessoas
 * inputs: lista de Pessoas e o nome da Pessoa
 * output: NULL, se a lista está vazia ou não encontrou a pessoa. Ou, a Pessoa com o nome passado
 * pre-condicao: lista e chave existem estão alocadas e válidas
 * pos-condicao: lista não é modificada
 */
Pessoa *retornaPessoa(ListaPessoa *lista, char *nome);

/*Modifica os campo numeroPlaylists e listaPlaylist de cada Pessoa
 * inputs: o ponteiro para a estrutura lista de pessoas
 * output: nenhum
 * pre-condicao: as pessoas da lista existem e já tem nome definido
 * pos-condicao: campos numeroPlaylists e listaPlaylist de cada pessoa da lista é modificados
 */
void lePlaylists(ListaPessoa *lista);

/*Modifica o campo listaMusica de todas as playlist da listaPlaylist de todas as pessoas da lista de pessoas
 * inputs: ponteiro para a lista de pessoa e para a lista com todas a músicas
 * output: nenhum
 * pre-condicao: estruturas lista de playlist e  playlist da listaPlaylist de todas as pessoa da lista já existem estão alocadas e válidas e as playlists já tem nome definido. Estrutura de ListaMusica todasMusicas existe está alocada e válida
 * pos-condicao: campo listaMusica de todas as playlist da listaPlaylist de todas as pessoa da lista e lista todasMusicas modificados
 */
void defineTodosPlaylists(ListaPessoa *lista, ListaMusica *todasMusicas);

/*Inicializa uma outra estrutura de listaPlaylists que separa as músicas por cantor de cada pessoa
 * inputs: ponteiro a lista de pessoa
 * output: nenhum
 * pre-condicao: listaPlaylist de cada pessoa existe está alocada e válida e preenchida com playlists com nomes de estilos musicais 
 * pos-condicao: estrutura listaPlaylists de cada pessoa modificada com uma lista nova que existe e possui as mesmas músicas da lista antiga. Porém, as músicas são separadas por cantor, em que cada playlist tem o nome de um cantor e o seu campo listaMusica é preenchido apenas pelas músicas do cantor com o mesmo nome da playlist. ListaPlaylist antiga de cada pessoa é liberada, menos as suas músicas. 
 */
void reInicListaPlaylistTodos(ListaPessoa *lista);

/*le as amizades de uma lista e grava a quantidade de musicas iguais
 * inputs: lista de Pessoas
 * output: nenhum
 * pre-condicao: arquivo de amizades existe
 * pos-condicao: Arquivos de similaridades existe
 */
void Similaridades(ListaPessoa *lista);

/*Imprime todas as pessoas da lista no arquivo played-refatorada.txt
 * inputs: ponteiro para a lista de pessoa
 * output: nenhum
 * pre-condicao: lista de pessoas e as pessoa existem estão alocados e válidos e as pessoas contém os seus campos já preenchidos 
 * pos-condicao: lista de pessoas e as pessoas não é modificada. Se já existir, o arquivo played-refatorada.txt primeiro é excluiso e depois é criado
 */
void refatoraTodos(ListaPessoa *lista);

/*le as amizades e cria lista de amigos em cada pessoa
 * inputs: ponteiro para a lista de pessoa
 * output: nenhum
 * pre-condicao: lista de pessoas e as pessoa existem estão alocados e válidos e as pessoas contém os seus campos já preenchidos 
 * pos-condicao: lista de pessoas e as pessoas não é modificada. Se já existir, o arquivo played-refatorada.txt primeiro é excluiso e depois é criado
 */
void defineAmizades(ListaPessoa *lista);

/*Faz o marge das Listas de Playlists de todos os amigos
 * inputs: a lista de pessoas com todas as pessoas
 * output: nenhum
 * pre-condicao: as listas de pessoas existe está alocadas e válida
 * pos-condicao: os amigos que tiverem playlists com o mesmo nome, passarão a ter as mesmas músicas nessas playlists.
 */
void mergeListaPessoa(ListaPessoa *lista);

/*Libera memória alocada para a lista
 * inputs: ponteiro para a estrutura listaPessoa e booleano tudo
 * output: nenhum
 * pre-condicao: lista existe está alocada e válida e booleano tudo existe e é válido
 * pos-condicao: Se o booleano tudo for 1, toda a memória alocada para a lista e para os todos os componentes que estão na lista são liberados. Caso ele seja 0, apenas a memória alocada para as a lista vai ser liberada.
 */
void liberaListaPessoa(ListaPessoa *lista, bool tudo);

#endif