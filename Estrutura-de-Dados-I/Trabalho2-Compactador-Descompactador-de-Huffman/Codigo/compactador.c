//
// Compactador de arquivos
//
// Criado por Gabrielly Cariman e Lucas Manfioletti em 02/09/21
//

#include <stdio.h>
#include <stdlib.h>
#include "listaCodificacao.h"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Arquivo nao encontrado!\n");
    return 0;
  }

  long qntCaracteresArquivo = calculaQuantidadeDeCaracteres(argv[1]);
  if (qntCaracteresArquivo <= 1)
  {
    printf("Quantidade de caracteres insuficiente para a compactacao!\n");
    return 0;
  }

  int *vetor = repeticaoCaracteres(argv[1]);

  char *nomeArquivoNovo = alteraFormato(argv[1], 1);

  ListaArvore *listaArv = inicListaArvore();

  ListaCodificacao *listaCod = inicListaCodificacao();

  if (defineListaArvore(listaArv, vetor) <= 1)
  {
    printf("Variacao de caracteres insuficiente para a compactacao!\n");
    return 0;
  }

  codificaArvore(listaArv);

  tabelaCodificacao(listaCod, listaArv);

  imprimeArvoreBinario(listaArv, nomeArquivoNovo);

  imprimeNumCaracteresBinario(argv[1], nomeArquivoNovo, qntCaracteresArquivo);

  imprimeCodificacaoBinario(listaCod, argv[1], nomeArquivoNovo);

  liberaListaCodificacao(listaCod);

  liberaListaArvore(listaArv);

  free(vetor);

  free(nomeArquivoNovo);

  return 0;
}