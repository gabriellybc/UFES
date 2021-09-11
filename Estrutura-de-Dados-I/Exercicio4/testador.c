#include <stdio.h>
#include "listaMat.h"

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

  //b. Inicializar uma lista encadeada;
  ListaMat *listaMat1 = InicListaMat();

  //c. Inserir as matrizes na lista;
  InsereMatLista(listaMat1, mat1);
  InsereMatLista(listaMat1, mat2);
  InsereMatLista(listaMat1, mat3);
  InsereMatLista(listaMat1, mat4);

  //d. Inicializar outra lista encadeada;
  ListaMat *listaMat2 = InicListaMat();

  //e. Inserir as matrizes transpostas na segunda lista encadeada;
  Matriz *mat1Trans = transposta(mat1);
  Matriz *mat2Trans = transposta(mat2);
  Matriz *mat3Trans = transposta(mat3);
  Matriz *mat4Trans = transposta(mat4);
  InsereMatLista(listaMat2, mat1Trans);
  InsereMatLista(listaMat2, mat2Trans);
  InsereMatLista(listaMat2, mat3Trans);
  InsereMatLista(listaMat2, mat4Trans);

  //f. Imprima as listas
  printf("\nLista 1: \n");
  ImprimeListaMat(listaMat1);
  printf("\n----------------------------------------------------------------\n");
  printf("\nLista 2: \n");
  ImprimeListaMat(listaMat2);

  //g. Retire algumas matrizes para verificar se o retira está funcionando (retire da primeira posição, última posição e caso comum);
  Matriz *primeira = RetiraMatLista(listaMat1, 0);
  printf("\nMatriz retirada: \n");
  imprimeMatriz(primeira);
  printf("\nLista sem a primeira matriz: \n");
  ImprimeListaMat(listaMat1);
  printf("\n----------------------------------------------------------------\n");

  Matriz *ultima = RetiraMatLista(listaMat1, 2);
  printf("\nMatriz retirada: \n");
  imprimeMatriz(ultima);
  printf("\nLista sem a ultima matriz: \n");
  ImprimeListaMat(listaMat1);
  printf("\n----------------------------------------------------------------\n");

  Matriz *meio = RetiraMatLista(listaMat2, 1);
  printf("\nMatriz retirada: \n");
  imprimeMatriz(meio);
  printf("\nLista 2 sem uma matriz do meio: \n");
  ImprimeListaMat(listaMat2);

  //Insira as matrizes novamente para verificar se o retira não “quebrou” a lista;
  printf("\nInserindo matriz 1: \n");
  InsereMatLista(listaMat1, primeira);
  ImprimeListaMat(listaMat1);
  printf("\n----------------------------------------------------------------\n");

  printf("\nInserindo matriz 4: \n");
  InsereMatLista(listaMat1, ultima);
  ImprimeListaMat(listaMat1);
  printf("\n----------------------------------------------------------------\n");

  printf("\nInserindo matriz 2 na lista 2: \n");
  InsereMatLista(listaMat2, meio);
  ImprimeListaMat(listaMat2);
  printf("\n----------------------------------------------------------------\n");

  //i. Libere as listas!
  LiberaListaMat(listaMat2);
  LiberaListaMat(listaMat1);

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