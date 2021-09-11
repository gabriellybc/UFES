#include "Pagina.h"

Pagina::Pagina():Usuario() {}
Pagina::Pagina(string nome, string id, tm data, string c, string s):Usuario(nome, id, data)
{
    categoria= new Categoria(c);
    sobre=s;
}
Categoria* Pagina::getCategoria()
{
    return this->categoria;
}
void Pagina::setCategoria(Categoria* categoria)
{
    this->categoria=categoria;
}
string Pagina::getSobre()
{
    return this->sobre;
}
void Pagina::setSobre(string sobre)
{
    this->sobre=sobre;
}
bool Pagina::validadeIdade(int idadeMinUsuarioAnos, int idadeMinPaginaDias)
{
    time_t tt;
    time(&tt);
    tm dataAtual=*localtime(&tt); //Pega data atual
    time_t x=mktime(&this->data); //Transforma data de nascimento em segundos
    time_t y=mktime(&dataAtual); //Transforma data atual em segundos
    double diferenca=difftime(y, x); //Compara a diferença de segundos
    diferenca=diferenca/(60*60*24); //Transforma  segundos  em  anos, representando a idade do usuário
    if(diferenca>=idadeMinPaginaDias)
    {
        return 1;
    }
    return 0;
}
void Pagina::imprimeInfo()
{
    cout << "Nome: " << nome << endl;
    cout << "ID: " << id << endl;
    cout << "Data de nascimento: " << data.tm_mday << "/" << data.tm_mon +1 << "/" << data.tm_year+1900 << endl;
    cout << "Categoria: " << categoria->getNome() << endl;
    cout << "Sobre: " << sobre << endl;
}
