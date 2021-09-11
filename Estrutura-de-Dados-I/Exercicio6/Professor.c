#include "Professor.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Tipo Professor (tipo opaco)
//Estrutura interna do tipo deve ser definida na implementação do TAD
struct professor
{
  int siape;
  char *nome;
  float salario;
};

/*Inicializa um Professor*/
Professor *inicializaProfessor(int siape, char *nome, float salario)
{
  Professor *prof = (Professor *)malloc(sizeof(Professor));
  if (!prof)
  {
    printf("** Erro: Memoria Insuficiente **");
    exit;
  }
  prof->siape = siape;
  prof->salario = salario;
  prof->nome = strdup(nome);
  return prof;
};

/*Imprime o Professor*/
void imprimeProfessor(Professor *prof)
{
  printf("siape: %d, nome: %s, salario: %.2f\n", prof->siape, prof->nome, prof->salario);
};

/*Retorna a siape do Professor*/
int retornaSiape(Professor *prof)
{
  return prof->siape;
};

/*Retorna nome do Professor*/
char *retornaNomeProfessor(Professor *prof)
{
  return prof->nome;
};

/*Retorna salario do Professor*/
float retornaSalario(Professor *prof)
{
  return prof->salario;
};

/*Libera memória alocada para Professor*/
void destroiProfessor(Professor *prof)
{
  free(prof->nome);
  free(prof);
};
