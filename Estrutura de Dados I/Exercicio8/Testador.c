#include "Fila.h"

int main()
{
  // Criando alunos
  Aluno *al1 = inicializaAluno(123, "Aluno1", 5.3);
  Aluno *al2 = inicializaAluno(456, "Aluno2", 7.8);
  Aluno *al3 = inicializaAluno(789, "Aluno3", 8.4);
  Aluno *al4 = inicializaAluno(951, "Aluno4", 3.7);

  Fila *f1 = inicFila();
  Fila *f2 = inicFila();

  Aluno *retirado;
  retirado = retiraFila(f1); //Fila vazia
  retirado = retiraFila(f2); //Fila vazia

  insereFila(f1, al1);
  insereFila(f1, al2);
  insereFila(f1, al3);
  insereFila(f1, al4);

  insereFila(f1, al1); //Fila cheia

  printf("\nFila1: \n");
  imprimeFila(f1);

  insereFila(f2, retiraFila(f1));

  printf("\nFila1: \n");
  imprimeFila(f1);

  printf("\nFila2: \n");
  imprimeFila(f2);

  insereFila(f2, retiraFila(f1));

  printf("\nFila1: \n");
  imprimeFila(f1);

  printf("\nFila2: \n");
  imprimeFila(f2);

  //Liberando a memoria das filas
  destroiFila(f1);
  destroiFila(f2);

  //Liberando a memoria dos alunos
  destroiAluno(al1);
  destroiAluno(al2);
  destroiAluno(al3);
  destroiAluno(al4);

  return 0;
}