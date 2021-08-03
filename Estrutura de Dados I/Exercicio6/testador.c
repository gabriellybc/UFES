#include <stdio.h>
#include "ListaHet.h"

int main()
{
  // Criando alunos
  Aluno *al1 = inicializaAluno(123, "Aluno1", 5.3);
  Aluno *al2 = inicializaAluno(456, "Aluno2", 7.8);
  Aluno *al3 = inicializaAluno(789, "Aluno3", 8.4);
  Aluno *al4 = inicializaAluno(951, "Aluno4", 3.7);

  // Criando professores
  Professor *prof1 = inicializaProfessor(987654, "Professor1", 8500.50);
  Professor *prof2 = inicializaProfessor(654321, "Professor2", 11530.80);

  // Inicializando a lista
  ListaHet *churrasco = InicListaHet();

  // Incerindo alunos e professores na lista:
  InsereAluno(churrasco, al1);
  InsereProfessor(churrasco, prof1);
  InsereAluno(churrasco, al2);
  InsereAluno(churrasco, al3);
  InsereProfessor(churrasco, prof2);
  InsereAluno(churrasco, al4);

  printf("Imprimindo a lista:\n");
  ImprimeListaHet(churrasco);

  printf("Valor do churrasco: %.2f \n", ValorChurrasco(churrasco));

  //Liberando a memoria da lista
  LiberaListaHet(churrasco);

  //Liberando a memoria dos alunos
  destroiAluno(al1);
  destroiAluno(al2);
  destroiAluno(al3);
  destroiAluno(al4);

  //Liberando a memoria dos professores
  destroiProfessor(prof1);
  destroiProfessor(prof2);

  return 0;
}