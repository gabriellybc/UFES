#include "Publicacao.h"
Publicacao::Publicacao(string a)
{
    conteudo=a;
    time_t tt;
    time(&tt);
    data=*localtime(&tt);
}
void Publicacao::imprimeInfo()
{
    cout << "Data da publicação: " << data.tm_mday << "/" << data.tm_mon+1 << "/" << data.tm_year+1900 << endl;
    cout << "Conteúdo: " << conteudo << endl;
}
tm Publicacao::getData()
{
    return this->data;
}
void Publicacao::setData(tm date)
{
    this->data=date;
}
string Publicacao::getConteudo()
{
    return this->conteudo;
}
void Publicacao::setConteudo(string conteudo)
{
    this->conteudo=conteudo;
}
