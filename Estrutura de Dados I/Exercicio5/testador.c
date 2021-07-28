#include <stdio.h>
#include "listaDplMat.h"

int main()
{
  int i, j;
  //a. Gerar algumas matrizes para teste;
  Matriz *mat1 = inicializaMatriz(1, 2);
  for (i = 0; i < recuperaNLinhas(mat1); i++)
    for (j = 0; j < recuperaNColunas(mat1); j++)
      modificaElemento(mat1, i, j, i + j);

  Matriz *mat2 = inicializaMatriz(3, 3);
  for (i = 0; i < recuperaNLinhas(mat2); i++)
    for (j = 0; j < recuperaNColunas(mat2); j++)
      modificaElemento(mat2, i, j, i + j);

  Matriz *mat3 = inicializaMatriz(4, 5);
  for (i = 0; i < recuperaNLinhas(mat3); i++)
    for (j = 0; j < recuperaNColunas(mat3); j++)
      modificaElemento(mat3, i, j, i + j);

  Matriz *mat4 = inicializaMatriz(6, 7);
  for (i = 0; i < recuperaNLinhas(mat4); i++)
    for (j = 0; j < recuperaNColunas(mat4); j++)
      modificaElemento(mat4, i, j, i + j);

  //b. Inicializar uma listaDpl encadeada;
  ListaDplMat *listaDplMat1 = InicListaDplMat();

  //c. Inserir as matrizes na lista;
  listaDplMat1 = InsereMatLista(listaDplMat1, mat1);
  listaDplMat1 = InsereMatLista(listaDplMat1, mat2);
  listaDplMat1 = InsereMatLista(listaDplMat1, mat3);
  listaDplMat1 = InsereMatLista(listaDplMat1, mat4);

  //d. Inicializar outra lista encadeada;
  ListaDplMat *listaDplMat2 = InicListaDplMat();

  //e. Inserir as matrizes transpostas na segunda lista encadeada;
  Matriz *mat1Trans = transposta(mat1);
  Matriz *mat2Trans = transposta(mat2);
  Matriz *mat3Trans = transposta(mat3);
  Matriz *mat4Trans = transposta(mat4);
  listaDplMat2 = InsereMatLista(listaDplMat2, mat1Trans);
  listaDplMat2 = InsereMatLista(listaDplMat2, mat2Trans);
  listaDplMat2 = InsereMatLista(listaDplMat2, mat3Trans);
  listaDplMat2 = InsereMatLista(listaDplMat2, mat4Trans);

  //f. Imprima as listas
  printf("\nLista 1: \n");
  ImprimeListaMat(listaDplMat1);
  printf("\n----------------------------------------------------------------\n");
  printf("\nLista 2: \n");
  ImprimeListaMat(listaDplMat2);

  //g. Retire algumas matrizes para verificar se o retira está funcionando (retire da primeira posição, última posição e caso comum);
  listaDplMat1 = RetiraMatLista(listaDplMat1, 0);
  printf("\nLista sem a primeira matriz: \n");
  ImprimeListaMat(listaDplMat1);
  printf("\n----------------------------------------------------------------\n");

  listaDplMat1 = RetiraMatLista(listaDplMat1, 2);
  printf("\nLista sem a ultima matriz: \n");
  ImprimeListaMat(listaDplMat1);
  printf("\n----------------------------------------------------------------\n");

  listaDplMat2 = RetiraMatLista(listaDplMat2, 2);
  printf("\nLista 2 sem uma matriz do meio: \n");
  ImprimeListaMat(listaDplMat2);

  //Insira as matrizes novamente para verificar se o retira não “quebrou” a lista;
  printf("\nInserindo matriz 1: \n");
  listaDplMat1 = InsereMatLista(listaDplMat1, mat4);
  ImprimeListaMat(listaDplMat1);
  printf("\n----------------------------------------------------------------\n");

  printf("\nInserindo matriz 4: \n");
  listaDplMat1 = InsereMatLista(listaDplMat1, mat1);
  ImprimeListaMat(listaDplMat1);
  printf("\n----------------------------------------------------------------\n");

  printf("\nInserindo matriz 2 na lista 2: \n");
  listaDplMat2 = InsereMatLista(listaDplMat2, mat2Trans);
  ImprimeListaMat(listaDplMat2);
  printf("\n----------------------------------------------------------------\n");

  //i. Libere as listas!
  LiberaListaMat(listaDplMat2);
  LiberaListaMat(listaDplMat1);

  //j. Libere as matrizes!
  destroiMatriz(mat1);
  destroiMatriz(mat2);
  destroiMatriz(mat3);
  destroiMatriz(mat4);

  destroiMatriz(mat1Trans);
  destroiMatriz(mat2Trans);
  destroiMatriz(mat3Trans);
  destroiMatriz(mat4Trans);

  return 0;
}