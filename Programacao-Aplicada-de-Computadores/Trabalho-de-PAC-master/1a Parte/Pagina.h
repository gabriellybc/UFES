#ifndef PAGINA_H_INCLUDED
#define PAGINA_H_INCLUDED
#include "Usuario.h"
#include "Categoria.h"

class Pagina: public Usuario
{
private:
    string sobre;
    Categoria *categoria;
public:
    Pagina();
    Pagina(string nome, string id, tm data, string categoria, string sobre);
    Categoria* getCategoria();
    void setCategoria(Categoria* categoria);
    string getSobre();
    void setSobre(string sobre);
    bool validadeIdade(int idadeMinUsuarioAnos, int idadeMinPaginaDias);
    void imprimeInfo();
};

#endif // PAGINA_H_INCLUDED
