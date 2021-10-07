#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "arquivos.h"

//Cria um vetor de inteiros com 256 elementos em que o indice é o código ASCII do caracter e o conteudo é o número de vezes que ele aparece no arquivo passado
int *repeticaoCaracteres(char *nomeArquivo)
{
  int *repeticao = (int *)malloc(256 * sizeof(int));
  for (int i = 0; i < 256; i++)
    repeticao[i] = 0; //zerando todo o vetor

  FILE *arqLeitura;
  unsigned char c;
  arqLeitura = fopen(nomeArquivo, "rb");
  if (arqLeitura == NULL)
  {
    printf("** ERRO: O arquivo não foi aberto **");
    exit;
  }
  else
  {
    //faz a leitura do caracter no arquivo apontado por arqLeitura ate o final do arquivo
    while (fread(&c, sizeof(char), 1, arqLeitura) != 0)
      repeticao[c]++;
  }
  fclose(arqLeitura); //fechando o arquivo
  return repeticao;
}

// Adiciona ao final do arquivo binario os bytes do bitmap passado
void escreveBinario(bitmap *bm, char *nomeArquivo)
{
  FILE *arqEscrita;
  arqEscrita = fopen(nomeArquivo, "ab");
  if (arqEscrita == NULL)
  {
    printf("** ERRO: O arquivo não foi aberto ou criado**");
    exit(1);
  }
  else
  {
    unsigned int tamanho, qntBytes;
    tamanho = bitmapGetLength(bm);
    qntBytes = (tamanho % 8) ? (tamanho / 8) + 1 : tamanho / 8;
    fwrite(bitmapGetContents(bm), sizeof(char), qntBytes, arqEscrita);
  }
  fclose(arqEscrita); //fechando o arquivo
}

char *alteraFormato(char *nomeArquivo, int opcao)
{
  int i = 0;
  char *nomeArquivoNovo;
  if (opcao == 1)
  {
    nomeArquivoNovo = (char *)malloc((strlen(nomeArquivo) + 6) * sizeof(char));
    // Realiza a cópia do nomeArquivo para nomeArquivoNovo
    strcpy(nomeArquivoNovo, nomeArquivo);
    // Realiza a concatenação do conteúdo de ".comp" o nomeArquivoNovo
    strcat(nomeArquivoNovo, ".comp");
    strcat(nomeArquivoNovo, "\0");
    return nomeArquivoNovo;
  }
  else
  {
    //remove o formato .comp do final da string
    if (nomeArquivo[strlen(nomeArquivo) - 5] != '.')
    {
      printf("ERRO, formato não suportado\n");
      return NULL;
    }
    else
    {
      nomeArquivoNovo = (char *)malloc((strlen(nomeArquivo) - 4) * sizeof(char));
      for (i = 0; i < (strlen(nomeArquivo) - 5); i++)
        nomeArquivoNovo[i] = nomeArquivo[i];
      nomeArquivoNovo[strlen(nomeArquivo) - 5] = '\0';
      return nomeArquivoNovo;
    }
  }
}

//Le quantidade de folhas e armazena a arvore do arquivo binario em uma estrutua Arvore
Arv *leituraArvore(char *nomeArquivo, long *posicaoFimArv, long qntCaracteresArquivo)
{
  Arv *a;
  *posicaoFimArv = 0; // posicao em bytes do arquivo
  FILE *arqLeitura;
  arqLeitura = fopen(nomeArquivo, "rb");
  if (arqLeitura == NULL)
  {
    printf("** ERRO: O arquivo não foi aberto **");
    exit;
  }
  else
  {
    //Leitura da quantidade de folhas total
    bitmap *bmQntFolhas = bitmapInit(8);
    fread(bitmapGetContents(bmQntFolhas), sizeof(char), 1, arqLeitura);
    int totalFolhas = bin2dec(bmQntFolhas) + 1;
    bitmapLibera(bmQntFolhas);

    //Leitura da arvore
    int folhasAtuais = 0, i = 0, leituras = 1;
    bool flagFolhasMax = 0;
    bitmap *bmArvore;
    if (qntCaracteresArquivo < 100000)
    {
      bmArvore = bitmapInit(qntCaracteresArquivo * 8);
      fread(bitmapGetContents(bmArvore), sizeof(char), qntCaracteresArquivo, arqLeitura);
    }
    else
    {
      bmArvore = bitmapInit(100000 * 8);
      fread(bitmapGetContents(bmArvore), sizeof(char), 100000, arqLeitura);
    }
    a = redefineArvore(a, bmArvore, totalFolhas, &folhasAtuais, &flagFolhasMax, &i, arqLeitura, &leituras, posicaoFimArv);
    bitmapLibera(bmArvore);
  }
  fclose(arqLeitura); //fechando o arquivo
  return a;
}

//Le quantidade de caracteres e armazena o valor no arquivo binario
void imprimeNumCaracteresBinario(char *nomeArquivo, char *nomeArquivoNovo, long qntCaracteres)
{
  //grava quantidade de caracteres com codificação 8 bits após a arvore no arquivo binario
  bitmap *bm;
  int var;
  do
  {
    var = (qntCaracteres % 10);
    qntCaracteres = qntCaracteres / 10;
    bm = dec2bin(var);
    escreveBinario(bm, nomeArquivoNovo);
    bitmapLibera(bm);
  } while (qntCaracteres > 0);
  bm = dec2bin(10); //10 sera utilizado aqui para separar o cabecalho da codificação
  escreveBinario(bm, nomeArquivoNovo);
  bitmapLibera(bm);
}

//Calcula a quantidade de caracteres no arquivo
long calculaQuantidadeDeCaracteres(char *nomeArquivo)
{
  //calcula o tamanho do arquivo
  long tamanho = 0;
  FILE *arqLeitura = fopen(nomeArquivo, "rb");
  if (arqLeitura == NULL)
  {
    printf("** ERRO: O arquivo não foi aberto **");
    exit;
  }
  else
  {
    // guarda o estado ante de chamar a função fseek
    long posicaoAtual = ftell(arqLeitura);
    // calcula o tamanho
    fseek(arqLeitura, 0, SEEK_END);
    tamanho = ftell(arqLeitura);
    // recupera o estado antigo do arquivo
    fseek(arqLeitura, posicaoAtual, SEEK_SET);
  }
  fclose(arqLeitura);
  return tamanho;
}

//Le a quantidade de caracteres do arquivo binário e restaura o arquivo original
void imprimeArquivoOrignal(char *nomeArquivo, char *nomeArquivoNovo, Arv *arv, long posicaoFimArv, long qntCaracteresArquivo)
{
  int vezesLeitura = 0, i, dec = 0, indice = 0;
  long qntCaracteres = 0, qntCaracteresParcela = 0, caracteresLidos = 0;
  FILE *arqLeitura;
  arqLeitura = fopen(nomeArquivo, "rb");
  if (arqLeitura == NULL)
  {
    printf("** ERRO: O arquivo não foi aberto **");
    exit;
  }
  else
  {
    //leitura da numero de caracteres
    fseek(arqLeitura, posicaoFimArv + 1, SEEK_SET);
    i = 0;
    int observacao = 0;
    bitmap *bmQntCaracteres = bitmapInit(8);
    while (fread(bitmapGetContents(bmQntCaracteres), sizeof(char), 1, arqLeitura) != 0)
    {
      observacao++;
      dec = bin2dec(bmQntCaracteres);
      if (observacao == 1 && dec > 10)
      {
        bitmapLibera(bmQntCaracteres);
        bmQntCaracteres = bitmapInit(8);
        fread(bitmapGetContents(bmQntCaracteres), sizeof(char), 1, arqLeitura);
      }
      if (dec < 10) //faz com que seja lido todos os numeros
      {
        //faz a leitura do arquivo de "trás pra frente" e atribui as dezenas de acordo com a quantidade exponencial
        qntCaracteres = qntCaracteres + (dec * pow((double)10, (double)i));
        i++;
        bitmapLibera(bmQntCaracteres);
        bmQntCaracteres = bitmapInit(8);
      }
      else
        break;
    }
    bitmapLibera(bmQntCaracteres);

    if (qntCaracteresArquivo < 100000)
    {
      bitmap *bm = bitmapInit(qntCaracteresArquivo * 8);
      unsigned char c;
      bitmap *bmLetra;
      fread(bitmapGetContents(bm), sizeof(char), qntCaracteresArquivo, arqLeitura);
      for (i = 0; i < qntCaracteres; i++)
      {
        c = retornaCaracter(bm, arv, &indice);
        bmLetra = dec2bin(c);
        escreveBinario(bmLetra, nomeArquivoNovo);
        bitmapLibera(bmLetra);
      }
      bitmapLibera(bm);
    }
    else
    {
      for (vezesLeitura = (qntCaracteres / 100000); vezesLeitura >= 0; vezesLeitura--)
      { //verifica a quantidade de leituras necessárias
        unsigned char c;
        bitmap *bmLetra, *bmCaracteres = bitmapInit(8 * 100000);
        fread(bitmapGetContents(bmCaracteres), sizeof(char), 100000, arqLeitura);
        for (i = 0; i < 100000; i++)
        {
          c = retornaCaracter(bmCaracteres, arv, &indice);
          bmLetra = dec2bin(c);
          escreveBinario(bmLetra, nomeArquivoNovo);
          bitmapLibera(bmLetra);
          caracteresLidos++;
          if (caracteresLidos == qntCaracteres)
            break;
        }
        indice = 0;
        bitmapLibera(bmCaracteres);
      }
    }
  }
  fclose(arqLeitura);
}
