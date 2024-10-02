#ifndef TST_STR
#define TST_STR

#include "pagina.h"
#include "lista.h"
#include "string.h"

typedef struct no_str TST_str;

TST_str *criar_no_str(unsigned char c);

TST_str *iniciar_no_str(TST_str *no_str, unsigned char c);

TST_str *rec_insert_palavra(TST_str *t, String *key, Pagina *val, unsigned int d);

TST_str *insert_palavra(TST_str *t, String *key, Pagina *val);

TST_str *rec_search_palavra(TST_str *t, String *key, int d);

Lista *search_palavra(TST_str *t, String *key);

TST_str **iniciar_arrey_tst_strs();

void imprimir_arrey_tst_strs(TST_str **arrey_tst_strs);

void imprimir_tst_str(TST_str *t);

void liberar_tst_str(TST_str *t);

void liberar_arrey_tst_strs(TST_str **arrey_tst_strs);

#endif
