#ifndef PUBLICACAO_H_INCLUDED
#define PUBLICACAO_H_INCLUDED
#include <iostream>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

class Publicacao
{
private:
    tm data;
    string conteudo;
public:
    tm getData();
    void setData(tm data);
    string getConteudo();
    void setConteudo(string conteudo);
    Publicacao(string a);
    void imprimeInfo();
};

#endif // PUBLICACAO_H_INCLUDED
