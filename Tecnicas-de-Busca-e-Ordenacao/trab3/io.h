#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "tst.h"
#include "tst_str.h"
#include "lista.h"

char *gerar_caminho_arquivo(const char *diretorio, const char *nome_arquivo);

TST *ler_index(const char *diretorio, Lista *lista_paginas);

void ler_graph(const char *diretorio, TST *tst_paginas);

Lista *ler_stop_words(const char *diretorio, TST_str **arrey);

void ler_pages(const char *diretorio, TST_str **arrey, Pagina **paginas, unsigned int tamanho);

void ler_consulta(TST_str **arrey);

#endif