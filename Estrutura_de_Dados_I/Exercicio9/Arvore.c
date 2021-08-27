#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arvore.h"

#define ZERO 0
#define UM 0
#define DOIS 1
#define TRES 2

typedef struct cel Celula;

struct cel
{
  Aluno *aluno;    //campo de Aluno, mas poderia ser qualquer coisa
  struct cel *esq; // ponteiro para a esquerda
  struct cel *dir; // ponteiro para a direita
};

//sentinela
struct arv
{
  Celula *prim;  // ponteiro para o nó raiz da celula
  int qnt_maior; // quantidade de elementos no nivel de hierarquia que tiver maior numero de elesmentos
};

//Cria uma árvore vazia
Arv *arv_criavazia()
{
  Arv *arv = (Arv *)malloc(sizeof(Arv));
  arv->prim = NULL;
  arv->qnt_maior = ZERO;
  return arv;
}

// Cria uma árvore com a informação do nó raiz al, e com subárvore esquerda e e subárvore direira d
Arv *arv_cria(Aluno *al, Arv *e, Arv *d)
{
  Celula *cel = (Celula *)malloc(sizeof(Celula));
  cel->aluno = al;
  cel->esq = e->prim;
  cel->dir = d->prim;

  Arv *arv = (Arv *)malloc(sizeof(Arv));
  arv->prim = cel;
  arv->qnt_maior = e->qnt_maior + d->qnt_maior;
  return arv;
}

static bool celula_vazia(Celula *cel);

//retorna true se a árvore estiver vazia e false caso contrário
bool arv_vazia(Arv *a)
{
  return a->prim == NULL;
}

static bool celula_vazia(Celula *cel)
{
  return cel == NULL;
}

static void celula_libera(Celula *cel);

//libera o espaço de memória ocupado pela árvore a
Arv *arv_libera(Arv *a)
{
  celula_libera(a->prim);
  return NULL; //Se a árvore estiver vazia, retorna NULL
}

static void celula_libera(Celula *cel)
{
  //Se não estiver vazia, entra aqui
  if (!celula_vazia(cel)) //caso base, redução da recursão
  {
    celula_libera(cel->esq);  //chamada recursiva
    celula_libera(cel->dir);  //chamada recursiva
    destroiAluno(cel->aluno); //libera raiz
  }
}

static bool celula_pertence(Celula *cel, char *nome);

//indica a ocorrência (1) ou não (0) do Aluno com o nome informador
bool arv_pertence(Arv *a, char *nome)
{
  return celula_pertence(a->prim, nome);
}

static bool celula_pertence(Celula *cel, char *nome)
{
  if (celula_vazia(cel))
    return 0;
  return strcmp(retornaNomeAluno(cel->aluno), nome) || celula_pertence(cel->esq, nome) || celula_pertence(cel->dir, nome);
}

static void celula_imprime(Celula *cel);

//imprime as informações dos nós da árvore
void arv_imprime(Arv *a)
{
  celula_imprime(a->prim);
}

static void celula_imprime(Celula *cel)
{
  printf("<");
  if (!celula_vazia(cel))
  {
    printf("%s", retornaNomeAluno(cel->aluno));
    celula_imprime(cel->esq);
    celula_imprime(cel->dir);
  }
  printf(">");
}

static void celula_imprime_graficamente(Celula *cel, int posicao);

void arv_imprime_graficamente(Arv *a)
{
  if (!arv_vazia(a))
  {
    for (int i = 0; i < a->qnt_maior / 2; i++)
      printf("\t");
    celula_imprime_graficamente(a->prim, a->qnt_maior / 2);
  }
}

static void celula_imprime_graficamente(Celula *cel, int posicao)
{
  if (!celula_vazia(cel))
  {
    printf("%s\n", retornaNomeAluno(cel->aluno));
    for (int i = 0; i < posicao - 2; i++)
      printf("\t");
    if (!celula_vazia(cel->esq))
      printf("%s\t\t", retornaNomeAluno(cel->esq->aluno));
    if (!celula_vazia(cel->dir))
      printf("%s\n", retornaNomeAluno(cel->dir->aluno));
    celula_imprime_graficamente(cel->esq->esq, posicao - 2);
    celula_imprime_graficamente(cel->esq->dir, posicao - 2);
    celula_imprime_graficamente(cel->dir->esq, posicao + 3);
    celula_imprime_graficamente(cel->dir->dir, posicao + 3);
  }
}