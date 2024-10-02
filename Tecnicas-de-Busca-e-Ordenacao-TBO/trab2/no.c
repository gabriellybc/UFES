#include <stdlib.h>
#include <stdio.h>
#include "no.h"

struct no {
    unsigned int id;
    double value;
};

No *criar_no(unsigned int id) {
    No *no = (No *)malloc(sizeof(No));
    no->id = id;
    no->value = 0.0;
    return no;
}

No **criar_vetor_no(unsigned int n) {
    No **vetor = (No **)malloc(n * sizeof(No *));
    for (int i = 0; i < n; i++) {
        vetor[i] = NULL;
    }
    return vetor;
}

unsigned int id(No *no) {
    return no->id;
}

void value(No *no, double val) {
    no->value = val;
}

double get_value(No *no) {
    return no->value;
}

int more(No *a, No *b) {
    return a->value > b->value;
}

void exch(No **a, No **b) {
    No *t = *a;
    *a = *b;
    *b = t;
}

void imprimir_no(No *no) {
    printf("Id: %u ", no->id);
    printf("Value: %lf\n", no->value);
}

void liberar_no(No *no) {
    free(no);
}