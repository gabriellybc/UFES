#ifndef REDESOCIAL_H_INCLUDED
#define REDESOCIAL_H_INCLUDED

#include <iostream>
#include <ctime>
#include "UsuarioComum.h"
#include "Pagina.h" // ta incluido publicação
#include "Grupo.h" // ta incluido categoria

using namespace std;

class RedeSocial
{
private:
    string nome;
    vector<Usuario*> usuarios;
    vector<Grupo*> grupos;
public:
    string getNome();
    void setNome(string nome);
    vector<Usuario*> getUsuarios();
    vector<Grupo*> getGrupos();
    friend int selecionaRedeSocial (vector <RedeSocial*> redesSociais);
    RedeSocial();
    RedeSocial(string n);
    bool datainvalida(tm data);
    void criarUsuario();
    int selecionaUsuario();
    void seguirUsuario();
    void deixarSeguirUsuario();
    void criarPublicacaoUsuario();
    void editarPublicacaoUsuario();
    void excluirPublicacaoUsuario();
    void imprimirPublicacoesUsuario();
    void imprimirSeguidoresUsuario();
    void criarGrupo();
    int selecionaGrupo();
    void excluirGrupo();
    void adicionarParticipanteGrupo();
    void removerParticipanteGrupo();
    void imprimirParticipantesGrupo();
    void imprimirUsuariosCadastrados();
    void imprimirGruposCadastrados(string s);
    void imprimirGruposCadastrados();
    void imprimirAniversariantesMes();
    void imprimirPublicacoes();
};

#endif // REDESOCIAL_H_INCLUDED
