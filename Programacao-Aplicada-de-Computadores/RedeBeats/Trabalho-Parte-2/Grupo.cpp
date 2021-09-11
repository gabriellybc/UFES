#include "Grupo.h"
#include "Pagina.h"
#include "UsuarioComum.h"

Grupo::Grupo()
{
    this->categoria= new Categoria();
}
Grupo::Grupo(string n, int ida, int pag, string c, Usuario* a)
{
    nome=n;
    idadeMinUsuarioAnos=ida;
    idadeMinPaginaDias=pag;
    categoria= new Categoria(c);
    adm=a;
}
void Grupo::adicionarParticipante(Usuario* usuario)
{
    int p,i;
    p=usuario->validadeIdade(this->idadeMinUsuarioAnos, this->idadeMinPaginaDias);
    if(p==0)
    {
        cout << "Você não tem a idade mínima necessária para entrar no grupo." << endl;
        return;
    }
    for(i=0; i<participantes.size(); i++)
    {
        if(participantes[i]->getId() == usuario->getId())
        {
            cout << "Você já está neste grupo." << endl;
            return;
        }
    }
    participantes.push_back(usuario);
    cout << "Você foi inserido nesse grupo." << endl;
}
void Grupo::imprimeInfo ()
{
    cout << "Nome: " << nome << endl;
    cout << "Idade mínima em anos: " << idadeMinUsuarioAnos << endl;
    cout << "Idade mínima da página em dias: " << idadeMinPaginaDias << endl;
    cout << "Categoria: " << categoria->getNome() << endl;
    cout << "Nome do administrador: " << getAdministrador()->getNome() << endl;
    cout << "Número de participantes: " <<  participantes.size() << endl;
}
void Grupo::imprimirParticipantes()
{
    if(participantes.size() == 0)
    {
        cout << "Não há participantes no grupo." << endl;
    }
    else
    {
        int i;
        for(i=0; i<participantes.size(); i++)
        {
            cout << "Participante: " << i <<endl;
            participantes[i]->imprimeInfo();
        }
    }
}
void Grupo::removerParticipante()
{
    int pos;
    this->imprimirParticipantes();
    do
    {
        cout << "Informe a posição do usuário no grupo: ";
        cin >> pos;
    }
    while (pos<0 || pos>=this->participantes.size());
    participantes.erase(participantes.begin()+pos);
    cout << "Um usuário deixou de participar do grupo com sucesso." << endl;
}
string Grupo::getNome()
{
    return this->nome;
}
void Grupo::setNome(string name)
{
    this->nome=name;
}
Categoria* Grupo::getCategoria()
{
    return this->categoria;
}
void Grupo::setCategoria(Categoria* category)
{
    this->categoria=category;
}
int Grupo::getidadeMinUsuarioAnos()
{
    return this->idadeMinUsuarioAnos;
}
void Grupo::setIdadeMinUsuarioAnos(int idadeMinUsuarioAnos)
{
    this->idadeMinUsuarioAnos=idadeMinUsuarioAnos;
}
int Grupo::getidadeMinPaginaDias()
{
    return this->idadeMinPaginaDias;
}
void Grupo::setidadeMinPaginaDias(int idadeMinPaginaDias)
{
    this->idadeMinPaginaDias=idadeMinPaginaDias;
}
Usuario* Grupo::getAdministrador()
{
    return this->adm;
}
void Grupo::setAdministrador(Usuario* adm)
{
    this->adm=adm;
}
vector<Usuario*> Grupo::getParticipantes()
{
    return this->participantes;
}
void Grupo::imprimeNoArquivo(ofstream &o)
{
    o << participantes.size() << endl;
    o << this->nome << endl;
    o << this->idadeMinUsuarioAnos << endl;
    o << this->idadeMinPaginaDias << endl;
    o << this->categoria->getNome() << endl;
    this->adm->imprimeSeguidor(o);
    for(int i=0; i<participantes.size(); i++)
    {
        participantes[i]->imprimeSeguidor(o);
    }
}
void Grupo::carregaArquivo(ifstream &arqRed)
{
    string tipo,ops;
    int part;
    arqRed >> part; // quantidade de participantes
    arqRed.ignore();
    getline(arqRed, this->nome);
    arqRed >> this->idadeMinUsuarioAnos;
    arqRed.ignore();
    arqRed >> this->idadeMinPaginaDias;
    arqRed.ignore();
    getline(arqRed,ops);
    this->categoria->setNome(ops);
    arqRed >> tipo;
    arqRed.ignore();
    if(tipo=="P")
    {
        Usuario* u;
        u = new Pagina();
        u->carregaSeguidor(arqRed);
        this->setAdministrador(u);
    }
    else
    {
        Usuario* u;
        u = new UsuarioComum();
        u->carregaSeguidor(arqRed);
        this->setAdministrador(u);
    }
    for(int i=0; i<part; i++)
    {
        arqRed >> tipo;
        arqRed.ignore();
        if(tipo=="P")
        {
            Usuario* u;
            u = new Pagina();
            participantes.push_back(u);
            participantes[i]->carregaSeguidor(arqRed);
        }
        else
        {
            Usuario* u;
            u = new UsuarioComum();
            participantes.push_back(u);
            participantes[i]->carregaSeguidor(arqRed);
        }
    }
}
