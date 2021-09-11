#include "Pagina.h"

Pagina::Pagina():Usuario() {}
Pagina::Pagina(string nome, string id, tm data,string u, string c, string s):Usuario(nome, id, data,u)
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
void Pagina::imprimeNoArquivo(ofstream &o)
{
    o.open("RedesSociais.txt");
    o << "P" << endl;
    o << this->nome << endl;
    o << this->id << endl;
    o << this->data.tm_mday <<"/" <<this->data.tm_mon << "/" << this->data.tm_year << endl;
    o << this->categoria->getNome() << endl;
    o << this->sobre << endl;
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
    cout << "Página " << this->nome << " salva com sucesso!" << endl;
}
void Pagina::imprimeSeguidor(ofstream &o)
{
    o.open("RedesSociais.txt");
    o << "P" << endl;
    o << this->nome << endl;
    o << this->id << endl;
    o << this->data.tm_mday <<"/" <<this->data.tm_mon << "/" << this->data.tm_year << endl;
    o << this->categoria << endl;
    o << this->sobre << endl;
    o << this->urlFoto << endl;
    o.close();
    cout << "Seguidor " << this->nome << " salvo com sucesso!" << endl;
}
void Pagina::carregaArquivo(ifstream &arqRed)
{
    arqRed.open("RedesSociais.txt");
    string ups;
    char x;
    string tipo;
    int n,w,d,m,a;
    Usuario* u;
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
    getline(arqRed, ups);
    this->categoria->setNome(ups);
    arqRed.ignore();
    getline(arqRed, this->sobre);
    arqRed >> this->sobre;
    arqRed.ignore();
    getline(arqRed, this->urlFoto);
    arqRed >> this->urlFoto;
    arqRed.ignore();
    arqRed >> n;
    for(int i=0;i<n;i++)
    {
        arqRed >> tipo;
        if(tipo=="P")
        {
            u = new Pagina();
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
        arqRed >> tipo;
        Publicacao* p;
        p = new Publicacao();
        p->carregaArquivo(arqRed);
        publicacoes.push_back(p);
    }
    arqRed.close();
    cout << "Página " << this->nome << " carregada com sucesso!" << endl;
}
void Pagina::carregaSeguidor(ifstream &arqRed)
{
    arqRed.open("RedesSociais.txt");
    int d,m,a;
    string oops;
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
    arqRed >> oops;
    this->categoria->setNome(oops);
    arqRed.ignore();
    getline(arqRed, this->sobre);
    arqRed >> this->sobre;
    arqRed.ignore();
    getline(arqRed, this->urlFoto);
    arqRed >> this->urlFoto;
    arqRed.close();
    cout << "Seguidor " << this->nome << " da página carregado com sucesso!" << endl;
}
void Pagina::imprimeNoHtmlPerfil(ofstream &o)
{

}
void Pagina::imprimeNoHtmlSeguidor(ofstream &o)
{

}
