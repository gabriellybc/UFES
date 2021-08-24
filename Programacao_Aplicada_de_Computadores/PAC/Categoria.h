#ifndef CATEGORIA_H_INCLUDED
#define CATEGORIA_H_INCLUDED

#include <string>
#include <fstream>

using namespace std;

class Categoria
{
private:
    string nome;
public:
    string getNome();
    void setNome(string nome);
    Categoria(string a);
    Categoria();
};

#endif // CATEGORIA_H_INCLUDED
