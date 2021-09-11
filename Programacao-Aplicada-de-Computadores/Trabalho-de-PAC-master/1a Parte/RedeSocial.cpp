#include "RedeSocial.h"

RedeSocial::RedeSocial()
{
}
RedeSocial::RedeSocial(string n)
{
    nome=n;
}
bool RedeSocial::datainvalida(tm data) // vê se a data digitada existe
{
    int d,m,a;
    d=data.tm_mday;
    m=data.tm_mon +1;
    a=data.tm_year+1900;
    if(d<1 || m<1)
    {
        return 1;
    }
    if(a>2019 || a<0||d>31 || d<1||m>12 || m<1)
    {
        return 1;
    }
    else if(d>30)
    {
        if(m==4 || m==7 || m== 9 || m==11)
        {
            return 1;
        }
    }
    else if(m==2)
    {
        if(d>29)
        {
            return 1;
        }
        else if(d==29)
        {
            if(a%4==0)
            {
                if(a%400!=0 && a%100==0)
                {
                    return 1;
                }
            }
            else return 1;
        }
    }
    return 0;
}
void RedeSocial::criarUsuario()
{
    int d,m,a,w,st,ops=0;
    tm data;
    string c,n,id,s,f;
    char g;
    Usuario *novo;
    cout << "Digite 1 para ser página ou 2 para usuário comum: ";
    cin >> w;
    cout << endl;
    do
        {
            cout << "Digite 1 para ser página ou 2 para usuário comum: "; 
            cin >> w;
            cout << endl;
        }
        while(w!=1 || w!=2);
    if(w==1)
    {
        cout << "Digite o nome da página: ";
        cin.ignore();
        getline(cin, n);
        cout << "Digite a ID da página: ";
        cin >> id;
        time_t tt;
        time(&tt);
        tm data=*localtime(&tt);
        cout << "Digite a categoria da página: ";
        cin.ignore();
        getline(cin, c);
        cout << "Escreva sobre a página: ";
        cin.ignore();
        getline(cin, s);
        novo= new Pagina(n,id,data,c,s);
        cout << endl;
    }
    else if(w==2)
    {
        cout << "Digite seu nome: ";
        cin >> n;
        cout << "Digite sua ID: ";
        cin >> id;
        do
        {
            if(ops>0)
            {
                cout << "Digite uma data existente no padrão dia/mês/ano." <<endl;
            }
            cout << "Digite sua data de nascimento: ";
            cin >> d;
            cin.get(); // serve para apagar o '/' que a pessoa escreve
            cin >> m;
            cin.get();
            cin >> a;
            data= {0,0,0,d,m-1,a-1900};
            ops++;
        }
        while(datainvalida(data));
        do
        {
            cout << "Digite o gênero\nM - Masculino\nF - Feminino" <<endl;
            cin >> g;
        }
        while(g!= 'M' && g!= 'm' && g!= 'F' && g!= 'f');
        cout << "Digite sua formação: ";
        cin.ignore();
        getline(cin,f);
        do
        {
            cout << "Escolha o status de relacionamento: " << endl;
            cout << "   1 - Solteiro(a)" << endl;
            cout << "   2 - Namorando" << endl;
            cout << "   3 - Casado(a)" << endl;
            cin >> st;
        }
        if(data.tm_year+1900<1900)
        {
            f= "Vampiro";
        }
        if(data.tm_year+1900<0)
        {
            f= "Lorde Vampiro";
        }
        while(st<1 || st>3);
        novo= new UsuarioComum(n,id,data,g, f,UsuarioComum::StatusRelacionamento(st));
        cout << endl;
    }
    if(usuarios.empty())
    {
        cout << "Você foi o primeiro usuário a se cadastrar nessa rede social...\nMeio solitario neh\n\n";
    }
    usuarios.push_back(novo);
    Usuario::qtdUsuarios++;
}
int RedeSocial::selecionaUsuario()
{
    int n;
    imprimirUsuariosCadastrados();
    if(usuarios.size() == 0)
    {
        n=-1;
    }
    else
    {
        cout << "Escolha o usuário desejado: ";
        cin >> n;
        while (n>=usuarios.size() || n<0)
        {
            cout << "Escolha um grupo válido: ";
            cin >> n;
        }
    }
    return n;
}
void RedeSocial::seguirUsuario()
{
    if(usuarios.size() < 2)
    {
        cout << "Não há pessoas disponíveis na sua região." << endl;
    }
    else
    {
        int seguidor,perseguido;
        seguidor=selecionaUsuario();
        perseguido=selecionaUsuario();
        this->usuarios[perseguido]->novoSeguidor(this->usuarios[seguidor]);
    }
}
void RedeSocial::deixarSeguirUsuario()
{
    if(usuarios.size() == 0)
    {
        cout<< "Não há usuários cadastrados." << endl;
    }
    else
    {
        int deixseguidor;
        cout << "Selecione  o  usuário  que  deseja  deixar  de  seguir: ";
        deixseguidor=selecionaUsuario();
        this->usuarios[deixseguidor]->removerSeguidor();
    }
}
void RedeSocial::criarPublicacaoUsuario()
{
    int usu;
    if(usuarios.empty()) {
    cout<< "Não tem usuário, bobinho." << endl;
    }
    else
    {
        usu=selecionaUsuario();
        this->usuarios[usu]->criarPublicacao();
    }
}
void RedeSocial::editarPublicacaoUsuario()
{
    if(usuarios.empty())
    {
        cout<< "Não tem usuário, bobinho." << endl;
    }
    else
    {
        int usu;
        usu=selecionaUsuario();
        this->usuarios[usu]->editarPublicacao();
    }
}
void RedeSocial::excluirPublicacaoUsuario()
{
    if(usuarios.empty())
    {
        cout<< "Não tem usuário, bobinho." << endl;
    }
    else
    {
        int usu;
        usu=selecionaUsuario();
        this->usuarios[usu]->excluirPublicacao();
    }
}
void RedeSocial::imprimirPublicacoesUsuario()
{
    if(usuarios.empty())
    {
        cout<< "Não tem usuário, bobinho." << endl;
    }
    else
    {
        int pos;
        this->imprimirUsuariosCadastrados();
        do
        {
            cout << "Digite a posição desejada: ";
            cin >> pos;
        }
        while(pos<0 || pos>=this->usuarios.size());
        this->usuarios[pos]->imprimirPublicacoes();
    }
}
void RedeSocial::imprimirSeguidoresUsuario()
{
    if(usuarios.empty())
    {
        cout<< "Não tem usuário, bobinho." << endl;
    }
    else
    {
        int usu;
        usu=selecionaUsuario();
        this->usuarios[usu]->imprimirSeguidores();
    }
}
void RedeSocial::criarGrupo()
{
    if(this->usuarios.empty())
    {
        cout << "Não há usuários cadastrados." << endl;
        return;
    }
    int idademinA, idademinD,adm;
    string nomeG,cat;
    cout << "Digite o nome do grupo: ";
    cin.ignore();
    getline (cin,nomeG);
    cout << "Digite a idade mínima de entrada para Usuários Comuns (em anos): ";
    cin >> idademinA;
    cout << "Digite a idade mínima de entrada para Páginas (em dias): ";
    cin >> idademinD;
    cout << "Digite a categoria: ";
    cin.ignore();
    getline(cin,cat);
    adm=selecionaUsuario();
    Grupo *g;
    g= new Grupo(nomeG,idademinA, idademinD,cat,this->usuarios[adm]);
    grupos.push_back(g);
    cout << endl << "Grupo criado com sucesso." << endl;
}
int RedeSocial::selecionaGrupo()
{
    int n;
    imprimirGruposCadastrados();
    if(grupos.size() == 0)
    {
        n=-1;
    }
    else
    {
        cout << "Escolha o grupo desejado: ";
        cin >> n;
        while(n>=grupos.size() || n<0)
        {
            cout << "Escolha um grupo válido: ";
            cin >> n;
        }
    }
    return n;
}
void RedeSocial::excluirGrupo()
{
    int i;
    if(grupos.size() == 0)
    {
        cout << "Não há grupos cadastrados." << endl;
        return;
    }
    i=selecionaGrupo();
    grupos.erase(grupos.begin()+i);
    cout << "O grupo foi excluído com sucesso." << endl;
}
void RedeSocial::adicionarParticipanteGrupo()
{
    int g,u;
    cout << "Selecione um grupo: ";
    g=selecionaGrupo();
    if(g!=-1)
    {
        u=selecionaUsuario();
        if(u!=-1)
        {
            grupos[g]->adicionarParticipante(usuarios[u]);
        }
    }
    else
    {
        cout << "Não há grupos cadastrados." << endl;
    }
}
void RedeSocial::removerParticipanteGrupo()
{
    int g;
    cout << "Selecione um grupo: ";
    g=selecionaGrupo();
    if(g!=-1)
    {
        grupos[g]->removerParticipante();
    }
    else
    {
        cout << "Não há grupos cadastrados." << endl;
    }
}
void RedeSocial::imprimirParticipantesGrupo()
{
    int g;
    cout << "Selecione um grupo: ";
    g=selecionaGrupo();
    if(g!=-1)
    {
        grupos[g]->imprimirParticipantes();
        cout << endl;
    }
    else
    {
        cout << "Não há grupos cadastrados." << endl;
    }
}
void RedeSocial::imprimirUsuariosCadastrados()
{
    if (usuarios.size() == 0)
    {
        cout << "Não existe nenhum usuário cadastrado." << endl;
    }
    else
    {
        int i;
        for(i=0; i<usuarios.size(); i++)
        {
            cout << "Usuário " << i << endl;
            usuarios[i]->imprimeInfo();
            cout << endl;
        }
    }
}
void RedeSocial::imprimirGruposCadastrados(string s)
{
    int i;
    if(grupos.size() == 0)
    {
        cout << "Não há grupos cadastrados." << endl;
        return;
    }
    for (i=0; i<grupos.size(); i++)
    {
        if(grupos[i]->getCategoria()->getNome() == s)
        {
            grupos[i]->imprimeInfo();
            cout << endl;
        }
    }
}
void RedeSocial::imprimirGruposCadastrados()
{
    int i;
    if(grupos.size() == 0)
    {
        cout << "Não há grupos cadastrados." << endl;
        return;
    }
    for (i=0; i<grupos.size(); i++)
    {
        cout << "Grupo " << i << endl;
        grupos[i]->imprimeInfo();
        cout << endl;
    }
}
void RedeSocial::imprimirAniversariantesMes()
{
    int niver=0;
    time_t tt;
    time(&tt);
    int i;
    tm dataAtual = *localtime(&tt);
    for(i=0; i<usuarios.size(); i++)
    {
        if(usuarios[i]->getData().tm_mon == dataAtual.tm_mon)
        {
            cout << "Usuário " << i << endl;
            usuarios[i]->imprimeInfo();
            cout << endl << "SEU ANIVERSARIO É NESSE MES EM!!!\n" <<endl;
            niver++;
        }
    }
    if(niver==0)
    {
         cout <<  "Não existem usuarios que farão aniversario nesse mes\n" <<endl;
    }
}
void RedeSocial::imprimirPublicacoes()
{
    int i,j;
    for(i=0; i<usuarios.size(); i++)
    {
        usuarios[i]->imprimirPublicacoes();
    }
}
string RedeSocial::getNome()
{
    return this->nome;
}
void RedeSocial::setNome(string name)
{
    this->nome=name;
}
vector<Usuario*> RedeSocial::getUsuarios()
{
    return this->usuarios;
}
vector<Grupo*> RedeSocial::getGrupos()
{
    return this->grupos;
}
