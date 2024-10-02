#include <stdlib.h>
#include <stdio.h>
#include "arquivo.h"
#include "grafo.h"

int main(int argc, char *argv[])
{
    Grafo *grafo = ler_entrada(argv[1]);
    Aresta ** inflacoes_rtt = calcular_caminhos_minimos(grafo);
    unsigned int tamanho_inflacoes_rtt = get_servidores(grafo)[0] * get_clientes(grafo)[0];
    ordenar_arestas_por_custo(inflacoes_rtt, tamanho_inflacoes_rtt);
    imprimir_saida(argv[2], inflacoes_rtt, tamanho_inflacoes_rtt);
    liberar_inflacoes_rtt(grafo, inflacoes_rtt);
    liberar_grafo(grafo);
    return 0;
}