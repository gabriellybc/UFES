#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void sigusr1_handler(int signum) {
    printf("Eu apanhei o SIGUSR1\n");
}

int main() {
    pid_t pid;

    // Cria o processo filho
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Falha ao criar processo filho\n");
        exit(1);
    } else if (pid == 0) {
        // Processo filho

        printf("Eu sou o processo filho, pid = %d\n", getpid());

        // Registra o manipulador de sinal para SIGUSR1
        signal(SIGUSR1, sigusr1_handler);

        while (1) {
            char c = getchar();
            printf("Caractere digitado: %c\n", c);
        }

        // O processo filho nunca chega nesse ponto, pois fica preso no loop acima
        exit(0);
    } else {
        // Processo pai

        printf("Eu sou o processo pai, pid = %d\n", getpid());

        sleep(5);

        // Envia o sinal SIGUSR1 para o processo filho
        kill(pid, SIGUSR1);

        // Espera 20 segundos para que o filho termine a leitura
        sleep(20);

        // Se o filho ainda estiver em execução, envia o sinal SIGKILL para encerrar
        if (waitpid(pid, NULL, WNOHANG) == 0) {
            printf("Meu filho ainda não terminou. Cansei de esperar, vou vazar com um sinal SIGKILL\n");
            kill(pid, SIGKILL);
        }
    }

    return 0;
}
