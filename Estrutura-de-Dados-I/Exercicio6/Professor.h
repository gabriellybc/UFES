#ifndef PROFESSOR_H_
#define PROFESSOR_H_

//Tipo Professor (tipo opaco)
//Estrutura interna do tipo deve ser definida na implementação do TAD
typedef struct professor Professor;

/*Inicializa um Professor*/
Professor *inicializaProfessor(int siape, char *nome, float salario);

/*Imprime o Professor*/
void imprimeProfessor(Professor *prof);

/*Retorna matricula do Professor*/
int retornaSiape(Professor *prof);

/*Retorna nome do Professor*/
char *retornaNomeProfessor(Professor *prof);

/*Retorna CRa do Professor*/
float retornaSalario(Professor *prof);

/*Libera memória alocada para o Professor*/
void destroiProfessor(Professor *prof);

#endif /*Professor_H_*/
