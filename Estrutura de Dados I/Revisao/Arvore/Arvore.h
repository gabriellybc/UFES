// Implementação de uma árvore binária. Ou ela está vazia, ou um nó raiz com duas subárvores

typedef struct arv Arv;

//Cria uma árvore vazia
Arv *arv_criavazia();

// Cria uma árvore com a informação do nó raiz c, //e com subárvore esquerda e e subárvore direira d
Arv *arv_cria(char c, Arv *e, Arv *d); //Recebe a informação do nó, que nesse caso é um char e as arvores da esquerda e direita

//retorna true se a árvore estiver vazia e false caso contrário
int arv_vazia(Arv *a); //rebe a raíz da árvore

//libera o espaço de memória ocupado pela árvore a
Arv *arv_libera(Arv *a); //rebe a raíz da árvore

//indica a ocorrência (1) ou não (0) do caracter c
int arv_pertence(Arv *a, char c); // Recebe a raíz a e um caracter c que é a chave de busca para verificar se ele está na árvore ou não

//imprime as informações dos nós da árvore
void arv_imprime(Arv *a); //rebe a raíz da árvore