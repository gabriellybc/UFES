#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_listas.h"

typedef struct cel Celula;

struct cel
{
  Lista *pag;
  Celula *prox;
};

struct lista_listas // Sentinela
{
  Celula *prim;
  Celula *ult;
  unsigned int tamanho;
};

Lista_listas *iniciar_lista_listas()
{
  Lista_listas *lista_listas = (Lista_listas *)malloc(sizeof(Lista_listas));
  lista_listas->prim = NULL;
  lista_listas->ult = NULL;
  lista_listas->tamanho = 0;
  return lista_listas;
};

//No Inicio
void inserir_lista_listas(Lista_listas *lista_listas, Lista *pag)
{
  lista_listas->tamanho++;
  Celula *nova = (Celula *)malloc(sizeof(Celula));
  nova->pag = pag; //O nova->pag recebe a pag que eu quero incerir na lista_listas
  nova->prox = lista_listas->prim; //Encadeando a nova celula na lista_listas fazendo ela receber o endereço da antiga primeira celula que vai virar a segunda
  lista_listas->prim = nova; //Mudando a primeira celula da lista_listas, o inicio da lista_listas apontar pra nova e assim colocando ela no primeiro lugar da lista_listas
  if (lista_listas->ult == NULL) //Caso a lista_listas estivesse vazia
  {
    lista_listas->ult = nova; //A nova vai ser a primeira celula da lista_listas
  }
};

//No Finpag
void inserir_lista_listas_ult(Lista_listas *lista_listas, Lista *pag)
{
  lista_listas->tamanho++;
  Celula *nova = (Celula *)malloc(sizeof(Celula));
  nova->pag = pag; //O nova->pag recebe a pag que eu quero incerir na lista_listas
  nova->prox = NULL;
  if (lista_listas->ult == NULL) //Caso a lista_listas estivesse vazia
  {
    lista_listas->prim = lista_listas->ult = nova; //A nova vai ser a primeira e a ultima celula da lista_listas
    return;
  }
  lista_listas->ult->prox = nova; //Encadeando a nova celula na lista_listas, encadeando a antiga ultima celula com a nova
  lista_listas->ult = nova; //Mudando a ultima celula da lista_listas, o finpag da lista_listas aponta pra nova e assim colocando ela no ultimo lugar da lista_listas
};

unsigned int get_tamanho_lista_listas(Lista_listas *lista_listas)
{
  return lista_listas->tamanho;
};

//Libera apenas a memoria da lista_listas, as Lista_listases contiarão armazenadas
void liberar_lista_listas(Lista_listas *lista_listas)
{
  Celula *p = lista_listas->prim; //ponteiro auxiliar recebendo a primeira celula da lista_listas
  Celula *t;               // outro ponteiro auxiliar

  while (p != NULL) //Enquanto não chegar ao finpag da lista_listas
  {
    t = p->prox; //O ponteiro temporário aponta para a proxima célula
    free(p);
    p = t;
  }
  //Liberando a sentinela
  free(lista_listas);
};

void imprimir_lista_listas(Lista_listas *lista_listas)
{
  Celula *p = lista_listas->prim;

  while (p != NULL) //Enquanto não chegar ao finpag da lista_listas
  {
    imprimir_lista(p->pag);
    p = p->prox; //O ponteiro temporário aponta para a proxima célula
  }
};



Pagina **listas_para_array(Lista_listas *lista_listas, unsigned int *tamanho) {
    *tamanho = 0;
    Celula *p = lista_listas->prim;

    // Primeiro, calcula o tamanho total do array combinando os tamanhos de todas as listas.
    while (p != NULL) { // Enquanto não chegar ao final da lista_listas
        *tamanho += get_tamanho_lista(p->pag); // Soma o tamanho de cada lista
        p = p->prox; // Aponta para a próxima célula
    }

    // Agora, aloca memória para o array total
    Pagina **paginas_total = iniciar_arrey_paginas(*tamanho);
    if (paginas_total == NULL) {
        printf("Erro ao alocar memoria!\n");
        return NULL;
    }

    Celula *t;   
    p = lista_listas->prim;
    int offset = 0;

    // Agora percorre novamente a lista para copiar os dados
    while (p != NULL) {
        t = p->prox; //O ponteiro temporário aponta para a proxima célula
        // Obtém o array de páginas da lista atual
        Pagina **paginas = lista_para_array_imprimir(p->pag, get_tamanho_lista(p->pag));

        // Copia os elementos da lista atual para o array final
        memcpy(paginas_total + offset, paginas, get_tamanho_lista(p->pag) * sizeof(Pagina *));
        free(paginas);

        // Atualiza o offset para a próxima posição no array final
        offset += get_tamanho_lista(p->pag);

        free(p);
        p = t;
    }
    free(lista_listas);

    return paginas_total; // Retorna o array combinado
}