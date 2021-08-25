#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listaMusica.h"

// Tipo celula
typedef struct cel Celula;

struct cel
{
  Musica *musica;
  Celula *prox;
};

// Tipo Lista de musica (tipo opaco)
// Sentinela
struct listaMusica
{
  Celula *Prim;
  Celula *Ult;
};

// Inicializa uma lista de musicas
ListaMusica *inicListaMusica()
{
  ListaMusica *lista = (ListaMusica *)malloc(sizeof(ListaMusica));
  if (!lista)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }
  lista->Prim = NULL;
  lista->Ult = NULL;
  return lista;
}

//Insere a musica na lista no final da lista
void insereMusica(ListaMusica *lista, Musica *music)
{
  Celula *nova = (Celula *)malloc(sizeof(Celula));
  if (!nova)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }
  nova->musica = music;    //O nova->musica recebe a musica que eu quero inserir na lista
  nova->prox = NULL;       //Encadeando a nova celula na lista fazendo ela receber o NULL no prox, pois será a ultima celula
  if (lista->Prim == NULL) //Caso a lista estivesse vazia
    lista->Prim = nova;    //A nova vai ser a primeira e ultima celula da lista
  else
    lista->Ult->prox = nova; //Encadeando a antiga ultima celula com a nova
  lista->Ult = nova;         //Mudando a ultima celula da lista, o final da lista aponta para a nova e assim coloca ela no ultimo lugar da lista
}

// Imprime a lista de musicas
void imprimeListaMusica(ListaMusica *lista)
{
  Celula *p; //ponteiro auxiliar que aponta para um celula que já existe e já foi alocada anteriormente
  for (p = lista->Prim; p != NULL; p = p->prox)
  {
    imprimeMusica(p->musica); //p anda em cada celula da lista
    printf("\n");
  }
}

// Imprime a lista de musicas no arquivo txt
void imprimeMusicasNoArquivo(ListaMusica *lista, char *nomeArquivo)
{
  FILE *arqPlaylist;
  char *linhaMusica;
  int result;
  arqPlaylist = fopen(nomeArquivo, "a");
  if (arqPlaylist == NULL)
  {
    printf("** ERRO: O arquivo não foi aberto **");
    exit;
  }
  Celula *p; //ponteiro auxiliar que aponta para um celula que já existe e já foi alocada anteriormente
  for (p = lista->Prim; p != NULL; p = p->prox)
  {
    //p anda em cada celula da lista
    linhaMusica = musicaParaArquivo(p->musica);
    // Se for a última Musica
    if (p->prox == NULL)
      // Tira o '\n' da última linha de música
      linhaMusica[strlen(linhaMusica) - 1] = '\0';
    result = fputs(linhaMusica, arqPlaylist);
    if (result == EOF)
    {
      printf("Erro na Gravacao\n");
      exit;
    }
    free(linhaMusica); //Libera a memória alocada em musica.c
  }
  fclose(arqPlaylist);
  free(nomeArquivo);
}

// Retira a musica de determinado nome da lista de musicas
Musica *retiraMusica(ListaMusica *lista, char *chave)
{
  Celula *p = lista->Prim; //ponteiro auxiliar p apontando para a primeira celula da lista
  Musica *music;           //Variavel auxiliar de musica para retornar ela.
  Celula *ant = NULL;      //Ponteiro auxiliar sempre na posição anterior ao p
  //Faz a busca
  while (p != NULL && strcmp(retornaNomeMusica(p->musica), chave))
  {
    ant = p;
    p = p->prox;
  }
  //Lista vazia ou não encontrou a musica
  if (p == NULL)
    return NULL;
  music = p->musica; //Atribui a musica de retorno
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
    ant->prox = NULL; // ou lista->Ult->prox = NULL;
  }
  else //caso comum
    ant->prox = p->prox;
  free(p);      //Liberando apenas a célula da lista
  return music; //Retornando a musica
}

// Retorna a musica de determinado cantor da lista de musicas
Musica *retornaMusicaCantor(ListaMusica *lista, char *cantor)
{
  Celula *p = lista->Prim; //ponteiro auxiliar p apontando para a primeira celula da lista
  Musica *music;           //Variavel auxiliar de musica para retornar ela.
  Celula *ant = NULL;      //Ponteiro auxiliar sempre na posição anterior ao p
  //Faz a busca
  while (p != NULL && strcmp(retornaCantor(p->musica), cantor))
  {
    ant = p;
    p = p->prox;
  }
  //Lista vazia ou não encontrou a musica
  if (p == NULL)
    return NULL;
  music = p->musica; //Atribui a musica de retorno
  return music;
}

// Retorna a musica de determinado nome da lista de musicas
Musica *retornaMusicaNomeLista(ListaMusica *lista, char *nome)
{
  Celula *p = lista->Prim; //ponteiro auxiliar p apontando para a primeira celula da lista
  Musica *music;           //Variavel auxiliar de musica para retornar ela.
  Celula *ant = NULL;      //Ponteiro auxiliar sempre na posição anterior ao p
  //Faz a busca
  while (p != NULL && strcmp(retornaNomeMusica(p->musica), nome))
  {
    ant = p;
    p = p->prox;
  }
  //Lista vazia ou não encontrou a musica
  if (p == NULL)
    return NULL;
  music = p->musica; //Atribui a musica de retorno
  return music;
}

// Retorna o nome do cantor da primeira musica da lista de musicas
char *retornaPrimeiroCantor(ListaMusica *lista)
{
  Celula *p = lista->Prim; //ponteiro auxiliar p apontando para a primeira celula da lista
  char *cantor;            //Variavel auxiliar de cantor para retornar ele.
  if (p == NULL)
    return NULL;
  cantor = retornaCantor(p->musica); //Atribui cantor de retorno
  return cantor;
}

//compara as musicas iguais de duas playlists
int comparaMusicas(ListaMusica *playlistP1, ListaMusica *playlistP2)
{
  int numSimilar=0;
  Celula *musicaP1, *musicaP2;
  for (musicaP1 = playlistP1->Prim; musicaP1 != NULL; musicaP1 = musicaP1->prox)
  { //varre todas as musicas da playlist da pessoa 1
    for (musicaP2 = playlistP2->Prim; musicaP2 != NULL; musicaP2 = musicaP2->prox)
    {  
      //varre todas as musicas da playlist da pessoa 2
      if (strcmp(retornaNomeMusica(musicaP1->musica), retornaNomeMusica(musicaP2->musica)) == 0 && strcmp(retornaCantor(musicaP1->musica), retornaCantor(musicaP2->musica)) == 0){ //verifica se a música é igual
        numSimilar++;
      }
      else
        ;
    }
  }
  return numSimilar;
}

// Faz o marge de duas Listas de Musicas
void mergeListaMusica(ListaMusica *listaMusica1, ListaMusica *listaMusica2)
{
  Musica *musica;
  char *nomeMusica;

  //Adicionando as musicas que ainda não existem na segunda lista
  Celula *p = listaMusica1->Prim; //ponteiro auxiliar
  while (p != NULL)               //Enquanto não chegar ao final da lista
  {
    nomeMusica = retornaNomeMusica(p->musica);
    musica = retornaMusicaNomeLista(listaMusica2, nomeMusica);
    if (musica == NULL)
    {
      musica = p->musica;
      insereMusica(listaMusica2, musica);
    }
    p = p->prox;
  }
  //Adicionando as musicas que ainda não existem na primeira lista
  p = listaMusica2->Prim;
  while (p != NULL) //Enquanto não chegar ao final da lista
  {
    nomeMusica = retornaNomeMusica(p->musica);
    musica = retornaMusicaNomeLista(listaMusica1, nomeMusica);
    if (musica == NULL)
    {
      musica = p->musica;
      insereMusica(listaMusica1, musica);
    }
    p = p->prox;
  }
}

//Libera a memoria da lista
void liberaListaMusica(ListaMusica *lista, bool tudo)
{
  Celula *p = lista->Prim; //ponteiro auxiliar recebendo a primeira celula da lista
  Celula *t;               // outro ponteiro auxiliar

  if (tudo)
  {
    while (p != NULL) //Enquanto não chegar ao final da lista
    {
      t = p->prox; //O ponteiro temporário aponta para a proxima célula
      deletaMusica(p->musica);
      free(p);
      p = t;
    }
  }
  else
  {
    while (p != NULL) //Enquanto não chegar ao final da lista
    {
      t = p->prox; //O ponteiro temporário aponta para a proxima célula
      free(p);
      p = t;
    }
  }
  //Liberando a sentinela
  free(lista);
}