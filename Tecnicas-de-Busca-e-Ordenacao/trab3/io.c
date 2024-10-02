#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "io.h"
#include "string.h"
#include "pagina.h"
#include "tst.h"
#include "lista_listas.h"
#include "lista_string.h"

char *gerar_caminho_arquivo(const char *diretorio, const char *nome_arquivo) {
    char *caminho_arquivo;
    if (diretorio[strlen(diretorio) - 1] != '/') {
        size_t tamanho_caminho = strlen(diretorio) + strlen(nome_arquivo) + 2;
        caminho_arquivo = (char *)malloc(tamanho_caminho * sizeof(char));
        strcpy(caminho_arquivo, diretorio);
        strcat(caminho_arquivo, "/");
        strcat(caminho_arquivo, nome_arquivo);
    } else {
        size_t tamanho_caminho = strlen(diretorio) + strlen(nome_arquivo) + 1;
        caminho_arquivo = (char *)malloc(tamanho_caminho * sizeof(char));
        strcpy(caminho_arquivo, diretorio);
        strcat(caminho_arquivo, nome_arquivo);
    }
    return caminho_arquivo;
}

char *gerar_caminho_pagina(const char *diretorio, const char *nome_arquivo) {
    char *caminho_arquivo;
    if (diretorio[strlen(diretorio) - 1] != '/') {
        size_t tamanho_caminho = strlen(diretorio) + strlen(nome_arquivo) + 9;
        caminho_arquivo = (char *)malloc(tamanho_caminho * sizeof(char));
        strcpy(caminho_arquivo, diretorio);
        strcat(caminho_arquivo, "/pages/");
        strcat(caminho_arquivo, nome_arquivo);
    } else {
        size_t tamanho_caminho = strlen(diretorio) + strlen(nome_arquivo) + 8;
        caminho_arquivo = (char *)malloc(tamanho_caminho * sizeof(char));
        strcpy(caminho_arquivo, diretorio);
        strcat(caminho_arquivo, "/pages/");
        strcat(caminho_arquivo, nome_arquivo);
    }
    return caminho_arquivo;
}

TST *ler_index(const char *diretorio, Lista *lista_paginas) {
    char *caminho_arquivo = gerar_caminho_arquivo(diretorio, "index.txt");
    unsigned char *linha = NULL;
    size_t tamanho = 0;
    ssize_t nread;
    unsigned char c;
    TST *tst_paginas = NULL; // Inicializar a variável

    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        free(caminho_arquivo);
        return NULL;
    }

    while ((nread = getline((char **)&linha, &tamanho, arquivo)) != -1) {
        if (linha[nread - 1] == '\n') {
            linha[nread - 1] = '\0';
            nread--;
        }
        String *nome = iniciar_string((char *)linha, nread); 
        Lista *paginas_influenciadas = iniciar_lista();
        Pagina *pagina = iniciar_pagina(nome, 0, 0, paginas_influenciadas, 0);
        inserir_lista(lista_paginas, pagina);
        c = linha[0];
        if (tst_paginas == NULL) {
            tst_paginas = criar_no(c);
        }
        tst_paginas = insert_pagina(tst_paginas, nome, pagina);
        free(linha);
        linha = NULL;
    }
    fclose(arquivo);
    free(caminho_arquivo);
    if (linha) {
        free(linha);
    }
    return tst_paginas;
}

void ler_graph(const char *diretorio, TST *tst_paginas) {
    char *caminho_arquivo = gerar_caminho_arquivo(diretorio, "graph.txt");
    unsigned int qnt_links_saida = 0;
    unsigned char *linha = NULL;
    size_t tamanho = 0;
    ssize_t nread;
    unsigned char *token;
    String *nome, *nome_pag; 
    Pagina *pagina, *pag;
    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        free(caminho_arquivo);
        return;
    }

    while ((nread = getline((char **)&linha, &tamanho, arquivo)) != -1) {
        if (linha[nread - 1] == '\n') {
            linha[nread - 1] = '\0';
            nread--;
        }
        token = strtok((char *)linha, " ");
        nome = iniciar_string((char *)token, strlen((char *)token));
        pagina = search_pagina(tst_paginas, nome);
        token = strtok(NULL, " ");
        qnt_links_saida = atoi((char *)token);
        set_qnt_links_saida(pagina, qnt_links_saida);
        if (qnt_links_saida > 0) {
            token = strtok(NULL, " ");
            while (token != NULL) {
                nome_pag = iniciar_string((char *)token, strlen((char *)token));
                pag = search_pagina(tst_paginas, nome_pag);
                inserir_pagina_influenciada(pag, pagina);
                liberar_string(nome_pag);
                token = strtok(NULL, " ");
            }
        }
        liberar_string(nome);
        free(linha);
        linha = NULL;
    }
    fclose(arquivo);
    free(caminho_arquivo);
    if (linha) {
        free(linha);
    }
}

Lista *ler_stop_words(const char *diretorio, TST_str **arrey) {
    char *caminho_arquivo = gerar_caminho_arquivo(diretorio, "stopwords.txt");
    Lista *lista_stop_word = iniciar_lista();
    unsigned char *linha = NULL;
    unsigned char c;
    size_t tamanho = 0;
    ssize_t nread;
    String *stop_word; 
    Pagina *pagina;
    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        free(caminho_arquivo);
        return NULL;
    }

    while ((nread = getline((char **)&linha, &tamanho, arquivo)) != -1) {
        if (linha[nread - 1] == '\n') {
            linha[nread - 1] = '\0';
            nread--;
        }
        stop_word = iniciar_string((char *)linha, nread);
        pagina = iniciar_pagina(stop_word, 0, 0, iniciar_lista(), 1);
        inserir_lista(lista_stop_word, pagina);
        c = linha[0];
        if (c > 96) {
            arrey[c - 84] = insert_palavra(arrey[c - 84], stop_word, pagina);
        } else if (c < 58) {
            arrey[c - 45] = insert_palavra(arrey[c - 45], stop_word, pagina);
        } else {
            arrey[c - 52] = insert_palavra(arrey[c - 52], stop_word, pagina);
        }
        free(linha);
        linha = NULL;
    }
    fclose(arquivo);
    free(caminho_arquivo);
    if (linha) {
        free(linha);
    }
    return lista_stop_word;
}

void ler_pages(const char *diretorio, TST_str **arrey, Pagina **paginas, unsigned int size) {
    unsigned char *linha = NULL;
    unsigned char c;
    unsigned char *token;
    size_t tamanho = 0;
    ssize_t nread;
    String *palavra; 
    Pagina *pagina;
    FILE *arquivo;
    char *caminho_arquivo;
    for (unsigned int i = 0; i < size; i++) {
        pagina = paginas[i];
        caminho_arquivo = gerar_caminho_pagina(diretorio, get_string(get_nome_pagina(pagina)));
        arquivo = fopen(caminho_arquivo, "r");
        if (arquivo == NULL) {
            perror("Erro ao abrir o arquivo");
            free(caminho_arquivo);
            continue;
        }

        while ((nread = getline((char **)&linha, &tamanho, arquivo)) != -1) {
            if (linha[nread - 1] == '\n') {
                linha[nread - 1] = '\0';
                nread--;
            }
            token = strtok((char *)linha, " \t\n");
            while (token != NULL) {
                palavra = iniciar_string((char *)token, strlen((char *)token));
                c = token[0];
                if (c > 96) {
                    arrey[c - 84] = insert_palavra(arrey[c - 84], palavra, pagina);
                } else if (c < 58) {
                    arrey[c - 45] = insert_palavra(arrey[c - 45], palavra, pagina);
                } else {
                    arrey[c - 52] = insert_palavra(arrey[c - 52], palavra, pagina);
                }
                liberar_string(palavra);
                token = strtok(NULL, " \t\n");
            }
        }
        fclose(arquivo);
        free(caminho_arquivo);
    }
    if (linha) {
        free(linha);
    }
}

void ler_consulta(TST_str **arrey) {
    unsigned char *linha = NULL;
    unsigned char c;
    unsigned char *token;
    unsigned int size = 0, tam = 0;
    size_t tamanho = 0;
    ssize_t nread;
    String *palavra; 
    Lista_string *consultas;
    Lista_listas *listas;
    Lista *lista;
    Pagina **pags;
    while ((nread = getline((char **)&linha, &tamanho, stdin)) != -1) {
        consultas = iniciar_lista_string();
        listas = iniciar_lista_listas();
        if (linha[nread - 1] == '\n') {
            linha[nread - 1] = '\0';
            nread--;
        }
        token = strtok((char *)linha, " ");
        while (token != NULL) {
            palavra = iniciar_string((char *)token, strlen((char *)token));
            inserir_lista_string(consultas, palavra);
            c = token[0];
            if (c > 96) {
                lista = search_palavra(arrey[c - 84], palavra);
            } else if (c < 58) {
                lista = search_palavra(arrey[c - 45], palavra);
            } else {
                lista = search_palavra(arrey[c - 52], palavra);
            }
            if(lista != NULL){
                inserir_lista_listas(listas, lista);
            }
            token = strtok(NULL, " ");
        }
        imprimir_lista_string(consultas);
        tam = get_tamanho_lista_listas(listas);
        if(tam > 0){
            pags = listas_para_array(listas, &size);
            imprimir_saida(pags, size, tam);
            free(pags);
        }
        else {
            liberar_lista_listas(listas);
            printf("\npages:");
            printf("\npr:");
            printf("\n");
        }
    }

    if (linha) {
        free(linha);
    }
}