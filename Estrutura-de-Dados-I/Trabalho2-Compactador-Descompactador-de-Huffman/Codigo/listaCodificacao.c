#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listaCodificacao.h"

// Tipo celula
typedef struct cel Celula;

struct cel
{
  Codificacao *codificacao;
  Celula *prox;
  Celula *ant;
};

// Tipo Lista de codificacao (tipo opaco)
// Sentinela
struct listaCodificacao
{
  Celula *Prim;
  Celula *Ult;
};

// Inicializa uma lista de Codificacoes
ListaCodificacao *inicListaCodificacao()
{
  ListaCodificacao *lista = (ListaCodificacao *)malloc(sizeof(ListaCodificacao));
  if (!lista)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }
  lista->Prim = NULL;
  lista->Ult = NULL;
  return lista;
}

//Funcao de retorno da Celula para a ordenacao crescente da lista
static Celula *ordena(ListaCodificacao *lista, int tamanhoAtual, bool final)
{
  Celula *p;
  int outroTamanho;
  if (final) //Comecando pelo final
  {
    p = lista->Ult;
    outroTamanho = bitmapGetMaxSize(retornaBitmapCodificacao(p->codificacao));
    //faz a busca
    while (p != lista->Prim && tamanhoAtual < outroTamanho) // Enquanto o tamanho da outra codificacao for maior
    {
      p = p->ant; //Vai para a celula anterior
      outroTamanho = bitmapGetMaxSize(retornaBitmapCodificacao(p->codificacao));
    }
  }
  else
  {
    p = lista->Prim;
    outroTamanho = bitmapGetMaxSize(retornaBitmapCodificacao(p->codificacao));
    //faz a busca
    while (p != lista->Ult && outroTamanho < tamanhoAtual) //Enquanto o tamanho da outra codificacao for menor
    {
      p = p->prox; //Vai para a prox celula
      outroTamanho = bitmapGetMaxSize(retornaBitmapCodificacao(p->codificacao));
    }
  }
  return p;
}

//Funcao que verficar se a Celula nova será inserida no inicio da lista ou na segunda posicao
static void adicionaInicio(ListaCodificacao *lista, Celula *nova)
{
  Celula *segund = lista->Prim->prox;
  if (bitmapGetMaxSize(retornaBitmapCodificacao(nova->codificacao)) < bitmapGetMaxSize(retornaBitmapCodificacao(lista->Prim->codificacao)))
  {
    nova->ant = NULL;
    nova->prox = lista->Prim;
    lista->Prim->ant = nova;
    lista->Prim = nova;
  }
  else
  {
    nova->ant = lista->Prim;
    nova->prox = lista->Prim->prox;
    segund->ant = nova;
    lista->Prim->prox = nova;
  }
}

//Funcao que verficar se a Celula nova será inserida no final da lista ou na penultima posicao
static void adicionaFinal(ListaCodificacao *lista, Celula *nova)
{
  Celula *penult = lista->Ult->ant;
  if (bitmapGetMaxSize(retornaBitmapCodificacao(nova->codificacao)) < bitmapGetMaxSize(retornaBitmapCodificacao(lista->Ult->codificacao)))
  {
    nova->ant = lista->Ult->ant;
    nova->prox = lista->Ult;
    lista->Ult->ant = nova;
    penult->prox = nova;
  }
  else
  {
    nova->ant = lista->Ult;
    nova->prox = NULL;
    lista->Ult->prox = nova;
    lista->Ult = nova;
  }
}

//Funcao que verficar se a Celula nova será inserida antes ou depois da Celula aux
static void adicionaMeio(Celula *aux, Celula *nova)
{
  if (bitmapGetMaxSize(retornaBitmapCodificacao(nova->codificacao)) < bitmapGetMaxSize(retornaBitmapCodificacao(aux->codificacao)))
  {
    nova->prox = aux;
    nova->ant = aux->ant;
    aux->ant->prox = nova;
    aux->ant = nova;
  }
  else
  {
    nova->prox = aux->prox;
    nova->ant = aux;
    aux->prox->ant = nova;
    aux->prox = nova;
  }
}

//Insere uma Codificacao na lista de forma ordenada crescente de acordo com tamanho do bitmap
void insereCodificacaoOrdenada(ListaCodificacao *lista, Codificacao *cod)
{
  Celula *nova = (Celula *)malloc(sizeof(Celula));
  if (!nova)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }
  nova->codificacao = cod;
  int tamanhoAtual = bitmapGetMaxSize(retornaBitmapCodificacao(cod));
  if (lista->Prim == NULL && lista->Ult == NULL) //Se a lista estiver vazia
  {
    nova->ant = nova->prox = NULL;
    lista->Ult = lista->Prim = nova;
  }

  else if (lista->Prim == lista->Ult) //Se a lista tiver apenas um elemento
  {
    if (tamanhoAtual < bitmapGetMaxSize(retornaBitmapCodificacao(lista->Prim->codificacao)))
    {
      nova->ant = NULL;
      nova->prox = lista->Prim;
      lista->Prim->ant = nova;
      lista->Prim = nova;
    }
    else
    {
      nova->ant = lista->Prim;
      nova->prox = NULL;
      lista->Prim->prox = nova;
      lista->Ult = nova;
    }
  }

  else //Se a lista tiver mais de um elemento
  {
    Celula *aux;
    if (abs(bitmapGetMaxSize(retornaBitmapCodificacao(lista->Ult->codificacao)) - tamanhoAtual) < abs((tamanhoAtual - bitmapGetMaxSize(retornaBitmapCodificacao(lista->Prim->codificacao)))))
      aux = ordena(lista, tamanhoAtual, 1); //se a diferenca para o lista->ult for menor
    else
      aux = ordena(lista, tamanhoAtual, 0);

    if (lista->Prim == aux) //Se retornar a primeira Celula da lista
      adicionaInicio(lista, nova);
    else if (lista->Ult == aux) //Se retornar a ultima Celula da lista
      adicionaFinal(lista, nova);
    else //caso geral
      adicionaMeio(aux, nova);
  }
}

// Imprime a lista de Codificacoes
void imprimeListaCodificacao(ListaCodificacao *lista)
{
  Celula *p; //ponteiro auxiliar que aponta para um celula que já existe e já foi alocada anteriormente
  for (p = lista->Prim; p != NULL; p = p->prox)
  {
    imprimeCodificacao(p->codificacao); //p anda em cada celula da lista
    printf("\n");
  }
}

//Funcao de retorno para a busca da codificacao com determinado caracter
static Celula *busca(Celula *primeira, unsigned char caracter)
{
  Celula *p = primeira;
  //faz a busacao
  while (p != NULL && retornaCaracterCodificacao(p->codificacao) != caracter)
    p = p->prox;
  return p;
}

// Retorna a codificacao de determinado nome da lista de codificacaos
Codificacao *retornaCodificacao(ListaCodificacao *lista, unsigned char caracter)
{
  Celula *p = busca(lista->Prim, caracter);

  //Lista vazia ou não encontrou a codificacao
  if (p == NULL)
    return NULL;

  //Atribui a codificacao de retorno
  Codificacao *cod = p->codificacao;
  return cod;
}

// Funcao recursiva estatica chamada para definir toda a tabela de Codificacoes do arquivo
static void defineTabelaCodificacao(ListaCodificacao *listaCod, bitmap *bm, Arv *a)
{
  if (retornaTemCaracter(a)) //caso base
  {
    bitmap *codificaBm = bitmapInit(bitmapGetLength(bm));
    for (int i = 0; i < bitmapGetLength(bm); i++)
      bitmapAppendLeastSignificantBit(codificaBm, bitmapGetBit(bm, i));
    Codificacao *cod = inicCodificacao(retornaInfo(a), codificaBm);
    insereCodificacaoOrdenada(listaCod, cod);
    return;
  }
  bitmapAppendLeastSignificantBit(bm, 0);
  defineTabelaCodificacao(listaCod, bm, retornaArvEsq(a));
  bitmapDeleteLeastSignificantBit(bm);
  bitmapAppendLeastSignificantBit(bm, 1);
  defineTabelaCodificacao(listaCod, bm, retornaArvDir(a));
  bitmapDeleteLeastSignificantBit(bm);
}

// Define toda a tabela de Codificacoes do arquivo
void tabelaCodificacao(ListaCodificacao *listaCod, ListaArvore *listaArv)
{
  Arv *arv = retornaArvore(listaArv, 0);
  int alturaArv = arvAltura(arv);
  bitmap *bm = bitmapInit(alturaArv);
  defineTabelaCodificacao(listaCod, bm, arv);
  bitmapLibera(bm);
}

//grava a codificacao no arquivo binario
void imprimeCodificacaoBinario(ListaCodificacao *lista, char *nomeArquivo, char *nomeArquivoComp)
{
  FILE *arqLeitura;
  unsigned char c;
  bitmap *bmArquivo, *bmCaracter;
  int index;
  bmArquivo = bitmapInit(100000 * 8);
  arqLeitura = fopen(nomeArquivo, "rb");
  if (arqLeitura == NULL)
  {
    printf("** ERRO: O arquivo não foi aberto **");
    exit;
  }
  else
  {
    //faz a leitura do caracter no arquivo apontado por arqLeitura ate o final do arquivo
    while (fread(&c, sizeof(char), 1, arqLeitura) != 0)
    {
      Codificacao *cod = retornaCodificacao(lista, c);
      if (cod)
        bmCaracter = retornaBitmapCodificacao(retornaCodificacao(lista, c));
      else
        printf("aqui\n");
      //obtem bitmap do caracter
      for (index = 0; index < bitmapGetLength(bmCaracter); index++)
        bitmapAppendLeastSignificantBit(bmArquivo, bitmapGetBit((bmCaracter), index));

      if ((bitmapGetMaxSize(bmArquivo) - bitmapGetLength(bmArquivo)) < 1000 && !(bitmapGetLength(bmArquivo) % 8))
      {
        escreveBinario(bmArquivo, nomeArquivoComp);
        bitmapLibera(bmArquivo);
        bmArquivo = bitmapInit(100000 * 8);
      }
    }
    escreveBinario(bmArquivo, nomeArquivoComp);
    bitmapLibera(bmArquivo);
  }
  fclose(arqLeitura); //fechando o arquivo
}

//Libera a memoria da lista
void liberaListaCodificacao(ListaCodificacao *lista)
{
  Celula *p = lista->Prim; //ponteiro auxiliar recebendo a primeira celula da lista
  Celula *t;               // outro ponteiro auxiliar
  while (p != NULL)        //Enquanto não chegar ao final da lista
  {
    t = p->prox; //O ponteiro temporário aponta para a proxima célula
    liberaCodificacao(p->codificacao);
    free(p);
    p = t;
  }
  //Liberando a sentinela
  free(lista);
}