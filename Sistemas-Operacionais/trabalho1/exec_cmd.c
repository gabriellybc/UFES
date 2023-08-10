#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "exec_cmd.h"
#include "config.h"

// Executa o comando 'cd' para mudar de diretório
void executar_comando_cd(char* diretorio) {
    int resultado = chdir(diretorio);
    if (resultado == 0) {
        char caminho_atual[2500];
        if (getcwd(caminho_atual, sizeof(caminho_atual)) != NULL) {
            printf("Diretório alterado para: %s\n", caminho_atual);
        } else {
            perror("Erro ao obter o diretório atual");
        }
    } else {
        perror("Erro ao mudar de diretório");
    }
}

// Executa o comando 'exit' para finalizar o shell
void executar_comando_exit() {
    pid_t pid;
    // Finalizar os processos de background
    if ((pid = fork()) < 0){
        fprintf(stderr, "Fork failed!\n");
        return;
    } else if (pid > 0) {
        waitpid(pid, NULL, 0);
    } else {
        if (kill(-1, SIGTERM) < 0){
            printf("\n\n");
            printf("Erro!.\n");
            printf("\nMais informacoes...\n");
            printf("Erro: %d\n", errno);
            printf("%s.\n", strerror(errno));
            printf("\n\n");
        }
    }

    // Aguardar a finalização dos processos de background
    // Finalizar o shell
    printf("Finalizando o shell...\n");
    exit(0);
}

// Copia um conjunto de strings de 'comandos' para 'subcomandos'
static void copiar_strings(char** comandos, int inicio, int fim, char** subcomandos) {
    int subcomandos_idx = 0;
    for (int i = inicio; i <= fim; i++) {
        subcomandos[subcomandos_idx] = comandos[i];
        subcomandos_idx++;
    }
    subcomandos[subcomandos_idx] = NULL;
}

// Trata os comandos digitados pelo usuário
void tratar_comandos(char** comandos, int num_comandos, struct sigaction oact_sigint, struct sigaction oact_sigtstp, struct sigaction oact_sigquit) {
    if (num_comandos == 0) {
        printf(" ************** Erro *************** \n");
        return;
    }
    if (strcmp(comandos[0], "") == 0 || strcmp(comandos[0], "\0") == 0 || strcmp(comandos[0], "\n") == 0 || strcmp(comandos[0], "\t") == 0 || strcmp(comandos[0], "\r") == 0 || strcmp(comandos[0], " ") == 0) {
        num_comandos = 0;
        printf("Erro: nenhum comando foi digitado corretamente\n");
        return;
    }

    int ultima_posicao = 0, subcomandos_externos = 0, coracoes = 0, qnt_comandos_externos = 0;
    bool tem_externo = false, tem_coracao = false, foreground = false; 

    for (int i = 0; i < num_comandos; i++) {
        if (strcmp(comandos[i], "cd") == 0) {
            if (tem_externo) {
                printf("Erro: o comando cd deve ser o primeiro\n");
                return;
            }
            if (num_comandos > 2) {
                printf("Erro: o comando cd deve ser o primeiro e deve ter apenas o caminho\n");
                return;
            }
            if (num_comandos == 1) {
                printf("Erro: o comando cd deve ser o primeiro e deve ter o caminho\n");
                return;
            }
            executar_comando_cd(comandos[i+1]);
            return;

        } else if (strcmp(comandos[i], "exit") == 0) {
            if (tem_externo) {
                printf("Erro: o comando cd deve ser o primeiro\n");
                return;
            }
            if (num_comandos > 1) {
                printf("Erro: o comando exit deve ser o primeiro e nao deve ter argumentos\n");
                return;
            }
            executar_comando_exit();
            return;

        } else {
            pid_t pid_f;
            pid_t pid_s = 0;
            
            if (tem_externo == false) {
                if ((pid_f = fork()) < 0){
                    fprintf(stderr, "Fork failed!\n");
                    return;
                }
                // Resetando para o tratador de sinais padrão
                sig_ctrl_padrao(oact_sigint, oact_sigtstp, oact_sigquit);
            }
            
            tem_externo = true;
            subcomandos_externos++;

            if (qnt_comandos_externos > QNTD_COMANDOS) {
                printf("Erro: o numero maximo de quantidade de comandos externos eh %d\n", QNTD_COMANDOS);
                return;
            }

            if (strcmp(comandos[i], "<3") == 0) {
                coracoes++;
                tem_coracao = true;
                if (ultima_posicao == i) {
                    printf("Erro: o comando <3 deve estar em uma linha de comando com um comando externo\n");
                    return;
                }
                if (i == num_comandos-1) {
                    printf("Erro: o comando <3 nao deve estar no final de uma linha de comando\n");
                    return;
                }
                if (coracoes > NUM_SUBCOMANDOS_MAXIMO){
                    printf("Erro: o comando <3 deve estar em uma linha de comando com no maximo 1 comando e 3 argumentos\n");
                    return;
                }
                if (num_comandos < 3) {
                    printf("Erro: o comando <3 deve estar em uma linha de comando com pelo menos 2 comandos\n");
                    return;
                }
                // Multiplos comandos externos (em background)
                if ((pid_f == 0) && (pid_s == 0)){
                    pid_s = setsid();
                    
                    // Como tera multiplos processos na sessao:
                    // - Configura o tratador de SIGUSR1 para processos aglomerados
                    if (signal(SIGUSR1, sig_usr1_grp) == SIG_ERR){
                        printf("Erro ao tentar me isolar do SIGUSR1\n");
                    }
                } else if (pid_f > 0) {
                    return;
                }
                
                char* subcomandos[i - ultima_posicao];
                copiar_strings(comandos, ultima_posicao, i-1, subcomandos);

                exec_cmds(subcomandos, foreground);
                
                ultima_posicao = i+1;
                subcomandos_externos = 0;
                qnt_comandos_externos++;
            }

            else if (strcmp(comandos[i], "%") == 0) {
                if (tem_coracao) {
                    printf("Erro: o comando %% nao pode estar em uma linha de comando com o comando <3\n");
                    return;
                }
                if (ultima_posicao == i) {
                    printf("Erro: o comando %% deve estar em uma linha de comando com um comando externo\n");
                    return;
                }
                if (num_comandos > NUM_SUBCOMANDOS_MAXIMO + 1){
                    printf("Erro: o comando %% deve estar em uma linha de comando com no maximo 1 comando e 3 argumentos\n");
                    return;
                }
                if (i < num_comandos-1) {
                    printf("Erro: o comando %% deve estar no final de uma linha de comando\n");
                    return;
                }
                // Comando externo unico em foreground
                foreground = true;
                if (pid_f > 0) {
                    waitpid(pid_f, NULL, 0);
                    return;
                }

                char* subcomandos[i - ultima_posicao];
                copiar_strings(comandos, ultima_posicao, i-1, subcomandos);

                exec_cmds(subcomandos, foreground);
                
                return;
            }

            if (subcomandos_externos > NUM_SUBCOMANDOS_MAXIMO) {
                printf("Erro: o numero maximo de comando com seus argumentos eh %d\n", NUM_SUBCOMANDOS_MAXIMO);
                return;
            }

            else if (i == num_comandos-1) {
                // Comando externo unico em background ou ultimo comando
                // Para unico comando externo (em background)
                if ((pid_f == 0) && (!tem_coracao)){
                    pid_s = setsid();

                    // Se unico comando na sessao, ignora sigusr1
                    if (signal(SIGUSR1, sig_usr1_iso) == SIG_ERR){
                        printf("Erro ao tentar me isolar do SIGUSR1\n");
                    }
                } else if (pid_f > 0) {
                    return;
                }
                
                char* subcomandos[i - ultima_posicao + 1];
                copiar_strings(comandos, ultima_posicao, i, subcomandos);
                
                exec_cmds(subcomandos, foreground);

                // O primeiro fork criado (lider da sessao)
                // Só finaliza se seus filhos tambem finalizarem!
                for (int j = 0; j <= qnt_comandos_externos; j++){
                    wait(NULL);
                }  
                exit(0);
            }
        }
    }
}

// Executa os programas passados pelo vetor de entrada
void exec_cmds(char** subcomando, bool foreground){
    // Executa o comando subcomando, com seus argumentos atraves do execvp
    pid_t pid;

    // Primeiro fork para representar o processo de execvp
    if ((pid = fork()) < 0){
            fprintf(stderr, "Fork failed!\n");
            return;
    } else if (pid == 0) {
        if (!foreground){
            /* No caso de processos em background:
            * - Para que o programa nao pare, utiliza-se a estrutura fork->exec 
            * - Alem disso, usa dois forks:
            *  - Um para representar o processo de execvp com os tratadores de sinal 
            *personalizado; e 
            *  - Outro para que o processo em execvp seja criado.
            * */
            if ((pid = fork()) < 0){
                fprintf(stderr, "Fork failed!\n");
                return;
            } else if (pid == 0) {
                execvp(subcomando[0], subcomando);
            } else {
                return;
            }
        } else { // Em foreground somente execvp
            execvp(subcomando[0], subcomando);
        }
    } else {
        waitpid(pid, NULL, 0);
        exit(0);
    }
    
    // Se houver erro, o codigo abaixo reporta o erro, senao, nunca roda o abaixo
    // A nao ser ls, que roda, mas retorna de execvp (nao consegui descobrir porque)
    if (errno != 0){
        printf("\n\n");
        printf("Erro, o programa indicado nao pode ser executado.\n");
        printf("Comando digitado: ");
        int j = 0;
        while (subcomando[j] != NULL){
            printf("%s ", subcomando[j]);
            j++;
        }
        printf("\nMais informacoes...\n");
        printf("Erro: %d\n", errno);
        printf("%s.\n", strerror(errno));
        printf("\n\n");
        exit(-1);
    }
    exit(0);
}

// Define um tratador para o sinal SIGUSR1 para programas isolados.
void sig_usr1_iso(int signo){
    (void)signo;
    return;
}

// Define um tratador para o sinal SIGUSR1 para programas não isolados.
void sig_usr1_grp(int signo){
    // Mata todos processos do mesmo grupo
    if(kill(-1*getpgid(getpid()), SIGKILL) < 0){
        printf("\n\n");
        printf("Erro!.\n");
        printf("\nMais informacoes...\n");
        printf("Erro: %d\n", errno);
        printf("%s.\n", strerror(errno));
        printf("\n\n");
    }
}

// Redefine o tratador para SIGINT, SIGTSTP e SIGQUIT.
void sig_ctrl_padrao(struct sigaction oact_sigint, struct sigaction oact_sigtstp, struct sigaction oact_sigquit){
    if ((sigaction(SIGINT, &oact_sigint, NULL)==-1))
        perror("Failed to install SIGINT signal handler");
    if (sigaction(SIGTSTP, &oact_sigtstp, NULL)==-1)
        perror("Failed to install SIGTSTP signal handler");
    if (sigaction(SIGQUIT, &oact_sigquit, NULL)==-1)
        perror("Failed to install SIGQUIT signal handler");
    return;
}

