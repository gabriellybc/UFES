#ifndef EXEC_CMD
#define EXEC_CMD

/**
 * Executa o comando 'cd' para mudar de diretório.
 * @param diretorio O diretório para o qual se deseja navegar.
 */
void executar_comando_cd(char* diretorio);

/**
 * Executa o comando 'exit' para finalizar o shell.
 * Realiza as seguintes etapas:
 * - Finaliza os processos de background.
 * - Aguarda a finalização dos processos de background.
 * - Finaliza o shell.
 */
void executar_comando_exit();

/**
 * Trata os comandos fornecidos e executa as ações correspondentes.
 * @param comandos Um vetor de strings contendo os comandos fornecidos.
 * @param num_comandos O número de comandos no vetor.
 * @param oact_sigint Tratador padrão do SIGINT
 * @param oact_sigtstp Tratador padrão do SIGTSTP
 * @param oact_sigquit Tratador padrão do SIGQUIT
 */
void tratar_comandos(char** comandos, 
                    int num_comandos, 
                    struct sigaction oact_sigint,
                    struct sigaction oact_sigtstp,
                    struct sigaction oact_sigquit);

/**
 * Executa os programas passados pelo vetor de entrada.
 * @param subcomando Um vetor de strings contendo o programa a ser executado com todos
 *  seus argumentos, e com o último elemento sendo um ponteiro para NULL.
 * @param foreground Indica se o programa indicado deve rodar em foreground (true) ou 
 *  background (false).
 */
void exec_cmds(char** subcomando, bool foreground);

/**
 * Define um tratador para o sinal SIGUSR1 para programas isolados.
 */
void sig_usr1_iso(int signo);

/**
 * Define um tratador para o sinal SIGUSR1 para programas não isolados.
 */
void sig_usr1_grp(int signo);

/**
 * Redefine o tratador para SIGINT, SIGTSTP e SIGQUIT.
 */
void sig_ctrl_padrao(struct sigaction oact_sigint, struct sigaction oact_sigtstp, struct sigaction oact_sigquit);


#endif // EXEC_CMD
