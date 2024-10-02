#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

//Função interna da implementação de um find de um 
//Weighted quick-union com desconexão
unsigned int uf_find(ponto p, array pts){
    unsigned int toReturn = ponto_getArvId(p);
    while(toReturn != ponto_getArvPid(p)){
        toReturn = ponto_getArvPid(p);
        p = (ponto)array_getElem(pts, toReturn);
    }
    return toReturn;
}

//Função interna para inverter o sentido
//entre pais e filhos
//p = atual pai (que vai se tornar filho)
//r = atual filho (que vai se tornar raiz)
void uf_changeRoot(ponto p, ponto r, array pts){
    //Se p for raiz, r se torna pai de p e a função retorna
    if(ponto_getArvPid(p) == ponto_getArvId(p)){
        ponto_setArvPid(p, ponto_getArvId(r));
        return;
    }
    
    //Chamada recursiva com p = pai de p e r = p
    uf_changeRoot(array_getElem(pts, ponto_getArvPid(p)), p, pts);
    //r se torna pai de p
    ponto_setArvPid(p, ponto_getArvId(r));
}

//Função interna da implementação do union de um
//Weighted quick-union com desconexão
void uf_union(ponto p, ponto q, array pts){
    //p1 = raiz do ponto p
    ponto p1 = (ponto)array_getElem(pts, uf_find(p, pts));
    //p2 = raiz do ponto q
    ponto p2 = (ponto)array_getElem(pts, uf_find(q, pts));
    //Se a árvore de p for menor que a árvore de q, pendura p sob q
    if(ponto_getArvSize(p1) < ponto_getArvSize(p2)){
        ponto_setArvSize(p2, ponto_getArvSize(p1) + ponto_getArvSize(p2));

        //Troca a raiz do pai de p (e todos os pais no caminho) para p.
        //De forma que ao desconectar p de seu pai, temos apenas uma componente
        //conexa
        uf_changeRoot(array_getElem(pts, ponto_getArvPid(p)), p, pts);
        ponto_setArvPid(p, ponto_getArvId(q));
        
    }
    //Se a árvore de p for menor que a árvore de q, pendura p sob q
    else{
        ponto_setArvSize(p1, ponto_getArvSize(p1) + ponto_getArvSize(p2));
        
        //Troca a raiz do pai de q (e todos os pais no caminho) para q.
        //De forma que ao desconectar q de seu pai, temos apenas uma componente
        //conexa
        uf_changeRoot(array_getElem(pts, ponto_getArvPid(q)), q, pts);
        ponto_setArvPid(q, ponto_getArvId(p));
        
    }
}

//Função interna para desconectar 2 pontos
void uf_disconnect(distancia dist, array pts){
    ponto p1 = dist_getP1(dist);
    ponto p2 = dist_getP2(dist);
    ponto r;

    dist_disconnect(dist);

    //Se p1 for filho de p2, p1 se torna raiz (se torna seu próprio pai)
    //e o tamanho da árvore de p2 (arvSize da raiz de p2) é reduzido
    if(ponto_getArvPid(p1) == ponto_getArvId(p2)){
        ponto_setArvPid(p1, ponto_getArvId(p1));
        r = array_getElem(pts, uf_find(p2, pts));
        ponto_setArvSize(r, ponto_getArvSize(r) - ponto_getArvSize(p1));
    }
    //Se p2 for filho de p1, p2 se torna raiz (se torna seu próprio pai)
    //e o tamanho da árvore de p1 (arvSize da raiz de p1) é reduzido
    else{
        ponto_setArvPid(p2, ponto_getArvId(p2));
        r = array_getElem(pts, uf_find(p1, pts));
        ponto_setArvSize(r, ponto_getArvSize(r) - ponto_getArvSize(p2));
    }
}

//Função interna para gerar uma MST a partir de um array de
//distâncias e um array de pontos.
//As informações da floresta estão armazenadas dentro da struct ponto
void kruskal_getMST(array dists, array pts){
    //Percorre o array ordenado de distâncias
    //Se os 2 pontos das distâncias estão desconectados, os conecta
    for(unsigned int i = 0; i < array_getSize(dists); i++){
        distancia dist = array_getElem(dists, i);
        ponto p1 = dist_getP1(dist);
        ponto p2 = dist_getP2(dist);
        if(uf_find(p1, pts) != uf_find(p2, pts)){
            uf_union(p1, p2, pts);
            dist_connect(dist);
        }
    }
}

/*
  Função que gera a MST a partir do array de pontos e distâncias
  e remove as k-1 arestas.
  As informações da floresta estão armazenadas dentro da struct ponto
*/
void tree_make(array dists, array pts, unsigned int qtdToRemove){
    kruskal_getMST(dists, pts);

    //Percorre ao contrário o array de distâncias ordenadas e se a distância for uma
    //conexão, desconecta seus 2 pontos k-1 vezes
    for (unsigned int i = array_getSize(dists) - 1, k = 0; i >= 0, k < qtdToRemove; i--){
        distancia dist = array_getElem(dists, i);
        if(dist_isConnected(dist)){
            uf_disconnect(dist, pts);
            k++;
        }
    }
}

//Função interna que verifica se um elemento é raiz;
//Passada como parâmetro de array_getTipoElem
void* getRaizes(void* elem, void* , array){
    ponto p = (ponto)elem;

    if(ponto_getArvId(p) == ponto_getArvPid(p)){
        return elem;
    }
    return NULL;
}

//Função interna que verifica se um elemento faz parte do grupo do elemento raiz;
//Passada como parâmetro de array_getTipoElem
void* getGrupo(void* elem, void* raiz, array pts){
    ponto p = (ponto)elem;
    ponto r = (ponto)raiz;
    if(uf_find(p, pts) == ponto_getArvId(r)){
        return elem;
    }
    return NULL;

}

/*
  Função que ordena o array de pontos pts de acordo com os grupos
  para impressão no arquivo de saída
*/
void tree_sort(array pts, unsigned int qtdGrupos){
    unsigned int gid, count;

    //Array com as raízes dos grupos
    array grupos = array_getTipoElem(pts, getRaizes, NULL, qtdGrupos);

    //Conta a quantidade de elementos em cada grupo e a insere em cada elemento
    for(unsigned int j = 0; j < qtdGrupos; j++){
        count = 0;
        gid = ponto_getArvId(array_getElem(grupos, j));
        for(unsigned int i = 0; i < array_getSize(pts); i++){
            if(uf_find(array_getElem(pts, i), pts) == gid){
                count++;
            }
        }
        for(unsigned int i = 0; i < array_getSize(pts); i++){
            ponto p = array_getElem(pts, i);
            if(uf_find(p, pts) == gid){
                ponto_setArvSize(p, count);
            }
        }
    }

    //Array auxiliar utilizado para ordenação
    array aux = array_init(array_getSize(pts));
    //Vetor com os tamanhos de cada grupo
    unsigned int sizes[array_getSize(grupos) + 1];
    //Vetor com os tamanhos de cada grupo (ordenado de acordo com a saída do projeto)
    unsigned int sizesOrdenados[array_getSize(grupos)+1];

    sizes[0] = 0;

    //Para cada elemento do array grupos, cria um sub-array grupo,
    //ordena grupo alfabeticamente, insere seu tamanho no vetor sizes
    //e insere o sub-array no array aux
    for(unsigned int i = 0; i < qtdGrupos; i++){
        ponto r = (ponto)array_getElem(grupos, i);
        array grupo = array_getTipoElem(pts, getGrupo, r, ponto_getArvSize(r));
        sizes[i+1] = array_getSize(grupo);
        array_sort(grupo, ponto_compare);
        array_copyFromGrupo(aux, grupo, sizes, i);
        array_free(grupo, NULL); //Libera memória alocada com o array grupo
    }
    array_free(grupos, NULL); //Libera a memória do array grupos

    //Grupos vira um array com o primeiro elemento de cada grupo
    grupos = array_getInterv(aux, sizes, qtdGrupos);
    array_sort(grupos, ponto_compare); //Ordena os grupos de forma alfabética

    //Preenche o vetor sizesOrdenados com os tamanhos ordenados dos grupos
    sizesOrdenados[0] = 0;
    for(unsigned int i = 0; i < qtdGrupos; i++){
        sizesOrdenados[i+1] = ponto_getArvSize(array_getElem(grupos, i));
    }

    //Ordena o vetor aux de acordo com a ordem dos grupos
    array_sortGrupos(aux, grupos, sizes, sizesOrdenados);
    //Copia os elementos de aux (ordenados) para o array pts
    array_copyFromArray(pts, aux);
    //Libera memória alocada com os arrays grupos e aux
    array_free(grupos, NULL);
    array_free(aux, NULL);
}
