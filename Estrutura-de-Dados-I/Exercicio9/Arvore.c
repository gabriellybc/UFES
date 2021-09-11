#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arvore.h"

struct arv
{
  Aluno *aluno;    //campo de Aluno, mas poderia ser qualquer coisa
  struct arv *esq; // ponteiro para a esquerda
  struct arv *dir; // ponteiro para a direita
};

// Cria uma árvore vazia
Arv *arv_criavazia()
{
  return NULL;
}

// Cria uma árvore com o aluno do nó raiz al, //e com subárvore esquerda e e subárvore direira d
Arv *arv_cria(Aluno *al, Arv *sae, Arv *sad)
//Recebe a informação do nó, a subárvore da esquerda e direita
{
  Arv *p = (Arv *)malloc(sizeof(Arv)); //malloc para criar o novo nó, p aponta para o novo nó
  p->aluno = al;
  p->esq = sae;
  p->dir = sad;
  return p;
}

//indica se uma árvore é ou não vazia
bool arv_vazia(Arv *a)
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

//Verifica se o aluno está ou não na árvore
bool arv_pertence(Arv *a, char *nome) //Usa 2 casos bases
{
  if (arv_vazia(a)) //1) Se a arvore está vazia
    return 0;       // árvore vazia: não encontrou
  else              // Caso contrário
  //2) Se a raiz já contém o aluno, ele já retorna 1. Se não for, chamada recursiva para esquerda
  {
    bool compara = (strcmp(retornaNomeAluno(a->aluno), nome) == 0) ? 1 : 0;
    return compara || arv_pertence(a->esq, nome) || arv_pertence(a->dir, nome);
  }
}

//percorre recursivamente a árvore, visitando todos os nós e imprimindo sua informação
void arv_imprime(Arv *a)
{
  printf("<");
  if (!arv_vazia(a))
  {
    printf("%s", retornaNomeAluno(a->aluno)); //mostra raiz
    arv_imprime(a->esq);                      //mostra sae
    arv_imprime(a->dir);                      //mostra sad
  }
  printf(">");
}

static int max2(int a, int b)
{
  return (a > b) ? a : b; // Se a for maior que b, então retorna a. Caso contrário, retorna b
}

int altura(Arv *a)
{
  if (arv_vazia(a)) //Condição de parada: Se a árvore estiver vazia
    return -1;      //Retorna -1
  else              //Caso contrário (árvore não vazia)
    return 1 + max2(altura(a->esq), altura(a->dir));
}

//retorna a quantidade de folhas de uma árvore binaria
int folhas(Arv *a)
{
  int qnt_folhas;
  if (arv_vazia(a)) //caso base
    return 0;
  else
  {
    qnt_folhas = folhas(a->esq) + folhas(a->dir);
    qnt_folhas = (qnt_folhas == 0) ? 1 : qnt_folhas; //Se qnt_folhas for igual a zero, retorna 1. Caso contrário, retorna qnt_folhas
    return qnt_folhas;
  }
}

//retorna o número de ocorrencias de um dado aluno na árvore
int ocorrencias(Arv *a, char *nome)
{
  if (arv_vazia(a)) //caso base
    return 0;
  bool compara = (strcmp(retornaNomeAluno(a->aluno), nome) == 0) ? 1 : 0;
  return compara + ocorrencias(a->esq, nome) + ocorrencias(a->dir, nome);
}
