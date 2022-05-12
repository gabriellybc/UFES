#ifndef CANDIDATO_H_
#define CANDIDATO_H_

#include "Pessoa.h"
#include <string>

using namespace std;

class Partido; // forward declaration

class Candidato : public Pessoa
{
    int numeroUrna;
    int votosNominais;
    string situacao;
    string nomeUrna;
    Partido *partido;

    friend class Partido;

    public:
        //Construtores e funções padrão para cópia
        Candidato();
        Candidato(int numeroUrna, int votosNominais, const string &situacao, const string &nome, const string &nomeUrna, const string &sexo, const string &dataNascimento, Partido *partido);
        Candidato(const Candidato &o);
        Candidato &operator=(const Candidato &o);

        /**
         * @brief Retorna o número do candidato na urna 
         * 
         * @return int número do candidato na urna 
         */
        int getNumeroUrna() const;

        /**
         * @brief Retorna a quatidade de votos nominais que o candidato possui 
         * 
         * @return int quatidade de votos nominais que o candidato possui 
         */
        int getVotosNominais() const;

        /**
         * @brief Retorna a situação do candidato em relação a Eleição 
         * 
         * @return string situação do candidato em relação a Eleição: Eleito, 
         * Não Eleito ou Suplente 
         */
        const string &getSituacao() const;

        /**
         * @brief Retorna o nome do candidato na urna 
         * 
         * @return string nome do candidato na urna 
         */
        const string &getNomeUrna() const;

        /**
         * @brief Retorna o objeto partido do candidato 
         * 
         * @return Object Partido  
         */
        Partido *getPartido() const;

        /**
         * @brief Altera o número do candidato na urna 
         * 
         * @param numeroUrna int número do candidato na urna 
         */
        void setNumeroUrna(int numeroUrna);

        /**
         * @brief Altera a quatidade de votos nominais que o candidato possui 
         * 
         * @param votosNominais int quatidade de votos nominais que o candidato possui 
         */
        void setVotosNominais(int votosNominais);

        /**
         * @brief Altera a situação do candidato em relação a Eleição 
         * 
         * @param situacao string situação do candidato em relação a Eleição: Eleito, 
         * Não Eleito ou Suplente 
         */
        void setSituacao(const string &situacao);

        /**
         * @brief Altera o nome do candidato na urna 
         * 
         * @param nomeUrna string nome do candidato na urna 
         */
        void setNomeUrna(const string &nomeUrna);

        /**
         * @brief Altera o objeto partido do candidato 
         * 
         * @param partido Partido
         */
        void setPartido(Partido *partido);

        /**
         * @brief Classe que compara candidato utilizando como parâmetro o número de votos nominais
         * que cada possui. A idade é considerada critério de desempate.
         * 
         */
        static bool comparaCandidatoPorVotosNominais(Candidato *o1,Candidato *o2);
        
        /**
         * @brief Destrutor da classe
         * 
         */
        ~Candidato();
};

#endif