#include <stdio.h>

int main()
{
  //String em C: Vetor do tipo char, terminado com o caractere nulo '\0'
  char str[4];
  str[0] = 'O';
  str[1] = 'l';
  str[2] = 'a';
  str[3] = '\0';
  printf("%s \n", str);

  //Exemplo scanf
  //Captura caracter
  char a;
  printf("Digite um caracter: ");
  scanf(" %c", &a); // Deixar um espaço antes do %c faz com que os espaços sejam ignorados até o caracter ser digitado
  printf("Carcter Digitado: %c\n", a);

  //String
  char str2[81];

  printf("Digite uma string ");
  scanf("%s", str2); // o %s só pega o primeiro nome até pegar um espaço em branco
  // aqui não precisa passar um endereço de memória pq o str2 já é o endereço da primeira posição da sting
  printf("String Digitada: %s\n", str2);

  //Especificador %[] melhor que %s
  printf("Digite outra string: ");
  scanf(" %80[^\n]", str); // Dentro do [] falo o que eu quero ler ou usar ^ para o que não quero ler depois do ^
  //Para " %80[^\n]" temos: quero ler todos os caracteres até o \n. Além disso, eu só vou ler 80 caracteres. Eu também estou ignorando os espaços do início
  printf("String Digitada: %s\n", str);

  return 0;
}