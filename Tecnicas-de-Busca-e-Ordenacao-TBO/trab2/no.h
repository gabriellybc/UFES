#ifndef NO_H
#define NO_H

/**
 * Estrutura de dados para um nó
 *
 * Esta estrutura representa um nó. Cada nó possui um identificador único.
 * 
 * - `id`: O identificador único do nó (`unsigned int`).
 * - `value`: O valor associado ao nó (`double`).
 */
typedef struct no No;

/**
 * Cria um novo nó com o identificador fornecido.
 *
 * Esta função aloca memória para uma nova estrutura `No`, inicializa seu campo `id` com o valor 
 * fornecido e o campo `value` com o valor padrão de 0.0. Em seguida, retorna um ponteiro para 
 * a nova estrutura `No`.
 *
 * @param id O identificador do nó.
 * 
 * @return Um ponteiro para a nova estrutura `No` criada.
 */
No *criar_no(unsigned int id);

/**
 * Aloca memória para um array de ponteiros para nós e inicializa todos os elementos como NULL.
 *
 * Esta função aloca memória para um array de ponteiros do tipo `No`, com tamanho especificado por `n`.
 * Cada elemento do array é inicializado como `NULL`, indicando que ainda não aponta para nenhum nó.
 *
 * @param n O número de elementos no array de ponteiros para nós.
 * 
 * @return Um ponteiro para o array de ponteiros do tipo `No`. Se a alocação de memória falhar,
 *         o comportamento é indefinido.
 */
No **criar_vetor_no(unsigned int n);

/**
 * Retorna o identificador de um nó.
 *
 * Esta função acessa o campo `id` da estrutura `No` e retorna o valor armazenado, 
 * que representa o identificador do nó.
 *
 * @param no Um ponteiro para a estrutura `No`.
 * 
 * @return O identificador do nó.
 */
unsigned int id(No *no);

/**
 * Define o valor de um nó.
 *
 * Esta função altera o campo `value` da estrutura `No` para o valor fornecido.
 *
 * @param no Um ponteiro para a estrutura `No`.
 * @param val O novo valor a ser atribuído ao campo `value` do nó.
 */
void value(No *no, double val);

/**
 * Retorna o valor de um nó.
 *
 * Esta função acessa o campo `value` da estrutura `No` e retorna o valor armazenado.
 *
 * @param no Um ponteiro para a estrutura `No`.
 * 
 * @return O valor armazenado no campo `value` do nó.
 */
double get_value(No *no);

/**
 * Compara os valores de dois nós.
 *
 * Esta função compara os valores dos campos `value` das estruturas `No` apontadas por `a` e `b`.
 * Retorna um valor não zero (verdadeiro) se o valor do nó `a` for maior que o valor do nó `b`, 
 * e 0 (falso) caso contrário.
 *
 * @param a Um ponteiro para a primeira estrutura `No`.
 * @param b Um ponteiro para a segunda estrutura `No`.
 * 
 * @return Um valor não zero se o valor de `a` for maior que o valor de `b`, e 0 caso contrário.
 */
int more(No *a, No *b);

/**
 * Troca os ponteiros para dois nós.
 *
 * Esta função troca os valores dos ponteiros para as estruturas `No` apontados por `a` e `b`.
 * Após a troca, o ponteiro `a` aponta para o nó que antes era apontado por `b`, e o ponteiro `b`
 * aponta para o nó que antes era apontado por `a`.
 *
 * @param a Um ponteiro para um ponteiro para a estrutura `No`.
 * @param b Um ponteiro para um ponteiro para a estrutura `No`.
 */
void exch(No **a, No **b);

/**
 * Imprime as informações de um nó.
 *
 * Esta função exibe no terminal o identificador (`id`) e o valor (`value`) de um nó,
 * fornecido por um ponteiro para a estrutura `No`.
 *
 * @param no Um ponteiro para a estrutura `No` cuja informação será impressa.
 */
void imprimir_no(No *no);

/**
 * Libera a memória alocada para um nó.
 *
 * Esta função libera a memória que foi alocada para a estrutura `No` apontada por `no`.
 * Após chamar esta função, o ponteiro `no` não deve mais ser usado.
 *
 * @param no Um ponteiro para a estrutura `No` cuja memória será liberada.
 */
void liberar_no(No *no);

#endif
