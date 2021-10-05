#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "musica.h"

//Tipo musica (tipo opaco)
struct musica
{
  char *nomeMusica;
  char *cantor;
};

//Inicializa a estrutura musica
Musica *inicializaMusica()
{
  Musica *musica = (Musica *)malloc(sizeof(Musica));
  if (!musica)
  {
    printf("** Erro: Memoria Insuficiente **\n");
    exit;
  }
  return musica;
}

//Copia um string para outra alocada dinamicamente
char *duplica(char *leitura, int tamanho)
{
  char *d = (char *)malloc((tamanho + 1) * sizeof(char));

  for (int i = 0; i < tamanho; i++)
  {
    d[i] = leitura[i];
  }
  d[tamanho] = '\0';
  return d;
}

//Modifica os campos nomeMusica e cantor de Musica
void defineMusica(Musica *musica, char *leitura)
{
  bool flagMalloc = 0;
  if (leitura[strlen(leitura) - 1] != '\n') // Se o último caractere não for o '/n'
  {
    int tamanho = strlen(leitura);
    leitura = duplica(leitura, tamanho + 1);
    leitura[tamanho] = '\n'; // Aloca outra string com o '\n' no último caractere
    flagMalloc = 1;
  }

  int i = 0, j = 0;
  char nomeMusica[1210];
  char nomeCantor[1210];
  while (leitura[i] != '-')
  {
    nomeCantor[i] = leitura[i]; // Atribui todos os caracteres até o '-' ao nomeCantor
    i++;
  }
  musica->cantor = duplica(nomeCantor, (i - 1)); // Retorna uma string alocada dinamicamente sem o ' '
  i = i + 2;
  while (leitura[i] != '\n')
  {
    nomeMusica[j] = leitura[i]; // Atribui todos os caracteres até o '\n' ao nomeMusica
    i++;
    j++;
  }
  musica->nomeMusica = duplica(nomeMusica, j); // Retorna uma string alocada dinamicamente
  if (flagMalloc)                              // Verifica se foi alocada para adicionar o '\n'
    free(leitura);
}

//Retorna o nome da musica
char *retornaNomeMusica(Musica *musica)
{
  return musica->nomeMusica;
}

//Retorna o nome do cantor ou banda da musica
char *retornaCantor(Musica *musica)
{
  return musica->cantor;
}

//Imprime a musica
void imprimeMusica(Musica *musica)
{
  printf("%s - %s", musica->cantor, musica->nomeMusica);
}

//Retorna uma string da musica no formato para o arquivoo
char *musicaParaArquivo(Musica *musica)
{
  char *linhaMusica = (char *)malloc((strlen(musica->nomeMusica) + 5 + strlen(musica->cantor)) * sizeof(char));
  // Realiza a cópia do musica->cantor para linhaMusica
  strcpy(linhaMusica, musica->cantor);
  // Realiza a concatenação do conteúdo de " - " a linhaMusica
  strcat(linhaMusica, " - ");
  // Realiza a concatenação do conteúdo de musica->nomeMusica a linhaMusica
  strcat(linhaMusica, musica->nomeMusica);
  // Realiza a concatenação do conteúdo de "\n" a linhaMusica
  strcat(linhaMusica, "\n");
  return linhaMusica;
}

//Libera memória alocada para a musica
void deletaMusica(Musica *musica)
{
  free(musica->nomeMusica);
  free(musica->cantor);
  free(musica);
}