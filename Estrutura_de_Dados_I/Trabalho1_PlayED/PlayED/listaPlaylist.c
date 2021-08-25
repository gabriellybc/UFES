#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaPlaylist.h"

//Definindo tipo célula
typedef struct cel Celula;

struct cel
{
  Playlist *playlist;
  Celula *prox;
};

//Definindo tipo opaco
struct listaPlaylist
{
  Celula *Prim;
  Celula *Ult;
};

//Inicializa uma lista de Playlists
ListaPlaylist *inicListaPlaylist()
{
  ListaPlaylist *lista = (ListaPlaylist *)malloc(sizeof(ListaPlaylist));
  if (!lista)
  {
    printf("** Erro: Memoria Insuficiente**");
    return NULL;
  }
  lista->Prim = NULL;
  lista->Ult = NULL;
  return lista;
}

//Insere Playlist no final da lista
void inserePlaylist(ListaPlaylist *lista, Playlist *playlist)
{
  Celula *nova = (Celula *)malloc(sizeof(Celula));
  if (!nova)
  {
    printf("** Erro: Memoria Insuficiente**");
    exit;
  }
  nova->playlist = playlist; // nova->playlist recebe a playlist que eu quero inserir na lista de playlists
  nova->prox = NULL;         //Encadeando a nova celula na lista fazendo ela receber o NULL no prox, pois será a ultima celula
  if (lista->Prim == NULL)   //Caso a lista estivesse vazia
    lista->Prim = nova;      //A nova vai ser a primeira e ultima celula da lista
  else
    lista->Ult->prox = nova; //Encadeando a antiga ultima celula com a nova
  lista->Ult = nova;         //Mudando a ultima celula da lista, o final da lista aponta para a nova e assim coloca ela no ultimo lugar da lista
}

//Imprime a lista de Playlists
void imprimeListaPlaylist(ListaPlaylist *lista)
{
  Celula *p; //ponteiro auxiliar que aponta para um celula que já existe e já foi alocada anteriormente
  p = lista->Prim;
  while (p != NULL) //Enquanto não chegar ao final da lista
  {
    imprimePlaylist(p->playlist); //p anda em cada celula da lista
    printf("\n");
    p = p->prox;
  }
}

// Imprime a lista de playlist no arquivo txt
void imprimeListaPlaylistNoArquivo(ListaPlaylist *lista, char *nomePessoa)
{
  Celula *p; //ponteiro auxiliar que aponta para um celula que já existe e já foi alocada anteriormente
  p = lista->Prim;
  while (p != NULL) //Enquanto não chegar ao final da lista
  {
    imprimePlaylistNoArquivo(p->playlist, nomePessoa); //p anda em cada celula da lista
    p = p->prox;
  }
}

//Retira a Playlist de determinado nome da lista de Playlists
Playlist *retiraPlaylist(ListaPlaylist *lista, char *chave)
{
  Celula *p = lista->Prim; //ponteiro auxiliar p apontando para a primeira celula da lista
  Playlist *playlist;      //Variavel auxiliar de playlist para retornar ela.
  Celula *ant = NULL;      //Ponteiro auxiliar sempre na posição anterior ao p
  //Faz a busca da playlist que se quer retirar
  while (p != NULL && strcmp(retornaNomePlaylist(p->playlist), chave))
  {
    ant = p;
    p = p->prox;
  }
  //Lista vazia ou não encontrou a playlist
  if (p == NULL)
  {
    return NULL;
  }
  playlist = p->playlist; //Atribui a playlist de retorno
  //Se for a única celula da lista
  if (p == lista->Prim && p == lista->Ult)
    lista->Prim = lista->Ult = NULL; //Lista fica vazia
  //Se for a primeira celula da lista
  else if (p == lista->Prim)
    lista->Prim = p->prox;
  //Se for a ultima Celula
  else if (p == lista->Ult)
  {
    lista->Ult = ant;
    ant->prox = NULL; //ou lista->Ult->prox = NULL;
  }
  else //caso comum
    ant->prox = p->prox;
  free(p);         //Liberando apenas a célula da lista
  return playlist; //Retornando a playlist
}

// Retorna a Playlist de determinado nome da lista de Playlists
Playlist *retornaPlaylist(ListaPlaylist *lista, char *nome)
{
  Celula *p = lista->Prim; //ponteiro auxiliar p apontando para a primeira celula da lista
  Playlist *playlist;      //Variavel auxiliar de pessoa para retornar ela.
  Celula *ant = NULL;      //Ponteiro auxiliar sempre na posição anterior ao p
  //Faz a busca da playlist que se quer retirar
  while (p != NULL && strcmp(retornaNomePlaylist(p->playlist), nome))
  {
    ant = p;
    p = p->prox;
  }
  //Lista vazia ou não encontrou a playlist
  if (p == NULL)
    return NULL;
  playlist = p->playlist; //Atribui a playlist de retorno
  return playlist;        //Retornando a playlist
}

// Modifica o campo listaMusica de todas as playlist da lista
void defineTodasListaMusica(ListaPlaylist *lista, ListaMusica *todasMusicas)
{
  Celula *p; //ponteiro auxiliar que aponta para um celula que já existe e já foi alocada anteriormente
  p = lista->Prim;
  while (p != NULL) //Enquanto não chegar ao final da lista
  {
    defineListaMusica(p->playlist, todasMusicas); //p anda em cada celula da lista
    p = p->prox;
  }
}

// Inicializa uma outra estrutura de lista de playlists que separa as músicas por cantor
ListaPlaylist *reInicListaPlaylist(ListaPlaylist *lista1, int *qtdPlaylists)
{
  ListaPlaylist *lista2 = inicListaPlaylist();
  Celula *p1; //ponteiro auxiliar
  p1 = lista1->Prim;
  ListaMusica *listaMusica1, *listaMusica2;
  char *cantor;
  Playlist *playlist1, *playlist2;
  Musica *musica;
  //Enquanto não chegar ao final da lista
  while (p1 != NULL)
  {
    //Retorna a ListaMusica da playlist
    listaMusica1 = retornaListaMusica(p1->playlist);
    //Retorna o nome do primeiro cantor que está na ListaMusica
    cantor = retornaPrimeiroCantor(listaMusica1);
    //Enquanto não chegar ao último cantor da listaMusica1
    while (cantor != NULL)
    {
      // Retorna a playlist que tenha como nome o mesmo que o do cantor, se ela não for encontrada, retorna NULL.
      if (retornaPlaylist(lista2, cantor) == NULL) //Caso não tenha uma playlist com o nome desse cantor ainda na lista 2
      {
        // Cria playlist com o campo nome igual ao do cantor
        playlist2 = criaPlaylistPorCantor(cantor);
        // Retorna a primeira música encontrada da lista 1 com o campo cantor informado
        musica = retornaMusicaCantor(listaMusica1, cantor);
        //Enquanto tiver musica com esse cantor na listaMusica1
        while (musica != NULL)
        {
          // Retorna a ListaMusica da playlist
          listaMusica2 = retornaListaMusica(playlist2);
          // Insere ela na playlist
          insereMusica(listaMusica2, musica);
          // Retira da lista1 a música que já foi adicionada na lista 2
          musica = retiraMusica(listaMusica1, retornaNomeMusica(musica));
          //Continua a busca por músicas daquele mesmo cantor na lista
          musica = retornaMusicaCantor(listaMusica1, cantor);
        }
        // Adiciona a playlista de determinado cantor na lista
        inserePlaylist(lista2, playlist2);
        // Adiciona a quantidade de playlists
        (*qtdPlaylists)++;
      }
      //Se já tiver uma playlist com o nome desse cantor na lista 2
      else
      {
        // Retorna a playlist que tenha como nome o mesmo que o do cantor
        playlist2 = retornaPlaylist(lista2, cantor);
        // Retorna a musica que tenha o nome do cantor do parametro, se ela não for encontrada, retorna NULL.
        musica = retornaMusicaCantor(listaMusica1, cantor);
        //Enquanto tiver musica com esse cantor na listaMusica1
        while (musica != NULL)
        {
          // Retorna a ListaMusica da playlist
          listaMusica2 = retornaListaMusica(playlist2);
          // Caso ainda não tenha a música com o nome informado
          if (retornaMusicaNomeLista(listaMusica2, retornaNomeMusica(musica)) == NULL)
            // Insere ela
            insereMusica(listaMusica2, musica);
          // Retira da lista1 a música que já foi adicionada na lista 2
          musica = retiraMusica(listaMusica1, retornaNomeMusica(musica));
          //Continua a busca por músicas daquele mesmo cantor na lista
          musica = retornaMusicaCantor(listaMusica1, cantor);
        }
      }
      //Vai para o próximo cantor da listaMusica1
      cantor = retornaPrimeiroCantor(listaMusica1);
    }
    // Vai para a próxima célula da lista de playlists1
    p1 = p1->prox;
  }
  return lista2;
}

// Imprime o nome de cada playlist da lista de playlist entre ';' no arquivo played-refatorada.txt
void refatoraNomePlaylist(ListaPlaylist *lista)
{
  Celula *p; //ponteiro auxiliar que aponta para um celula que já existe e já foi alocada anteriormente
  p = lista->Prim;
  while (1)
  {
    FILE *arqRefatorada;
    int result;
    arqRefatorada = fopen("played-refatorada.txt", "a");
    if (arqRefatorada == NULL)
    {
      printf("** ERRO: O arquivo nao foi aberto **");
      exit;
    }
    if (p->prox == NULL) //Se for a última playlist, imprime no arquivo com quebra de linha
    {
      result = fprintf(arqRefatorada, "%s\n", retornaNomePlaylist(p->playlist));
      if (result == EOF)
        printf("Erro na Gravacao\n");
      fclose(arqRefatorada);
      break;
    }
    result = fprintf(arqRefatorada, "%s;", retornaNomePlaylist(p->playlist));
    if (result == EOF)
    {
      printf("Erro na Gravacao\n");
      exit;
    }
    fclose(arqRefatorada);
    p = p->prox;
  }
}

//varre uma lista de playlists e compara suas músicas
int comparaPlaylist(ListaPlaylist *playlistP1, ListaPlaylist *playlistP2)
{
  int numSimilar = 0;
  Celula *p1, *p2;
  for (p1 = playlistP1->Prim; p1 != NULL; p1 = p1->prox)
  { //varre todas as playlists da pessoa 1
    for (p2 = playlistP2->Prim; p2 != NULL; p2 = p2->prox)
    {                                                                                                   //varre todas as playlists da pessoa 2
      numSimilar += comparaMusicas(retornaListaMusica(p1->playlist), retornaListaMusica(p2->playlist)); //compara as musicas de 2 plalists e retorna a quantidade de musicas iguais
    }
  }
  return numSimilar;
}

// Faz o marge de duas Listas de Playlists
void mergePlaylists(ListaPlaylist *playlists1, ListaPlaylist *playlists2)
{
  Playlist *play2;
  char *nomePlaylist;
  Celula *p = playlists1->Prim; //ponteiro auxiliar
  while (p != NULL)             //Enquanto não chegar ao final da lista
  {
    nomePlaylist = retornaNomePlaylist(p->playlist);
    play2 = retornaPlaylist(playlists2, nomePlaylist);
    if (play2 != NULL)
    {
      mergeListaMusica(retornaListaMusica(p->playlist), retornaListaMusica(play2));
    }
    p = p->prox;
  }
}

//Libera memória alocada para a lista
void liberaListaPlaylist(ListaPlaylist *lista, bool tudo)
{
  Celula *p = lista->Prim; //ponteiro auxiliar recebendo a primeira celula da lista
  Celula *t;               // outro ponteiro auxiliar

  while (p != NULL) //Enquanto não chegar ao final da lista
  {
    t = p->prox; //O ponteiro temporário aponta para a proxima célula
    deletaPlaylist(p->playlist, tudo);
    free(p);
    p = t;
  }
  //Liberando a sentinela playlist
  free(lista);
}
