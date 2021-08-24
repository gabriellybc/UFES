#include "RedeSocial.h"
#include "Funcoes.h"

int Usuario::qtdUsuarios = 0;
void salvarDadosRedesSociais(vector <RedeSocial*> redes)
{
    ofstream o;
    o.open("RedesSociais.txt");
    int i;
    o << redes.size() << endl;
    for(i=0; i<redes.size(); i++)
    {
        redes[i]->ImprimeNoArquivo(o);
    }
    o.close();
    cout << "Arquivo com as Redes Sociais foi criado com sucesso!" << endl;
}
vector<RedeSocial*> carregarDadosRedesSociais(ifstream &arqRede)
{
    vector<RedeSocial*> redesSociais;
    Usuario::qtdUsuarios=0;
    int i,x;
    arqRede >> x;
    cout << "A quantidade de redes sociais eh: "<< x <<endl;
    RedeSocial* p;
    for(i=0; i<x; i++)
    {
        p = new RedeSocial();
        redesSociais.push_back(p);
        redesSociais[i]->carregaArquivo(arqRede);
    }
    cout << "Todas as Redes Sociais foram carregadas com sucesso!" << endl;
    return redesSociais;
}
int main()
{
    setlocale(LC_ALL, "Portuguese");
    string catego;
    int a;
    vector<RedeSocial*> redes;
    RedeSocial *r1,*r2,*r3;
    r1 = new RedeSocial("Alface");
    redes.push_back(r1);
    r2 = new RedeSocial("Beterraba");
    redes.push_back(r2);
    r3 = new RedeSocial("Cenoura");
    redes.push_back(r3);
    int i;
    do
    {
        do
        {
            menu();
            cin >> a;
            cout << endl;
        }
        while (a<1 || a>23);
        if(a>=1 && a<=18 || a == 22)
        {
            i=selecionaRedeSocial(redes);
        }
        switch(a)
        {
        case 1:
            redes[i]->criarUsuario();
            break;
        case 2:
            redes[i]->criarGrupo();
            break;
        case 3:
            redes[i]->excluirGrupo();
            break;
        case 4:
            redes[i]->imprimirAniversariantesMes();
            break;
        case 5:
            redes[i]->imprimirUsuariosCadastrados();
            break;
        case 6:
            redes[i]->imprimirGruposCadastrados();
            break;
        case 7:
            cout << "Escolha a categoria: ";
            cin.ignore();
            getline (cin,catego);
            redes[i]->imprimirGruposCadastrados(catego);
            break;
        case 8:
            redes[i]->imprimirPublicacoes();
            break;
        case 9:
            redes[i]->adicionarParticipanteGrupo();
            break;
        case 10:
            redes[i]->removerParticipanteGrupo();
            break;
        case 11:
            redes[i]->imprimirParticipantesGrupo();
            break;
        case 12:
            redes[i]->seguirUsuario();
            break;
        case 13:
            redes[i]->deixarSeguirUsuario();
            break;
        case 14:
            redes[i]->criarPublicacaoUsuario();
            break;
        case 15:
            redes[i]->editarPublicacaoUsuario();
            break;
        case 16:
            redes[i]->excluirPublicacaoUsuario();
            break;
        case 17:
            redes[i]->imprimirPublicacoesUsuario();
            break;
        case 18:
            redes[i]->imprimirSeguidoresUsuario();
            break;
        case 19:
            Usuario::imprimeQtdUsuarios();
            break;
        case 20:
            salvarDadosRedesSociais(redes);
            break;
        case 21:
        {
            ifstream arqRede;
            arqRede.open("RedesSociais.txt");
            if(arqRede.is_open())
            {
                redes.clear();
                redes=carregarDadosRedesSociais(arqRede);
            }
            else
            {
                cout << "O arquivo a ser carregado não existe!" << endl;
            }
            arqRede.close();
        }
        break;
        case 22:
            redes[i]->exportarRedeSocial();
            break;
        case 23:
            redes.clear();
            break;
        }
    }
    while(a!=23);
}
