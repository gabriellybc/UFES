#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Filme
{
private:
    string nome, genero;
    int duracaoEmMinutos, anoLancamento, classificacaoIndicativa;
public:
    Filme()
    {
        cin.ignore(1,'\n');
        cout << "Digite o nome do filme: ";
        getline(cin, nome);
        cout << "Digite o gênero do filme: ";
        getline(cin, genero);
        cout << "Digite a duração em minutos: ";
        cin >> duracaoEmMinutos;
        cout << "Digite o ano de lançamento: ";
        cin >> anoLancamento;
        cout << "Digite a classificação indicativa: ";
        cin >> classificacaoIndicativa;
        cout << "Filme cadastrado com sucesso!\n\n";
    }
    void imprimeInfo()
    {
        cout << "Nome do filme: " << nome << endl;
        cout << "Gênero do filme: " << genero << endl;
        cout << "Duração em minutos: " << duracaoEmMinutos << endl;
        cout << "Ano de lançamento: " << anoLancamento << endl;
        cout << "Classificação indicativa: " << classificacaoIndicativa << endl;
    }
    void imprimeArquivoHtml(ofstream &o)
    {
        o << "<td>" << nome << "</td>" << endl;
        o << "<td>" << genero << "</td>" << endl;
        o << "<td>" << duracaoEmMinutos << "</td>" << endl;
        o << "<td>" << anoLancamento << "</td>" << endl;
        o << "<td>" << classificacaoIndicativa << "</td>" << endl;
    }
    void tabela(ofstream &o)
    {
        o << "<tr>" << endl;
        o << "<th>Nº</th>" << endl;
        o << "<th>Nome</th>" << endl;
        o << "<th>Gênero</th>" << endl;
        o << "<th>Duração (min)</th>" << endl;
        o << "<th>Ano de Lançamento</th>" << endl;
        o << "<th>Classificação Indicativa</th>" << endl;
        o << "</tr>" << endl;
    }
};

class Musica
{
private:
    string nome, genero, cantorOuBanda;
    int duracaoEmMinutos, anoLancamento, classificacaoIndicativa;
public:
    Musica()
    {
        cin.ignore(1,'\n');
        cout << "Digite o nome da música: ";
        getline(cin, nome);
        cout << "Digite o gênero da música: ";
        getline(cin, genero);
        cout << "Digite o nome do cantor ou da banda: ";
        getline(cin, cantorOuBanda);
        cout << "Digite a duração em minutos: ";
        cin >> duracaoEmMinutos;
        cout << "Digite o ano de lançamento: ";
        cin >> anoLancamento;
        cout << "Música cadastrada com sucesso!\n\n";
    }
    void imprimeInfo()
    {
        cout << "Nome da música: " << nome << endl;
        cout << "Gênero da música: " << genero << endl;
        cout << "Cantor ou banda: " << cantorOuBanda << endl;
        cout << "Duração em minutos: " << duracaoEmMinutos << endl;
        cout << "Ano de lançamento: " << anoLancamento << endl;
    }
    void imprimeArquivoHtml(ofstream &o)
    {
        o << "<td>" << nome << "</td>" << endl;
        o << "<td>" << genero << "</td>" << endl;
        o << "<td>" << cantorOuBanda << "</td>" << endl;
        o << "<td>" << duracaoEmMinutos << "</td>" << endl;
        o << "<td>" << anoLancamento << "</td>" << endl;
    }
    void tabela(ofstream &o)
    {
        o << "<tr>" << endl;
        o << "<th>Nº</th>" << endl;
        o << "<th>Nome</th>" << endl;
        o << "<th>Gênero</th>" << endl;
        o << "<th>Cantor ou Banda</th>" << endl;
        o << "<th>Duração (min)</th>" << endl;
        o << "<th>Ano de Lançamento</th>" << endl;
        o << "</tr>" << endl;
    }
};

template <typename Produto>
class PlataformaDigital
{
private:
    string nome;
    vector<Produto*> produtos;
public:
    void criarProduto()
    {
        Produto *p;
        p = new Produto();
        this->produtos.push_back(p);
    }
    void imprimeProdutos()
    {
        int i;
        if (produtos.empty())
        {
            cout << "Não há produtos cadastrados!\n";
        }
        else
        {
            cout << "\nLISTA DE PRODUTOS\n";
            for (i=0; i<produtos.size(); i++)
            {
                produtos[i]->imprimeInfo();
            }
            cout << endl;
        }
    }
    void exportarBiblioteca()
    {
        ofstream o;
        o.open("exportado.html");
        int i;
        o << "<!DOCTYPE html>" << endl;
        o << "<html lang=\"pt-BR\">" << endl;
        o << "<head>" << endl;
        o << "<style>" << endl;
        o << "body{" << endl;
        o << "background-color: powderblue;" << endl;
        o << "font-family: sans-serif;" << endl;
        o << "}" << endl;
        o << "h2{" << endl;
        o << "text-align: center;" << endl;
        o << "text-transform: uppercase;" << endl;
        o << "}" << endl;
        o << "table{" << endl;
        o << "background-color: white;" << endl;
        o << "font-family: arial, sans-serif;" << endl;
        o << "border-collapse: collapse;" << endl;
        o << "width: 100%;" << endl;
        o << "}" << endl;
        o << "th{" << endl;
        o << "background-color: darkgray;" << endl;
        o << "}" << endl;
        o << "td," << endl;
        o << "th{" << endl;
        o << "border: 1px solid #dddddd;" << endl;
        o << "text-align: left;" << endl;
        o << "padding: 8px;" << endl;
        o << "}" << endl;
        o << ".divTabela{" << endl;
        o << "width: 900px;" << endl;
        o << "text-align: left;" << endl;
        o << "margin: auto" << endl;
        o << "}" << endl;
        o << "</style>" << endl;
        o << "</head>" << endl;
        o << "<body>" << endl;
        o << "<h2>Produtos</h2>" << endl;
        o << "<div class=\"divTabela\">" << endl;
        o << "<table>" << endl;
        produtos[0]->tabela(o);
        for (i=0; i<produtos.size(); i++)
        {
            o << "<tr>" << endl;
            o << "<td>" << i+1 << "</td>" << endl;
            produtos[i]->imprimeArquivoHtml(o);
            o << "</tr>" << endl;
        }
        o << "</table>" << endl;
        o << "</div>" << endl;
        o << "</body>" << endl;
        o << "</html>" << endl;
    }
};

void plat()
{
    cout << "1. Netflix\n";
    cout << "2. Spotify\n";
}

void menu()
{
    cout << "\n1. Criar produto\n";
    cout << "2. Imprimir produtos\n";
    cout << "3. Exportar biblioteca\n";
    cout << "4. Sair\n\n";
}

int main()
{
    int opc1, opc2=0;
    PlataformaDigital<Filme> *f;
    f = new PlataformaDigital<Filme>();
    PlataformaDigital<Musica> *m;
    m = new PlataformaDigital<Musica>();
    do
    {
        do
        {
            plat();
            cout << "Escolha uma das plataformas: ";
            cin >> opc1;
        }
        while(opc1!=1 && opc1!=2);
        if(opc1==1)
        {
            menu();
            cout << "Escolha uma das opções: ";
            cin >> opc2;
            cout << endl;
            if(opc2==1)
            {
                f->criarProduto();
            }
            else if(opc2==2)
            {
                f->imprimeProdutos();
            }
            else if(opc2==3)
            {
                f->exportarBiblioteca();
            }
            else if(opc2==4)
            {
                delete f, m;
            }
        }
        else if(opc1==2)
        {
            menu();
            cout << "Escolha uma das opções: ";
            cin >> opc2;
            cout << endl;
            if(opc2==1)
            {
                m->criarProduto();
            }
            else if(opc2==2)
            {
                m->imprimeProdutos();
            }
            else if(opc2==3)
            {
                m->exportarBiblioteca();
            }
            else if (opc2==4)
            {
                delete f, m;
            }
        }
    }
    while(opc2!=4);
}
