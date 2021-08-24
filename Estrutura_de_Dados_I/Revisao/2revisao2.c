#include <stdio.h>

/* Ponteiros são variáveis que contém endereços de memória */

void fat(int n, int *f); // f é um ponteiro para inteiro

int main()
{
  int n;
  int *f;
  int nf = 1;
  f = &nf; // Para f apontar para nf:
  // f recebe o endereço de nf

  printf("Digite um valor nao negativo: ");
  scanf("%d", &n);

  fat(n, f);                     //DIFERENTEMENTE DA OUTRA, estou passando o ponteiro logo
  printf("Fatorial = %d\n", *f); //printa o conteúdo de f ou:
  printf("Fatorial = %d\n", nf);

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

  // Dúvida: parece que sim um diferença no tempo, parece que com ponteiros é mais rápido. Contúdo, como é feito apenas uma copia do endereço, existe alguma vantagem em relação a economia de memoria? Não me pareceu ser mais vantajoso?
}
