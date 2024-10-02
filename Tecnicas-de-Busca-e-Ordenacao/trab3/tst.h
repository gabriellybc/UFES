#ifndef TST_H
#define TST_H

#include "pagina.h"
#include "string.h"

typedef struct no TST;

TST *criar_no(unsigned char c);

TST *iniciar_no(TST *no, unsigned char c);

TST *rec_insert_pagina(TST *t, String *key, Pagina *val, unsigned int d);

TST *insert_pagina(TST *t, String *key, Pagina *val);

TST *rec_search_pagina(TST *t, String *key, int d);

Pagina *search_pagina(TST *t, String *key);

void imprimir_tst(TST *t);

void liberar_tst(TST *t);

#endif
