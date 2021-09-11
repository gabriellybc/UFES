#ifndef PAGINA_H_INCLUDED
#define PAGINA_H_INCLUDED

#include "Usuario.h"
#include "UsuarioComum.h"
#include "Categoria.h"

class Pagina: public Usuario
{
private:
    string sobre,urlFoto;
    Categoria *categoria;
public:
    Pagina();
    Pagina(string nome, string id, tm data, string urlFoto, string categoria, string sobre);
    Categoria* getCategoria();
    void setCategoria(Categoria* categoria);
    string getSobre();
    void setSobre(string sobre);
    bool validadeIdade(int idadeMinUsuarioAnos, int idadeMinPaginaDias);
    void imprimeInfo();
    void imprimeNoArquivo(ofstream &o);
    void imprimeSeguidor(ofstream &o);
    void carregaArquivo(ifstream &arqRed);
    void carregaSeguidor(ifstream &arqRed);
    void imprimeNoHtmlPerfil(ofstream &o);
    void imprimeNoHtmlSeguidor(ofstream &o);
};

#endif // PAGINA_H_INCLUDED
