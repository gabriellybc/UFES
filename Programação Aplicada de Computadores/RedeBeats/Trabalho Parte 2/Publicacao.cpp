#include "Publicacao.h"

Publicacao::Publicacao() {}
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
void Publicacao::imprimeNoArquivo(ofstream &o)
{
    o<< this->conteudo << endl;
    o << data.tm_mday << "/" << data.tm_mon+1 << "/" << data.tm_year+1900 << endl;
    cout << "Publicação salva com sucesso!" << endl;
}
void Publicacao::carregaArquivo(ifstream &arqRed)
{
    int d,m,a;
    getline(arqRed, this->conteudo);
    arqRed >> d;
    arqRed.ignore();
    arqRed >> m;
    arqRed.ignore();
    arqRed >> a;
    arqRed.ignore();
    this->data= {0,0,0,d,m-1,a-1900};
    cout << "Publicação carregada com sucesso!" << endl;
}
