/*No arquivo aula1_1.c: Elabore um programa que declare 4 variáveis do tipo inteiro e 4 do
tipo ponteiro para inteiro e faça com que as variáveis ponteiro apontem para as variáveis
do tipo inteiro. Coloque comandos que permitam modificar os valores das variáveis inteiras
através das variáveis ponteiro. Faça a simulação passo-a-passo para visualizar o que está
acontecendo em cada linha do programa.

Nome: Gabrielly Cariman         Data:23/06/2021
*/

#include <stdio.h>

int main()
{
  // Declarando 4 variáveis do tipo inteiro:
  int variavel1 = 0, variavel2 = 0, variavel3 = 0, variavel4 = 0;

  // Declarando 4 ponteiros para inteiro:
  int *ponteiro1, *ponteiro2, *ponteiro3, *ponteiro4;

  // Apontando para variáveis do tipo inteiro:
  ponteiro1 = &variavel1; // ponteiro1 recebe o endereço de variavel1
  ponteiro2 = &variavel2; // ponteiro2 recebe o endereço de variavel2
  ponteiro3 = &variavel3; // ponteiro3 recebe o endereço de variavel3
  ponteiro4 = &variavel4; // ponteiro4 recebe o endereço de variavel4

  printf("\nDigite o valor de variavel1: ");
  scanf("%d", &variavel1);
  printf("Digite o valor de variavel2: ");
  scanf("%d", &variavel2);
  printf("Digite o valor de variavel3: ");
  scanf("%d", &variavel3);
  printf("Digite o valor de variavel4: ");
  scanf("%d", &variavel4);
  printf("variavel1 = %d | variavel2 = %d | variavel3 = %d | variavel4 = %d\n", variavel1, variavel2, variavel3, variavel4);
  printf("==|Alterando o valor das variaveis utilizando ponteiros|==");

  // Comandos que modificam os valores das variáveis inteiras através das variáveis ponteiro:
  printf("\nInforme o primeiro valor inteiro: ");
  scanf(" %d", ponteiro1);

  printf("\nInforme o segundo valor inteiro: ");
  scanf(" %d", ponteiro2);

  printf("\nInforme o terceiro valor inteiro: ");
  scanf(" %d", ponteiro3);

  printf("\nInforme o quarto valor inteiro: ");
  scanf(" %d", ponteiro4);

  printf("\nvariavel1 = %d\n", variavel1);
  printf("variavel2 = %d\n", variavel2);
  printf("variavel3 = %d\n", variavel3);
  printf("variavel4 = %d\n", variavel4);

  return 0;
}