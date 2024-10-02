#ifndef PONTO_H
#define PONTO_H

/*
  Estrutura ponto que armazena suas coordenadas, seu id,
  seu id de árvore, o id de árvore do seu pai e o tamanho da sua árvore
*/
typedef struct Ponto * ponto;

/*
  Função para criar os pontos a partir de um id, quantidade de eixos
  e das componentes da sua coordenada
*/
ponto ponto_init(char* id, float* componentes);

/*
Função para calcular a distância euclidiana entre 2 pontos
*/
float ponto_distancia(void* p1, void* p2, int qtdEixos);

/*
Função para liberar a memória de um ponto
*/
void ponto_free(void* p);

/*
  Função usada no debug para imprimir os dados de um ponto
*/
void ponto_imprime(void* p, int m);

/*
  Função usada para obter o id de um ponto
*/
char* ponto_getId(ponto p);

/*
  Função usada para obter o id de árvore de um ponto
*/
unsigned int ponto_getArvId(ponto p);

/*
  Função usada para setar o pai do ponto
  (seta o id de árvore do pai)
*/
void ponto_setArvPid(ponto p, unsigned int id);

/*
  Função usada para obter o id de árvore do pai do ponto
*/
unsigned int ponto_getArvPid(ponto p);

/*
  Função usada pára inicializar os valores do id de árvore do ponto
  e do pai do ponto (valor = id)
*/
void ponto_setArvIds(void* pt, unsigned int id);

/*
  Função usada para setar o tamanho da árvore do ponto
*/
void ponto_setArvSize(ponto p, unsigned int size);

/*
  Função usada ára obter o tamanho da árvore do ponto
*/
unsigned int ponto_getArvSize(ponto p);

/*
  Função usada para comparar 2 pontos pela ordem alfabética de seus ids
*/
int ponto_compare(const void* pt1, const void* pt2);

#endif