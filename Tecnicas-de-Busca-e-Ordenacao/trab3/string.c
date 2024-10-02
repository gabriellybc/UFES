#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "string.h"

struct string {
    unsigned char *c;
    unsigned int len;
};

String *iniciar_string(unsigned char *c, unsigned int len) {
    String *s = (String *)malloc(sizeof(String));
    s->c = strdup(c);
    s->len = len;
    return s;
}

char *get_string(String *s) {
    return s->c;
}

unsigned int get_len(String *s) {
    return s->len;
}

void imprimir_string(String *s) {
    printf("%s", s->c);
    printf(" - %u\n", s->len);
}

void liberar_string(String *s) {
    free(s->c);
    free(s);
}
