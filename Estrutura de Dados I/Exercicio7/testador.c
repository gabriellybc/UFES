#include <stdio.h>
#include "TadPilhasDuplas.h"

int main()
{
  PilhaDupla *p;
  int num[6] = {0, 1, 2, 3, 4, 5};
  Item *a, *b, *c, *d, *pop, *e, *f;
  a = &num[0];
  b = &num[1];
  c = &num[2];
  d = &num[3];
  e = &num[4];
  f = &num[5];
  p = inicPilhaDupla();
  pushPilha1(p, a);
  pushPilha1(p, c);
  pushPilha1(p, f);
  pushPilha2(p, b);
  pushPilha2(p, d);
  pushPilha2(p, e);

  //pop = popPilha1(p);
  //pop = popPilha2(p);

  imprimePilha1(p);
  imprimePilha2(p);
}
