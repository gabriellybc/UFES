#include "UsuarioComum.h"

UsuarioComum::UsuarioComum():Usuario() {}
UsuarioComum::UsuarioComum(string nome, string id, tm data,string u ,char g , string f, StatusRelacionamento s):Usuario(nome, id, data,u)
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
void UsuarioComum::imprimeNoArquivo(ofstream &o)
{
    o.open("RedesSociais.txt");
    o << "C" << endl;
    o << this->nome << endl;
    o << this->id << endl;
    o << this->data.tm_mday << "/" << this->data.tm_mon +1 << "/" << this->data.tm_year+1900 << endl;
    o << this->genero << endl;
    o << this->formacao << endl;
    o << this->status << endl;
    o << this->urlFoto << endl;
    o << seguidores.size() << endl;
    for(int i=0;i<seguidores.size();i++)
    {
        seguidores[i]->imprimeSeguidor(o);
    }
    o << publicacoes.size() << endl;
    for(int i=0;i<publicacoes.size();i++)
    {
        publicacoes[i]->imprimeNoArquivo(o);
    }
    o.close();
    cout << "Usuário comum " << this->nome << " salvo com sucesso!" << endl;
}
void UsuarioComum::imprimeSeguidor(ofstream &o)
{
    o.open("RedesSociais.txt");
    o << "C" << endl;
    o << this->nome << endl;
    o << this->id << endl;
    o << this->data.tm_mday << "/" << this->data.tm_mon +1 << "/" << this->data.tm_year+1900 << endl;
    o << this->genero << endl;
    o << this->formacao << endl;
    o << this->getStringStatus()<< endl;
    o << this->urlFoto << endl;
    o.close();
    cout << "Seguidor " << this->nome << " salvo com sucesso!" << endl;
}
void UsuarioComum::carregaArquivo(ifstream &arqRed)
{
    arqRed.open("RedesSociais.txt");
    Usuario *u;
    char x;
    string tipo;
    int n,w,d,m,a, opa;
    arqRed >> x;
    getline(arqRed, this->nome);
    arqRed >> this->nome;
    arqRed.ignore();
    getline(arqRed, this->id);
    arqRed >> this->id;
    arqRed.ignore();
    arqRed >> d;
    arqRed.get();
    arqRed >> m;
    arqRed.get();
    arqRed >> a;
    this->data= {0,0,0,d,m-1,a-1900};
    arqRed >> this->genero;
    arqRed.ignore();
    getline(arqRed, this->formacao);
    arqRed.ignore();
    arqRed >> opa;
    this->setStatus(UsuarioComum::StatusRelacionamento(opa));

    getline(arqRed, this->urlFoto);
    arqRed.ignore();
    arqRed >> n;
    for(int i=0;i<n;i++)
    {
        arqRed >> tipo;
        if(tipo=="P")
        {
            u = (Pagina*)new Pagina();
            u->carregaSeguidor(arqRed);
            seguidores.push_back(u);
        }
        else
        {
            u = new UsuarioComum();
            u->carregaSeguidor(arqRed);
            seguidores.push_back(u);
        }
    }
    arqRed >> w;
    for(int i=0;i<n;i++)
    {
        arqRed >> a;
        Publicacao* p;
        p = new Publicacao();
        p->carregaArquivo(arqRed);
        publicacoes.push_back(p);
    }
    arqRed.close();
    cout << "Usuário comum " << this->nome << " carregado com sucesso!" << endl;
}
void UsuarioComum::carregaSeguidor(ifstream &arqRed)
{
    arqRed.open("RedesSociais.txt");
    int d,m,a, opa;
    getline(arqRed, this->nome);
    arqRed >> this->nome;
    arqRed.ignore();
    getline(arqRed, this->id);
    arqRed >> this->id;
    arqRed.ignore();
    arqRed >> d;
    arqRed.get();
    arqRed >> m;
    arqRed.get();
    arqRed >> a;
    this->data= {0,0,0,d,m-1,a-1900};
    arqRed >> this->genero;
    arqRed.ignore();
    getline(arqRed, this->formacao);
    arqRed >> this->formacao;
    arqRed.ignore();
    arqRed >> opa;
    this->setStatus(UsuarioComum::StatusRelacionamento(opa));
    arqRed >> this->urlFoto;
    arqRed.close();
    cout << "Seguidor " << this->nome << " do usuário comum carregado com sucesso!" << endl;
}
void imprimeNoHtmlPerfil(ofstream &o)
{

}
void imprimeNoHtmlSeguidor(ofstream &o)
{

}
