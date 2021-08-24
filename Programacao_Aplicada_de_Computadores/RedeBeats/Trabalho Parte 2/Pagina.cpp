#include "Pagina.h"

Pagina::Pagina():Usuario()
{
    this->categoria= new Categoria();
}
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
    o << "P" << endl;
    o << this->nome << endl;
    o << this->id << endl;
    o << this->data.tm_mday << "/" <<this->data.tm_mon+1 << "/" << this->data.tm_year+1900 << endl;
    o << this->categoria->getNome() << endl;
    o << this->sobre << endl;
    o << this->getUrlFoto() << endl;
    o << seguidores.size() << endl;
    for(int i=0; i<seguidores.size(); i++)
    {
        seguidores[i]->imprimeSeguidor(o);
    }
    o << publicacoes.size() << endl;
    for(int i=0; i<publicacoes.size(); i++)
    {
        publicacoes[i]->imprimeNoArquivo(o);
    }
    cout << "Página " << this->nome << " salva com sucesso!" << endl;
}
void Pagina::imprimeSeguidor(ofstream &o)
{
    o << "P" << endl;
    o << this->nome << endl;
    o << this->id << endl;
    o << this->data.tm_mday <<"/" <<this->data.tm_mon+1 << "/" << this->data.tm_year+1900 << endl;
    o << this->categoria->getNome() << endl;
    o << this->sobre << endl;
    o << this->getUrlFoto() << endl;
    cout << "Seguidor " << this->nome << " salvo com sucesso!" << endl;
}
void Pagina::carregaArquivo(ifstream &arqRed)
{
    string ups,tipo,urlll;
    int n,w,d,m,a;
    getline(arqRed, this->nome);
    getline(arqRed, this->id);
    arqRed >> d;
    arqRed.ignore();
    arqRed >> m;
    arqRed.ignore();
    arqRed >> a;
    arqRed.ignore();
    this->data= {0,0,0,d,m-1,a-1900};
    getline(arqRed, ups);
    this->categoria->setNome(ups);
    arqRed.ignore();
    getline(arqRed, this->sobre);
    arqRed >> urlll;
    arqRed.ignore();
    this->setUrlFoto(urlll);
    arqRed >> n; // número de seguidores
    arqRed.ignore();
    for(int i=0; i<n; i++)
    {
        arqRed >> tipo;
        arqRed.ignore();
        if(tipo=="P")
        {
            Usuario* u;
            u = new Pagina();
            u->carregaSeguidor(arqRed);
            seguidores.push_back(u);
        }
        else
        {
            Usuario* u;
            u = new UsuarioComum();
            u->carregaSeguidor(arqRed);
            seguidores.push_back(u);
        }
    }
    arqRed >> w; // número de publicações
    arqRed.ignore();
    for(int i=0; i<w; i++)
    {
        Publicacao* p;
        p = new Publicacao();
        p->carregaArquivo(arqRed);
        publicacoes.push_back(p);
    }
    cout << "Página " << this->nome << " carregada com sucesso!" << endl;
}
void Pagina::carregaSeguidor(ifstream &arqRed)
{
    int d,m,a;
    string oops,urlll;
    getline(arqRed, this->nome);
    getline(arqRed, this->id);
    arqRed >> d;
    arqRed.ignore();
    arqRed >> m;
    arqRed.ignore();
    arqRed >> a;
    arqRed.ignore();
    this->data= {0,0,0,d,m-1,a-1900};
    arqRed >> oops;
    arqRed.ignore();
    this->categoria->setNome(oops);
    getline(arqRed, this->sobre);
    arqRed >> urlll;
    arqRed.ignore();
    this->setUrlFoto(urlll);
    cout << "Seguidor " << this->nome << " da página carregado com sucesso!" << endl;
}
void Pagina::imprimeNoHtmlPerfil(ofstream &o)
{

}
void Pagina::imprimeNoHtmlSeguidor(ofstream &o)
{

}
