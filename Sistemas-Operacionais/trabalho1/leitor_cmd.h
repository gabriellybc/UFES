#ifndef LEITOR_CMD
#define LEITOR_CMD

/**
 * Lê um comando a partir do stdin.
 * @param linha O buffer para armazenar o comando lido.
 */
void ler_comando(char* linha);

/**
 * Separa os comandos da linha de entrada em um vetor.
 * @param linha A linha de entrada contendo os comandos.
 * @param comandos O vetor de strings para armazenar os comandos separados.
 * @param num_comandos Um ponteiro para o número de comandos encontrados.
 */
void separar_comandos(char* linha, char** comandos, int* num_comandos);

#endif /* LEITOR_CMD */
