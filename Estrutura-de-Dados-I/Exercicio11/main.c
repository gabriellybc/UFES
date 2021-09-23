#include <stdio.h>
#include "hash.h"
#include <ctype.h> //biblioteca p/ a funcao isalpha
#define NPAL 65
#define NTAB 127

int lePalavra(FILE *fp, char *s)
{
  int i = 0;
  int c;

  //pula carac que nao sao letras
  while ((c = fgetc(fp)) != EOF)
  {
    if (isalpha(c))
      break;
  }
  if (c == EOF)
    return 0;
  else
    s[i++] = c;

  while ((i < NPAL - 1) && (c = fgetc(fp)) != EOF && isalpha(c))
    s[i++] = c;

  s[i] = '\0';
  return i;
}

int main(int argc, char const *argv[])
{
  FILE *fp;
  Hash *tab;
  char s[NPAL];

  if (argc != 2)
  {
    printf("Arquivo nao encontrado!\n");
    return 0;
  }

  fp = fopen(argv[1], "rt");
  if (fp == NULL)
  {
    printf("Erro na abertura do Arquivo!\n");
    return 0;
  }

  tab = inicHash(NTAB);

  while (lePalavra(fp, s))
  {
    Palavra *p = acessa(tab, s);
    //incrementa a ocorrencia de palavra
    atualizaOcorrencias(p);
  }

  //Imprimindo a tabela
  imprimeHash(tab);

  //Liberando espaço alocado
  liberaHash(tab);

  fclose(fp);

  return 0;
}
