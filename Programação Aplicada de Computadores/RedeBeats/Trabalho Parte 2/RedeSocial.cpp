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
            else
                return 1;
        }
    }
    return 0;
}
void RedeSocial::criarUsuario()
{
    int d,m,a,w,st,ops=0;
    tm data;
    string c,n,id,s,f,url;
    char g;
    Usuario *novo;
    cout << endl;
    do
    {
        cout << "Digite 1 para ser página ou 2 para usuário comum: ";
        cin >> w;
        cout <<endl;
    }
    while(w<1 || w>2);
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
        getline(cin, s);
        cout << "Digite a url da imagem da página: ";
        getline(cin, url);
        novo = new Pagina(n,id,data,url,c,s);
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
        while(st<1 || st>3);
        if(data.tm_year+1900<1900)
        {
            f= "Vampiro";
        }
        if(data.tm_year+1900<100)
        {
            f= "Lorde Vampiro";
        }
        cout << "Digite a url da imagem do usuário comum: ";
        cin.ignore();
        getline(cin, url);
        novo= new UsuarioComum(n,id,data,url,g, f,UsuarioComum::StatusRelacionamento(st));
        cout << endl;
    }
    if(usuarios.empty())
    {
        cout << "Você foi o primeiro usuário a se cadastrar nessa rede social...\nMeio solitario neh\n\n";
    }
    else
    {
        cout<< "Cadastrado com sucesso\n\n";
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
    if(usuarios.empty())
    {
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
    int i,k=0;
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
            k++;
            cout << endl;
        }
    }
    if(k==0)
    {
        cout<< "Não há grupos nessa categoria\n";
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
            cout << endl << "SEU ANIVERSARIO É NESSE MÊS EM!!!\n" <<endl;
            niver++;
        }
    }
    if(niver==0)
    {
        cout <<  "Não existem usuários que fazem aniversário nesse mês\n" <<endl;
    }
}
void RedeSocial::imprimirPublicacoes()
{
    int i,j;
    if(usuarios.empty())
    {
        cout << "Não existem usuários cadastrados portanto não existem publicações\n";
    }
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
void RedeSocial::ImprimeNoArquivo(ofstream &o)
{
    o << this->nome << endl;
    o << this->usuarios.size() << endl;
    for(int i=0; i<this->usuarios.size(); i++)
    {
        usuarios[i]->imprimeNoArquivo(o);
    }
    o << this->grupos.size() << endl;
    for(int j=0; j<this->grupos.size(); j++)
    {
        grupos[j]->imprimeNoArquivo(o);
    }
    cout << "Rede social " << this->nome << " salva com sucesso!" << endl;
}
void RedeSocial::carregaArquivo(ifstream &arqRede)
{
    arqRede >> this->nome;
    arqRede.ignore();
    int x,y;
    string tipo;
    arqRede >> x;
    arqRede.ignore();
    Usuario::qtdUsuarios+=x;
    for(int i=0; i<x; i++)
    {
        arqRede >> tipo;
        arqRede.ignore();
        if(tipo=="P")
        {
            Usuario* u;
            u = new Pagina();
            usuarios.push_back(u);
            usuarios[i]->carregaArquivo(arqRede);
        }
        else
        {
            Usuario* u;
            u = new UsuarioComum();
            usuarios.push_back(u);
            usuarios[i]->carregaArquivo(arqRede);
        }
    }
    arqRede >> y;
    arqRede.ignore();
    for(int i=0; i<y; i++)
    {
        Grupo* g;
        g = new Grupo();
        grupos.push_back(g);
        grupos[i]->carregaArquivo(arqRede);
    }
    cout << "Rede social " << this->nome << " carregada com sucesso!" << endl;
}
void RedeSocial::exportarRedeSocial(ofstream &o)
{
	//código base html e css:
	/*
    o << "<html>" << endl;
    o << "<head>" << endl;
    o << "<meta charset=\"UTF-8\">" << endl;
    o << "<style>" << endl;
    o << "body {" << endl;
    o << "background-color: rgb(245, 245, 245);" << endl;
    o << "font-family: 'Roboto', sans-serif;" << endl;
    o << "margin: 0;" << endl;
    o << "}" << endl;
    o << "#divBody {" << endl;
    o << "justify-content: center;" << endl;
    o << "margin:auto;" << endl;
    o << "align-items: center;" << endl;
    o << "width: 1400px;" << endl;
    o << "overflow-x: scroll;" << endl;
    o << "}" << endl;
    o << "#bar {" << endl;
    o << "height: 50px;" << endl;
    o << "background: #4267b2;" << endl;
    o << "text-align: center;" << endl;
    o << "}" << endl;
    o << "#perfil {" << endl;
    o << "width: 300px;" << endl;
    o << "}" << endl;
    o << "#perfil #sobre {" << endl;
    o << "text-align: left;" << endl;
    o << "color: rgba(0, 0, 0, .8);" << endl;
    o << "background-color: rgb(252, 252, 252);" << endl;
    o << "border: 1px solid rgb(220, 220, 220);" << endl;
    o << "margin-left: 19px;" << endl;
    o << "width: calc(300px - 40px);" << endl;
    o << "}" << endl;
    o << "#publicacoes {" << endl;
    o << "width: 500px;" << endl;
    o << "margin: 0 auto;" << endl;
    o << "}" << endl;
    o << "#seguidores {" << endl;
    o << "width: 500px;" << endl;
    o << "margin: 0 auto;" << endl;
    o << "}" << endl;
    o << "h1 {" << endl;
    o << "color: white;" << endl;
    o << "padding-top: 10px;" << endl;
    o << "font-size: 26px;" << endl;
    o << "}" << endl;
    o << "h2 {" << endl;
    o << "font-size: 20px;" << endl;
    o << "margin: 30px auto 10px auto;" << endl;
    o << "color: rgba(0, 0, 0, .8);" << endl;
    o << "}" << endl;
    o << "h3 {" << endl;
    o << "font-size: 18px;" << endl;
    o << "margin-left: 20px;" << endl;
    o << "float: left;" << endl;
    o << "color: rgba(0, 0, 0, .8);" << endl;
    o << "}" << endl;
    o << "h4 {" << endl;
    o << "font-size: 15px;" << endl;
    o << "color: rgba(0, 0, 0, .75);" << endl;
    o << "margin: 10px;" << endl;
    o << "font-weight: 400;" << endl;
    o << "}" << endl;
    o << ".text-center {" << endl;
    o << "text-align: center;" << endl;
    o << "}" << endl;
    o << ".row {" << endl;
    o << "width: 100%;" << endl;
    o << "display: flex;" << endl;
    o << "flex-wrap: wrap;" << endl;
    o << "margin-left: 0;" << endl;
    o << "margin-right: 0;" << endl;
    o << "}" << endl;
    o << ".col-12 {" << endl;
    o << "width: 100%;" << endl;
    o << "}" << endl;
    o << "#perfil .bg-img{" << endl;
    o << "text-align: center;" << endl;
    o << "}" << endl;
    o << "#perfil .bg-img img, #seguidores .bg-img img {" << endl;
    o << "border: 1px solid rgb(200, 200, 200);" << endl;
    o << "width: calc(300px - 40px);" << endl;
    o << "}" << endl;
    o << "#card {" << endl;
    o << "display: table;" << endl;
    o << "margin: auto;" << endl;
    o << "}" << endl;
    o << "#card .row {" << endl;
    o << "margin-bottom: 20px;" << endl;
    o << "}" << endl;
    o << "#card .bg-img{" << endl;
    o << "background-position: center;" << endl;
    o << "background-size: cover;" << endl;
    o << "background-repeat: no-repeat;" << endl;
    o << "position: relative;" << endl;
    o << "height: 100%;" << endl;
    o << "}" << endl;
    o << "#card .bg-img img{" << endl;
    o << "background-color: white;" << endl;
    o << "height: 100%;" << endl;
    o << "width: 100%;" << endl;
    o << "border: 1px solid rgb(220, 220, 220);" << endl;
    o << "}" << endl;
    o << "#card #divImage{" << endl;
    o << "position: relative;" << endl;
    o << "float: left;" << endl;
    o << "}" << endl;
    o << "#publicacoes #card #divImage{" << endl;
    o << "width: 220px;" << endl;
    o << "height: 180px;" << endl;
    o << "}" << endl;
    o << "#seguidores #card #divImage{" << endl;
    o << "width: 220px;" << endl;
    o << "height: 210px;" << endl;
    o << "}" << endl;
    o << "#card h3{" << endl;
    o << "color: rgba(0,0,0,0.7);" << endl;
    o << "font-size: 17px;" << endl;
    o << "margin: 10px;" << endl;
    o << "padding-bottom: 5px;" << endl;
    o << "border-bottom: 1px solid lightgray;" << endl;
    o << "width: calc(100% - 20px);" << endl;
    o << "}" << endl;
    o << "#card #info{" << endl;
    o << "border: 1px solid rgb(220, 220, 220);" << endl;
    o << "background-color: white;" << endl;
    o << "position: relative;" << endl;
    o << "float: left;" << endl;
    o << "}" << endl;
    o << "#publicacoes #card #info{" << endl;
    o << "width: 275px;" << endl;
    o << "height: 180px;" << endl;
    o << "}" << endl;
    o << "#seguidores #card #info{" << endl;
    o << "width: 275px;" << endl;
    o << "height: 210px;" << endl;
    o << "}" << endl;
    o << "#card .info h4{" << endl;
    o << "color: black;" << endl;
    o << "font-size: 16px;" << endl;
    o << "line-height: 1em;" << endl;
    o << "adding: 7px 0;" << endl;
    o << "}" << endl;
    o << "</style>" << endl;
    o << "<title>Beterraba</title>" << endl;
    o << "</head>" << endl;
    o << "<body>" << endl;
    o << "<div id=\"bar\">" << endl;
    o << "<h1>Beterraba</h1>" << endl;
    o << "</div>" << endl;
    o << "<div id=\"divBody\">" << endl;
    o << "<div class=\"row\">" << endl;
    o << "<div class=\"col-12 text-center\">" << endl;
    o << "<h2>raquel (Usuario Comum)</h2>" << endl;
    o << "</div>" << endl;
    o << "<div id=\"perfil\">" << endl;
    o << "<div class=\"row\">" << endl;
    o << "<div class=\"col-12\">" << endl;
    o << "<h3>Perfil</h3>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    o << "<div class=\"bg-img\">" << endl;
    o << "<img src=\"https://statig1.akamaized.net/bancodeimagens/5i/6x/4l/5i6x4ly396q2ioenmxznv4zd3.jpg\" />" << endl;
    o << "</div>" << endl;
    o << "<div id=\"sobre\">" << endl;
    o << "<h4>1</h4>" << endl;
    o << "<h4>31/12/1999</h4>" << endl;
    o << "<h4>Feminino</h4>" << endl;
    o << "<h4>Solteiro</h4>" << endl;
    o << "<h4>estudante</h4>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    o << "<div id=\"publicacoes\">" << endl;
    o << "<div class=\"row\">" << endl;
    o << "<div class=\"col-12\">" << endl;
    o << "<h3>Publicacoes</h3>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    o << "<div id=\"card\">" << endl;
    o << "<div class=\"row\">" << endl;
    o << "<div id=\"divImage\">" << endl;
    o << "<div class=\"bg-img\">" << endl;
    o << "<img src=\"https://thumbs.dreamstime.com/b/alpaca-branca-do-beb%C3%AA-que-dorme-em-sun-26797946.jpg\" />" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    o << "<div id=\"info\">" << endl;
    o << "<div>" << endl;
    o << "<h3>4/12/2019</h3>" << endl;
    o << "</div>" << endl;
    o << "<h4>hihihi que fofinho adoro alpacas</h4>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    o << "<div id=\"seguidores\">" << endl;
    o << "<div class=\"row\">" << endl;
    o << "<div class=\"col-12\">" << endl;
    o << "<h3>Seguidores</h3>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    o << "<h4 style=\"font-style: italic; text-decoration: underline;\"> Nenhum seguidor ate o momento!</h4>" << endl;
    o << "</div>" << endl;
    o << "<div style=\"border-bottom: 1px solid rgb(215, 215, 215); margin-top: 30px;\" class=\"row\">" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    o << "</div>" << endl;
    o << "</body>" << endl;
    o << "</html>" << endl;
	*/
}
