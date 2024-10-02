#include <stdlib.h>
#include <stdio.h>
#include "tst.h"
#include "tst_str.h"
#include "io.h"

int main(int argc, char *argv[])
{
    float alpha = 0.85f;
    double epsilon = 0.000001;
    unsigned int tamanho = 0;
    const char *diretorio = argv[1];
    Lista *lista_paginas = iniciar_lista();
    TST *tst_paginas = ler_index(diretorio, lista_paginas);

    ler_graph(diretorio, tst_paginas);
    liberar_tst(tst_paginas);

    Pagina **paginas = lista_para_array(lista_paginas, &tamanho);
    calcular_pagerank(paginas, tamanho, alpha, epsilon);
    ordernar_paginas(paginas, tamanho);

    TST_str **arrey_tsts = iniciar_arrey_tst_strs();
    Lista *lista_stop_word = ler_stop_words(diretorio, arrey_tsts);

    ler_pages(diretorio, arrey_tsts, paginas, tamanho);
    ler_consulta(arrey_tsts);

    liberar_arrey_tst_strs(arrey_tsts);
    liberar_lista_stop_word(lista_stop_word);
    liberar_arrey_paginas(paginas, tamanho);
    return 0;
}