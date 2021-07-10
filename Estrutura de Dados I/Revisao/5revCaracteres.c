#include <stdio.h>
#include <string.h>

int digito(char c);
char maiuscula(char c);
char *duplica(char *s);
char *lelinha(void);

int main()
{
  printf("tamanho char %lu bytes(s)\n", sizeof(char));
  // o char tem tamnho de 1 byte, ou seja, 8 bites, então podemos codificar 256 caracteres. Tabela ASCII
  // %lu é o unsigned long
  // %lf é double

  char c = 97;
  printf("%d %c\n", c, c);
  // em um char cabem coisas até 1 byte por isso da pra colocar
  // "97" no %d é o codigo de "a" do %c na tabela ASCII

  char c2 = 'a';
  printf("%d %c\n", c2, c2); //O mesmo valor do exemplo acima é obtido

  printf("%c e digito? %d\n", c, digito(c));

  c = '0';
  c2 = '5';

  printf("%c e digito? %d\n", c, digito(c));
  printf("%c e digito? %d\n", c2, digito(c2));
  // ------------------------------
  c = 'P';
  c2 = 'p';

  printf("Maiúscola de %c é %c", c, maiuscula(c));
  printf("Maiúscola de %c é %c", c2, maiuscula(c2));

  return 0;
}

//Função para verificar se um caracter é dígito
int digito(char c)
{
  if ((c >= '0') && (c <= '9')) //Só pode pq os digitos estão em sequencia na tabela ASCII
    return 1;
  else
    return 0;
}

//Função que retorna a letra maiuscula de determinado caracter
char maiuscula(char c)
{
  if (c >= 'a' && c <= 'z') // Se o caracter for uma letra minuscula
    c = c - 'a' + 'A';      // Encotro a distancia do caracter para a primeireira letra "a", se somo com a distancia até "A", encontro o caracter maiusculo
  return c;                 // Se ele não for minusculo, retorno ele mesmo
}