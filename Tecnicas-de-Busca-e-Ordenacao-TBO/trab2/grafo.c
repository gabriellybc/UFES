#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include "grafo.h"
#include "PQ.h"

struct grafo {
    unsigned int qnt_nos;
    unsigned int qnt_arestas;
    No **nos;
    Aresta **arestas;
    unsigned int *servidores;
    unsigned int *clientes;
    unsigned int *monitores;
};

Grafo *criar_grafo(unsigned int qnt_nos, unsigned int qnt_arestas, unsigned int qnt_servidores, unsigned int qnt_clientes, unsigned int qnt_monitores) {
    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    grafo->qnt_nos = qnt_nos;
    grafo->qnt_arestas = qnt_arestas;
    grafo->nos = criar_vetor_no(qnt_nos);
    grafo->arestas = criar_arestas(qnt_arestas);
    grafo->servidores = (unsigned int *)malloc((qnt_servidores + 1) * sizeof(unsigned int));
    grafo->clientes = (unsigned int *)malloc((qnt_clientes + 1) * sizeof(unsigned int));
    grafo->monitores = (unsigned int *)malloc((qnt_monitores + 1) * sizeof(unsigned int));
    grafo->servidores[0] = qnt_servidores;
    grafo->clientes[0] = qnt_clientes;
    grafo->monitores[0] = qnt_monitores;
    return grafo;
}

void imprimir_grafo(Grafo *grafo) {
    printf("Quantidade de nós: %u\n", grafo->qnt_nos);
    printf("Quantidade de arestas: %u\n", grafo->qnt_arestas);
    printf("Servidores: ");
    for (unsigned int i = 1; i <= grafo->servidores[0]; i++) {
        printf("%u ", grafo->servidores[i]);
    }
    printf("\nClientes: ");
    for (unsigned int i = 1; i <= grafo->clientes[0]; i++) {
        printf("%u ", grafo->clientes[i]);
    }
    printf("\nMonitores: ");
    for (unsigned int i = 1; i <= grafo->monitores[0]; i++) {
        printf("%u ", grafo->monitores[i]);
    }
    printf("\nNós: \n");
    for (unsigned int i = 0; i < grafo->qnt_nos; i++) {
        imprimir_no(grafo->nos[i]);
    }
    printf("\nArestas: \n");
    for (unsigned int i = 0; i < grafo->qnt_arestas; i++) {
        imprimir_aresta(grafo->arestas[i]);
    }
}

unsigned int get_qnt_nos(Grafo *grafo) {
    return grafo->qnt_nos;
}

unsigned int get_qnt_arestas(Grafo *grafo) {
    return grafo->qnt_arestas;
}

unsigned int *get_servidores(Grafo *grafo) {
    return grafo->servidores;
}

unsigned int *get_clientes(Grafo *grafo) {
    return grafo->clientes;
}

unsigned int *get_monitores(Grafo *grafo) {
    return grafo->monitores;
}

Aresta **get_arestas(Grafo *grafo) {
    return grafo->arestas;
}

No **get_nos(Grafo *grafo) {
    return grafo->nos;
}

void liberar_grafo(Grafo *grafo) {
    for (unsigned int i = 0; i < grafo->qnt_arestas; i++) {
        liberar_aresta(grafo->arestas[i]);
    }
    for (unsigned int i = 0; i < grafo->qnt_nos; i++) {
        liberar_no(grafo->nos[i]);
    }
    free(grafo->nos);
    free(grafo->arestas);
    free(grafo->servidores);
    free(grafo->clientes);
    free(grafo->monitores);
    free(grafo);
}

double *dijkstra(Grafo *grafo, unsigned int no, unsigned int qnt_destinos, unsigned int *destinos) {
    PQ *pq = PQ_init(grafo->qnt_nos);
    for (unsigned int i = 0; i < grafo->qnt_nos; i++) {
        // Inicializa todos os nós com valor infinito
        value(grafo->nos[i], DBL_MAX);
    }
    // Inicializa o nó de origem com valor 0
    value(grafo->nos[no], 0.0);
    // Insere o nó de origem na fila de prioridade
    PQ_insert(pq, grafo->nos[no]);
    while (!PQ_empty(pq)) {
        No *origem = PQ_delmin(pq);
        unsigned int u = id(origem);
        for (unsigned int i = 0; i < grafo->qnt_arestas; i++) {
            if (get_origem(grafo->arestas[i]) == u) {
                unsigned int v = get_destino(grafo->arestas[i]);
                No *destino = grafo->nos[v];
                double custo = get_custo(grafo->arestas[i]);
                double valor = get_value(origem) + custo;
                // Atualiza o valor do nó destino se o novo valor for menor
                if (valor < get_value(destino)) {
                    value(destino, valor);
                    // Insere o nó destino na fila de prioridade se ele não estiver lá
                    if (!PQ_contains(pq, destino)) {
                        PQ_insert(pq, destino);
                    } else {
                        PQ_decrease_key(pq, v, valor);
                    }
                }
            }
        }
    }
    // Retorna as distâncias mínimas para os destinos especificados
    double *distancias = (double *)malloc(qnt_destinos * sizeof(double));
    for (unsigned int i = 1; i <= qnt_destinos; i++) {
        distancias[i-1] = get_value(grafo->nos[destinos[i]]);
    }
    PQ_finish(pq);
    return distancias;
}

double** get_distancias(Grafo* grafo, unsigned int* origens, unsigned int* destinos, unsigned int qnt_distancias, unsigned int qnt_destinos){
    double** distancias = (double **)malloc(qnt_distancias * sizeof(double *));
    for(unsigned int i = 1; i <= qnt_distancias; i++){
        // Calcula as distâncias mínimas para cada nó de origem
        distancias[i - 1] = dijkstra(grafo, origens[i], qnt_destinos, destinos);
    }
    return distancias;
}

void imprimir_distancias(double *distancias, unsigned int qnt_distancias) {
    for(unsigned int i = 0; i < qnt_distancias; i++){
        printf("Distancias: %lf \n", distancias[i]);
    }
}

void liberar_distancias(double **distancias, unsigned int qnt_distancias) {
    for(unsigned int i = 0; i < qnt_distancias; i++){
        free(distancias[i]);
    }
    free(distancias);
}

Aresta **calcular_caminhos_minimos(Grafo *grafo) {
    Aresta **inflacoes_rtt = criar_arestas(grafo->servidores[0] * grafo->clientes[0]);
    unsigned int i, j, k;
    double rtt_real_entre_servidores_clientes, rtt_aproximado_entre_servidores_monitores;
    double rtt_aproximado_entre_servidores_clientes, rtt_aproximado_entre_monitores_clientes;
    double menor_rtt_aproximado_entre_servidores_clientes = DBL_MAX;

    // Calcula as distâncias mínimas entre servidores e clientes
    double **caminhos_minimos_servidores_para_clientes = get_distancias(grafo, grafo->servidores, grafo->clientes, grafo->servidores[0], grafo->clientes[0]);
    double **caminhos_minimos_clientes_para_servidores = get_distancias(grafo, grafo->clientes, grafo->servidores, grafo->clientes[0], grafo->servidores[0]);

    double **caminhos_minimos_servidores_para_monitores = get_distancias(grafo, grafo->servidores, grafo->monitores, grafo->servidores[0], grafo->monitores[0]);
    double **caminhos_minimos_monitores_para_servidores = get_distancias(grafo, grafo->monitores, grafo->servidores, grafo->monitores[0], grafo->servidores[0]);

    double **caminhos_minimos_monitores_para_clientes = get_distancias(grafo, grafo->monitores, grafo->clientes, grafo->monitores[0], grafo->clientes[0]);
    double **caminhos_minimos_clientes_para_monitores = get_distancias(grafo, grafo->clientes, grafo->monitores, grafo->clientes[0], grafo->monitores[0]);

    // Calcula a inflação do RTT entre servidores e clientes
    for(i = 1; i <= grafo->servidores[0]; i++){
        for (j = 1; j <= grafo->clientes[0]; j++) {
            rtt_real_entre_servidores_clientes = caminhos_minimos_servidores_para_clientes[i-1][j-1] + caminhos_minimos_clientes_para_servidores[j-1][i-1];
            for(k = 1; k <= grafo->monitores[0]; k++){
                rtt_aproximado_entre_servidores_monitores = caminhos_minimos_servidores_para_monitores[i-1][k-1] + caminhos_minimos_monitores_para_servidores[k-1][i-1];
                rtt_aproximado_entre_monitores_clientes = caminhos_minimos_monitores_para_clientes[k-1][j-1] + caminhos_minimos_clientes_para_monitores[j-1][k-1];
                rtt_aproximado_entre_servidores_clientes = rtt_aproximado_entre_servidores_monitores + rtt_aproximado_entre_monitores_clientes;
                if(rtt_aproximado_entre_servidores_clientes < menor_rtt_aproximado_entre_servidores_clientes){
                    menor_rtt_aproximado_entre_servidores_clientes = rtt_aproximado_entre_servidores_clientes;
                }
            }
            double inflacao_rtt = menor_rtt_aproximado_entre_servidores_clientes / rtt_real_entre_servidores_clientes;
            inflacoes_rtt[((i - 1) * grafo->clientes[0] + (j - 1))] = criar_aresta(grafo->servidores[i], grafo->clientes[j], inflacao_rtt);
            menor_rtt_aproximado_entre_servidores_clientes = DBL_MAX;
        }
    }

    // Libera a memória alocada para as distâncias mínimas
    liberar_distancias(caminhos_minimos_servidores_para_clientes, grafo->servidores[0]);
    liberar_distancias(caminhos_minimos_clientes_para_servidores, grafo->clientes[0]);

    liberar_distancias(caminhos_minimos_servidores_para_monitores, grafo->servidores[0]);
    liberar_distancias(caminhos_minimos_monitores_para_servidores, grafo->monitores[0]);

    liberar_distancias(caminhos_minimos_monitores_para_clientes, grafo->monitores[0]);
    liberar_distancias(caminhos_minimos_clientes_para_monitores, grafo->clientes[0]);
    
    return inflacoes_rtt;
}

void imprimir_inflacoes_rtt(Grafo *grafo, Aresta **inflacoes_rtt) {
    for(unsigned int i = 0; i < grafo->servidores[0] * grafo->clientes[0]; i++){
        imprimir_aresta(inflacoes_rtt[i]);
    }
}

void liberar_inflacoes_rtt(Grafo *grafo,Aresta **inflacoes_rtt) {
    for(unsigned int i = 0; i < grafo->servidores[0] * grafo->clientes[0]; i++){
        liberar_aresta(inflacoes_rtt[i]);
    }
    free(inflacoes_rtt);
}