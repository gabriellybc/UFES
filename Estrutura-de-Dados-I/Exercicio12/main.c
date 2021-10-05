#include <stdio.h>
#include "listaalunos.h"

int main()
{
  ListaGen *lista = criaLista();
  // Criando alunos
  Aluno *gab = inicializaAluno(123, "Gabi", 5.3);
  lista = insereLista(lista, gab);
  Aluno *hen = inicializaAluno(456, "Henrique", 7.8);
  lista = insereLista(lista, hen);
  Aluno *isa = inicializaAluno(789, "Isa", 8.4);
  lista = insereLista(lista, isa);
  Aluno *con = inicializaAluno(951, "Jose", 3.7);
  lista = insereLista(lista, con);
  Aluno *neu = inicializaAluno(357, "Neuzi", 8.8);
  lista = insereLista(lista, neu);

  imprimeListaAlunos(lista);

  //retira Gabi
  lista = retiraAluno(lista, 123);

  printf("\n");
  imprimeListaAlunos(lista);

  if (pertenceAluno(lista, 951) == 0)
    printf("\nConsul esta na lista!\n");
  else
    printf("\nConsul NAO esta na lista!\n");

  float media = mediaTurma(lista);

  printf("\nMedia da turma e': %.2f\n", media);

  liberaLista(lista);

  destroiAluno(gab);
  destroiAluno(hen);
  destroiAluno(isa);
  destroiAluno(neu);
  destroiAluno(con);

  return 0;
}
