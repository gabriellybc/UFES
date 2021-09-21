#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"

struct arv
{
  Aluno *info;     //campo de Aluno, mas poderia ser qualquer coisa
  struct arv *esq; // ponteiro para a esquerda
  struct arv *dir; // ponteiro para a direita
};

// Cria uma árvore vazia
Arv *abb_cria()
{
  return NULL;
}

//indica se uma árvore é ou não vazia
bool abb_vazia(Arv *a)
{
  return a == NULL; //Se a raiz for nula, então ela é vazia
}

//percorre recursivamente a árvore, visitando todos os nós e imprimindo sua informação
void abb_imprime(Arv *a)
{
  if (!abb_vazia(a))
  {
    abb_imprime(a->esq);   //mostra sae
    imprimeAluno(a->info); //mostra raiz
    abb_imprime(a->dir);   //mostra sad
  }
}

// Se encontrar, retorna o nó que contém o aluno
// Se não encontrar, retorna NULL
Arv *abb_busca(Arv *r, int chave)
{
  if (abb_vazia(r))
    return NULL;
  else if (retornaMat(r->info) > chave)
    return abb_busca(r->esq, chave);
  else if (retornaMat(r->info) < chave)
    return abb_busca(r->dir, chave);
  else
    return r;
}

// Insere sempre como folha da arvore
Arv *abb_insere(Arv *a, Aluno *al)
{
  if (abb_vazia(a))
  {
    a = (Arv *)malloc(sizeof(Arv));
    a->info = al;
    a->esq = a->dir = NULL;
  }
  // procura onde inserir
  else if (retornaMat(al) < retornaMat(a->info))
    a->esq = abb_insere(a->esq, al);
  else
    a->dir = abb_insere(a->dir, al);
  return a;
}

Arv *abb_retira(Arv *r, int v)
{
  if (abb_vazia(r))
    return NULL;
  else if (retornaMat(r->info) > v)
    r->esq = abb_retira(r->esq, v);
  else if (retornaMat(r->info) < v)
    r->dir = abb_retira(r->dir, v);
  // se achou
  else
  {
    // se e' no folha
    if (r->esq == NULL && r->dir == NULL)
    {
      free(r);
      r = NULL;
    }

    // no' so tem filho a direita
    else if (r->esq == NULL)
    {
      Arv *t = r;
      r = r->dir;
      free(t);
    }
    // no' so tem filho a esquerda
    else if (r->dir == NULL)
    {
      Arv *t = r;
      r = r->esq;
      free(t);
    }
    // no tem os dois filhos
    else
    {
      //acha o antecessor do no
      Arv *f = r->esq;
      while (f->dir != NULL)
        f = f->dir;
      //faz a troca de informações
      Aluno *t = r->info;
      r->info = f->info;
      f->info = t;
      r->esq = abb_retira(r->esq, v);
    }
  }
  return r;
}

//libera o espaço de memória ocupado pela árvore a
Arv *abb_libera(Arv *a)
{
  //Se a árvore não estiver vazia, entra aqui
  if (!abb_vazia(a)) //Caso base: árvore estar vazia
  {
    //Chamando recursivamente para sae
    abb_libera(a->esq); //libera sae
    //Chamando recursivamente para sad
    abb_libera(a->dir); //libera sad
    free(a);            //libera raiz
  }
  return NULL; //Se a árvore estiver vazia, retorna NULL
}