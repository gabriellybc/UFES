#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreC.h"
/*
#define ZERO 0
#define UM 0

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
  if (e->qnt_maior == ZERO && d->qnt_maior == ZERO)
    arv->qnt_maior = UM;
  else if (e->qnt_maior == ZERO && d->qnt_maior == UM)
    arv->qnt_maior = 1;
  else if (e->qnt_maior == UM && d->qnt_maior == ZERO)
    arv->qnt_maior = 1;
  else if (e->qnt_maior == UM && d->qnt_maior == UM)
    arv->qnt_maior = 2;
  else
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

//libera o espaço de memória ocupado pela árvore a
Arv *arv_libera(Arv *a)
{
  celula_libera(a->prim);
  return NULL; //Se a árvore estiver vazia, retorna NULL
}

static bool celula_pertence(Celula *cel, char *nome)
{
  if (celula_vazia(cel))
    return 0;
  return strcmp(retornaNomeAluno(cel->aluno), nome) || celula_pertence(cel->esq, nome) || celula_pertence(cel->dir, nome);
}

//indica a ocorrência (1) ou não (0) do Aluno com o nome informador
bool arv_pertence(Arv *a, char *nome)
{
  return celula_pertence(a->prim, nome);
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

//imprime as informações dos nós da árvore
void arv_imprime(Arv *a)
{
  celula_imprime(a->prim);
}

static int max2(int a, int b)
{
  return (a > b) ? a : b; // Se a for maior que b, então retorna a. Caso contrário, retorna b
}

static int celula_altura(Celula *cel)
{
  if (celula_vazia(cel)) //Condição de parada: Se a árvore estiver vazia
    return -1;           //Retorna -1
  else
    return 1 + max2(celula_altura(cel->esq), celula_altura(cel->dir));
}

//Retorna a altura da árvore
int arv_altura(Arv *a)
{
  return celula_altura(a->prim);
}

static int celula_folhas(Celula *cel)
{
  if (celula_vazia(cel)) //caso base
    return 0;
  int qnt_folhas;
  qnt_folhas = celula_folhas(cel->esq) + celula_folhas(cel->dir);
  qnt_folhas = (qnt_folhas == 0) ? 1 : qnt_folhas; //Se qnt_folhas for igual a zero, retorna 1. Caso contrário, retorna qnt_folhas
  return qnt_folhas;
}

//retorna a quantidade de folhas de uma árvore binaria
int folhas(Arv *a)
{
  return celula_folhas(a->prim);
}

static int celula_ocorrencias(Celula *cel, char *nome)
{
  if (celula_vazia(cel))
    return 0;
  bool compara = (strcmp(retornaNomeAluno(cel->aluno), nome) == 0) ? 1 : 0;
  return compara + celula_ocorrencias(cel->esq, nome) + celula_ocorrencias(cel->dir, nome);
}

//retorna o número de ocorrencias de um dado nome de Aluno na árvore
int ocorrencias(Arv *a, char *nome)
{
  return celula_ocorrencias(a->prim, nome);
}


static Aluno celula_aluno(Celula *cel)
{
  return cel->aluno;
}

//retorna o campo aluno de um dado nó
Aluno *aluno(Arv *a)
{
  return celula_aluno(a->prim);
}


static void celula_imprime_graficamente(Celula *cel, int posicao, char *string);

void arv_imprime_graficamente(Arv *a)
{
  if (!arv_vazia(a))
  {
    char *string;
    celula_imprime_graficamente(a->prim, a->qnt_maior / 2, string);
  }
}

static void celula_imprime_graficamente(Celula *cel, int posicao, char *string)
{
  int i;
  if (!celula_vazia(cel))
  {
    if (!celula_vazia(cel->esq))
    {
      if (!celula_vazia(cel->dir))
      {
        char *atual, *anterior;
        atual = (char *)malloc((posicao + strlen(retornaNomeAluno(cel->aluno)) + 2) * sizeof(char));
        anterior = (char *)malloc((strlen(atual) + strlen(string)) * sizeof(char));
        strcpy(anterior, string);
        strcpy(atual, "\t");
        for (int i = 0; i < posicao; i++)
          strcat(atual, "\t");
        strcat(atual, retornaNomeAluno(cel->aluno));
        strcat(atual, "\n");
        for (int i = 0; i < posicao - 2; i++)
          strcat(atual, "\t");
        strcat(atual, retornaNomeAluno(cel->esq->aluno));
        strcat(atual, "\t");
        strcat(atual, "\t");
        strcat(atual, retornaNomeAluno(cel->dir->aluno));
        strcat(atual, "\n");
        strcat(atual, "\0");
        strcat(anterior, atual);
        free(atual);

        if (!celula_vazia(cel->esq->esq))
          celula_imprime_graficamente(cel->esq->esq, posicao - 2, anterior);
        if (!celula_vazia(cel->esq->dir))
          celula_imprime_graficamente(cel->esq->dir, posicao - 2, anterior);
        if (!celula_vazia(cel->dir->esq))
          celula_imprime_graficamente(cel->dir->esq, posicao + 3, anterior);
        if (!celula_vazia(cel->dir->dir))
          celula_imprime_graficamente(cel->dir->dir, posicao + 3, anterior);
        return;
      }

      else
      {
        char *atual = (char *)malloc((posicao + strlen(retornaNomeAluno(cel->aluno)) + strlen(retornaNomeAluno(cel->esq->aluno)) + 4) * sizeof(char));
        char *anterior = (char *)malloc((strlen(atual) + strlen(string)) * sizeof(char));
        strcpy(anterior, string);
        strcpy(atual, "\t");
        for (int i = 0; i < posicao - 1; i++)
          strcat(atual, "\t");
        strcat(atual, retornaNomeAluno(cel->aluno));
        strcat(atual, "\n");
        for (int i = 0; i < posicao - 3; i++)
          strcat(atual, "\t");
        strcat(atual, retornaNomeAluno(cel->esq->aluno));
        strcat(atual, "\n");
        strcat(atual, "\0");
        strcat(anterior, atual);
        free(atual);

        if (!celula_vazia(cel->esq->esq))
          celula_imprime_graficamente(cel->esq->esq, posicao - 2, anterior);
        if (!celula_vazia(cel->esq->dir))
          celula_imprime_graficamente(cel->esq->dir, posicao - 2, anterior);
        return;
      }
    }
    else if (!celula_vazia(cel->dir))
    {
      char *atual = (char *)malloc((posicao + strlen(retornaNomeAluno(cel->aluno)) + strlen(retornaNomeAluno(cel->dir->aluno)) + 7) * sizeof(char));
      char *anterior = (char *)malloc((strlen(atual) + strlen(string)) * sizeof(char));
      strcpy(anterior, string);
      strcpy(atual, "\t");
      for (int i = 0; i < posicao - 1; i++)
        strcat(atual, "\t");
      strcat(atual, retornaNomeAluno(cel->aluno));
      strcat(atual, "\n");
      for (int i = 0; i < posicao - 3; i++)
        strcat(atual, "\t");
      strcat(atual, "\t");
      strcat(atual, "\t");
      strcat(atual, "\t");
      strcat(atual, retornaNomeAluno(cel->dir->aluno));
      strcat(atual, "\n");
      strcat(atual, "\0");
      strcat(anterior, atual);
      free(atual);

      if (!celula_vazia(cel->dir->esq))
        celula_imprime_graficamente(cel->dir->esq, posicao + 3, anterior);
      if (!celula_vazia(cel->dir->dir))
        celula_imprime_graficamente(cel->dir->dir, posicao + 3, anterior);
      return;
    }
  }
  else
  {
    char *atual = (char *)malloc((posicao + strlen(retornaNomeAluno(cel->aluno)) + 5) * sizeof(char));
    char *anterior = (char *)malloc((strlen(atual) + strlen(string)) * sizeof(char));
    strcpy(anterior, string);
    strcpy(atual, "\t");
    i = 0;
    while (i < posicao)
    {
      strcat(atual, "\t");
      i++;
    }
    strcat(atual, retornaNomeAluno(cel->aluno));
    strcat(atual, "\n");
    strcat(anterior, atual);
    free(atual);
    return;
  }
  printf("%s", string);
}


static void celula_imprime_graficamente(Celula *cel, int posicao, char *atual)
{
  int i;
  if (!celula_vazia(cel))
  {
    if (!celula_vazia(cel->esq))
    {
      if (!celula_vazia(cel->dir))
      {
        char *atual = (char *)malloc((posicao + strlen(retornaNomeAluno(cel->aluno)) + strlen(retornaNomeAluno(cel->esq->aluno)) + strlen(retornaNomeAluno(cel->dir->aluno)) + 7) * sizeof(char));
        strcpy(atual, "\t");
        i = 0;
        while (i < posicao)
        {
          strcat(atual, "\t");
          i++;
        }
        strcat(atual, retornaNomeAluno(cel->aluno));
        strcat(atual, "\n");
        i = 0;
        while (i < posicao - 2)
        {
          strcat(atual, "\t");
          i++;
        }
        strcat(atual, retornaNomeAluno(cel->esq->aluno));
        strcat(atual, "\t");
        strcat(atual, "\t");
        strcat(atual, retornaNomeAluno(cel->dir->aluno));
        strcat(atual, "\n");
        strcat(atual, "\0");

        if (!celula_vazia(cel->esq->esq))
          celula_imprime_graficamente(cel->esq->esq, posicao - 2, atual);
        if (!celula_vazia(cel->esq->dir))
          celula_imprime_graficamente(cel->esq->dir, posicao - 2, atual);
        if (!celula_vazia(cel->dir->esq))
          celula_imprime_graficamente(cel->dir->esq, posicao + 3, atual);
        if (!celula_vazia(cel->dir->dir))
          celula_imprime_graficamente(cel->dir->dir, posicao + 3, atual);
        return;
      }
      else
      {
        char *atual = (char *)malloc((posicao + strlen(retornaNomeAluno(cel->aluno)) + strlen(retornaNomeAluno(cel->esq->aluno)) + 4) * sizeof(char));
        strcpy(atual, "\t");
        for (int i = 0; i < posicao - 1; i++)
          strcat(atual, "\t");
        strcat(atual, retornaNomeAluno(cel->aluno));
        strcat(atual, "\n");
        for (int i = 0; i < posicao - 3; i++)
          strcat(atual, "\t");
        strcat(atual, retornaNomeAluno(cel->esq->aluno));
        strcat(atual, "\n");
        strcat(atual, "\0");

        if (!celula_vazia(cel->esq->esq))
          celula_imprime_graficamente(cel->esq->esq, posicao - 2, atual);
        if (!celula_vazia(cel->esq->dir))
          celula_imprime_graficamente(cel->esq->dir, posicao - 2, atual);
        return;
      }
    }
    else if (!celula_vazia(cel->dir))
    {
      char *atual = (char *)malloc((posicao + strlen(retornaNomeAluno(cel->aluno)) + strlen(retornaNomeAluno(cel->dir->aluno)) + 7) * sizeof(char));
      strcpy(atual, "\t");
      for (int i = 0; i < posicao - 1; i++)
        strcat(atual, "\t");
      strcat(atual, retornaNomeAluno(cel->aluno));
      strcat(atual, "\n");
      for (int i = 0; i < posicao - 3; i++)
        strcat(atual, "\t");
      strcat(atual, "\t");
      strcat(atual, "\t");
      strcat(atual, "\t");
      strcat(atual, retornaNomeAluno(cel->dir->aluno));
      strcat(atual, "\n");
      strcat(atual, "\0");

      if (!celula_vazia(cel->dir->esq))
        celula_imprime_graficamente(cel->dir->esq, posicao + 3, atual);
      if (!celula_vazia(cel->dir->dir))
        celula_imprime_graficamente(cel->dir->dir, posicao + 3, atual);
      return;
    }

    else
    {
      char *atual = (char *)malloc((posicao + strlen(retornaNomeAluno(cel->aluno)) + 5) * sizeof(char));
      strcpy(atual, "\t");
      i = 0;
      while (i < posicao)
      {
        strcat(atual, "\t");
        i++;
      }
      strcat(atual, retornaNomeAluno(cel->aluno));
      strcat(atual, "\n");
      return;
    }
    printf("%s", atual);
    free(atual);
  }
}
*/