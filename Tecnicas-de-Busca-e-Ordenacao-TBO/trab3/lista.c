#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "lista.h"

typedef struct cel Celula;

struct cel
{
  Pagina *pag;
  Celula *prox;
};

struct lista // Sentinela
{
  Celula *prim;
  Celula *ult;
  unsigned int tamanho;
};

Lista *iniciar_lista()
{
  Lista *lista = (Lista *)malloc(sizeof(Lista));
  lista->prim = NULL;
  lista->ult = NULL;
  lista->tamanho = 0;
  return lista;
};

//No Inicio
void inserir_lista(Lista *lista, Pagina *pag)
{
  lista->tamanho++;
  Celula *nova = (Celula *)malloc(sizeof(Celula));
  nova->pag = pag; //O nova->pag recebe a pag que eu quero incerir na lista
  nova->prox = lista->prim; //Encadeando a nova celula na lista fazendo ela receber o endereço da antiga primeira celula que vai virar a segunda
  lista->prim = nova; //Mudando a primeira celula da lista, o inicio da lista apontar pra nova e assim colocando ela no primeiro lugar da lista
  if (lista->ult == NULL) //Caso a lista estivesse vazia
  {
    lista->ult = nova; //A nova vai ser a primeira celula da lista
  }
};

//No Finpag
void inserir_lista_ult(Lista *lista, Pagina *pag)
{
  lista->tamanho++;
  Celula *nova = (Celula *)malloc(sizeof(Celula));
  nova->pag = pag; //O nova->pag recebe a pag que eu quero incerir na lista
  nova->prox = NULL;
  if (lista->ult == NULL) //Caso a lista estivesse vazia
  {
    lista->prim = lista->ult = nova; //A nova vai ser a primeira e a ultima celula da lista
    return;
  }
  lista->ult->prox = nova; //Encadeando a nova celula na lista, encadeando a antiga ultima celula com a nova
  lista->ult = nova; //Mudando a ultima celula da lista, o finpag da lista aponta pra nova e assim colocando ela no ultimo lugar da lista
};

unsigned int get_tamanho_lista(Lista *lista)
{
  return lista->tamanho;
};

void imprimir_lista(Lista *lista)
{
  Celula *p; //ponteiro auxiliar que aponta para um celula que já existe e já foi pagocada anteriormente

  printf("Tamanho: %u\n", lista->tamanho);
  for (p = lista->prim; p != NULL; p = p->prox)
  {
    imprimir_pagina(p->pag); //p anda em cada celula da lista
    printf("\n");
  }
};

Pagina *retirar_lista(Lista *lista, int pos)
{
  lista->tamanho--;
  Celula *p = lista->prim; //ponteiro auxiliar p apontando para a primeira celula da lista
  Pagina *pag;               //Variavel auxiliar de paguno para retornar ele.
  Celula *ant = NULL;      //Ponteiro auxiliar sempre na posição anterior ao p

  int posicao = 0;
  //Faz a busca
  while (p != NULL && posicao != pos)
  {
    ant = p;
    p = p->prox;
    posicao++;
  }

  //Lista vazia ou não encontrou a Pagina
  if (p == NULL)
  {
    lista->tamanho++;
    return NULL;
  }

  //Atribui a Pagina de retorno
  pag = p->pag;

  //Se for a única celula da lista
  if (p == lista->prim && p == lista->ult)
    lista->prim = lista->ult = NULL; //lista fica vazia
  else if (p == lista->prim)         //Se for a primeira celula da lista
    lista->prim = p->prox;
  else if (p == lista->ult) //Se for a ultima Celula
  {
    lista->ult = ant;
    ant->prox = NULL; // ou lista->ult->prox = NULL;
  }
  else //caso comum
  {
    ant->prox = p->prox;
  }

  free(p); //Liberando apenas a célula da lista

  return pag; //Retornando o paguno
};

//Libera apenas a memoria da lista, as Paginaes contiarão armazenadas
void liberar_lista(Lista *lista)
{
  Celula *p = lista->prim; //ponteiro auxiliar recebendo a primeira celula da lista
  Celula *t;               // outro ponteiro auxiliar

  while (p != NULL) //Enquanto não chegar ao finpag da lista
  {
    t = p->prox; //O ponteiro temporário aponta para a proxima célula
    free(p);
    p = t;
  }
  //Liberando a sentinela
  free(lista);
};

void liberar_lista_stop_word(Lista *lista)
{
  Celula *p = lista->prim; //ponteiro auxiliar recebendo a primeira celula da lista
  Celula *t;               // outro ponteiro auxiliar

  while (p != NULL) //Enquanto não chegar ao finpag da lista
  {
    t = p->prox; //O ponteiro temporário aponta para a proxima célula
    liberar_pagina(p->pag);
    free(p);
    p = t;
  }
  //Liberando a sentinela
  free(lista);
};



Pagina **lista_para_array(Lista *lista, unsigned int *tamanho){
  *tamanho = lista->tamanho;
  Pagina **paginas = iniciar_arrey_paginas(*tamanho);
  Celula *p = lista->prim;
  Celula *t;
  for (int i = 0; i < *tamanho; i++){
    t = p->prox;
    set_pagerank(p->pag, (1.0 / lista->tamanho));
    paginas[i] = p->pag;
    free(p);
    p = t;
  }
  free(lista);
  return paginas;
};

Pagina **lista_para_array_imprimir(Lista *lista, unsigned int tamanho){
  Pagina **paginas = iniciar_arrey_paginas(tamanho);
  Celula *p = lista->prim;
  Celula *t;
  for (int i = 0; i < tamanho; i++){
    t = p->prox;
    paginas[i] = p->pag;
    p = t;
  }
  return paginas;
};


double lista_pagerank(Lista *lista) {
    double pagerank_total = 0.0;
    Celula *p = lista->prim;
    
    while (p != NULL) {
        Pagina *pagina = p->pag;
        atualizar_cache(pagina);  
        pagerank_total += get_pagerank_por_links(pagina);
        p = p->prox;
    }

    return pagerank_total;
}


Pagina *get_ultima_pagina(Lista *lista){
  return lista->ult->pag;
};


void imprimir_lista_saida(Lista *lista)
{
  Celula *p = lista->prim; //ponteiro auxiliar recebendo a primeira celula da lista
  Celula *t;               // outro ponteiro auxiliar
  unsigned int index = 0;
  unsigned int tamanho_max = lista->tamanho -1;

  printf("\npages:");
  while (p != NULL) //Enquanto não chegar ao finpag da lista
  {
    t = p->prox; //O ponteiro temporário aponta para a proxima célula
    if(index != tamanho_max) {
      printf("%s ", get_string(get_nome_pagina(p->pag)));
    }
    else {
      printf("%s", get_string(get_nome_pagina(p->pag)));
    }
    p = t;
    index++;
  }
  index = 0;
  
  p = lista->prim;
  printf("\npr:");
  while (p != NULL) //Enquanto não chegar ao finpag da lista
  {
    t = p->prox; //O ponteiro temporário aponta para a proxima célula
    if(index != tamanho_max) {
      printf("%.*g ", DBL_DIG, get_pagerank(p->pag));
    }
    else {
      printf("%.*g", DBL_DIG, get_pagerank(p->pag));
    }
    free(p);
    p = t;
  }
  printf("\n");
  //Liberando a sentinela
  free(lista);
};