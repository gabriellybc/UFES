#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include "Publicacao.h"

using namespace std;
class Usuario
{
protected:
    string nome,id,urlFoto;
    tm data;
    vector<Publicacao*> publicacoes;
    vector<Usuario*> seguidores;
public:
    static int qtdUsuarios;
    static void imprimeQtdUsuarios();
    string getId();
    string getNome();
    tm getData();
    void setId(string id);
    void setNome(string nome);
    void setData(tm data);
    string getUrlFoto();
    void setUrlFoto(string urlFoto);
    vector<Usuario*> getSeguidores();
    vector<Publicacao*> getPublicacoes();
    Usuario();
    Usuario(string n, string c, tm dn, string u);
    virtual void imprimeInfo() = 0;
    void imprimirPublicacoes();
    void imprimirSeguidores();
    void novoSeguidor(Usuario* u);
    void removerSeguidor();
    void criarPublicacao();
    void editarPublicacao();
    void excluirPublicacao();
    virtual bool validadeIdade(int idadeMinUsuarioAnos, int idadeMinPaginaDias) = 0;
    virtual void imprimeNoArquivo(ofstream &o) = 0;
    virtual void imprimeSeguidor(ofstream &o) = 0;
    virtual void carregaArquivo(ifstream &arqRed) = 0;
    virtual void carregaSeguidor(ifstream &arqRed) = 0;
    virtual void imprimirNoHtmlPerfil() = 0;
    virtual void imprimirNoHtmlSeguidor() = 0;
};

#endif // USUARIO_H_INCLUDED
