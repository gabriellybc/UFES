#include "UsuarioComum.h"

UsuarioComum::UsuarioComum():Usuario() {}
UsuarioComum::UsuarioComum(string nome, string id, tm data, char g, string f, StatusRelacionamento s):Usuario(nome, id, data)
{
    genero=g;
    formacao=f;
    status=s;
}
char UsuarioComum::getGenero()
{
    return this->genero;
}
void UsuarioComum::setGenero(char genero)
{
    this->genero=genero;
}
string UsuarioComum::getFormacao()
{
    return this->formacao;
}
void UsuarioComum::setFormacao(string formacao)
{
    this->formacao=formacao;
}
UsuarioComum::StatusRelacionamento UsuarioComum::getStatus()
{
    return this->status;
}
void UsuarioComum::setStatus(UsuarioComum::StatusRelacionamento status)
{
    this->status=status;
}
string UsuarioComum::getStringStatus()
{
    switch(this->status)
    {
    case 1:
        return "Solteiro(a)";
    case 2:
        return "Namorando";
    case 3:
        return "Casado(a)";
    default:
        return "";
    }
}
bool UsuarioComum::validadeIdade(int idadeMinUsuarioAnos, int idadeMinPaginaDias)
{
    time_t tt;
    time(&tt);
    tm dataAtual = *localtime(&tt); //Pega data atual
    time_t x = mktime(&this->data); //Transforma data de nascimento em segundos
    time_t y = mktime(&dataAtual); //Transforma data atual em segundos
    double diferenca = difftime(y, x); //Compara a diferença de segundos
    diferenca = diferenca/(365*60*60*24); //Transforma  segundos  em  anos, representando a idade do usuário
    if(diferenca>=idadeMinUsuarioAnos)
    {
        return 1;
    }
    return 0;
}
void UsuarioComum::imprimeInfo()
{
    cout << "Nome: " << nome << endl;
    cout << "ID: " << id << endl;
    cout << "Data de nascimento: " << data.tm_mday << "/" << data.tm_mon +1 << "/" << data.tm_year+1900 << endl;
    cout << "Gênero: " << genero << endl;
    cout << "Formação: " << formacao << endl;
    cout << "Status de relacionamento: " << this->getStringStatus() << endl;
}
