#include <stdlib.h>
#include <stdio.h>
#include "aresta.h"

struct aresta {
    unsigned int origem;
    unsigned int destino;
    double custo;
};

Aresta *criar_aresta(unsigned int origem, unsigned int destino, double custo) {
    Aresta *aresta = (Aresta *)malloc(sizeof(Aresta));
    aresta->origem = origem;
    aresta->destino = destino;
    aresta->custo = custo;
    return aresta;
}

Aresta **criar_arestas(unsigned int qnt_arestas) {
    Aresta **arestas = (Aresta **)malloc(qnt_arestas * sizeof(Aresta *));
    return arestas;
}

unsigned int get_origem(Aresta *aresta) {
    return aresta->origem;
}

unsigned int get_destino(Aresta *aresta) {
    return aresta->destino;
}

double get_custo(Aresta *aresta) {
    return aresta->custo;
}

void imprimir_aresta(Aresta *aresta) {
    printf("Origem: %u ", aresta->origem);
    printf("Destino: %u ", aresta->destino);
    printf("Custo: %lf\n", aresta->custo);
}


void liberar_aresta(Aresta *aresta) {
    free(aresta);
}

int comparar_por_custo(const void *a, const void *b) {
    const Aresta *aresta1 = *(const Aresta **)a;
    const Aresta *aresta2 = *(const Aresta **)b;
    if (aresta1->custo < aresta2->custo) return -1;
    if (aresta1->custo > aresta2->custo) return 1;
    return 0;
}


void ordenar_arestas_por_custo(Aresta **arestas, unsigned int tamanho) {
    qsort(arestas, tamanho, sizeof(Aresta *), comparar_por_custo);
}
