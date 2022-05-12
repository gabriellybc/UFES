#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "Leitura.h"
#include "StringUtils.h"
#include "InvalidFormatArgumentException.h"
#include "FileNotFoundException.h"
#include "InvalidFormatDateException.h"
using namespace std;
using namespace cpp_util;

void Leitura::run(const int argc, const char **args, Eleicao &eleicao)
{
	lerEntradas(argc, args, eleicao);
	eleicao.gerarRelatorios();
}

void Leitura::lerEntradas(const int argc, const char **args, Eleicao &eleicao)
{
	string file1 = args[1];
	string file2 = args[2];
	try {
		// Verifica se tem no mínimo o número esperado de entradas e se as entradas 1 e 2 são .csv 
		if (argc > 3 && file1.compare(file1.size() - 4, 4, ".csv") == 0 && file2.compare(file2.size() - 4, 4, ".csv") == 0) {
				// Verifica se data é válida
				if (!validDate(args[3], DATE_FORMAT_PT_BR_SHORT)) {
					throw InvalidFormatDateException();
				}
				eleicao.setDataAtual(args[3]);
				lerArquivoPartidos(args[2], eleicao);
				lerArquivoCandidatos(args[1], eleicao);
		} else {
			throw InvalidFormatArgumentException();
		}
	} catch (InvalidFormatArgumentException &e) {
		cout << e.what() << endl;
		exit(1);
	} catch (InvalidFormatDateException &e) {
		cout << e.what() << endl;
		exit(1);
	}
}

void Leitura::lerArquivoPartidos(const string &filePath, Eleicao &eleicao)
{
	vector<string> row;
	string line, word, nome, sigla;

	fstream fs;
	fs.open(filePath, ios::in);
	try {
		if (!fs.is_open()) {
			throw FileNotFoundException();
		}
		// Verifica se o cabeçalho é o esperado
		getline(fs, line);
		if (line.compare("numero_partido,votos_legenda,nome_partido,sigla_partido") == 0) {
			while (getline(fs, line)) {
				row.clear();
				stringstream str(line);
				while (getline(str, word, ','))
					row.push_back(word);
				//	Número esperado de entradas
				if (row.size() == 4) {
					Partido *partido = new Partido(stoi(row[0]), stoi(row[1]), trim(row[2]), trim(row[3]));
					eleicao.addPartido(partido);
				}
			}
		} else {
			throw InvalidFormatArgumentException();
		}
		fs.close();
	}
	catch (InvalidFormatArgumentException &e)
	{
		fs.close();
		cout << e.what() << ": Partidos header" << endl;
		exit(1);
	}
	catch (FileNotFoundException &e)
	{
		fs.close();
		cout << e.what() << endl;
		exit(1);
	}
	catch (InvalidFormatDateException &e)
	{
		fs.close();
		cout << e.what() << endl;
		exit(1);
	}
}

void Leitura::lerArquivoCandidatos(const string &filePath, Eleicao &eleicao)
{
	vector<string> row;
	string line, word, nome, sigla;

	fstream fs;
	try
	{
		fs.open(filePath, ios::in);
		if (!fs.is_open()) {
			throw FileNotFoundException();
		}
		// Verifica se o cabeçalho é o esperado
		getline(fs, line);
		if (line.compare("numero,votos_nominais,situacao,nome,nome_urna,sexo,data_nasc,destino_voto,numero_partido") == 0)
		{
			while (getline(fs, line))
			{
				row.clear();
				stringstream str(line);

				while (getline(str, word, ','))
					row.push_back(word);
				//	Número esperado de entradas
				if (row.size() == 9) {
					if (trim(row[7]).compare("Válido") != 0)
						continue;
					
					// Verifica se data é válida
					if (!validDate(trim(row[6]), DATE_FORMAT_PT_BR_SHORT))
						throw InvalidFormatDateException();

					// Verifica se partido existe
					Partido *partido = eleicao.getPartidoPorNumero(stoi(row[8]));
					if (partido != NULL) {
						Candidato *candidato = new Candidato(stoi(row[0]), stoi(row[1]), trim(row[2]), trim(row[3]), trim(row[4]), trim(row[5]), trim(row[6]), partido);

						eleicao.addCandidato(candidato);
						partido->adicionarCandidato(candidato);
					}
				}
			}
		} else {
			throw InvalidFormatArgumentException();
		}
		fs.close();
	}
	catch (InvalidFormatArgumentException &e)
	{
		fs.close();
		cout << e.what() << ": Candidatos header" << endl;
		exit(1);
	}
	catch (FileNotFoundException &e)
	{
		fs.close();
		cout << e.what() << endl;
		exit(1);
	}
	catch (InvalidFormatDateException &e)
	{
		fs.close();
		cout << e.what() << endl;
		exit(1);
	}
}
