#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arquivo.h"

#define TAM_LINHA 300

/*
  Função para ler o arquivo de entrada e
  armazenar os pontos em uma lista de pontos l
*/
void arq_lerEntrada(char *pathToFile, lista l)
{
    FILE *arqLeitura = fopen(pathToFile, "r");
    if (arqLeitura == NULL)
    {
        printf("** ERRO: O arquivo de entrada não foi aberto **");
        exit;
    }
    
    char linha[TAM_LINHA];
    char *token, *id;
    int qntEixos = -1;
    float *listaEixos;
    ponto p;

    //Lê uma linha
    fgets(linha, sizeof(linha), arqLeitura);

    //Conta quantos eixos tem
    token = strtok(linha,",");
    while (token != NULL){
        qntEixos++;
        token = strtok(NULL, ",");
    }
    lista_setQtdEixos(l, qntEixos);
    fseek(arqLeitura, 0, SEEK_SET);

    //Lê linha por linha
    for (unsigned int i = 0; fgets(linha, sizeof(linha), arqLeitura) != NULL; i++) {
        listaEixos = (float *)malloc((qntEixos)*sizeof(float));
        token = strtok(linha, ",");
        id = strdup(token);

        //Lê cada componente de coordenada
        for (int i = 0; i < qntEixos; i++) {
            token = strtok(NULL, ",");
            listaEixos[i] = atof(token);
        }

        //Cria um ponto e o insere na lista
        p = ponto_init(id, listaEixos);
        lista_insere(l, p);
    }
    fclose(arqLeitura);
}

/*
  Função para imprimir a saída em um arquivo,
  usando os pontos (já ordenados) de um array a
*/
void arq_imprimeSaida(array a, char* pathToFile){
    FILE *arq = fopen(pathToFile, "w");
    unsigned int i = 0, size, index;

    if (arq == NULL) {
        printf("** ERRO: O arquivo não foi aberto **");
        exit;
    }

    //Percorre cada ponto raiz do array a, pegando o tamanho
    //de cada árvore/grupo
    while(i < array_getSize(a)){
        ponto p = array_getElem(a, i);
        size = ponto_getArvSize(p);
        index = i;
        //Percorre os pontos de 1 árvore/grupo do array
        for(unsigned int j = i; j < (size + index); j++, i++){
            p = array_getElem(a, i);
            //Se for o último elemento da linha imprime com \n
            if(j == ((size + index) - 1)){
                /* Era usado para não imprimir \n na última linha
                if(j == (array_getSize(a) -1)){
                    fprintf(arq, "%s", ponto_getId(p));
                } else{*/
                fprintf(arq, "%s\n", ponto_getId(p));
                //}
            }
            else{
                //Caso contrário imprime com vírgula
                fprintf(arq, "%s,", ponto_getId(p));
            }
        }
    }

    fclose(arq);
}