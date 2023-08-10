// MonitorBanheiro.h
#ifndef MONITOR_BANHEIRO_H
#define MONITOR_BANHEIRO_H

/**
 * Inicializa o Monitor do banheiro.
 * Deve ser chamado antes de utilizar as outras funções do Monitor.
 */
void initMonitor();

/**
 * Função chamada por um corintiano para entrar no banheiro.
 * O corintiano aguarda sua vez e a capacidade disponível.
 * Imprime o número de pessoas de cada time no banheiro após entrar.
 */
void corintianoQuerEntrar();

/**
 * Função chamada por um corintiano para sair do banheiro.
 * O corintiano decrementa o contador de corintianos e sinaliza outras threads.
 * Imprime o número de pessoas de cada time no banheiro após sair.
 */
void corintianoSai();

/**
 * Função chamada por um palmeirense para entrar no banheiro.
 * O palmeirense aguarda sua vez e a capacidade disponível.
 * Imprime o número de pessoas de cada time no banheiro após entrar.
 */
void palmeirenseQuerEntrar();

/**
 * Função chamada por um palmeirense para sair do banheiro.
 * O palmeirense decrementa o contador de palmeirenses e sinaliza outras threads.
 * Imprime o número de pessoas de cada time no banheiro após sair.
 */
void palmeirenseSai();

#endif // MONITOR_BANHEIRO_H
