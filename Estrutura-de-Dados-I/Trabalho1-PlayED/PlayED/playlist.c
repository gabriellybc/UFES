#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

//Tipo playlist (tipo opaco)
struct playlist
{
  char *nomePlaylist;
  ListaMusica *listaMusica;
};

//Inicializa uma playlist
Playlist *inicializaPlaylist()
{
  Playlist *playlist = (Playlist *)malloc(sizeof(Playlist));
  if (!playlist)
  {
    printf("** Erro: Memoria Insuficiente **\n");
    exit;
  }
  return playlist;
}

//Modifica o campo nomePlaylist de Playlist
void defineNomePlaylist(Playlist *playlist, char *leitura)
{
  int i = 0;
  char nomePlaylist[121];
  while (leitura[i] != '.')
  {
    nomePlaylist[i] = leitura[i];
    i++;
  }
  playlist->nomePlaylist = duplica(nomePlaylist, i);
}

// Modifica o campo listaMusica de playlist
void defineListaMusica(Playlist *playlist, ListaMusica *todasMusicas)
{
  ListaMusica *lista = inicListaMusica();
  char *nomeArquivo = (char *)malloc((strlen(playlist->nomePlaylist) + 5) * sizeof(char));
  // Realiza a cópia do conteúdo de uma variável a outra
  strcpy(nomeArquivo, playlist->nomePlaylist);
  // Realiza a concatenação do conteúdo de uma variável a outra
  strcat(nomeArquivo, ".txt");
  FILE *arqPlaylist;
  arqPlaylist = fopen(nomeArquivo, "r");
  if (arqPlaylist == NULL)
  {
    printf("** ERRO: O arquivo não foi aberto **");
    exit;
  }
  char linha[1000];
  Musica *musica;
  while (1)
  {
    //A função feof retona um valor inteiro diferente de zero se o indicador de fim de arquivo está marcado para linha
    if (feof(arqPlaylist))
      break;
    fgets(linha, 1000, arqPlaylist); // o 'fgets' lê até 9999 caracteres ou até o '\n'
    musica = inicializaMusica();
    defineMusica(musica, linha);
    insereMusica(lista, musica);
    insereMusica(todasMusicas, musica); //Inserindo a música na lista com todas
  }
  fclose(arqPlaylist);
  playlist->listaMusica = lista;
  free(nomeArquivo);
}

// Inicializa a estrutura Playlist com nome
Playlist *criaPlaylistPorCantor(char *cantor)
{
  Playlist *playlist = inicializaPlaylist();
  playlist->nomePlaylist = strdup(cantor);
  ListaMusica *lista = inicListaMusica();
  playlist->listaMusica = lista;
  return playlist;
}

//Retorna o nome da Playlist
char *retornaNomePlaylist(Playlist *playlist)
{
  return playlist->nomePlaylist;
}

//Retorna a lista de musicas da Playlist
ListaMusica *retornaListaMusica(Playlist *playlist)
{
  return playlist->listaMusica;
}

//Imprime a Playlist
void imprimePlaylist(Playlist *playlist)
{
  printf("Playlist: %s\n", playlist->nomePlaylist);
  imprimeListaMusica(playlist->listaMusica);
}

// Imprime a playlist no arquivo txt
void imprimePlaylistNoArquivo(Playlist *playlist, char *nomePessoa)
{
  char *nomeArquivo = (char *)malloc((strlen(nomePessoa) + (strlen(playlist->nomePlaylist)) + 8) * sizeof(char));
  // Realiza a cópia do conteúdo de uma variável a outra
  strcpy(nomeArquivo, "./");
  // Realiza a concatenação do conteúdo de uma variável a outra
  strcat(nomeArquivo, nomePessoa);
  // Realiza a concatenação do conteúdo de uma variável a outra
  strcat(nomeArquivo, "/");
  // Realiza a concatenação do conteúdo de uma variável a outra
  strcat(nomeArquivo, playlist->nomePlaylist);
  // Realiza a concatenação do conteúdo de uma variável a outra
  strcat(nomeArquivo, ".txt");
  FILE *arqPlaylist;
  arqPlaylist = fopen(nomeArquivo, "w");
  if (arqPlaylist == NULL)
  {
    printf("** ERRO: O arquivo não foi aberto **");
    exit;
  }
  fclose(arqPlaylist);
  imprimeMusicasNoArquivo(playlist->listaMusica, nomeArquivo);
}

//Libera memória alocada para a Playlist
void deletaPlaylist(Playlist *playlist, bool tudo)
{
  free(playlist->nomePlaylist);
  liberaListaMusica(playlist->listaMusica, tudo);
  free(playlist);
}