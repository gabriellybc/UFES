#ifndef MACACO_PONTE_H
#define MACACO_PONTE_H

/**
 * Representa a travessia dos macacos e gorilas pela ponte.
 * 
 * Essa função é responsável por controlar a passagem dos macacos e gorilas pela ponte de corda,
 * garantindo que os gorilas tenham prioridade na travessia e só possam atravessar sozinhos.
 * 
 * @param args Um ponteiro para um array de inteiros que contém o ID do macaco (args[0]) e
 *             um valor inteiro que representa se o macaco é um gorila (1) ou não (0) (args[1]).
 * @return NULL
 */
void* atravessa_ponte(void* args);

/**
 * Inicializa os semáforos utilizados para o controle da travessia dos macacos e gorilas.
 */
void inicializa_semaforos();

/**
 * Destroi os semáforos após a conclusão da travessia.
 */
void destroi_semaforos();

#endif
