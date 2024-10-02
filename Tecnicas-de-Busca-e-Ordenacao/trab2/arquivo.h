#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "grafo.h"

/**
 * Lê os dados de um arquivo de entrada e cria um grafo com base nas informações fornecidas.
 *
 * Esta função abre um arquivo especificado por `nome_arquivo`, lê as informações sobre o número de nós, 
 * arestas, servidores, clientes e monitores, e cria um grafo com essas informações. Em seguida, 
 * lê as arestas do grafo e as armazena na estrutura apropriada. 
 *
 * @param nome_arquivo Nome do arquivo de entrada contendo os dados do grafo.
 * 
 * @return Um ponteiro para a estrutura `Grafo` criada a partir dos dados lidos.
 *
 *       A função assume que o arquivo de entrada está no formato correto e que contém as seguintes informações:
 *       - Primeira linha: dois inteiros representando a quantidade de nós e arestas.
 *       - Segunda linha: três inteiros representando a quantidade de servidores, clientes e monitores.
 *       - Linhas subsequentes: IDs dos servidores, IDs dos clientes, IDs dos monitores e as arestas (origem, destino, custo).
 */
Grafo *ler_entrada(char *nome_arquivo);


/**
 * Escreve os dados das arestas inflacionadas em um arquivo de saída.
 *
 * Esta função abre um arquivo especificado por `nome_arquivo` no modo de escrita, e grava nele 
 * as informações das arestas armazenadas em `inflacoes_rtt`.
 *
 * @param nome_arquivo Nome do arquivo de saída onde os dados serão escritos.
 * @param inflacoes_rtt Um array de ponteiros para as estruturas `Aresta` que contêm as arestas.
 * @param tamanho_inflacoes_rtt O número de arestas no array `inflacoes_rtt`.
 *
 * O arquivo de saída será sobrescrito se já existir. O custo das arestas será impresso com uma precisão de 16 casas decimais.
 */
void imprimir_saida(char *nome_arquivo, Aresta **inflacoes_rtt, unsigned int tamanho_inflacoes_rtt);

#endif