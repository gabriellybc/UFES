#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "no.h"

/**
 * Estrutura de dados para uma fila de prioridade.
 *
 * Esta estrutura representa uma fila de prioridade usando um heap.
 *
 * - `pq`: Um vetor de ponteiros para nós (`No **`), onde o índice representa a posição no heap.
 * - `map`: Um array de índices (`unsigned int *`), onde cada índice corresponde à posição do nó
 *   na fila de prioridade.
 * - `N`: O número de elementos atualmente na fila de prioridade (`unsigned int`).
 */
typedef struct pq PQ;

/**
 * Inicializa uma fila de prioridade com capacidade para um número máximo de elementos.
 *
 * Esta função aloca e inicializa uma estrutura de fila de prioridade (`PQ`). Cria um vetor de ponteiros para
 * nós e um mapeamento de índices, além de definir o número de elementos (`N`) como zero.
 *
 * @param maxN O número máximo de elementos que a fila de prioridade pode armazenar.
 * 
 * @return Um ponteiro para a estrutura `PQ` inicializada.
 */
PQ *PQ_init(unsigned int maxN);

/**
 * Insere um nó na fila de prioridade.
 *
 * Esta função adiciona um nó (`no`) na fila de prioridade (`pq`). O nó é colocado na posição adequada para
 * manter a propriedade de heap da fila de prioridade. Após a inserção, a função ajusta a posição do nó
 * para cima, se necessário, para manter a ordem correta dos elementos na fila.
 *
 * @param pq Um ponteiro para a estrutura `PQ` que representa a fila de prioridade.
 * @param no Um ponteiro para a estrutura `No` que será inserida na fila de prioridade.
 */
void PQ_insert(PQ *pq, No *no);

/**
 * Remove e retorna o nó com o menor valor da fila de prioridade.
 *
 * Esta função remove o nó com o menor valor (a raiz da fila de prioridade) da estrutura `PQ`. Após remover
 * o nó, a função troca a raiz com o último nó na fila e ajusta a posição do novo nó na raiz para baixo
 * para manter a propriedade de heap. O nó removido é retornado.
 *
 * @param pq Um ponteiro para a estrutura `PQ` que representa a fila de prioridade.
 *
 * @return Um ponteiro para o nó com o menor valor que foi removido da fila de prioridade.
 */
No *PQ_delmin(PQ *pq);

/**
 * Diminui o valor de um nó na fila de prioridade e ajusta a posição do nó.
 *
 * Esta função atualiza o valor de um nó específico identificado por `id` para um novo valor `value` na fila de prioridade
 * (`pq`). Após atualizar o valor, a função ajusta a posição do nó para cima para garantir que a propriedade de heap
 * seja mantida.
 *
 * @param pq Um ponteiro para a estrutura `PQ` que representa a fila de prioridade.
 * @param id O identificador do nó cujo valor deve ser diminuído.
 * @param value O novo valor a ser atribuído ao nó.
 */
void PQ_decrease_key(PQ *pq, unsigned int id, double value);

/**
 * Retorna o nó com o menor valor na fila de prioridade.
 *
 * Esta função retorna o nó com o menor valor, que é o nó na raiz da fila de prioridade (`pq`). A fila de prioridade
 * deve ter pelo menos um elemento para que esta função funcione corretamente.
 *
 * @param pq Um ponteiro para a estrutura `PQ` que representa a fila de prioridade.
 *
 * @return Um ponteiro para o nó com o menor valor na fila de prioridade.
 */
No *PQ_min(PQ *pq);

/**
 * Verifica se a fila de prioridade está vazia.
 *
 * Esta função verifica se a fila de prioridade (`pq`) contém elementos. Retorna `true` se a fila estiver vazia 
 * (ou seja, não contém elementos) e `false` caso contrário.
 *
 * @param pq Um ponteiro para a estrutura `PQ` que representa a fila de prioridade.
 *
 * @return Um valor booleano indicando se a fila de prioridade está vazia (`true`) ou não (`false`).
 */
bool PQ_empty(PQ *pq);

/**
 * Retorna o número de elementos na fila de prioridade.
 *
 * Esta função retorna a quantidade de elementos atualmente armazenados na fila de prioridade (`pq`).
 *
 * @param pq Um ponteiro para a estrutura `PQ` que representa a fila de prioridade.
 *
 * @return O número de elementos na fila de prioridade.
 */
unsigned int PQ_size(PQ *pq);

/**
 * Libera a memória alocada para a fila de prioridade.
 *
 * Esta função libera a memória alocada para a estrutura de fila de prioridade (`pq`), incluindo o vetor de
 * ponteiros para nós (`pq`) e o array de mapeamento de índices (`map`). Após liberar esses recursos, a própria
 * estrutura de fila de prioridade também é liberada.
 *
 * @param pq Um ponteiro para a estrutura `PQ` que representa a fila de prioridade a ser liberada.
 */
void PQ_finish(PQ *pq);

/**
 * Verifica se um nó está presente na fila de prioridade.
 * 
 * @param pq Ponteiro para a estrutura da fila de prioridade.
 * @param n Ponteiro para o nó a ser verificado.
 * @return Retorna verdadeiro se o nó está presente na fila de prioridade, falso caso contrário.
 */
bool PQ_contains(PQ *pq, No *n);

#endif
