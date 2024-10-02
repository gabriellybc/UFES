#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "lista.h"
#include "ponto.h"
#include "array.h"

/*
  Função para ler o arquivo de entrada e
  armazenar os pontos em uma lista de pontos l
*/
void arq_lerEntrada(char* pathToFile, lista l);

/*
  Função para imprimir a saída em um arquivo,
  usando os pontos (já ordenados) de um array a
*/
void arq_imprimeSaida(array a, char* pathToFile);

#endif