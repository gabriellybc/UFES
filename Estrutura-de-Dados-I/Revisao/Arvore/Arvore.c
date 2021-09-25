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
Arv *arv_criavazia()
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

static int max2(int a, int b)
{
  return (a > b) ? a : b; // Se a for maior que b, então retorna a. Caso contrário, retorna b
}

int arv_altura(Arv *a)
{
  if (arv_vazia(a)) //Condição de parada: Se a árvore estiver vazia
    return -1;      //Retorna -1
  else              //Caso contrário (árvore não vazia)
  {
    return 1 + max2(arv_altura(a->esq), arv_altura(a->dir));
  }
}

//Retorna o numero total de nos de uma arvore cheia
int arvNos(Arv *a)
{
  int nos = 1, altura = arv_altura(a);
  for (int i = 0; i < altura + 1; i++)
    nos *= 2; // nos = nos * 2
  return nos - 1;
}

//retorna a quantidade de folhas de uma árvore binaria
int folhas(Arv *a)
{
  int qnt_folhas;
  if (arv_vazia(a)) //caso base
    return 0;
  qnt_folhas = folhas(a->esq) + folhas(a->dir);
  qnt_folhas = (qnt_folhas == 0) ? 1 : qnt_folhas; //Se qnt_folhas for igual a zero, retorna 1. Caso contrário, retorna qnt_folhas
  return qnt_folhas;
}

//retorna o número de ocorrencias de um dado caracter na árvore
int ocorrencias(Arv *a, char c)
{
  if (arv_vazia(a)) //caso base
    return 0;
  return (a->info == c) + ocorrencias(a->esq, c) + ocorrencias(a->dir, c);
}

//retorna o campo informação de um dado nó
char info(Arv *a)
{
  if (arv_vazia(a))
    return '0';
  return a->info;
}