#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arquivo.h"

Grafo *ler_entrada(char *nome_arquivo) {
    unsigned int qnt_nos = 0, qnt_arestas = 0, qnt_servidores = 0, qnt_clientes = 0, qnt_monitores = 0;
    FILE *arquivo = fopen(nome_arquivo, "r");
    fscanf(arquivo, "%u %u", &qnt_nos, &qnt_arestas);
    fscanf(arquivo, "%u %u %u", &qnt_servidores, &qnt_clientes, &qnt_monitores);
    Grafo *grafo = criar_grafo(qnt_nos, qnt_arestas, qnt_servidores, qnt_clientes, qnt_monitores);
    unsigned int *servidores = get_servidores(grafo);
    for (unsigned int i = 1; i <= qnt_servidores; i++) {
        fscanf(arquivo, "%u", &servidores[i]);
    }
    unsigned int *clientes = get_clientes(grafo);
    for (unsigned int i = 1; i <= qnt_clientes; i++) {
        fscanf(arquivo, "%u", &clientes[i]);
    }
    unsigned int *monitores = get_monitores(grafo);
    for (unsigned int i = 1; i <= qnt_monitores; i++) {
        fscanf(arquivo, "%u", &monitores[i]);
    }
    No **nos = get_nos(grafo);
    Aresta **arestas = get_arestas(grafo);
    for (unsigned int i = 0; i < qnt_arestas; i++) {
        unsigned int origem, destino;
        double custo;
        fscanf(arquivo, "%u %u %lf", &origem, &destino, &custo);
        arestas[i] = criar_aresta(origem, destino, custo);
        if (!nos[origem]) {
            nos[origem] = criar_no(origem);
        }
    }
    fclose(arquivo);
    return grafo;
}


void imprimir_saida(char *nome_arquivo, Aresta **inflacoes_rtt, unsigned int tamanho_inflacoes_rtt) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    for (unsigned int i = 0; i < tamanho_inflacoes_rtt; i++) {
        fprintf(arquivo, "%u %u %.16lf\n", get_origem(inflacoes_rtt[i]), get_destino(inflacoes_rtt[i]), get_custo(inflacoes_rtt[i]));
    }
    fclose(arquivo);
}