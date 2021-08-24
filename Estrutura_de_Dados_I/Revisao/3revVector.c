#include <stdio.h>
#include <stdlib.h> // Biblioteca padrão para alocar memória: trabalha com alocação de memória (malloc, free, realloc)

void fat(int n, double *vet); // f é um ponteiro para inteiro

int main()
{
  int n;
  int i;

  printf("Digite um valor nao negativo: ");
  scanf("%d", &n);

  //alocar um vetor vet de tamanho n
  // vai conter valores dos fatorias de números

  // alocaçãp dinâmica

  double *vet = (double *)malloc(sizeof(double) * n);
  //vet é ponteiro de double

  // o malloc recebe um parametro em bytes que é o bloco de memoria que o programador está pedindo para ser alocado

  // o vet precisa de n espaços em tamanho double
  // o operador "sizeof" retorna o número de bytes de um tipo ou de uma variável qualquer
  //logo, sizeof(double) * n dá o tamanho do bloco em bytes que precisa ser alocado
  // o malloc espera isso

  // o malloc retorna um ponteiro, o void pointer (void*), ele é o ponteiro generico do C, é um ponteiro para qualquer coisas

  //para fazer conversão de tipo para um tipo específico, usa-se a notação: (double*) malloc(...)
  //Para converter o void pointer (void*) para o tipo mais específico double pointer (double*), usou-se aquela notação

  // vet é um ponteiro para double pq ele vai conter o endereço da memória de primeira posição desse veteor
  // vet é o ponteiro q vai acessar o bloco de memória q ele acabou de alocar

  if (!vet)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }

  vet[0] = 1; // nicialização do fatorial de 1

  fat(n, vet);

  // Imprimendo o vetor

  for (i = 0; i < n; i++)
    printf("%0.2lf ", vet[i]); // lf é long flout

  free(vet); // liberando o vetor após a alocação com o malloc

  return 0;
}

//calcula o fatorial de n
void fat(int n, double *vet) // f é um int pointer (ponteiro para inteiro)
{
  int i;
  for (i = 1; i < n; i++)
    vet[i] = i * vet[i - 1];
}