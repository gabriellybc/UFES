#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "pessoa.h"

//Definindo tipo opaco
typedef struct pessoa
{
  char *nome;
  int numeroPlaylists;
  ListaPlaylist *listaPlaylist;
  ListaPessoa *amizades;
} Pessoa;

//Inicializa a estrutura pessoa com nome e amizades alocados
Pessoa *inicializaPessoa(char *nome)
{
  Pessoa *pessoa = (Pessoa *)malloc(sizeof(Pessoa));
  if (!pessoa)
  {
    printf("** Erro: Memoria Insuficiente **\n");
    exit;
  }
  pessoa->nome = nome;
  ListaPessoa *listaAmigos = inicListaPessoa();
  pessoa->amizades = listaAmigos;
  return pessoa;
}

//Insere uma pessoa na lista de amigos da outra, de forma recíproca
void adAmigo(Pessoa *pessoa1, Pessoa *pessoa2)
{
  inserePessoa(pessoa1->amizades, pessoa2);
  inserePessoa(pessoa2->amizades, pessoa1);
}

// Modifica os campo numeroPlaylists e listaPlaylist de Pessoa
void definePlaylists(Pessoa *pessoa, char *leitura)
{
  int quant = 0, j = 2, k;
  leitura = duplica(leitura, strlen(leitura));
  leitura[strlen(leitura) - 1] = ';';
  //leitura[0] - '0'é equivalente a ((int)leitura[0]) - ((int)'0'), o que significa que os valores ascii dos caracteres são subtraídos um do outro. A diferença entre os dois fornece o número que o caractere arepresenta.
  quant = leitura[0] - '0';
  pessoa->numeroPlaylists = quant;
  char nomePlaylist[121];
  Playlist *playlist;
  ListaPlaylist *lista;
  lista = inicListaPlaylist();
  for (int i = 0; i < quant; i++)
  {
    k = 0;
    while (leitura[j] != ';')
    {
      nomePlaylist[k] = leitura[j];
      j++;
      k++;
    }
    j++;
    char *nome = duplica(nomePlaylist, k);
    playlist = inicializaPlaylist();
    defineNomePlaylist(playlist, nome);
    inserePlaylist(lista, playlist);
    free(nome);
  }
  pessoa->listaPlaylist = lista;
  free(leitura);
}

//Retorna o nome da pessoa
char *retornaNomePessoa(Pessoa *pessoa)
{
  return pessoa->nome;
}

//Retorna o campo listaPlaylist da pessoa
ListaPlaylist *retornaListaPlaylistPessoa(Pessoa *pessoa)
{
  return pessoa->listaPlaylist;
}

//Retorna o campo amizades da pessoa
ListaPessoa *retornaListaAmizades(Pessoa *pessoa)
{
  return pessoa->amizades;
}

//Imprime a pessoa
void imprimePessoa(Pessoa *pessoa)
{
  printf("Nome da pessoa: %s | Quantidade de playlists: %d\n", pessoa->nome, pessoa->numeroPlaylists);
  imprimeListaPlaylist(pessoa->listaPlaylist);
}

//Cria pasta no local com o nome passado
static int criarDiretorio(char *nome);

//Imprime a lista de playlists da pessoa no arquivo txt
void imprimePlaylistPessoaNoArquivo(Pessoa *pessoa)
{
  int pasta = criarDiretorio(pessoa->nome);
  imprimeListaPlaylistNoArquivo(pessoa->listaPlaylist, pessoa->nome);
}

//Modifica o campo listaMusica de todas as playlist da listaPlaylist da pessoa
void carregaPlaylists(Pessoa *pessoa, ListaMusica *todasMusicas)
{
  defineTodasListaMusica(pessoa->listaPlaylist, todasMusicas);
}

// Inicializa uma outra estrutura de listaPlaylists que separa as músicas por cantor da pessoa
void reInicListaPlaylistPessoa(Pessoa *pessoa)
{
  int qtdPlaylists = 0;
  ListaPlaylist *listaNova;
  listaNova = reInicListaPlaylist(pessoa->listaPlaylist, &qtdPlaylists);
  liberaListaPlaylist(pessoa->listaPlaylist, 0);
  pessoa->listaPlaylist = listaNova;
  pessoa->numeroPlaylists = qtdPlaylists;
}

// Imprime o nome da pessoa e sua quantida de playlists separados por ';' no arquivo
void refatoraPessoa(Pessoa *pessoa)
{
  FILE *arqRefatorada;
  int result;
  arqRefatorada = fopen("played-refatorada.txt", "a");
  if (arqRefatorada == NULL)
  {
    printf("** ERRO: O arquivo não foi aberto **");
    exit;
  }
  result = fprintf(arqRefatorada, "%s;%d;", pessoa->nome, pessoa->numeroPlaylists);
  fclose(arqRefatorada);
  if (result == EOF)
  {
    printf("Erro na Gravacao\n");
    exit;
  }
  else
    refatoraNomePlaylist(pessoa->listaPlaylist);
}

//Libera memória alocada para a pessoa
void deletaPessoa(Pessoa *pessoa, bool tudo)
{
  free(pessoa->nome);
  liberaListaPlaylist(pessoa->listaPlaylist, tudo);
  liberaListaPessoa(pessoa->amizades, 0);
  free(pessoa);
}

// Includes para a criação da pasta que verifica o SO
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif
//Cria pasta no local com o nome passado
static int criarDiretorio(char *nome)
{
#ifdef _WIN32
  return CreateDirectory(nome, NULL);
#else
  return mkdir(nome, 0777);
#endif
}