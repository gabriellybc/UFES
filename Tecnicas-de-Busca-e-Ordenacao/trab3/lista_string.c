#include <stdio.h>
#include <stdlib.h>
#include "lista_string.h"

typedef struct cel Celula;

struct cel
{
  String *pag;
  Celula *prox;
};

struct lista_string // Sentinela
{
  Celula *prim;
  Celula *ult;
  unsigned int tamanho;
};

Lista_string  *iniciar_lista_string()
{
  Lista_string  *lista_string = (Lista_string  *)malloc(sizeof(Lista_string ));
  lista_string->prim = NULL;
  lista_string->ult = NULL;
  lista_string->tamanho = 0;
  return lista_string;
};

//No Inicio
void inserir_lista_string(Lista_string  *lista_string, String *pag)
{
  lista_string->tamanho++;
  Celula *nova = (Celula *)malloc(sizeof(Celula));
  nova->pag = pag; //O nova->pag recebe a pag que eu quero incerir na lista_string
  nova->prox = lista_string->prim; //Encadeando a nova celula na lista_string fazendo ela receber o endereço da antiga primeira celula que vai virar a segunda
  lista_string->prim = nova; //Mudando a primeira celula da lista_string, o inicio da lista_string apontar pra nova e assim colocando ela no primeiro lugar da lista_string
  if (lista_string->ult == NULL) //Caso a lista_string estivesse vazia
  {
    lista_string->ult = nova; //A nova vai ser a primeira celula da lista_string
  }
};

//No Finpag
void inserir_lista_string_ult(Lista_string  *lista_string, String *pag)
{
  lista_string->tamanho++;
  Celula *nova = (Celula *)malloc(sizeof(Celula));
  nova->pag = pag; //O nova->pag recebe a pag que eu quero incerir na lista_string
  nova->prox = NULL;
  if (lista_string->ult == NULL) //Caso a lista_string estivesse vazia
  {
    lista_string->prim = lista_string->ult = nova; //A nova vai ser a primeira e a ultima celula da lista_string
    return;
  }
  lista_string->ult->prox = nova; //Encadeando a nova celula na lista_string, encadeando a antiga ultima celula com a nova
  lista_string->ult = nova; //Mudando a ultima celula da lista_string, o finpag da lista_string aponta pra nova e assim colocando ela no ultimo lugar da lista_string
};

unsigned int get_tamanho_lista_string(Lista_string  *lista_string)
{
  return lista_string->tamanho;
};

//Libera apenas a memoria da lista_string, as Lista_string es contiarão armazenadas
void liberar_lista_string(Lista_string  *lista_string)
{
  Celula *p = lista_string->prim; //ponteiro auxiliar recebendo a primeira celula da lista_string
  Celula *t;               // outro ponteiro auxiliar

  while (p != NULL) //Enquanto não chegar ao finpag da lista_string
  {
    t = p->prox; //O ponteiro temporário aponta para a proxima célula
    free(p);
    p = t;
  }
  //Liberando a sentinela
  free(lista_string);
};


void imprimir_lista_string(Lista_string  *lista_string)
{
  Celula *p = lista_string->prim; //ponteiro auxiliar recebendo a primeira celula da lista_string
  Celula *t;               // outro ponteiro auxiliar
  unsigned int index = 0, max_tamanho = get_tamanho_lista_string(lista_string)-1;
  printf("search:");
  while (p != NULL) //Enquanto não chegar ao finpag da lista_string
  {
    t = p->prox; //O ponteiro temporário aponta para a proxima célula
    if(index == max_tamanho) {
      printf("%s", get_string(p->pag));
    }
    else {
      printf("%s ", get_string(p->pag));
    }
    liberar_string(p->pag);
    free(p);
    p = t;
    index++;
  }
  //Liberando a sentinela
  free(lista_string);
};