#include <stdio.h>
#include <string.h>

int main()
{
  char nome[30] = "Jose da Silva"; //uma string é atribuida ao vetor
  char *p1, *p2;                   //ponteiros
  char car;
  int i;

  p1 = nome;     // atribuição de ponteiro que é o endereço do primeiro caracter "J"
  car = nome[3]; // 'e'
  car = p1[0];   // 'J'
  p2 = &nome[5]; // 'd'
  printf("%s\n", p2);

  p2 = p1;     // 'J'
  p2 = p1 + 5; // 'd'
  printf("%s\n", (p1 + 5));

  printf("%s\n", (p1 + 20));

  for (i = 0; i <= strlen(nome) - 1; i++)
  {
    //printf("%c", nome[i]);
    p2 = p1 + i;
    printf("%c", *p2); //*p2 pega o conteudo do ponteiro, ou seja, o caracter que quer
    //Mas vc não coloca o endereço no printf? NÃO!!! Não entendi Eu sei, pq NESSE CASO, o conteudo de p2 são endereços
  }
  printf("\n");
  return 0;
}