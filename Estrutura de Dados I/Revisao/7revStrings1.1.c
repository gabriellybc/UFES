#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  //Algumas funções da biblioteca string.h
  //strlen: número de caracteres sem o '\0'

  char *teste = "teste strlen";                                            // com aspas duplas o '\0' já é colocado automaticamente
  printf("\n Numero de caracteres na string teste: %lu\n", strlen(teste)); // é quantidade de caracteres, então começa a contar do 1 e não considera o '/0'

  //strcpy: copia string origem para string destino (ambas alocadas)

  //Primeiro alocamos destino
  char *destino = (char *)malloc((strlen(teste) + 1) * sizeof(char));
  //alocação dinamica:
  //destino recebe char pointer malloc (função para alocar)
  //alocando na exata quantidade de biets necessários (strlen+1) +1 é o espaço para o '/0'
  //multiplicado por sizeof(char)

  //depois podemos copiar
  strcpy(destino, teste);

  printf("String destino: %s\n", destino);

  //liberando destino
  free(destino);

  //strdup: aloca e copia string origem para uma string destino
  destino = strdup(teste);

  printf("String destino depois do dup: %s\n", destino);

  //strcmp: compara strings S1 e S2. Se forem iguais, retorna 0
  // se S1 preceder S2: retorna valores negativos
  // se S2 preceder S1: retorna valores positivos

  if (!strcmp(destino, teste))
    printf("Destino e teste são iguais\n");
  else
  {
    printf("Destino e testes são diferentes\n");
  }

  char str[] = "ola";

  //agora uma string diferente
  int r = strcmp(str, destino);
  if (!r)
    printf("Destino e str sao iguais\n");
  else
  {
    printf("Destino e str sao diferentes\n");
    printf("Valor e strcmp: %d\n", r);
  }

  return 0;
}