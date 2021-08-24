#include "Categoria.h"

string Categoria::getNome()
{
    return this->nome;
}
void Categoria::setNome(string name)
{
    this->nome=name;
}
Categoria::Categoria(string a)
{
    nome=a;
}
Categoria::Categoria()
{
}
