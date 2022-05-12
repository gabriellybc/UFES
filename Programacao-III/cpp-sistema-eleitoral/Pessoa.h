#ifndef PESSOA_H_
#define PESSOA_H_

#include <string>
#include <ctime>
#include "DateUtils.h"

using namespace std;
using namespace cpp_util;

class Pessoa {
	protected:
		string nome;
		string sexo;
		time_t dataNascimento;

	public:
		//Construtores e funções padrão para cópia
		Pessoa();
		Pessoa(const string &nome, const string &sexo, const string &dataNascimento);
		Pessoa(const Pessoa &o);
		Pessoa &operator=(const Pessoa &o);

		/**
		 * @brief Retorna o nome 
		 * 
		 * @return string nome 
		 */
		const string &getNome() const;

		/**
		 * @brief Altera o nome  
		 * 
		 * @param nome string nome 
		 */
		void setNome(const string &nome);

		/**
		 * @brief Retorna o sexo 
		 * 
		 * @return string sexo: F ou M 
		 */
		const string &getSexo() const;

		/**
		 * @brief Altera o sexo
		 * 
		 * @param sexo string sexo: F ou M 
		 */
		void setSexo(const string &sexo);

		/**
		 * @brief Retorna a data de nascimento 
		 * 
		 * @return time_t data de nascimento 
		 */
		const time_t &getDataNascimento() const;

		/**
		 * @brief Altera a data de nascimento 
		 * 
		 * @param dataNascimento string data de nascimento
		 */
		void setDataNascimento(const time_t &dataNascimento);

		/**
		 * @brief Cálcula a idade da pessoa 
		 * 
		 * @param time_t dataAtual
		 * @return int idade da pessoa 
		 * ou 0 caso data de nascimento ou a data de referência sejam nulos
		 */
		int calculaIdade(const time_t &dataAtual) const;

		/**
		 * @brief Compara idade entre duas pessoas
		 * 
		 * @param o2 Pessoa para comparar
		 * @return int 
		 * se o1 é mais velho o retorno é 1
		 * se o2 é mais velho o retorno é -1
		 * se o1 e o2 tiverem a mesma idade o retorno é 0
		 */
		int comparaIdade(Pessoa *o2);

		/**
		 * @brief Destrutor da classe
		 * 
		 */
		~Pessoa();

};

#endif