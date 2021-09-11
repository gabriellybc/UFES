#ifndef Aluno_H_
#define Aluno_H_

//Tipo Aluno (tipo opaco)
//Estrutura interna do tipo deve ser definida na implementação do TAD
typedef struct aluno Aluno;

/*Inicializa uma Aluno*/
Aluno *inicializaAluno(int mat, char *nome, float CR);

/*Imprime o Aluno*/
void imprimeAluno(Aluno *al);

/*Retorna matricula do Aluno*/
int retornaMat(Aluno *al);

/*Retorna nome do Aluno*/
char *retornaNomeAluno(Aluno *al);

/*Retorna CR do Aluno*/
float retornaCR(Aluno *al);

/*Libera memória alocada para o Aluno*/
void destroiAluno(Aluno *al);

#endif /*Aluno_H_*/
