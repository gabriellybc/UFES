#include <stdlib.h>
#include <stdio.h>
#include "tst.h"

struct no {
    Pagina *val;
    unsigned char c;
    struct no *l, *m, *r;
};

TST *criar_no(unsigned char c) {
    TST *no = (TST *)malloc(sizeof(TST));
    no->val = NULL;
    no->c = c;
    no->l = NULL;
    no->m = NULL;
    no->r = NULL;
    return no;
}


TST *rec_insert_pagina(TST *t, String *key, Pagina *val, unsigned int d) {
    unsigned char c = get_string(key)[d];
    if (t == NULL) {
        t = criar_no(c);
    }
    if (c < t->c) {
        t->l = rec_insert_pagina(t->l, key, val, d);
    } else if (c > t->c) {
        t->r = rec_insert_pagina(t->r, key, val, d);
    } else if (d < get_len(key) - 1) {
        t->m = rec_insert_pagina(t->m, key, val, d + 1);
    } else {
        t->val = val;
    }
    return t;
}

TST *insert_pagina(TST *t, String *key, Pagina *val) {
    return rec_insert_pagina(t, key, val, 0);
}


TST *rec_search_pagina(TST *t, String *key, int d) {
    if (t == NULL) {
        return NULL;
    }
    unsigned char c = get_string(key)[d];
    if (c < t->c) {
        return rec_search_pagina(t->l, key, d);
    } else if (c > t->c) {
        return rec_search_pagina(t->r, key, d);
    } else if (d < get_len(key) - 1) {
        return rec_search_pagina(t->m, key, d + 1);
    } else {
        return t;
    }
}

Pagina *search_pagina(TST *t, String *key) {
    t = rec_search_pagina(t, key, 0);
    if (t == NULL) {
        return NULL;
    } else {
        return t->val;
    }
}


void imprimir_tst(TST *t) {
    if (t == NULL) {
        return;
    }
    imprimir_tst(t->l);
    printf("%c\n", t->c);
    imprimir_tst(t->m);
    imprimir_tst(t->r);
}



void liberar_tst(TST *t) {
    if (t == NULL) {
        return;
    }
    liberar_tst(t->l);
    liberar_tst(t->m);
    liberar_tst(t->r);
    free(t);
}