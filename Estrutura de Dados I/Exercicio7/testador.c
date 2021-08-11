#include <stdio.h>
#include "TadPilhasDuplas.h"

int main()
{
  PilhaDupla *p;
  int num[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  Item *a, *b, *c, *d, *pop1, *e, *f, *g, *h, *i, *j, *k, *l, *pop2;
  a = &num[0];
  b = &num[1];
  c = &num[2];
  d = &num[3];
  e = &num[4];
  f = &num[5];
  g = &num[6];
  h = &num[7];
  i = &num[8];
  j = &num[9];
  k = &num[9];
  l = &num[9];

  p = inicPilhaDupla();

  pop1 = popPilha1(p); // pilha vazia
  pop2 = popPilha2(p); // pilha vazia

  pushPilha1(p, a);
  pushPilha1(p, c);
  pushPilha1(p, e);
  pushPilha1(p, g);
  pushPilha1(p, i);

  pushPilha2(p, b);
  pushPilha2(p, d);
  pushPilha2(p, f);
  pushPilha2(p, h);
  pushPilha2(p, j);

  pushPilha1(p, k); // pilha cheia
  pushPilha2(p, l); // pilha cheia

  imprimePilha1(p);
  imprimePilha2(p);

  pushPilha1(p, popPilha1(p));
  pushPilha2(p, popPilha2(p));

  imprimePilha1(p);
  imprimePilha2(p);

  destroiPilhaDupla(p);
}
