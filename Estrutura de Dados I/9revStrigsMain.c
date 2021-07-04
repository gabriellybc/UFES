#include <stdio.h>

int main(int argc, char **argv)
{
  //argc é o número de argumentos que vc tá pasando
  // o nome do progama sendo executado é o primeiro parametro, então sempre temos 1+ argumentos em argc, pq ele já é 1

  //argv é um char pointer pointer, é um vetor para strings, onde cada string vai ser um dos parametros que vc passou.
  //argv[0] é o nome do programa sendo executado

  //Trabalhando com argc e argv
  //argc é o número de parametros
  //argv é um vetor de strings. Cada posição do vetor contém um argumento. O primeiro é o nome do programa

  printf("argv[0] %s\n", argv[0]); // Mostra o nome do programa que está sendo rodado

  return 0;
}