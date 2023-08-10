#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "leitor_cmd.h"
#include "config.h"

// Função para ler o comando a partir do stdin
void ler_comando(char* linha) {
    fgets(linha, TAMANHO_MAXIMO, stdin);
    linha[strcspn(linha, "\n")] = '\0';
}

// Função para separar os comandos da linha de entrada
void separar_comandos(char* linha, char** comandos, int* num_comandos) {
    const char* delimitador = " ";
    int contador = 0;
    int ultima_posicao = 0, subcomandos_externos = 0, coracoes = 0, qnt_comandos_externos = 0;
    bool tem_externo = false, tem_coracao = false, tem_cd = false, tem_exit = false, tem_porcento = false; 

    char* token = strtok(linha, delimitador);
    while (token != NULL && contador < NUM_COMANDOS_MAXIMO) {
        // Verifica se o comando é "cd"
        if (strcmp(token, "cd") == 0) {
            tem_cd = true;
            // Verifica a posição correta do comando "cd"
            // e se não há outros comandos antes dele
            if (tem_externo) {
                printf("Erro: o comando cd deve ser o primeiro\n");
                *num_comandos = 0;
                return;
            }
            if (tem_exit) {
                printf("Erro: o comando cd deve ser o primeiro\n");
                *num_comandos = 0;
                return;
            }
            if (contador > 0) {
                printf("Erro: o comando cd deve ser o primeiro e deve ter apenas o caminho\n");
                *num_comandos = 0;
                return;
            }
        }
        // Verifica se o comando é "exit"
        else if (strcmp(token, "exit") == 0) {
            tem_exit = true;
            // Verifica a posição correta do comando "exit"
            // e se não há outros comandos antes dele
            if (tem_externo) {
                printf("Erro: o comando exit deve ser o primeiro\n");
                *num_comandos = 0;
                return;
            }
            if (tem_cd) {
                printf("Erro: o comando exit deve ser o primeiro\n");
                *num_comandos = 0;
                return;
            }
            if (contador > 0) {
                printf("Erro: o comando exit deve ser o primeiro e nao deve ter argumentos\n");
                *num_comandos = 0;
                return;
            }
        }
        // Comando externo
        else {
            tem_externo = true;
            subcomandos_externos++;

            // Verifica se há comandos inválidos combinados, como "exit" ou "%"
            if (tem_exit || tem_porcento) {
                printf("Erro: comando invalido\n");
                *num_comandos = 0;
                return;
            }
            // Verifica o número máximo de comandos externos permitidos
            if (qnt_comandos_externos > QNTD_COMANDOS) {
                printf("Erro: o numero maximo de quantidade de comandos externos eh %d\n", QNTD_COMANDOS);
                *num_comandos = 0;
                return;
            }

            // Verifica se o comando é "<3"
            if (strcmp(token, "<3") == 0) {
                coracoes++;
                tem_coracao = true;
                // Verifica combinações inválidas com o comando "<3"
                if (tem_cd) {
                    printf("Erro: o comando <3 nao pode estar em uma linha de comando com o comando cd\n");
                    *num_comandos = 0;
                    return;
                }
                if (tem_porcento) {
                    printf("Erro: o comando <3 nao pode estar em uma linha de comando com o comando %%\n");
                    *num_comandos = 0;
                    return;
                }
                if (ultima_posicao == contador) {
                    printf("Erro: o comando <3 deve estar em uma linha de comando com um comando externo\n");
                    *num_comandos = 0;
                    return;
                }
                if (coracoes > NUM_SUBCOMANDOS_MAXIMO){
                    printf("Erro: o comando <3 deve estar em uma linha de comando com no maximo 1 comando e 3 argumentos\n");
                    *num_comandos = 0;
                    return;
                }
                if (contador == 0) {
                    printf("Erro: o comando <3 deve estar em uma linha de comando com pelo menos 2 comandos\n");
                    *num_comandos = 0;
                    return;
                }
                ultima_posicao = contador + 1;
                subcomandos_externos = 0;
                qnt_comandos_externos++;
            }

            // Verifica se o comando é "%"
            else if (strcmp(token, "%") == 0) {
                tem_porcento = true;
                // Verifica combinações inválidas com o comando "%"
                if (tem_cd) {
                    printf("Erro: o comando %% nao pode estar em uma linha de comando com o comando cd\n");
                    *num_comandos = 0;
                    return;
                }
                if (tem_coracao) {
                    printf("Erro: o comando %% nao pode estar em uma linha de comando com o comando <3\n");
                    *num_comandos = 0;
                    return;
                }
                if (ultima_posicao == contador) {
                    printf("Erro: o comando %% deve estar em uma linha de comando com um comando externo\n");
                    *num_comandos = 0;
                    return;
                }
                if (contador > NUM_SUBCOMANDOS_MAXIMO + 1){
                    printf("Erro: o comando %% deve estar em uma linha de comando com no maximo 1 comando e 3 argumentos\n");
                    *num_comandos = 0;
                    return;
                }
                subcomandos_externos = 0;
            }

            // Verifica o número máximo de subcomandos externos permitidos
            if (subcomandos_externos > NUM_SUBCOMANDOS_MAXIMO) {
                printf("Erro: o numero maximo de comando com seus argumentos eh %d\n", NUM_SUBCOMANDOS_MAXIMO);
                *num_comandos = 0;
                return;
            }
        }

        comandos[contador] = token;
        contador++;

        token = strtok(NULL, delimitador);
    }

    *num_comandos = contador;

    // Verifica se algum comando válido foi digitado
    if (*num_comandos == 0) {
        printf("Erro: nenhum comando valido foi digitado\n");
        *num_comandos = 0;
        return;
    }
    // Verifica se o número máximo de comandos foi excedido
    if (*num_comandos > NUM_COMANDOS_MAXIMO) {
        printf("Erro: o numero maximo de comandos eh %d\n", NUM_COMANDOS_MAXIMO);
        *num_comandos = 0;
        return;
    }
}
