#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaPessoa.h"

//Definindo tipo célula
typedef struct cel Celula;

struct cel
{
  Pessoa *pessoa;
  Celula *prox;
};

//Definindo tipo opaco
struct listaPessoa
{
  Celula *Prim;
  Celula *Ult;
};

//Inicializa uma lista de pessoas
ListaPessoa *inicListaPessoa()
{
  ListaPessoa *lista = (ListaPessoa *)malloc(sizeof(ListaPessoa));
  if (!lista)
  {
    printf("** Erro: Memoria Insuficiente**");
    return NULL;
  }
  lista->Prim = NULL;
  lista->Ult = NULL;
  return lista;
}

//Insere pessoa no final da lista
void inserePessoa(ListaPessoa *lista, Pessoa *people)
{
  Celula *nova = (Celula *)malloc(sizeof(Celula));
  if (!nova)
  {
    printf("** Erro: Memoria Insuficiente**");
    exit;
  }
  nova->pessoa = people;   // nova->pessoa recebe a pessoa que eu quero inserir na lista de pessoas
  nova->prox = NULL;       //Encadeando a nova celula na lista fazendo ela receber o NULL no prox, pois será a ultima celula
  if (lista->Prim == NULL) //Caso a lista estivesse vazia
    lista->Prim = nova;    //A nova vai ser a primeira e ultima celula da lista
  else
    lista->Ult->prox = nova; //Encadeando a antiga ultima celula com a nova
  lista->Ult = nova;         //Mudando a ultima celula da lista, o final da lista aponta para a nova e assim coloca ela no ultimo lugar da lista
}

void lePessoas(ListaPessoa *lista)
{
  Pessoa *pessoa;
  char *nome, nomePessoa[500], linha[2000];
  int i = 0, j = 0;
  FILE *arqAmizade;
  arqAmizade = fopen("amizade.txt", "r");
  if (arqAmizade == NULL)
  {
    printf("** ERRO: O arquivo não foi aberto **");
    exit;
  }
  else
  {
    fgets(linha, 2000, arqAmizade); // o 'fgets' lê até 1999 caracteres ou até o '\n'
    while (1)
    {
      if (linha[i] == ';')
      {
        nome = duplica(nomePessoa, j);
        pessoa = inicializaPessoa(nome);
        inserePessoa(lista, pessoa);
        i = i + 1; //Pulando o ;
        j = 0;
      }
      else if (linha[i] == '\n')
      {
        //Adicionando a última pessoa
        nome = duplica(nomePessoa, j);
        pessoa = inicializaPessoa(nome);
        inserePessoa(lista, pessoa);
        break;
      }
      nomePessoa[j] = linha[i];
      i++;
      j++;
    }
  }

  fclose(arqAmizade);
}

//Imprime a lista de Pessoas
void imprimeListaPessoa(ListaPessoa *lista)
{
  Celula *p; //ponteiro auxiliar que aponta para um celula que já existe e já foi alocada anteriormente
  p = lista->Prim;
  while (p != NULL) //Enquanto não chegar ao final da lista
  {
    imprimePessoa(p->pessoa); //p anda em cada celula da lista
    printf("\n");
    p = p->prox;
  }
}

// Imprime a lista de playlist de todas as pessoas da listaPessoa no arquivo txt
void imprimeTodasPlaylistsNoArquivo(ListaPessoa *lista)
{
  Celula *p; //ponteiro auxiliar que aponta para um celula que já existe e já foi alocada anteriormente
  p = lista->Prim;
  while (p != NULL) //Enquanto não chegar ao final da lista
  {
    imprimePlaylistPessoaNoArquivo(p->pessoa); //p anda em cada celula da lista
    p = p->prox;
  }
}

//Retira a Pessoa de determinado nome da lista de Pessoas
Pessoa *retiraPessoa(ListaPessoa *lista, char *chave)
{
  Celula *p = lista->Prim; //ponteiro auxiliar p apontando para a primeira celula da lista
  Pessoa *people;          //Variavel auxiliar de pessoa para retornar ela.
  Celula *ant = NULL;      //Ponteiro auxiliar sempre na posição anterior ao p
  //Faz a busca da pessoa que se quer retirar
  while (p != NULL && strcmp(retornaNomePessoa(p->pessoa), chave))
  {
    ant = p;
    p = p->prox;
  }
  //Lista vazia ou não encontrou a pessoa
  if (p == NULL)
  {
    return NULL;
  }
  people = p->pessoa; //Atribui a pessoa de retorno
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
  free(p);       //Liberando apenas a célula da lista
  return people; //Retornando a pessoa
}

//Retorna a Pessoa de determinado nome da lista de Pessoas
Pessoa *retornaPessoa(ListaPessoa *lista, char *nome)
{
  Celula *p = lista->Prim; //ponteiro auxiliar p apontando para a primeira celula da lista
  Pessoa *people;          //Variavel auxiliar de pessoa para retornar ela.
  Celula *ant = NULL;      //Ponteiro auxiliar sempre na posição anterior ao p
  //Faz a busca da pessoa que se quer retirar
  while (p != NULL && strcmp(retornaNomePessoa(p->pessoa), nome))
  {
    ant = p;
    p = p->prox;
  }
  //Lista vazia ou não encontrou a pessoa
  if (p == NULL)
    return NULL;
  people = p->pessoa; //Atribui a pessoa de retorno
  return people;      //Retornando a pessoa
}

// Modifica os campo numeroPlaylists e listaPlaylist de cada Pessoa
void lePlaylists(ListaPessoa *lista)
{
  Pessoa *pessoa;
  char nomePessoa[50], linha[200];
  int i;
  FILE *arqPlaylist;
  arqPlaylist = fopen("playlists.txt", "r");
  if (arqPlaylist == NULL)
  {
    printf("** ERRO: O arquivo não foi aberto **");
    exit;
  }
  while (1)
  {
    //A função feof retona um valor inteiro diferente de zero se o indicador de fim de arquivo está marcado para linha
    if (feof(arqPlaylist))
      break;
    fgets(linha, 200, arqPlaylist); // o 'fgets' lê até 199 caracteres ou até o '\n'
    i = 0;
    while (linha[i] != ';')
    {
      nomePessoa[i] = linha[i];
      i++;
    }
    char *nome = duplica(nomePessoa, i);
    pessoa = retornaPessoa(lista, nome);
    i = i + 1;
    definePlaylists(pessoa, &linha[i]);
    free(nome);
  }
  fclose(arqPlaylist);
}

// Modifica o campo listaMusica de todas as playlist da listaPlaylist de todas as pessoas da lista de pessoas
void defineTodosPlaylists(ListaPessoa *lista, ListaMusica *todasMusicas)
{
  Celula *p; //ponteiro auxiliar que aponta para um celula que já existe e já foi alocada anteriormente
  p = lista->Prim;
  while (p != NULL) //Enquanto não chegar ao final da lista
  {
    carregaPlaylists(p->pessoa, todasMusicas); //p anda em cada celula da lista
    p = p->prox;
  }
}

// Inicializa uma outra estrutura de listaPlaylists que separa as músicas por cantor de cada pessoa
void reInicListaPlaylistTodos(ListaPessoa *lista)
{
  Celula *p; //ponteiro auxiliar que aponta para um celula que já existe e já foi alocada anteriormente
  p = lista->Prim;
  while (p != NULL) //Enquanto não chegar ao final da lista
  {
    reInicListaPlaylistPessoa(p->pessoa); //p anda em cada celula da lista
    p = p->prox;
  }
}

//le as amizades de uma lista e grava a quantidade de musicas iguais
void Similaridades(ListaPessoa *lista)
{
  FILE *arqAmizade;
  int numSimilar = 0;
  FILE *arqSimilaridades;
  char pessoa1[100], pessoa2[100], leitura[200], *linha, *ppe1, *ppe2;
  int flagMalloc = 0, i = 0, j = 0;
  arqAmizade = fopen("amizade.txt", "r");
  if (arqAmizade == NULL)
    printf("Erro, nao foi possivel abrir o arquivo\n");
  else
  {
    fgets(leitura, 200, arqAmizade); //salta a leitura inicial
    arqSimilaridades = fopen("similaridades.txt", "w");
    while (1)
    {
      //A função feof retona um valor inteiro diferente de zero se o indicador de fim de arquivo está marcado para leitura
      if (feof(arqAmizade)) // le o arquivo até o final
        break;
      fgets(leitura, 200, arqAmizade);

      if (leitura[strlen(leitura) - 1] != '\n') // Se o último caractere não for o '/n'
      {
        int tamanho = strlen(leitura);
        linha = duplica(leitura, tamanho + 1);
        linha[tamanho] = '\n'; // Aloca outra string com o '\n' no último caractere
        flagMalloc = 1;
      }
      i = 0;
      j = 0;
      while (leitura[i] != ';')
      {
        pessoa1[i] = leitura[i]; // Atribui todos os caracteres até o ';' a pessoa1
        i++;
      }
      ppe1 = duplica(pessoa1, i); // Retorna uma string alocada dinamicamente
      i = i + 1;
      while (leitura[i] != '\n')
      {
        pessoa2[j] = leitura[i]; // Atribui todos os caracteres até o '\n' a pessoa2
        i++;
        j++;
      }
      ppe2 = duplica(pessoa2, j); // Retorna uma string alocada dinamicamente
      if (flagMalloc)             //Verifica se foi alocada para adicionar o '\n'
        free(linha);
      //compara todas as musicas dessas 2 pessoas
      numSimilar = comparaPlaylist(retornaListaPlaylistPessoa(retornaPessoa(lista, ppe1)), retornaListaPlaylistPessoa(retornaPessoa(lista, ppe2)));
      //cria novo arquivo com o número de similaridaes entre 2 pessoas
      if (arqAmizade == NULL)
        printf("Erro, nao foi possivel criar o arquivo\n");
      else
      {
        fprintf(arqSimilaridades, "%s;%s;%d\n", ppe1, ppe2, numSimilar);
      }

      free(ppe1);
      free(ppe2);
    }
    fclose(arqSimilaridades);
  }
  fclose(arqAmizade);
}

// Imprime todas as pessoas da lista no arquivo played-refatorada.txt
void refatoraTodos(ListaPessoa *lista)
{
  Celula *p; //ponteiro auxiliar que aponta para um celula que já existe e já foi alocada anteriormente
  p = lista->Prim;
  int status = remove("played-refatorada.txt"); //Exclui o arquivo
  while (p != NULL)                             //Enquanto não chegar ao final da lista
  {
    refatoraPessoa(p->pessoa);
    p = p->prox;
  }
}

//le as amizades e cria lista de amigos em cada pessoa
void defineAmizades(ListaPessoa *lista)
{
  FILE *arqAmizade;
  char pessoa1[100], pessoa2[100], leitura[200], *linha, *ppe1, *ppe2;
  int flagMalloc = 0, i = 0, j = 0;
  arqAmizade = fopen("amizade.txt", "r");
  if (arqAmizade == NULL)
    printf("Erro, nao foi possivel abrir o arquivo\n");
  else
  {
    fgets(leitura, 200, arqAmizade); //salta a leitura inicial
    while (1)
    {
      //A função feof retona um valor inteiro diferente de zero se o indicador de fim de arquivo está marcado para leitura
      if (feof(arqAmizade)) // le o arquivo até o final
        break;
      fgets(leitura, 200, arqAmizade);

      if (leitura[strlen(leitura) - 1] != '\n') // Se o último caractere não for o '/n'
      {
        int tamanho = strlen(leitura);
        linha = duplica(leitura, tamanho + 1);
        linha[tamanho] = '\n'; // Aloca outra string com o '\n' no último caractere
        flagMalloc = 1;
      }
      i = 0;
      j = 0;
      while (leitura[i] != ';')
      {
        pessoa1[i] = leitura[i]; // Atribui todos os caracteres até o ';' a pessoa1
        i++;
      }
      ppe1 = duplica(pessoa1, i); // Retorna uma string alocada dinamicamente
      i = i + 1;
      while (leitura[i] != '\n')
      {
        pessoa2[j] = leitura[i]; // Atribui todos os caracteres até o '\n' a pessoa2
        i++;
        j++;
      }
      ppe2 = duplica(pessoa2, j); // Retorna uma string alocada dinamicamente
      if (flagMalloc)             //Verifica se foi alocada para adicionar o '\n'
        free(linha);

      adAmigo(retornaPessoa(lista, ppe1), retornaPessoa(lista, ppe2));
      free(ppe1);
      free(ppe2);
    }
  }
  fclose(arqAmizade);
}

//Função para uso recursivo fazendo o merge da ListaPessoa do final para o inicio
static void mergeListaPessoaEstatica(Celula *p);

// Faz o marge das Listas de Playlists de todos os amigos
void mergeListaPessoa(ListaPessoa *lista)
{
  Celula *p, *pa; //ponteiro auxiliar
  ListaPessoa *amigos;
  p = lista->Prim;
  //Fazendo o merge da ListaPessoa do inicio para o final
  while (p != NULL) //Enquanto não chegar ao final da lista
  {
    amigos = retornaListaAmizades(p->pessoa); //p anda em cada celula da lista
    pa = amigos->Prim;
    while (pa != NULL)
    {
      mergePlaylists(retornaListaPlaylistPessoa(p->pessoa), retornaListaPlaylistPessoa(pa->pessoa));
      pa = pa->prox;
    }
    p = p->prox;
  }
  mergeListaPessoaEstatica(lista->Prim);
}

//Libera memória alocada para a lista
void liberaListaPessoa(ListaPessoa *lista, bool tudo)
{
  Celula *p = lista->Prim; //ponteiro auxiliar recebendo a primeira celula da lista
  Celula *t;               // outro ponteiro auxiliar
  if (tudo)
  {
    while (p != NULL) //Enquanto não chegar ao final da lista
    {
      t = p->prox; //O ponteiro temporário aponta para a proxima célula
      deletaPessoa(p->pessoa, 0);
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

//Faz o merge da ListaPessoa do final para o inicio de maneira recursiva
static void mergeListaPessoaEstatica(Celula *p)
{
  Celula *pa; //ponteiro auxiliar
  ListaPessoa *amigos;
  if (p != NULL) // testa caso base
  {
    mergeListaPessoaEstatica(p->prox);        //redução da recursão
    amigos = retornaListaAmizades(p->pessoa); //p anda em cada celula da lista
    pa = amigos->Prim;
    while (pa != NULL)
    {
      mergePlaylists(retornaListaPlaylistPessoa(p->pessoa), retornaListaPlaylistPessoa(pa->pessoa));
      pa = pa->prox;
    }
  }
}