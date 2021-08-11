#include <stdio.h>
#include "TadPilhasDuplas.h"

int main()
{
  PilhaDupla *p;
  int num[5] = {0, 1, 2, 3, 4};
  Item *a, *b, *c, *d, *pop;
  a = &num[0];
  b = &num[1];
  c = &num[2];
  d = &num[3];
  a = &num[0];
  p = inicPilhaDupla();
  pushPilha1(p, a);
  pushPilha1(p, c);
  pushPilha2(p, b);
  pushPilha2(p, d);

  pop = popPilha1(p);
  pop = popPilha2(p);

  imprimePilha1(p);
  imprimePilha2(p);
}
