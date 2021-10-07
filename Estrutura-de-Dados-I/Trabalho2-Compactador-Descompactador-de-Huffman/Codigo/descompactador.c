//
// Descompactador de arquivos
//
// Criado por Gabrielly Cariman e Lucas Manfioletti em 25/09/21
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "arquivos.h"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Arquivo nao encontrado!\n");
    return 0;
  }

  long posicaoFimArv;

  long qntCaracteresArquivo = calculaQuantidadeDeCaracteres(argv[1]);

  char *nomeArquivoNovo = alteraFormato(argv[1], 2);

  remove(nomeArquivoNovo); //Exclui o arquivo se ele ja existir

  Arv *arv = leituraArvore(argv[1], &posicaoFimArv, qntCaracteresArquivo);

  imprimeArquivoOrignal(argv[1], nomeArquivoNovo, arv, posicaoFimArv, qntCaracteresArquivo);

  arvLibera(arv);

  free(nomeArquivoNovo);

  return 0;
}