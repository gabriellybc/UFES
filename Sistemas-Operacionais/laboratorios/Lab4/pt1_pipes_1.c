/*
#include <signal.h>
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>


#define BUFF_SIZE 256

int main(int argc,char *argv[]){
    pid_t pid1, pid2, pid3;
    pid_t pid = 1;
    // Variaveis para o pipe 
    int fd[3][2]; // 3 pipes
    // P0 = pai | P1 = filho 1 | P2 = filho 2 | P3 = filho 3
    // Pipe1 = P0 => P1 | Pipe2 = P1 => P2 | Pipe3 = P2 => P0
    
    // Variavel lida pelo pai
    int x, y;

    // =================================================================
    // Criando os pipes no processo pai (3)
    for (int i = 0; i < 3; i++){
        if (pipe(fd[i]) < 0){
            perror("Erro ao criar o pipe!");
            return 1;
        }
    }

    // =================================================================
    // a) Processo pai le um valor de 1 a 5
    while(1){
        printf("Digite um numero entre 1 e 5: ");
        scanf("%d", &x);

        if ((x < 1) || (x > 5)){
            printf("Numero invalido, o valor deve ser de 1 a 5!\n");
        } else {
            break;
        }
    }

    // ========================================================================
    // b) Criando os dois filhos:
    for (int i = 0; i < 2; i++){
        if ((pid = fork()) < 0){ // Se deu erro
            printf("Erro no fork!\n");
            return 2;
        } else if (pid == 0) { // Se sao os filhos
            if (i == 0) {
                pid1 = getpid();
            } else if (i == 1){
                pid2 = getpid();
            }
            break;
        }
    }

    // ========================================================================
    if (pid > 0){   // Processo pai
        // ====================================================================
        // c) Enviando x para o Filho 1
        if (write(fd[0][1], &x, sizeof(int)) == -1){
            printf("Erro ao escrever no pipe!\n");
            return 3;
        }

        // ====================================================================
        // d) Enviando a frase para o Filho 1
        char frase[] = "Meu filho, crie e envie para o seu irmão um array de números inteiros com valores randômicos entre 1 e o valor enviado anteriormente. O tamanho do array também deve ser randômico, na faixa de 1 a 10 \0";
        int size_frase = strlen(frase)+1;
        // Enviando o tamanho da frase
        if (write(fd[0][1], &size_frase, sizeof(int)) == -1){
            printf("Erro ao escrever no pipe!\n");
            return 15;
        }
        // Enviando a frase
        if (write(fd[0][1], frase, sizeof(char)*size_frase) == -1){
            printf("Erro ao escrever no pipe!\n");
            return 16;
        }

        // ====================================================================
        // i) Agora, aguarda para receber a soma do vetor do Filho 2
        int soma_vet;
        
        if (read(fd[2][0], &soma_vet, sizeof(int)) == -1){
            printf("Erro ao ler do pipe!\n");
            return 11;
        }

        printf("Recebi do meu segundo filho a soma do vetor: %d.\n", soma_vet);

        // ====================================================================
        // j) Cria o terceiro filho:
        if ((pid3 = fork()) < 0){
            printf("Erro no fork!\n");
            return 12;
        } else if (pid3 > 0) { // Pai
            char resul[BUFF_SIZE];
            // Espera o filho mandar as informacoes:
            if (read(fd[0][0], resul, sizeof(char)*BUFF_SIZE) == -1){
                printf("Erro ao ler do pipe!\n");
                return 13;
            }
            printf("Recebi do meu terceiro filho: %s\n", resul);
        } else {
            // =================================================================
            // FALTANDO
            // =================================================================
            // Executa "date" e envia pro pai atraves do pipe[0]
            // Processo para desviar o retorno de 'date':
            int file2 = dup2(fd[0][1], STDOUT_FILENO);

            execl("/bin/date", "/bin/date", NULL);
        }


    } else if (getpid() == pid1) { // Filho 1
        // ====================================================================
        // c) Recebendo x do Pai
        if (read(fd[0][0], &y, sizeof(int)) == -1){
            printf("Erro ao ler do pipe!\n");
            return 4;
        }
        
        // ====================================================================
        // d) Recebendo a frase do pai
        // Primeiro, recebe o tamanho da frase:
        int size_frase;
        if (read(fd[0][0], &size_frase, sizeof(int)) == -1){
            printf("Erro ao ler do pipe!\n");
            return 17;
        }
        // Recebendo a frase:
        char frase_f[size_frase];
        if (read(fd[0][0], frase_f, sizeof(char)*size_frase) == -1){
            printf("Erro ao ler do pipe!\n");
            return 18;
        }
        // ====================================================================
        // e) Imprimindo a frase recebida do Pai
        printf("%s\n", frase_f);

        // ====================================================================
        // f) Criando o vetor de tamanho randomico
        // Gerando uma seed para rand
        srand(time(NULL));

        // Tamanho do vetor entre 1 e 10
        //rand() % (max_number + 1 - minimum_number) + minimum_number;
        int arr_size = (rand() % 10) + 1;

        int arr[arr_size];
        // Gerando os valores do vetor:
        printf("Array: [");
        for (int i = 0; i < arr_size; i++){
            arr[i] = rand() % x + 1;
            if (i < arr_size-1)
                printf("%d, ", arr[i]);
            else   
                printf("%d]\n", arr[i]);
        }

        // ====================================================================
        // g) Primeiro, envia o tamanho do vetor para o irmao
        if (write(fd[1][1], &arr_size, sizeof(int)) == -1){
            printf("Erro ao escrever no pipe!\n");
            return 6;
        }
        // Entao, envia o vetor
        if (write(fd[1][1], arr, sizeof(int)*arr_size) == -1){
            printf("Erro ao escrever no pipe!\n");
            return 7;
        }
        
        // P1 nao tem mais nada pra fazer, pode sair

    } else if (getpid() == pid2) { // Filho 2
        // ====================================================================
        // h) Aguarda o recebimento do tamanho do vetor que o Filho 1 enviara
        int arr_size2;
        if (read(fd[1][0], &arr_size2, sizeof(int)) == -1){
            printf("Erro ao ler do pipe!\n");
            return 8;
        }

        // Cria o vetor que recebera o vetor vindo do Filho 1
        int arr2[arr_size2];

        // Aguarda o recebimento do vetor que o Filho 1 enviara
        if (read(fd[1][0], arr2, sizeof(int)*arr_size2) == -1){
            printf("Erro ao ler do pipe!\n");
            return 9;
        }

        int soma = 0;
        for (int i = 0; i < arr_size2; i++){
            soma += arr2[i];
        }

        // Enviando a soma para o pai:
        if (write(fd[2][1], &soma, sizeof(int)) == -1){
            printf("Erro ao escrever no pipe!\n");
            return 10;
        }

        // P2 nao tem mais nada pra fazer, pode sair

    }

    // ========================================================================
    // Apos o pai terminar, espera todos os filhos terminarem para finalizar:
    if (pid > 0){
        // Espera os tres filhos finalizarem
        for (int i = 0; i < 3; i++){
            wait(NULL);
        }
    }

    // ========================================================================
    // Fechando todos os pipes (todos os processos rodam as linhas abaixo)
    for(int i = 0; i < 4; i++){
        close(fd[i][0]);    // Fechando read
        close(fd[i][1]);    // Fechando write
    }

}
