#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // For the syscall functions.
#include <signal.h>     // For the signal functions.

int num_ctrl_c = 0;

static void sig_stp(int signo){ //SIGTSTP - ^Z
    (void)signo;
    printf("\nO número de ^C apanhados é %d.\n", num_ctrl_c);
}

static void sig_int(int signo){ //SIGINT - ^C
    (void)signo;
    num_ctrl_c++;
    if (num_ctrl_c >= 5){
        char answer;
        printf("Tem certeza que quer sair? (Y/N)\n");
        scanf("%c", &answer);
        printf("\n");
        if (answer == 'y' || answer == 'Y') {
            printf("Saindo!\n");
            exit(42);
        } else if (answer == 'n' || answer == 'N') {
            printf("OK, não vou sair!\n");
        } else {
            printf("Resposta inválida, vou retornar então!\n");
        }
    }
}

int main(int argc, char* argv[]){
    if (signal(SIGTSTP, sig_stp) == SIG_ERR){
        fprintf(stderr, "can't set signal handler!\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGINT, sig_int) == SIG_ERR){
        fprintf(stderr, "can't set signal handler!\n");
        exit(EXIT_FAILURE);
    }
    
    for(;;);

}