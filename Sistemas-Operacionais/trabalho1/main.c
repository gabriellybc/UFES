#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include "leitor_cmd.h"
#include "exec_cmd.h"
#include "config.h"


/*
Exemplos de comandos:
ls -l
ping -c 4 github.com
*/

void sig_ctrl(int signo){
    printf("\nNão adianta me enviar o sinal por Ctrl-... . Estou vacinado!!\n");
}

int main() {
    char linha[TAMANHO_MAXIMO]; // Buffer para armazenar a linha de comando
    char* comandos[NUM_COMANDOS_MAXIMO]; // Vetor para armazenar os comandos separados
    int num_comandos = 0; // Número de comandos encontrados na linha de comando
    int num_subcomandos = 0; // Número de subcomandos encontrados em um comando externo
    
    // Instalando o tratador de sinais para o terminal:
    struct sigaction act;
    struct sigaction oact_sigint;
    struct sigaction oact_sigtstp;
    struct sigaction oact_sigquit;
    
    act.sa_handler = sig_ctrl;
    act.sa_flags = 0;				/* no special options */
    if ((sigemptyset(&act.sa_mask)== -1) || /*no other signals blocked*/
        (sigaction(SIGINT, &act, &oact_sigint)==-1))
        perror("Failed to install SIGINT signal handler");
    if (sigaction(SIGTSTP, &act, &oact_sigtstp)==-1)
        perror("Failed to install SIGTSTP signal handler");
    if (sigaction(SIGQUIT, &act, &oact_sigquit)==-1)
        perror("Failed to install SIGQUIT signal handler");

    while (true) {
        printf("acsh> "); // Exibe o prompt do shell
        ler_comando(linha); // Lê o comando a partir do stdin e armazena em linha

        separar_comandos(linha, comandos, &num_comandos); // Separa os comandos da linha de entrada

        tratar_comandos(comandos, num_comandos, oact_sigint, oact_sigtstp, oact_sigquit); // Processa os comandos separados

        // O loop continua para aguardar novos comandos do usuário
    }

    return 0;
}
