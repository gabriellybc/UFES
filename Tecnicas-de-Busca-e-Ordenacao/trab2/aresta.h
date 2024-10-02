#ifndef ARESTA_H
#define ARESTA_H

/**
 * Estrutura de dados para uma aresta em um grafo.
 *
 * Esta estrutura representa uma aresta em um grafo, que conecta dois nós e possui um custo associado.
 *
 * - `origem`: O identificador do nó de origem da aresta (`unsigned int`).
 * - `destino`: O identificador do nó de destino da aresta (`unsigned int`).
 * - `custo`: O custo associado à aresta (`double`).
 */
typedef struct aresta Aresta;

/**
 * Cria uma nova aresta com os dados fornecidos.
 *
 * Esta função aloca memória para uma nova estrutura `Aresta`, inicializa seus campos 
 * com os valores fornecidos para a origem, destino e custo, e retorna um ponteiro para a 
 * nova estrutura.
 *
 * @param origem O nó de origem da aresta.
 * @param destino O nó de destino da aresta.
 * @param custo O custo associado à aresta.
 * 
 * @return Um ponteiro para a nova estrutura `Aresta` criada. Se a alocação de memória falhar, 
 *         o comportamento é indefinido.
 */
Aresta *criar_aresta(unsigned int origem, unsigned int destino, double custo);

/**
 * Aloca memória para um array de ponteiros para arestas.
 *
 * Esta função aloca memória para um array de ponteiros do tipo `Aresta`, com tamanho 
 * especificado por `qnt_arestas`. Cada elemento do array pode posteriormente apontar 
 * para uma estrutura `Aresta` específica.
 *
 * @param qnt_arestas O número de arestas para as quais será alocada memória.
 * 
 * @return Um ponteiro para o array de ponteiros do tipo `Aresta`.
 */
Aresta **criar_arestas(unsigned int qnt_arestas);

/**
 * Retorna o nó de origem de uma aresta.
 *
 * Esta função acessa o campo `origem` da estrutura `Aresta` e retorna o valor armazenado,
 * que representa o nó de origem da aresta.
 *
 * @param aresta Um ponteiro para a estrutura `Aresta`.
 * 
 * @return O nó de origem da aresta.
 */
unsigned int get_origem(Aresta *aresta);

/**
 * Retorna o nó de destino de uma aresta.
 *
 * Esta função acessa o campo `destino` da estrutura `Aresta` e retorna o valor armazenado,
 * que representa o nó de destino da aresta.
 *
 * @param aresta Um ponteiro para a estrutura `Aresta`.
 * 
 * @return O nó de destino da aresta.
 */
unsigned int get_destino(Aresta *aresta);

/**
 * Retorna o custo associado a uma aresta.
 *
 * Esta função acessa o campo `custo` da estrutura `Aresta` e retorna o valor armazenado,
 * que representa o custo associado à aresta.
 *
 * @param aresta Um ponteiro para a estrutura `Aresta`.
 * 
 * @return O custo associado à aresta.
 */
double get_custo(Aresta *aresta);

/**
 * Imprime os dados de uma aresta na saída padrão.
 *
 * Esta função imprime os valores dos campos `origem`, `destino` e `custo` da estrutura `Aresta` 
 * na saída padrão, formatados de acordo com as especificações do projeto.
 *
 * @param aresta Um ponteiro para a estrutura `Aresta`.
 */
void imprimir_aresta(Aresta *aresta);

/**
 * Libera a memória alocada para uma aresta.
 *
 * Esta função libera a memória alocada para uma estrutura `Aresta`, incluindo a própria estrutura.
 *
 * @param aresta Um ponteiro para a estrutura `Aresta` que será liberada.
 */
void liberar_aresta(Aresta *aresta);

/**
 * Compara duas arestas pelo custo associado.
 *
 * Esta função compara duas arestas com base no custo associado a cada uma. Se a aresta `a` tiver 
 * um custo menor que a aresta `b`, a função retorna um valor negativo. Se a aresta `a` tiver um 
 * custo maior que a aresta `b`, a função retorna um valor positivo. Se os custos forem iguais, a 
 * função retorna zero.
 *
 * @param a Um ponteiro para a primeira estrutura `Aresta`.
 * @param b Um ponteiro para a segunda estrutura `Aresta`.
 * 
 * @return Um valor negativo se a aresta `a` tiver custo menor que a aresta `b`, um valor positivo 
 *         se a aresta `a` tiver custo maior que a aresta `b`, ou zero se os custos forem iguais.
 */
int comparar_por_custo(const void *a, const void *b);

/**
 * Ordena um array de ponteiros para arestas pelo custo associado.
 *
 * Esta função ordena um array de ponteiros para estruturas `Aresta` com base no custo associado 
 * a cada aresta. A ordenação é feita em ordem crescente de custo.
 *
 * @param arestas Um array de ponteiros para as estruturas `Aresta` que serão ordenadas.
 * @param tamanho O número de elementos no array `arestas`.
 */
void ordenar_arestas_por_custo(Aresta **arestas, unsigned int tamanho);

#endif