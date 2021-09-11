#include "matriz.h"
#include <stdlib.h>
#include <stdio.h>

//Tipo matriz (tipo opaco)
//Estrutura interna do tipo deve ser definida na implementação do TAD
struct matriz
{
  int nlinhas;
  int ncolunas;
  int *matriz;
};

/*Inicializa uma matriz de nlinhas e ncolunas
 * inputs: nlinhas (no de linhas) e ncolunas (no de colunas)
 * output: ponteiro para a matriz inicializada
 * pre-condicao: nlinhas e ncolunas diferentes de 0
 * pos-condicao: matriz de retorno existe e contem nlinhas e ncolunas
 */
Matriz *inicializaMatriz(int nlinhas, int ncolunas)
{
  Matriz *mat = (Matriz *)malloc(sizeof(Matriz));
  if (!mat)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }
  mat->nlinhas = nlinhas;
  mat->ncolunas = ncolunas;
  int *matriz = (int *)malloc(sizeof(int) * nlinhas * ncolunas);
  if (!matriz)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }
  mat->matriz = matriz;
  return mat;
};

/*Modifica o elemento [linha][coluna] da matriz mat
 * inputs: a matriz, a linha, a coluna, e o novo elemento
 * output: nenhum
 * pre-condicao: matriz mat existe, linha e coluna são válidos na matriz
 * pos-condicao: elemento [linha][coluna] da matriz modificado
 */
void modificaElemento(Matriz *mat, int linha, int coluna, int elem)
{
  mat->matriz[linha * recuperaNColunas(mat) + coluna] = elem;
};

/*Retorna o elemento mat[linha][coluna]
 * inputs: a matriz, a linha e a coluna
 * output: elemento mat[linha][coluna]
 * pre-condicao: matriz mat existe, linha e coluna são válidos na matriz
 * pos-condicao: mat não é modificada
 */
int recuperaElemento(Matriz *mat, int linha, int coluna)
{
  return mat->matriz[linha * recuperaNColunas(mat) + coluna];
};

/*Retorna o número de colunas da matriz mat
 * inputs: a matriz
 * output: o número de colunas da matriz
 * pre-condicao: matriz mat existe
 * pos-condicao: mat não é modificada
 */
int recuperaNColunas(Matriz *mat)
{
  return mat->ncolunas;
};

/*Retorna o número de linhas da matriz mat
 * inputs: a matriz
 * output: o número de linhas da matriz
 * pre-condicao: matriz mat existe
 * pos-condicao: mat não é modificada
 */
int recuperaNLinhas(Matriz *mat)
{
  return mat->nlinhas;
};

/*Retorna a matriz transposta de mat
 * inputs: a matriz
 * output: a matriz transposta
 * pre-condicao: matriz mat existe
 * pos-condicao: mat não é modificada e matriz transposta existe
 */
Matriz *transposta(Matriz *mat)
{
  Matriz *transposta = inicializaMatriz(recuperaNColunas(mat), recuperaNLinhas(mat));
  for (int i = 0; i < recuperaNLinhas(mat); i++)
  {
    for (int j = 0; j < recuperaNColunas(mat); j++)
    {
      modificaElemento(transposta, j, i, recuperaElemento(mat, i, j));
    }
  }
  return transposta;
};

/*Retorna a matriz multiplicacao entre mat1 e mat2
 * inputs: as matrizes mat1 e mat2
 * output: a matriz multiplicação
 * pre-condicao: matrizes mat1 e mat2 existem, e o numero de colunas de mat1
 * correponde ao numero de linhas de mat2
 * pos-condicao: mat1 e mat2 não são modificadas e a matriz multiplicacao existe
 */
Matriz *multiplicacao(Matriz *mat1, Matriz *mat2)
{
  Matriz *multiplicacao = inicializaMatriz(recuperaNLinhas(mat1), recuperaNColunas(mat2));
  for (int i = 0; i < recuperaNLinhas(mat1); i++)
  {
    for (int j = 0; j < recuperaNColunas(mat2); j++)
    {
      int x = 0;
      for (int k = 0; k < recuperaNLinhas(mat2); k++)
        x += recuperaElemento(mat1, i, k) * recuperaElemento(mat2, k, j);
      modificaElemento(multiplicacao, i, j, x);
    }
  }
  return multiplicacao;
};

/*Imprime a matriz
 * inputs: matriz mat
 * output: nenhum
 * pre-condicao: matriz mat existe
 * pos-condicao: nenhuma
 */
void imprimeMatriz(Matriz *mat)
{
  for (int i = 0; i < recuperaNLinhas(mat); i++)
  {
    for (int j = 0; j < recuperaNColunas(mat); j++)
      printf("%d\t", recuperaElemento(mat, i, j));
    printf("\n");
  }
};

/*Libera memória alocada para a matriz
 * inputs: matriz mat
 * output: nenhum
 * pre-condicao: matriz mat existe
 * pos-condicao: toda a memória alocada para matriz foi liberada
 */
void destroiMatriz(Matriz *mat)
{
  free(mat->matriz);
  free(mat);
};
