#ifndef PAGINA_H
#define PAGINA_H

#include <stdbool.h>
#include "string.h"

typedef struct pagina Pagina;

#include "lista.h"


/**
 * Estrutura de dados para uma aresta em um grafo.
 *
 * Esta estrutura representa uma aresta em um grafo, que conecta dois nós e possui um custo associado.
 *
 * - `origem`: O identificador do nó de origem da aresta (`unsigned int`).
 * - `destino`: O identificador do nó de destino da aresta (`unsigned int`).
 * - `custo`: O custo associado à aresta (`double`).
 */

Pagina *iniciar_pagina(String *nome, double pagerank, unsigned int qnt_links_saida, Lista *paginas_influenciadas, bool stop_word);

void imprimir_pagina(Pagina *pagina);

void liberar_pagina(Pagina *pagina);

void set_pagerank(Pagina *pagina, double pagerank);

void set_qnt_links_saida(Pagina *pagina, unsigned int qnt_links_saida);

double get_pagerank_por_links(Pagina *pagina);

double get_pagerank(Pagina *pagina);

bool get_stop_word(Pagina *pag);

String *get_nome_pagina(Pagina *pagina);

Lista *get_paginas_influenciadas(Pagina *pagina);

Pagina **iniciar_arrey_paginas(unsigned int tamanho);

void liberar_arrey_paginas(Pagina **paginas, unsigned int tamanho);

void inserir_pagina_influenciada(Pagina *pagina, Pagina *pag);

void atualizar_cache(Pagina *pagina);

void calcular_pagerank(Pagina **paginas, unsigned int tamanho, float alpha, double epsilon);

void ordernar_paginas(Pagina **paginas, unsigned int tamanho);

void liberar_stop_word(Pagina *pagina);

void imprimir_saida(Pagina **paginas, unsigned int size, unsigned int tamanho);

#endif