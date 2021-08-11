#ifndef TadPilhasDuplas_H_
#define TadPilhasDuplas_H_

typedef int Item;

typedef struct pilhadupla PilhaDupla;

PilhaDupla *inicPilhaDupla(void);

void pushPilha1(PilhaDupla *p, Item *item);

void pushPilha2(PilhaDupla *p, Item *item);

Item *popPilha1(PilhaDupla *p);

Item *popPilha2(PilhaDupla *p);

void imprimePilha1(PilhaDupla *p);

void imprimePilha2(PilhaDupla *p);

void destroiPilhaDupla(PilhaDupla *p);

#endif