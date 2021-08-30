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
  arv->qnt_maior = 0;
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
  arv->qnt_maior = ((e->qnt_maior + d->qnt_maior) > 1) ? (e->qnt_maior + d->qnt_maior) : 1;
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

/*
static void celula_imprime_graficamente(Celula *cel, int posicao, char *string);

void arv_imprime_graficamente(Arv *a)
{
  if (!arv_vazia(a))
  {
    char *local;
    celula_imprime_graficamente(a->prim, a->qnt_maior / 2, local);
  }
}

static void celula_imprime_graficamente(Celula *cel, int posicao, char *local)
{
  int i;
  if (!celula_vazia(cel))
  {
    local = (char *)malloc((posicao + strlen(retornaNomeAluno(cel->aluno)) + strlen(retornaNomeAluno(cel->esq->aluno)) + strlen(retornaNomeAluno(cel->dir->aluno)) + 7) * sizeof(char));
  }

  int i;
  if (!celula_vazia(cel))
  {
    if (!celula_vazia(cel->esq))
    {
      if (!celula_vazia(cel->dir))
      {
        char *local = (char *)malloc((posicao + strlen(retornaNomeAluno(cel->aluno)) + strlen(retornaNomeAluno(cel->esq->aluno)) + strlen(retornaNomeAluno(cel->dir->aluno)) + 7) * sizeof(char));
        strcpy(local, "\t");
        i = 0;
        while (i < posicao)
        {
          strcat(local, "\t");
          i++;
        }
        strcat(local, retornaNomeAluno(cel->aluno));
        strcat(local, "\n");
        i = 0;
        while (i < posicao - 2)
        {
          strcat(local, "\t");
          i++;
        }
        strcat(local, retornaNomeAluno(cel->esq->aluno));
        strcat(local, "\t");
        strcat(local, "\t");
        strcat(local, retornaNomeAluno(cel->dir->aluno));
        strcat(local, "\n");
        strcat(local, "\0");
        printf("%s", local);
        free(local);

        if (!celula_vazia(cel->esq->esq))
          celula_imprime_graficamente(cel->esq->esq, posicao - 2);
        if (!celula_vazia(cel->esq->dir))
          celula_imprime_graficamente(cel->esq->dir, posicao - 2);
        if (!celula_vazia(cel->dir->esq))
          celula_imprime_graficamente(cel->dir->esq, posicao + 3);
        if (!celula_vazia(cel->dir->dir))
          celula_imprime_graficamente(cel->dir->dir, posicao + 3);
        return;
      }
      else
      {
        char *local = (char *)malloc((posicao + strlen(retornaNomeAluno(cel->aluno)) + strlen(retornaNomeAluno(cel->esq->aluno)) + 4) * sizeof(char));
        strcpy(local, "\t");
        for (int i = 0; i < posicao - 1; i++)
          strcat(local, "\t");
        strcat(local, retornaNomeAluno(cel->aluno));
        strcat(local, "\n");
        for (int i = 0; i < posicao - 3; i++)
          strcat(local, "\t");
        strcat(local, retornaNomeAluno(cel->esq->aluno));
        strcat(local, "\n");
        strcat(local, "\0");
        printf("%s", local);
        free(local);

        if (!celula_vazia(cel->esq->esq))
          celula_imprime_graficamente(cel->esq->esq, posicao - 2);
        if (!celula_vazia(cel->esq->dir))
          celula_imprime_graficamente(cel->esq->dir, posicao - 2);
        return;
      }
    }
    else if (!celula_vazia(cel->dir))
    {
      char *local = (char *)malloc((posicao + strlen(retornaNomeAluno(cel->aluno)) + strlen(retornaNomeAluno(cel->dir->aluno)) + 7) * sizeof(char));
      strcpy(local, "\t");
      for (int i = 0; i < posicao - 1; i++)
        strcat(local, "\t");
      strcat(local, retornaNomeAluno(cel->aluno));
      strcat(local, "\n");
      for (int i = 0; i < posicao - 3; i++)
        strcat(local, "\t");
      strcat(local, "\t");
      strcat(local, "\t");
      strcat(local, "\t");
      strcat(local, retornaNomeAluno(cel->dir->aluno));
      strcat(local, "\n");
      strcat(local, "\0");
      printf("%s", local);
      free(local);

      if (!celula_vazia(cel->dir->esq))
        celula_imprime_graficamente(cel->dir->esq, posicao + 3);
      if (!celula_vazia(cel->dir->dir))
        celula_imprime_graficamente(cel->dir->dir, posicao + 3);
      return;
    }

    else
    {
      char *local = (char *)malloc((posicao + strlen(retornaNomeAluno(cel->aluno)) + 5) * sizeof(char));
      strcpy(local, "\t");
      i = 0;
      while (i < posicao)
      {
        strcat(local, "\t");
        i++;
      }
      strcat(local, retornaNomeAluno(cel->aluno));
      strcat(local, "\n");
      printf("%s", local);
      free(local);
      return;
    }
  }
}
*/

//Retorna a altura da árvore
int arv_altura(Arv *a);

//retorna a quantidade de folhas de uma árvore binaria
int folhas(Arv *a);

//retorna o número de ocorrencias de um dado nome de Aluno na árvore
int ocorrencias(Arv *a, char *nome);

//retorna o campo aluno de um dado nó
Aluno *aluno(Arv *a);