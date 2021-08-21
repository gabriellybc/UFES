#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

struct arv
{
  char info;       //campo de char, mas poderia ser qualquer coisa. Como Aluno* e tal
  struct arv *esq; // ponteiro para a esquerda
  struct arv *dir; // ponteiro para a direita
};

// Cria uma árvore vazia
Arv *arv_criavazia(void)
{
  return NULL;
}

// Cria uma árvore com a informação do nó raiz c, //e com subárvore esquerda e e subárvore direira d
Arv *arv_cria(char c, Arv *sae, Arv *sad)
//Recebe a informação do nó, a subárvore da esquerda e direita
{
  Arv *p = (Arv *)malloc(sizeof(Arv)); //malloc para criar o novo nó, p aponta para o novo nó
  p->info = c;                         // Se fosse Aluno, receberia aluno, etc
  p->esq = sae;
  p->dir = sad;
  return p;
}

//indica se uma árvore é ou não vazia
int arv_vazia(Arv *a)
{
  return a == NULL; //Se a raiz for nula, então ela é vazia
}

//libera o espaço de memória ocupado pela árvore a
Arv *arv_libera(Arv *a)
{
  //Se a árvore não estiver vazia, entra aqui
  if (!arv_vazia(a)) //Caso base: árvore estar vazia
  {
    //Chamando recursivamente para sae
    arv_libera(a->esq); //libera sae
    //Chamando recursivamente para sad
    arv_libera(a->dir); //libera sad
    free(a);            //libera raiz
  }
  return NULL; //Se a árvore estiver vazia, retorna NULL
}

//Verifica se o caracter está ou não na árvore
int arv_pertence(Arv *a, char c) //Usa 2 casos bases
{
  if (arv_vazia(a)) //1) Se a arvore está vazia
    return 0;       // árvore vazia: não encontrou
  else              // Caso contrário
    //2) Se a raiz já contém o caractere, ele já retorna 1. Se não for, chamada recursiva para esquerda
    return a->info == c || arv_pertence(a->esq, c) || arv_pertence(a->dir, c);
}

//percorre recursivamente a árvore, visitando todos os nós e imprimindo sua informação
void arv_imprime(Arv *a)
{
  printf("<");
  if (!arv_vazia(a))
  {
    printf("%c", a->info); //mostra raiz
    arv_imprime(a->esq);   //mostra sae
    arv_imprime(a->dir);   //mostra sad
  }
  printf(">");
}