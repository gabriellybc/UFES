#include <stdlib.h>
#include <stdio.h>
#include "tst_str.h"

struct no_str {
    Lista *val;
    unsigned char c;
    struct no_str *l, *m, *r;
};

TST_str *criar_no_str(unsigned char c) {
    TST_str *no_str = (TST_str *)malloc(sizeof(TST_str));
    no_str->val = NULL;
    no_str->c = c;
    no_str->l = NULL;
    no_str->m = NULL;
    no_str->r = NULL;
    return no_str;
}

TST_str *rec_insert_palavra(TST_str *t, String *key, Pagina *val, unsigned int d) {
    Pagina *pag;
    unsigned char c = get_string(key)[d];
    if (c > 64 && c < 91) {
        c += 32;
    }
    if (t == NULL) {
        t = criar_no_str(c);
    }
    if (c < t->c) {
        t->l = rec_insert_palavra(t->l, key, val, d);
    } else if (c > t->c) {
        t->r = rec_insert_palavra(t->r, key, val, d);
    } else if (d < get_len(key) - 1) {
        t->m = rec_insert_palavra(t->m, key, val, d + 1);
    } else {
        if(t->val != NULL){
            pag = get_ultima_pagina(t->val);
            if(pag != val){
                if(!get_stop_word(pag)){
                    inserir_lista_ult(t->val, val);
                }
            }
        }
        else {
            t->val = iniciar_lista();
            inserir_lista_ult(t->val, val);
        }
    }
    return t;
}

TST_str *insert_palavra(TST_str *t, String *key, Pagina *val) {
    return rec_insert_palavra(t, key, val, 0);
}

TST_str *rec_search_palavra(TST_str *t, String *key, int d) {
    Pagina *pag;
    if (t == NULL) {
        return NULL;
    }
    unsigned char c = get_string(key)[d];
    if (c > 64 && c < 91) {
        c += 32;
    }
    if (c < t->c) {
        return rec_search_palavra(t->l, key, d);
    } else if (c > t->c) {
        return rec_search_palavra(t->r, key, d);
    } else if (d < get_len(key) - 1) {
        return rec_search_palavra(t->m, key, d + 1);
    } else {
        if(t->val == NULL){
            return NULL;
        }
        pag = get_ultima_pagina(t->val);
        if(get_stop_word(pag)){
            return NULL;
        }
        return t;
    }
}

Lista *search_palavra(TST_str *t, String *key) {
    t = rec_search_palavra(t, key, 0);
    if (t == NULL) {
        return NULL;
    } else {
        return t->val;
    }
}

TST_str **iniciar_arrey_tst_strs() {
    TST_str **arrey = (TST_str **)malloc(39 * sizeof(TST_str *));
    unsigned char c = 45;
    arrey[0] = criar_no_str(c);
    for (unsigned char i = 1; i < 13; i++) {
        c = i+45;
        arrey[i] = criar_no_str(c);
    }
    for (unsigned char i = 13; i < 39; i++) {
        c = i+84;
        arrey[i] = criar_no_str(c);
    }
    return arrey;
}



void imprimir_TST_str(TST_str *t) {
    if (t == NULL) {
        return;
    }
    imprimir_TST_str(t->l);
    printf("%c\n", t->c);
    imprimir_TST_str(t->m);
    imprimir_TST_str(t->r);
}

void imprimir_arrey_tst_strs(TST_str **arrey_TST_strs){
    for (unsigned char i = 0; i < 39; i++) {
        imprimir_TST_str(arrey_TST_strs[i]);
    }
}


void liberar_TST_str(TST_str *t) {
    if (t == NULL) {
        return;
    }
    liberar_TST_str(t->l);
    liberar_TST_str(t->m);
    liberar_TST_str(t->r);
    if(t->val != NULL){
        liberar_lista(t->val);
    }
    free(t);
}

void liberar_arrey_tst_strs(TST_str **arrey_TST_strs) {
    for (unsigned char i = 0; i < 39; i++) {
        liberar_TST_str(arrey_TST_strs[i]);
    }
    free(arrey_TST_strs);
}