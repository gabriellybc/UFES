#include <stdio.h>

/* Ponteiros são variáveis que contém endereços de memória */

void fat(int n, int *f); // f é um ponteiro para inteiro

int main()
{
  int n, f = 1;

  printf("Digite um valor nao negativo: ");
  scanf("%d", &n);

  fat(n, &f); //o "endereço da variável f" (&f) é um ponteiro.
  //Para passar o valor ponteiro, tendo o f conteudo, é preciso passar o endereço de f
  printf("Fatorial = %d\n", f);

  return 0;
}

//calcula o fatorial de n
void fat(int n, int *f) // f é um int pointer (ponteiro para inteiro)
// a variável final é um ponteiro
{
  int i;
  for (i = 1; i <= n; i++)
    (*f) *= i; // f = f*1
  // O operador conteúdo de f (*f) retorna o conteúdo final da variável f que é do tipo ponteiro

  // usando o operador conteudo de f em um ponteiro pra inteiro , o retorno é o inteiro que está sendo apontado pelo ponteiro
}
