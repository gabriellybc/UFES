#ifndef USUARIOCOMUM_H_INCLUDED
#define USUARIOCOMUM_H_INCLUDED
#include "Usuario.h"

class UsuarioComum: public Usuario
{
public:
    enum StatusRelacionamento
    {
        Solteiro=1,
        Namorando=2,
        Casado=3
    };
private:
    char genero;
    string formacao;
    StatusRelacionamento status;
public:
    UsuarioComum();
    UsuarioComum(string nome, string id, tm data, char genero, string formacao, StatusRelacionamento status);
    void setGenero(char genero);
    char getGenero();
    void setFormacao(string formacao);
    string getFormacao();
    StatusRelacionamento getStatus();
    void setStatus(StatusRelacionamento status);
    string getStringStatus();
    bool validadeIdade(int idadeMinUsuarioAnos, int idadeMinPaginaDias);
    void imprimeInfo();
};

#endif // USUARIOCOMUM_H_INCLUDED
