#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"

struct pq {
    No **pq;
    unsigned int *map;
    unsigned int N;

};

/**
 * Troca dois elementos em uma fila de prioridade e atualiza o mapeamento dos índices.
 */
static void swap(PQ *p, unsigned int i, unsigned int j) {
    exch(&p->pq[i], &p->pq[j]);
    p->map[id(p->pq[i])] = i;
    p->map[id(p->pq[j])] = j;
}

/**
 * Reorganiza uma fila de prioridade para garantir a propriedade de heap.
 */
void fix_up(PQ *pq, No **a, unsigned int k) {
    while (k > 1 && more(a[k/2], a[k])) {
        swap(pq, k, k/2);
        k = k/2;
    }
}

/**
 * Reorganiza uma fila de prioridade para garantir a propriedade de heap movendo um elemento para baixo.
 */
void fix_down(PQ *pq, No **a, unsigned int sz, unsigned int k){
  while (2*k <= sz) {
    unsigned int j = 2*k;
    if (j < sz && more(a[j], a[j+1])){
      j++;
    }
    if (!more(a[k], a[j])) {
      break;
    }
    swap(pq, k, j);
    k = j;
  }
}

PQ *PQ_init(unsigned int maxN) {
    PQ *p = (PQ *)malloc(sizeof(PQ));
    p->pq = criar_vetor_no(maxN+1);
    p->map = (unsigned int *) malloc((maxN+1) * sizeof (unsigned int));
    p->N = 0;
    return p;
}

void PQ_insert(PQ *p, No *v) {
    p->N++;
    p->pq[p->N] = v;
    p->map[id(v)] = p->N;
    fix_up(p, p->pq, p->N);
}

No *PQ_delmin(PQ *p) {
    No *min = p->pq[1];
    swap(p, 1, p->N);
    p->N--;
    fix_down(p, p->pq, p->N, 1);
    return min;
}

void PQ_decrease_key(PQ *p, unsigned int id, double val) {
    unsigned int i = p->map[id];
    value(p->pq[i], val);
    fix_up(p, p->pq, i);
}

No *PQ_min(PQ *p) {
    return p->pq[1];
}

bool PQ_empty(PQ *pq) {
    return pq->N == 0;
}

unsigned int  PQ_size(PQ *pq) {
    return pq->N;
}

void PQ_finish(PQ *p) {
    free(p->pq);
    free(p->map);
    free(p);
}

bool PQ_contains(PQ *p, No *v) {
    unsigned int id_v = id(v);
    unsigned int index = p->map[id_v];
    // Verifica se o índice é válido e se o nó na posição correspondente é o mesmo
    if (index > 0 && index <= p->N && p->pq[index] == v) {
        return true;
    } else {
        return false;
    }
}
