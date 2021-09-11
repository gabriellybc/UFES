#include "Grupo.h"
#include "Pagina.h"
#include "UsuarioComum.h"

Grupo::Grupo() {}
Grupo::Grupo(string n, int ida, int pag, string c, Usuario* a)
{
    nome=n;
    idadeMinUsuarioAnos=ida;
    idadeMinPaginaDias=pag;
    categoria= new Categoria(c);
    adm=a;
    participantes.push_back(adm);
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
    o.open("RedesSociais.txt");
    o << this->nome << endl;
    o << this->idadeMinUsuarioAnos << endl;
    o << this->idadeMinPaginaDias << endl;
    o << this->categoria << endl;
    this->adm->imprimeNoArquivo(o);
    o << participantes.size() << endl;
    for(int i=0;i<participantes.size();i++)
    {
        participantes[i]->imprimeSeguidor(o);
    }
    o.close();
}
void Grupo::carregaArquivo(ifstream &arqRed)
{
    arqRed.open("RedesSociais.txt");
    char x;
    string b,ops;
    int n,d,m,a;
    Usuario* u;
    arqRed >> x;
    getline(arqRed, this->nome);
    arqRed.ignore();
    arqRed >> this->idadeMinUsuarioAnos;
    arqRed >> this->idadeMinPaginaDias;
    getline(arqRed,ops);
    this->categoria->setNome(ops);
    arqRed.ignore();
    arqRed >> n;
    for(int i=0;i<n;i++)
    {
        arqRed >> b;
        if(b=="P")
        {
            u = new Pagina();
            u->carregaSeguidor(arqRed);
            participantes.push_back(u);
        }
        else
        {
            u = new UsuarioComum();
            u->carregaSeguidor(arqRed);
            participantes.push_back(u);
        }
    }
    arqRed.close();
}
