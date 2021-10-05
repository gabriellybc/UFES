#include "listagen.h"
#include "Aluno.h"

//retira o aluno com a matricula dada
ListaGen *retiraAluno(ListaGen *lista, int matricula);

//verifica se o aluno esta na lista
int pertenceAluno(ListaGen *lista, int matricula);

//imprime a lista de Alunos
void imprimeListaAlunos(ListaGen *lista);

//calcula media de CRs da turma
float mediaTurma(ListaGen *lista);