#ifndef PALAVRA_H_
#define PALAVRA_H_

// Define o tipo opaco Palavra que tambem e' uma lista para tratamento de colisao
typedef struct palavra Palavra;

Palavra *inicPalavra(char *str);

char *retornaString(Palavra *pal);

void atualizaOcorrencias(Palavra *pal);

int retornaOcorrencias(Palavra *pal);

//busca a palavra na lista de colisoes
Palavra *buscaPalavra(Palavra *pal, char *string);

//Insere a palavra na lista de colisoes
Palavra *inserePalavraLista(Palavra *lista, Palavra *p);

// Retorna o numero de palavra da lista de colisoes
int contaPalavrasLista(Palavra *p);

void imprimeLista(Palavra *p);

void liberaListaPalavra(Palavra *pal);

#endif /*PALAVRA_H_*/