#include <stdio.h>
#include <stdlib.h>
#include "listaArvore.h"

// Tipo celula
typedef struct cel Celula;

struct cel
{
  Arv *arv;
  Celula *prox;
  Celula *ant;
};

// Tipo Lista de arvore (tipo opaco)
// Sentinela
struct listaArvore
{
  Celula *Prim;
  Celula *Ult;
};

// Inicializa uma lista de arvores
ListaArvore *inicListaArvore()
{
  ListaArvore *lista = (ListaArvore *)malloc(sizeof(ListaArvore));
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
static Celula *ordena(ListaArvore *lista, int pesoAtual, bool final)
{
  Celula *p;
  int outroPeso;
  if (final) //Comecando pelo final
  {
    p = lista->Ult;
    outroPeso = retornaPeso(p->arv);
    //faz a busca
    while (p != lista->Prim && pesoAtual < outroPeso) // Enquanto o peso da outra arvore for maior
    {
      p = p->ant; //Vai para a celula anterior
      outroPeso = retornaPeso(p->arv);
    }
  }
  else
  {
    p = lista->Prim;
    outroPeso = retornaPeso(p->arv);
    //faz a busca
    while (p != lista->Ult && outroPeso < pesoAtual) //Enquanto o peso da outra arvore for menor
    {
      p = p->prox; //Vai para a prox celula
      outroPeso = retornaPeso(p->arv);
    }
  }
  return p;
}

//Funcao que verficar se a Celula nova será inserida no inicio da lista ou na segunda posicao
static void adicionaInicio(ListaArvore *lista, Celula *nova)
{
  Celula *segund = lista->Prim->prox;
  if (retornaPeso(nova->arv) < retornaPeso(lista->Prim->arv))
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
static void adicionaFinal(ListaArvore *lista, Celula *nova)
{
  Celula *penult = lista->Ult->ant;
  if (retornaPeso(nova->arv) < retornaPeso(lista->Ult->arv))
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
  if (retornaPeso(nova->arv) < retornaPeso(aux->arv))
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

//Insere arvore na lista de forma ordenada crescente de acordo com o peso da arvore
void insereArvoreOrdenada(ListaArvore *lista, Arv *arv, bool final)
{
  Celula *nova = (Celula *)malloc(sizeof(Celula));
  if (!nova)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }
  int pesoArv = retornaPeso(arv);
  nova->arv = arv;
  if (lista->Prim == NULL && lista->Ult == NULL) //Se a lista estiver vazia
  {
    nova->ant = nova->prox = NULL;
    lista->Ult = lista->Prim = nova;
  }

  else if (lista->Prim == lista->Ult) //Se a lista tiver apenas um elemento
  {
    if (pesoArv < retornaPeso(lista->Prim->arv))
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
    if (final)
      aux = ordena(lista, pesoArv, 1);
    else
    {
      if (abs(retornaPeso(lista->Ult->arv) - pesoArv) < abs((pesoArv - retornaPeso(lista->Prim->arv))))
        aux = ordena(lista, pesoArv, 1);
      else
        aux = ordena(lista, pesoArv, 0);
    }

    if (lista->Prim == aux) //Se retornar a primeira Celula da lista
      adicionaInicio(lista, nova);
    else if (lista->Ult == aux) //Se retornar a ultima Celula da lista
      adicionaFinal(lista, nova);
    else //caso geral
      adicionaMeio(aux, nova);
  }
}

//Define a lista de arvores passada, de forma crescente, com arvores criadas com caracteres do vetor de inteiros diferentes de zero
int defineListaArvore(ListaArvore *lista, int *repeticoes)
{
  int qnt = 0;
  Arv *arv;
  for (int i = 0; i < 256; i++)
  {
    if (repeticoes[i] != 0)
    {
      qnt++;
      arv = arvCria(i, repeticoes[i], 1, arvCriaVazia(), arvCriaVazia());
      insereArvoreOrdenada(lista, arv, 0);
    }
  }
  return qnt;
}

//Cria uma unica arvore com a lista de arvores
Arv *codificaArvore(ListaArvore *lista)
{
  if (lista->Prim->prox != NULL)
  {
    Celula *p = lista->Prim;
    Celula *q = p->prox;
    Arv *arvoreNova;
    arvoreNova = arvCria('\0', retornaPeso(p->arv) + retornaPeso(q->arv), 0, p->arv, q->arv);
    retiraArvore(lista, 0);
    retiraArvore(lista, 0);
    insereArvoreOrdenada(lista, arvoreNova, 1);
    codificaArvore(lista);
  }
  else
    return lista->Prim->arv;
}

//Imprime a lista de arvores
void imprimeListaArvore(ListaArvore *lista)
{
  Celula *p; //ponteiro auxiliar que aponta para um celula que já existe e já foi alocada anteriormente

  for (p = lista->Prim; p != NULL; p = p->prox)
  {
    arvImprime(p->arv); //p anda em cada celula da listaDpl
    printf("\n");
  }
}

//Funcao de retorno para a busca de arvore em determinada posicao
static Celula *busca(Celula *primeira, int posicao)
{
  Celula *p = primeira;
  int atual = 0;
  //faz a busacao
  while (p != NULL && atual != posicao)
  {
    p = p->prox;
    atual++;
  }
  return p;
}

//Retira a arvore de determinado posicao da lista de arvores
Arv *retiraArvore(ListaArvore *lista, int posicao)
{
  Celula *p = busca(lista->Prim, posicao);

  //Lista vazia ou nao encontrou a arvore
  if (p == NULL)
    return NULL;

  //Atribui a arvore de retorno
  Arv *arv = p->arv;

  if (p->prox == NULL && p->ant == NULL) //Unico elemento
    lista->Prim = lista->Ult = NULL;     //Lista fica vazia

  else if (p == lista->Prim) // testa se é o primeiro elemento
  {
    p->prox->ant = NULL;
    lista->Prim = p->prox;
  }
  else if (p == lista->Ult) //ultimo elemento
  {
    p->ant->prox = NULL;
    lista->Ult = p->ant;
  }
  else // Caso comum
  {
    p->ant->prox = p->prox;
    p->prox->ant = p->ant;
  }
  free(p);    //Liberando apenas a célula da lista
  return arv; //Retornando a arvore
}

//Retorna a arvore de determinado posicao da lista de arvores
Arv *retornaArvore(ListaArvore *lista, int posicao)
{
  Celula *p = busca(lista->Prim, posicao);

  //Lista vazia ou nao encontrou a arvore
  if (p == NULL)
    return NULL;

  //Atribui a arvore de retorno
  Arv *arv = p->arv;

  return arv; //Retornando a arvore
}

//Imprime a quantidade de folhas e a primeira arvore da lista no arquivo binario
void imprimeArvoreBinario(ListaArvore *lista, char *nomeArquivo)
{
  remove(nomeArquivo); //Exclui o arquivo se ele ja existir
  Arv *a = retornaArvore(lista, 0);
  int folhas = arvFolhas(a);
  //Imprimindo a quantidade de folhas
  bitmap *binFolhas = dec2bin(folhas - 1);
  escreveBinario(binFolhas, nomeArquivo);
  bitmapLibera(binFolhas);

  //Imprimindo a arvore
  int tamMax = arvNos(a) + (folhas * 8);
  tamMax = (tamMax % 8) ? ((tamMax / 8) + 1) * 8 : tamMax;
  bitmap *bm = bitmapInit(tamMax);
  arvBinario(a, bm);
  unsigned int tamanho = bitmapGetLength(bm);

  int limite = (((tamanho / 8) + 1) * 8) - tamanho;
  for (int i = 0; i < limite; i++) //tratando lixo
    bitmapAppendLeastSignificantBit(bm, 0);
  escreveBinario(bm, nomeArquivo);
  bitmapLibera(bm);
}

//Libera memória alocada para a lista
void liberaListaArvore(ListaArvore *lista)
{
  Celula *p = lista->Prim; //ponteiro auxiliar recebendo a primeira celula da lista
  Celula *t;               // outro ponteiro auxiliar

  while (p != NULL) //Enquanto nao chegar ao final da lista
  {
    t = p->prox; //O ponteiro temporário aponta para a proxima célula
    arvLibera(p->arv);
    free(p);
    p = t;
  }
  //Liberando a sentinela
  free(lista);
}
