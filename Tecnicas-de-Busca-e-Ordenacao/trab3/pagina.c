#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include "pagina.h"

struct pagina {
    String *nome;
    double pagerank;
    unsigned int  qnt_links_saida;
    Lista *paginas_influenciadas;
    double pagerank_por_links;
    bool atualizado;
    bool stop_word;
};

Pagina *iniciar_pagina(String *nome, double pagerank, unsigned int qnt_links_saida, Lista *paginas_influenciadas, bool stop_word) {
    Pagina *pagina = (Pagina *)malloc(sizeof(Pagina));
    pagina->nome = nome;
    pagina->pagerank = pagerank;
    pagina->qnt_links_saida = qnt_links_saida;
    pagina->paginas_influenciadas = paginas_influenciadas;
    pagina->pagerank_por_links = 0.0;
    pagina->atualizado = false;
    pagina->stop_word = stop_word;
    return pagina;
}

void imprimir_pagina(Pagina *pagina) {
    printf("Nome: ");
    imprimir_string(pagina->nome);
    printf("Pagerank: %f\n", pagina->pagerank);
    printf("Quantidade de links de saída: %u\n", pagina->qnt_links_saida);
}


void liberar_pagina(Pagina *pagina) {
    liberar_string(pagina->nome);
    liberar_lista(pagina->paginas_influenciadas);
    free(pagina);
}

void liberar_stop_word(Pagina *pagina) {
    free(pagina);
}

void set_pagerank(Pagina *pagina, double pagerank) {
    pagina->pagerank = pagerank;
}

void set_qnt_links_saida(Pagina *pagina, unsigned int qnt_links_saida) {
    pagina->qnt_links_saida = qnt_links_saida;
}

double get_pagerank_por_links(Pagina *pagina){
    return pagina->pagerank_por_links;
}

double get_pagerank(Pagina *pagina){
    return pagina->pagerank;
}

bool get_stop_word(Pagina *pag){
    return pag->stop_word;
}

String *get_nome_pagina(Pagina *pagina) {
    return pagina->nome;
}

Lista *get_paginas_influenciadas(Pagina *pagina) {
    return pagina->paginas_influenciadas;
}

Pagina **iniciar_arrey_paginas(unsigned int tamanho) {
    return (Pagina **)malloc(sizeof(Pagina *) * tamanho);
}

void liberar_arrey_paginas(Pagina **paginas, unsigned int tamanho) {
    for (unsigned int i = 0; i < tamanho; i++) {
        liberar_pagina(paginas[i]);
    }
    free(paginas);
}

void inserir_pagina_influenciada(Pagina *pagina, Pagina *pag) {
    inserir_lista(pagina->paginas_influenciadas, pag);
}

void atualizar_cache(Pagina *pagina) {
    if (!pagina->atualizado && pagina->qnt_links_saida > 0) {
        pagina->pagerank_por_links = pagina->pagerank / pagina->qnt_links_saida;
        pagina->atualizado = true;
    }
}

void calcular_pagerank(Pagina **paginas, unsigned int tamanho, float alpha, double epsilon) {
    double *novos_pageranks = (double *)malloc(tamanho * sizeof(double));  // Armazena novos valores de PageRank
    bool convergiu = false;
    double pagerank_anterior, soma_diferenca = 0.0;
    double div_alpha = (1 - alpha) / tamanho;
    Lista *paginas_influenciadas;

    while (!convergiu) {
        soma_diferenca = 0.0;
        for (unsigned int i = 0; i < tamanho; i++) {
            pagerank_anterior = paginas[i]->pagerank;
            paginas_influenciadas = paginas[i]->paginas_influenciadas;
            
            if (paginas[i]->qnt_links_saida != 0) {
                novos_pageranks[i] = div_alpha + (alpha * lista_pagerank(paginas_influenciadas));
            } else {
                novos_pageranks[i] = div_alpha + (alpha * pagerank_anterior) + (alpha * lista_pagerank(paginas_influenciadas));
            }
            soma_diferenca += fabs(novos_pageranks[i] - pagerank_anterior);
        }
        if (soma_diferenca < epsilon * tamanho) {  // Se a diferença média for pequena o suficiente, convergiu
            convergiu = true;
        }

        // Atualiza os valores antigos de PageRank
        for (unsigned int i = 0; i < tamanho; i++) {
            paginas[i]->pagerank = novos_pageranks[i];
            paginas[i]->atualizado = false;
        }
    }

    free(novos_pageranks);  // Libera memória alocada
}


int comparar_paginas(const void *a, const void *b) {
    // O casting correto para acessar as páginas
    Pagina *pag1 = *(Pagina **)a;
    Pagina *pag2 = *(Pagina **)b;

    // Comparar PageRank de forma decrescente
    if (pag1->pagerank > pag2->pagerank) {
        return -1;
    } else if (pag1->pagerank < pag2->pagerank) {
        return 1;
    } else {
        // Em caso de empate no PageRank, comparar os nomes de forma crescente
        return strcmp(get_string(pag1->nome), get_string(pag2->nome));
    }
}


void ordernar_paginas(Pagina **paginas, unsigned int tamanho) {
    qsort(paginas, tamanho, sizeof(Pagina *), comparar_paginas);
}


void imprimir_saida(Pagina **paginas, unsigned int tamanho, unsigned int tamanho_max){
    Lista *lista = iniciar_lista();
    Pagina *pag;
    char *s1, *s2, *s3;
    unsigned int rept = 1;
    if (tamanho_max > 1){
        ordernar_paginas(paginas, tamanho);
        s1 = get_string(paginas[0]->nome);
        for(unsigned int i = 1; i < tamanho; i++){
            s2 = get_string(paginas[i]->nome);
            if(strcmp(s1, s2) == 0){
                rept++;
                if(rept >= tamanho_max){
                    if(get_tamanho_lista(lista) > 0) {
                        pag = get_ultima_pagina(lista);
                        s3 = get_string(get_nome_pagina(pag));
                        if(strcmp(s3, s2) != 0) {
                            inserir_lista_ult(lista, paginas[i]);
                        }
                    }
                    else {
                        inserir_lista_ult(lista, paginas[i]);
                    }
                    rept = 1;
                }
            } else {
                rept = 1;
            }
            s1 = s2;
        }
    }
    else {
        for(unsigned int i = 0; i < tamanho; i++){
            inserir_lista_ult(lista, paginas[i]);
        }
    }
    imprimir_lista_saida(lista);
}