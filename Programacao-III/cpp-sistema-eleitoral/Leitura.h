#ifndef LEITURA_H_
#define LEITURA_H_

#include <string>
#include <vector>
#include <exception>
#include "Eleicao.h"

class Leitura
{
    public:
        /**
         * @brief Esse método recebe os dados da Eleição, armazena nas listas e chama método para gerar relatórios
         * 
         * @param argc tamanho de args
         * @param args Array com três posições: primeira contendo o nome do arquivo contendo a lista de partidos, 
         * a lista de candidatos e uma data de referência
         * @param Objeto tipo Eleicao
         */
        void run(const int argc, const char **args, Eleicao &eleicao);

        /**
         * @brief Esse método recebe os dados da Eleição e armazena nas listas para posteriormente gerar o relatório
         * 
         * @param argc tamanho de args
         * @param args Array com três posições: primeira contendo o nome do arquivo contendo a lista de partidos, 
         * a lista de candidatos e uma data de referência
         * @param Objeto tipo Eleicao
         */
        void lerEntradas(const int argc, const char **args, Eleicao &eleicao);

        /** 
         * @brief Recebe os dados dos partidos e armazena na lista de partidos da Eleição
         *
         * @param filePath nome do arquivo contendo os dados dos partidos 
         * @param Objeto tipo Eleicao
         */
        void lerArquivoPartidos(const string &filePath, Eleicao &eleicao);

        /** 
         * @brief Recebe os dados dos candidatos e armazena na lista de partidos da Eleição
         *
         * @param filePath nome do arquivo contendo os dados dos candidatos 
         * @param Objeto tipo Eleicao
         */
        void lerArquivoCandidatos(const string &filePath, Eleicao &eleicao);
};

#endif