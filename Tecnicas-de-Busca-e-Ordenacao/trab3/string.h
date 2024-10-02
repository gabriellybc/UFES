#ifndef STRING_H
#define STRING_H

typedef struct string String;

String *iniciar_string(unsigned char *c, unsigned int len);

char *get_string(String *s);

unsigned int get_len(String *s);

void imprimir_string(String *s);

void liberar_string(String *s);

#endif
