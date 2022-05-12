#ifndef PARTIDO_H
#define PARTIDO_H

#include <string>
#include <vector>
#include <algorithm>
#include "Candidato.h"
using namespace std;

class Partido {
    int numero;
    int votosLegenda;
    string nome;
    string sigla;
    int votosNominais;
    int numeroCandidatosEleitos;
    vector<Candidato*> candidatos; //lista candidatos do partido

    public:
        //Construtores e funções padrão para cópia
        Partido();
        Partido(int numero, int votosLegenda, const string& nome, const string& sigla);
        Partido(const Partido &o);
        Partido &operator=(const Partido &o);

        /**
         * @brief Retorna o número do partido na urna 
         * 
         * @return int número do partido na urna 
         */
        int getNumero() const;

        /**
         * @brief Retorna a quantidade de votos de legenda
         * 
         * @return int quantidade de votos de legenda
         */
        int getVotosLegenda() const;

        /**
         * @brief Retorna o nome do partido 
         * 
         * @return string nome do partido 
         */
        const string& getNome() const;

        /**
         * @brief Retorna a sigla do partido 
         * 
         * @return string sigla do partido 
         */
        const string& getSigla() const;

        /**
         * @brief Retorna a quantidade de votos nominais 
         * 
         * @return int quantidade de votos nominais 
         */
        int getVotosNominais() const;

        /**
         * @brief Retorna o número de candidatos do partido eleitos 
         * 
         * @return int número de candidatos do partido eleitos 
         */
        int getNumeroCandidatosEleitos() const;

        /**
         * @brief Retorna Candidato object
         * 
         * @param idx 
         * @return Candidato* 
         */
        Candidato* getCandidato(int idx) const;

        /**
         * @brief Retorna o Ultimo Candidato object
         * 
         * @return Candidato* 
         */
        Candidato* getUltimoCandidato() const;

        /**
         * @brief Altera o número do partido na urna 
         * 
         * @param numeroPartido int número do partido na urna 
         */
        void setNumero(int numero);

        /**
         * @brief Altera a quantidade de votos de legenda
         * 
         * @param votosLegenda int quantidade de votos de legenda
         */
        void setVotosLegenda(int votosLegenda);

        /**
         * @brief Altera o nome do partido 
         * 
         * @param nomePartido string nome do partido 
         */
        void setNome(const string& nome);

        /**
         * @brief Altera a sigla do partido 
         * 
         * @param sigla string sigla do partido 
         */
        void setSigla(const string& sigla);

        /**
         * @brief Adiciona valor ao quantitativo de votos nominais 
         * 
         * @param votosNominais int quantidade de votos nominais 
         */
        void setVotosNominais(int votosNominais);

        /**
         * @brief Adiciona +1 ao número de candidatos do partido eleitos 
         * 
         */
        void addNumeroCandidatosEleitos();

        /**
         * @brief Adicona candidato a lista do partido
         * 
         * @param candidato 
         */
        void adicionarCandidato(Candidato* candidato);

        /**
         * @brief Retorna Candidato Menos Votado do partido
         * 
         * @return Candidato* 
         */
        Candidato* getCandidatoMenosVotado() const;

        /**
         * @brief Classe que compara partido utilizando como parâmetro o número total de votos
         * que cada possui. O número do partido é considerado critério de desempate.
         * 
         */
        static bool comparaPartidoPorTotalVotos (Partido* o1, Partido* o2);
        
        /**
         * @brief Classe que compara partido utilizando como parâmetro o número de votos de legenda
         * que cada possui. O número de votos nominais é considerando em caso de empate. 
         * O número do partido é considerado critério de desempate final.
         * 
         */
        static bool comparaPartidoPorVotosLegenda (Partido* o1, Partido* o2);
        
        /**
         * @brief Classe que compara partido utilizando como parâmetro o número de votos de nominais
         * que cada possui. O número do partido é considerado critério de desempate.
         * 
         */
        static bool comparaPartidoPorTotalVotosNominaisDoCandidatoMaisVotado (Partido* o1, Partido* o2);
        
        /**
         * @brief Destrutor da classe
         * 
         */
        ~Partido();
};

#endif