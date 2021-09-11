// Revisão de tipos estruturados

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct ponto
{
  //Campos: são as propriedades de uma struct
  float x;
  float y;
};

typedef struct ponto Ponto;
//Defino um tipo do usuário com o typedef, o nome desse tipo é Ponto e esse tipo é definido como um struct ponto

struct circ
{
  //Campos
  Ponto *p; // ponteiro de ponto p
  float r;
};

typedef struct circ Circulo; // Definindo um tipo do usuário

void imprimePonto(Ponto p);
void mudaPosicao(Ponto *p, float x, float y);
float distancia(Ponto *p, Ponto *q);
int interior(Circulo *c, Ponto *p);

int main()
{
  //criando um ponto - alocação estática, local (escopo local)
  Ponto p;
  // para acessar os valores:
  p.x = 10.0;
  p.y = 6.2;

  Ponto *pp; //Ponteiro para ponto
  pp = &p;   //Inicialização da variável pp que recebe o endereço de memória de p

  //(*pp).x  // Também da certo e pode ser usado
  //Conteudo de pp (*pp) Pode usar o . ou então usa-se a seta

  pp->x = 5.0;
  pp->y = 5.0;
  // A seta é para ponteiros acessarem os campos

  //Alocação dinâmica de estruturas
  //espaço é alocado na heap

  Ponto *a = (Ponto *)malloc(sizeof(Ponto));
  //Alocação do ponto a que é o endereço dessa estrutura alocada na heap
  //O ponteiro a para Ponto, recebe type cast para ponteiro de Ponto, malloc, sizeof do tamanho da estrutura
  // a está na stack e é uma variavel local
  // o conteúdo dela é um endereço que foi alocado na heap

  a->x = 4.0;
  a->y = 3.0;

  //passagem de parametro
  imprimePonto(p);

  mudaPosicao(a, 2.0, 4.0);

  imprimePonto(*a);

  //Captura de dados pelo teclado
  captura(pp);
  imprimePonto(*pp);

  //iniciando um círculo
  Circulo *c = (Circulo *)malloc(sizeof(Circulo));

  c->p = pp;
  c->r = 10.0;

  //aninhamento de estruturas
  int i = interior(c, pp);
  printf("Interior %d\n", i);

  i = interior(c, a);
  printf("Interior %d\n", i);

  a->x += 20.0;
  a->y += 20.0;

  i = interior(c, a);
  printf("Interior %d\n", i);
}

//passagem da estrutura por parâmetro

//a estrutura é copiada para pilha
void imprimePonto(Ponto p)
{
  printf("Coordenada x: %.2f e y:%.2f\n", p.x, p.y);
}

void mudaPosicao(Ponto *p, float x, float y)
{
  p->x += x;
  p->y += y;
}

void captura(Ponto *p)
{
  printf("Digte coordenada x: ");
  scanf(" %f", &p->x); // Dou o enderenço do campo x
  printf("\nDigite coordenada y: ");
  scanf(" %f", &p->y);
}

//distancia entre dois poontos
float distancia(Ponto *p, Ponto *q)
{
  float d = sqrt((q->x - p->x) * (q->x - p->x) + (q->y - p->y) * (q->y - p->y));
  return d;
}

//verifica se um ponto está dentro de um circulo
int interior(Circulo *c, Ponto *p)
{
  float d = distancia(c->p, p);
  return (d < c->r); // Se a distancia for menor que o raio, está dentro do circulo e se for maior, está fora
}