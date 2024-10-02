#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ponto.h"
#include "arquivo.h"
#include "distancia.h"
#include "array.h"
#include "tree.h"

int main(int argc, char* argv[]){
    lista l = lista_init();
    unsigned int qtdToRemove;
    char* arqSaida;

    //O if era utilizado para rodar o debug do vscode
    //Não estava dando para passar argumento para main com o debug
    if(argc > 1){
        arq_lerEntrada(argv[1], l);
        qtdToRemove = atoi(argv[2]) - 1;
        arqSaida = argv[3];
    } else{
        arq_lerEntrada("../entrada.txt", l);
        qtdToRemove = 2;
        strcpy(arqSaida, "../saida.txt");
    }
    
    array pts = array_copyFromList(l, ponto_setArvIds);
    lista_free(l);
    
    array dists = array_calcDist(pts, ponto_distancia, dist_init);
    array_sort(dists, dist_compare);
    
    tree_make(dists, pts, qtdToRemove);
    array_free(dists, dist_free);
    
    tree_sort(pts, qtdToRemove + 1);
    
    arq_imprimeSaida(pts, arqSaida);
    
    array_free(pts, ponto_free);
    
   return 0;
}
