/* Gabrielly Cariman        Data:29/06/2021
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// (2.1)
/*
void calc_esfera(float r, float *area, float *volume);

int main()
{
  float r = 0, area = 0, volume = 0;
  printf("Informe o raio: ");
  scanf(" %f", &r);

  calc_esfera(r, &area, &volume);
  printf("Area da superficie = %0.2f \nVolume = %0.2f\n", area, volume);

  return 0;
}

void calc_esfera(float r, float *area, float *volume)
{
  *area = 4 * M_PI * r * r;
  *volume = (4 * M_PI * r * r * r) / 3;
}
*/

//  (2.2)
/*
int raizes(float a, float b, float c, float *x1, float *x2);

int main()
{
  float a = 0, b = 0, c = 0, x1 = 0, x2 = 0;

  printf("Informe o valor de a: ");
  scanf("%f", &a);
  printf("Informe o valor de b: ");
  scanf("%f", &b);
  printf("Informe o valor de c: ");
  scanf("%f", &c);

  if (raizes(a, b, c, &x1, &x2))
    printf("Raiz 1 = %0.2f\nRaiz 2 = %0.2f\n", x1, x2);

  else
    printf("Delta > 0, portanto a equacao nao tem raizes reais.\n");
}

int raizes(float a, float b, float c, float *x1, float *x2)
{
  float delta = (b * b) - (4 * a * c);
  if (delta >= 0)
  {
    *x1 = ((-b) + sqrt(delta)) / (2 * a);
    *x2 = ((-b) - sqrt(delta)) / (2 * a);
    return 1;
  }
  else
    return 0;
}
*/

// (2.3)
/*
int pares(int n, int *vet);

int main()
{
  int n = 0;
  printf("Informe o tamanho do vetor: ");
  scanf(" %d", &n);

  int *vet = (int *)malloc(sizeof(int) * n);
  if (!vet)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }

  for (int i = 0; i < n; i++)
  {
    printf("Informe um valor inteiro: ");
    scanf(" %d", &vet[i]);
  }

  printf("\nQuantidade de numeros pares: %d\n", pares(n, vet));

  free(vet);

  return 0;
}

int pares(int n, int *vet)
{
  int numPares = 0;
  for (int i = 0; i < n; i++)
  {
    if (vet[i] % 2 == 0)
    {
      numPares++;
    }
  }
  return numPares;
}
*/

//  (2.4)
/*
void inverte(int n, int *vet);

int main()
{
  int n = 0, i;
  printf("Informe o tamanho do vetor: ");
  scanf(" %d", &n);

  int *vet = (int *)malloc(sizeof(int) * n);
  if (!vet)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }

  for (i = 0; i < n; i++)
  {
    printf("Informe um valor inteiro: ");
    scanf(" %d", &vet[i]);
  }

  inverte(n, vet);
  printf("Vetor invertido: ");
  for (i = 0; i < n; i++)
  {
    printf("\n%d\t", vet[i]);
  }

  free(vet);

  return 0;
}

void inverte(int n, int *vet)
{
  int i, temporaria;
  for (i = 0; (int)(i < n / 2); i++)
  {
    temporaria = vet[i];
    vet[i] = vet[n - 1 - i];
    vet[n - 1 - i] = temporaria;
  }
}
*/

//  (2.5)

double avalia(double *poli, int grau, double x);

int main()
{
  int grau = 0, i;
  double x = 0, polinomio = 0;

  printf("Informe o grau do polinomio: ");
  scanf(" %d", &grau);

  printf("Informe o valor da variavel x: ");
  scanf(" %lf", &x);

  double *poli = (double *)malloc(sizeof(double) * (grau + 1));
  if (!poli)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }

  for (i = 0; i <= grau; i++)
  {
    printf("Informe o valor do coeficiente de x^%d: ", grau - i);
    scanf(" %lf", &poli[i]);
  }

  polinomio = avalia(poli, grau, x);
  printf("\nValor do polinomio: %0.2lf\n", polinomio);
  free(poli);
  return 0;
}

double avalia(double *poli, int grau, double x)
{
  double polinomio = 0;
  for (int i = grau; i >= 0; i--)
    polinomio += poli[i] * pow(x, (grau - i));

  return polinomio;
}
