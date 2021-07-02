#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *lelinha(void);

int main()
{
  int tam = 0;
  printf("Digite o tamanho da turma: ");
  scanf(" %d", &tam);

  char **turma = (char **)malloc(tam * sizeof(char *));
  //matriz com numero de colunas variaveis
  //ponteiro para ponteiro para caracter
  //char** turma
  //qual é o tipo do vetor? qual é o tipo do conteudo dele?
  //é um vetor de ponteiro para caracter. Ou seja:
  //Estrutura para matriz de strings está acima
  //Vetor de ponteiro de ponteiro de caracter

  for (int i = 0; i < tam; i++)
    turma[i] = lelinha();
  //A copia da string é um espaço dinamico na memoria e é atribuido ao vetor na posição i. Portanto,
  //turma[i] contém as strings alocadas dinamicamente, sem disperdicio de espaço

  //Imprimir nomes:
  for (int i = 0; i < tam; i++)
    printf("%s\n", turma[i]);

  //Liberar o espaço:
  for (int i = 0; i < tam; i++)
    free(turma[i]); //Free em cada uma das strings. Se eu não aloquei essas strigs pq preciso dar o free?

  free(turma); // Libero o ponteiro do vetor de strings turma

  return 0;
}

char *lelinha(void)
{
  // A função captura do teclado em uma memoria estatisca, faz a copia, retorna a copia em memoria dinamica e sai liberando a memoria estatica
  char linha[121];
  printf("Digite um nome: ");
  scanf(" %120[^\n]", linha);

  return strdup(linha);
}