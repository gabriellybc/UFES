#ifndef GRUPO_H_INCLUDED
#define GRUPO_H_INCLUDED

#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include "Categoria.h"
#include "Usuario.h"

using namespace std;
class Grupo
{
private:
    string nome;
    int idadeMinUsuarioAnos, idadeMinPaginaDias;
    vector<Usuario*> participantes;
    Categoria* categoria;
    Usuario* adm;
public:
    string getNome();
    Categoria* getCategoria();
    int getidadeMinUsuarioAnos();
    int getidadeMinPaginaDias();
    void setNome(string nome);
    void setCategoria(Categoria* categoria);
    void setIdadeMinUsuarioAnos(int idadeMinUsuarioAnos);
    void setidadeMinPaginaDias(int idadeMinPaginaDias);
    Usuario* getAdministrador();
    vector<Usuario*> getParticipantes();
    void setAdministrador(Usuario* adm);
    Grupo();
    Grupo(string n, int ida, int pag, string c, Usuario* a);
    void adicionarParticipante(Usuario* usuario);
    void imprimeInfo ();
    void imprimirParticipantes();
    void removerParticipante();
    void imprimeNoArquivo(ofstream &o);
    void carregaArquivo(ifstream &o);
};

#endif // GRUPO_H_INCLUDED
