#ifndef GRAFO_H
#define GRAFO_H

#include "aresta.h"
#include "no.h"

/**
 * Estrutura de dados para um grafo.
 *
 * Esta estrutura representa um grafo com um conjunto de nós e arestas, além de categorias específicas de nós
 * como servidores, clientes e monitores.
 *
 * - `qnt_nos`: O número total de nós no grafo (`unsigned int`).
 * - `qnt_arestas`: O número total de arestas no grafo (`unsigned int`).
 * - `nos`: Um vetor de ponteiros para nós (`No **`), representando todos os nós do grafo.
 * - `arestas`: Um vetor de ponteiros para arestas (`Aresta **`), representando todas as arestas do grafo.
 * - `servidores`: Um array de identificadores de servidores (`unsigned int *`).
 * - `clientes`: Um array de identificadores de clientes (`unsigned int *`).
 * - `monitores`: Um array de identificadores de monitores (`unsigned int *`).
 */
typedef struct grafo Grafo;

/**
 * Cria uma nova instância de um grafo.
 *
 * Esta função aloca e inicializa uma nova estrutura de grafo com o número especificado de nós, arestas e
 * diferentes categorias de nós (servidores, clientes e monitores). Inicializa os arrays internos do grafo
 * para armazenar as informações sobre nós e arestas.
 *
 * @param qnt_nos O número total de nós no grafo (`unsigned int`).
 * @param qnt_arestas O número total de arestas no grafo (`unsigned int`).
 * @param qnt_servidores O número total de servidores (`unsigned int`).
 * @param qnt_clientes O número total de clientes (`unsigned int`).
 * @param qnt_monitores O número total de monitores (`unsigned int`).
 *
 * @return Um ponteiro para a estrutura `Grafo` recém-criada e inicializada.
 */
Grafo *criar_grafo(unsigned int qnt_nos, unsigned int qnt_arestas, unsigned int qnt_servidores, unsigned int qnt_clientes, unsigned int qnt_monitores);

/**
 * Imprime as informações sobre um grafo.
 *
 * Esta função exibe no console detalhes sobre o grafo, incluindo a quantidade total de nós,
 * arestas, e listas de servidores, clientes e monitores. Além disso, imprime cada nó e aresta presente no grafo.
 *
 * @param grafo Um ponteiro para a estrutura `Grafo` a ser impresso.
 *
 * A função utiliza as funções auxiliares `imprimir_no` e `imprimir_aresta` para exibir detalhes
 * dos nós e arestas, respectivamente.
 */
void imprimir_grafo(Grafo *grafo);

/**
 * Retorna o número total de nós em um grafo.
 *
 * Esta função acessa o campo `qnt_nos` da estrutura `Grafo` e retorna o valor armazenado,
 * que representa o número total de nós no grafo.
 *
 * @param grafo Um ponteiro para a estrutura `Grafo`.
 *
 * @return O número total de nós no grafo.
 */
unsigned int get_qnt_nos(Grafo *grafo);

/**
 * Retorna o número total de arestas em um grafo.
 *
 * Esta função acessa o campo `qnt_arestas` da estrutura `Grafo` e retorna o valor armazenado,
 * que representa o número total de arestas no grafo.
 *
 * @param grafo Um ponteiro para a estrutura `Grafo`.
 *
 * @return O número total de arestas no grafo.
 */
unsigned int get_qnt_arestas(Grafo *grafo);

/**
 * Obtém o array de servidores de um grafo.
 *
 * Esta função retorna um ponteiro para o array de servidores associado a um grafo. O primeiro elemento do
 * array contém a quantidade total de servidores, e os elementos subsequentes contêm os IDs dos servidores.
 *
 * @param grafo Um ponteiro para a estrutura `Grafo` do qual os servidores serão obtidos.
 *
 * @return Um ponteiro para o array de IDs dos servidores no grafo.
 */
unsigned int *get_servidores(Grafo *grafo); 

/**
 * Obtém o array de clientes de um grafo.
 *
 * Esta função retorna um ponteiro para o array de clientes associado a um grafo. O primeiro elemento do
 * array contém a quantidade total de clientes, e os elementos subsequentes contêm os IDs dos clientes.
 *
 * @param grafo Um ponteiro para a estrutura `Grafo` do qual os clientes serão obtidos.
 *
 * @return Um ponteiro para o array de IDs dos clientes no grafo.
 */
unsigned int *get_clientes(Grafo *grafo);

/**
 * Obtém o array de monitores de um grafo.
 *
 * Esta função retorna um ponteiro para o array de monitores associado a um grafo. O primeiro elemento do
 * array contém a quantidade total de monitores, e os elementos subsequentes contêm os IDs dos monitores.
 *
 * @param grafo Um ponteiro para a estrutura `Grafo` do qual os monitores serão obtidos.
 *
 * @return Um ponteiro para o array de IDs dos monitores no grafo.
 */
unsigned int *get_monitores(Grafo *grafo);

/**
 * @brief Obtém o array de arestas de um grafo.
 *
 * Esta função retorna um ponteiro para o array de arestas associado a um grafo. Cada elemento do array é um
 * ponteiro para uma estrutura `Aresta`, representando uma aresta no grafo.
 *
 * @param grafo Um ponteiro para a estrutura `Grafo` do qual as arestas serão obtidas.
 *
 * @return Um ponteiro para o array de ponteiros para estruturas `Aresta` no grafo.
 */
Aresta **get_arestas(Grafo *grafo);

/**
 * Obtém o array de nós de um grafo.
 *
 * Esta função retorna um ponteiro para o array de nós associado a um grafo. Cada elemento do array é um
 * ponteiro para uma estrutura `No`, representando um nó no grafo.
 *
 * @param grafo Um ponteiro para a estrutura `Grafo` do qual os nós serão obtidos.
 *
 * @return Um ponteiro para o array de ponteiros para estruturas `No` no grafo.
 */
No **get_nos(Grafo *grafo);

/**
 * Libera a memória alocada para um grafo.
 *
 * Esta função libera toda a memória alocada para o grafo, incluindo os nós, arestas e arrays associados
 * (servidores, clientes e monitores). Ela também libera a estrutura principal do grafo.
 *
 * @param grafo Um ponteiro para a estrutura `Grafo` que será liberada.
 */

void liberar_grafo(Grafo *grafo);

/**
 * Calcula as distâncias mínimas a partir de um nó de origem usando o algoritmo de Dijkstra.
 *
 * Esta função calcula as distâncias mínimas do nó de origem especificado para um conjunto de destinos
 * usando o algoritmo de Dijkstra. Ela inicializa uma fila de prioridade para manter o controle
 * das distâncias mínimas encontradas até o momento e ajusta as distâncias com base nas arestas do grafo.
 *
 * @param grafo Um ponteiro para a estrutura `Grafo` que contém as informações do grafo.
 * @param no O nó de origem a partir do qual as distâncias mínimas serão calculadas.
 * @param qnt_destinos O número de destinos para os quais as distâncias mínimas serão calculadas.
 * @param destinos Um array de IDs de destinos para os quais as distâncias mínimas serão retornadas.
 *
 * @return Um ponteiro para um array de distâncias mínimas do nó de origem para cada destino especificado.
 */
double *dijkstra(Grafo *grafo, unsigned int no, unsigned int qnt_destinos, unsigned int *destinos);

/**
 * Calcula as distâncias mínimas entre um conjunto de nós de origem e um conjunto de destinos.
 *
 * Esta função calcula as distâncias mínimas de múltiplos nós de origem para um conjunto de destinos
 * usando o algoritmo de Dijkstra para cada nó de origem. O resultado é uma matriz onde cada linha contém
 * as distâncias mínimas do nó de origem correspondente para todos os destinos especificados.
 *
 * @param grafo Um ponteiro para a estrutura `Grafo` que contém as informações do grafo.
 * @param origens Um array de IDs dos nós de origem para os quais as distâncias mínimas serão calculadas.
 * @param destinos Um array de IDs dos destinos para os quais as distâncias mínimas serão calculadas a partir de cada nó de origem.
 * @param qnt_distancias O número de nós de origem para os quais as distâncias mínimas serão calculadas.
 * @param qnt_destinos O número de destinos para os quais as distâncias mínimas serão calculadas.
 *
 * @return Um ponteiro para uma matriz de distâncias mínimas, onde cada linha representa as distâncias mínimas
 *         do nó de origem correspondente para todos os destinos. Cada linha é um array de distâncias para os destinos.
 */
double** get_distancias(Grafo* grafo, unsigned int* origem, unsigned int* destino, unsigned int qnt_distancias, unsigned int qnt_destinos);

/**
 * Imprime as distâncias armazenadas em um array.
 *
 * Esta função imprime cada valor de distância presente no array `distancias`, que representa as distâncias
 * mínimas calculadas entre um nó de origem e um conjunto de destinos. Cada distância é impressa em uma linha.
 *
 * @param distancias Um ponteiro para o array de distâncias a serem impressas.
 * @param qnt_distancias O número de distâncias no array `distancias`.
 */
void imprimir_distancias(double *distancias, unsigned int qnt_distancias);

/**
 * Libera a memória alocada para um array de distâncias.
 *
 * Esta função libera a memória alocada para o array de distâncias, onde cada elemento é um ponteiro para um
 * array de distâncias. Primeiro, libera a memória de cada array de distâncias individual e, em seguida,
 * libera o array principal.
 *
 * @param distancias Um ponteiro para o array de ponteiros para distâncias a serem liberadas.
 * @param qnt_distancias O número de arrays de distâncias no array `distancias`.
 */
void liberar_distancias(double **distancias, unsigned int qnt_distancias);

/**
 * Calcula a inflação do RTT entre servidores e clientes em um grafo.
 *
 * Esta função utiliza o algoritmo de Dijkstra para calcular os caminhos mínimos entre diferentes conjuntos
 * de nós no grafo, incluindo servidores, clientes e monitores. A inflação do RTT é calculada com base nos
 * tempos reais e aproximados de viagem entre servidores e clientes. O resultado é uma lista de arestas que
 * representam a inflação do RTT entre cada par de servidor e cliente.
 *
 * @param grafo Um ponteiro para o grafo que contém os nós e arestas.
 *
 * @return Um ponteiro para um array de arestas que representam a inflação do RTT entre cada par de servidor
 *         e cliente. O tamanho do array é o produto do número de servidores e clientes.
 */
Aresta **calcular_caminhos_minimos(Grafo *grafo);

/**
 * Imprime as arestas representando a inflação do RTT entre servidores e clientes.
 *
 * Esta função percorre o array de arestas que representa a inflação do RTT calculada entre servidores e
 * clientes. Para cada aresta, a função imprime suas informações usando a função `imprimir_aresta`.
 *
 * @param grafo Um ponteiro para o grafo que contém os nós e arestas.
 * @param inflacoes_rtt Um ponteiro para o array de arestas que representa a inflação do RTT entre servidores
 *                      e clientes. O tamanho do array é o produto do número de servidores e clientes.
 */
void imprimir_inflacoes_rtt(Grafo *grafo, Aresta **inflacoes_rtt);

/**
 * Libera a memória alocada para as arestas de inflação do RTT.
 *
 * Esta função libera a memória alocada para o array de arestas que representa a inflação do RTT entre
 * servidores e clientes. Primeiro, libera a memória para cada aresta individualmente e, em seguida, libera
 * a memória para o array de ponteiros de arestas.
 *
 * @param grafo Um ponteiro para o grafo que contém a informação sobre o número de servidores e clientes.
 *              Utilizado para determinar o tamanho do array de arestas.
 * @param inflacoes_rtt Um ponteiro para o array de arestas que representa a inflação do RTT entre servidores
 *                      e clientes. Cada aresta deve ser liberada antes de liberar o array de ponteiros.
 */
void liberar_inflacoes_rtt(Grafo *grafo, Aresta **inflacoes_rtt);

#endif