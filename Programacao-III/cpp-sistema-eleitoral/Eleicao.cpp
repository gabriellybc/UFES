#include <iostream>
#include "Eleicao.h"
#include "NumberUtils.h"
using namespace std;

Eleicao::Eleicao(){}

const time_t &Eleicao::getDataAtual() const
{
    return dataAtual;
}

Partido *Eleicao::getPartido(int idx) const
{
    return partidos[idx];
}

Candidato *Eleicao::getCandidato(int idx) const
{
    return todosCandidatos[idx];
}

Candidato *Eleicao::getCandidatoEleito(int idx) const
{
    return candidatosEleitos[idx];
}

void Eleicao::setDataAtual(const string &data)
{
    this->dataAtual = parseDate(data, DATE_FORMAT_PT_BR_SHORT);
}

void Eleicao::addPartido(Partido *partido)
{
    partidos.push_back(partido);
}

void Eleicao::addCandidato(Candidato *candidato)
{
    todosCandidatos.push_back(candidato);
    if (candidato->getSituacao().compare("Eleito") == 0)
        candidatosEleitos.push_back(candidato);
}

void Eleicao::addCandidatoEleito(Candidato *candidato)
{
    candidatosEleitos.push_back(candidato);
}

int Eleicao::getEleitosPorSexo(const string &str) const
{
    int count = 0;
    for (auto f : candidatosEleitos)
    {
        if (str.compare(f->getSexo()) == 0)
        {
            count++;
        }
    }
    return count;
}

Partido *Eleicao::getPartidoPorNumero(const int numeroPartido) const
{
    for (auto p : this->partidos)
        if (p->getNumero() == numeroPartido)
            return p;
    return NULL;
}

string Eleicao::getNomenclaturaVoto(const int voto) const
{
    if (voto <= 1)
        return "voto";
    return "votos";
}

string Eleicao::getNomenclaturaCandidatoEleito(const int candidato) const
{
    if (candidato <= 1)
        return "candidato eleito";

    return "candidatos eleitos";
}

string Eleicao::getNomenclaturaNominal(const int voto) const
{
    if (voto <= 1)
        return "nominal";
    return "nominais";
}

void Eleicao::gerarRelatorios()
{
    gerarRelatorio01();
    gerarRelatorio02();
    gerarRelatorio03();
    gerarRelatorio04();
    gerarRelatorio05();
    gerarRelatorio06();
    gerarRelatorio07();
    gerarRelatorio08();
    gerarRelatorio09();
    gerarRelatorio10();
    gerarRelatorio11();
}

void Eleicao::gerarRelatorio01() const
{
    cout << "Número de vagas: " << candidatosEleitos.size() << endl
         << endl;
}

void Eleicao::gerarRelatorio02()
{
    sort(candidatosEleitos.begin(), candidatosEleitos.end(), Candidato::comparaCandidatoPorVotosNominais);
    int idx = 1;
    cout << "Vereadores eleitos:" << endl;
    for (auto candidato : this->candidatosEleitos)
    {
        printf("%d - %s / %s (%s, %d %s)\n", idx, candidato->getNome().c_str(), candidato->getNomeUrna().c_str(),
               candidato->getPartido()->getSigla().c_str(), candidato->getVotosNominais(),
               getNomenclaturaVoto(candidato->getVotosNominais()).c_str());
        idx++;
    }
    cout << endl;
}

void Eleicao::gerarRelatorio03()
{
    sort(todosCandidatos.begin(), todosCandidatos.end(), Candidato::comparaCandidatoPorVotosNominais);
    cout << "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << endl;
    int idx = 1;
    for (auto candidato : todosCandidatos)
    {
        printf("%d - %s / %s (%s, %d %s)\n", idx, candidato->getNome().c_str(), candidato->getNomeUrna().c_str(),
               candidato->getPartido()->getSigla().c_str(), candidato->getVotosNominais(),
               getNomenclaturaVoto(candidato->getVotosNominais()).c_str());
        if (idx == (int)candidatosEleitos.size())
            break;
        idx++;
    }
    cout << endl;
}

void Eleicao::gerarRelatorio04()
{
    sort(todosCandidatos.begin(), todosCandidatos.end(), Candidato::comparaCandidatoPorVotosNominais);
    cout << "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:" << endl;
    cout << "(com sua posição no ranking de mais votados)" << endl;
    int idx = 1;
    for (auto candidato : todosCandidatos)
    {
        if (candidato->getSituacao().compare("Eleito") != 0)
        {
            printf("%d - %s / %s (%s, %d %s)\n", idx, candidato->getNome().c_str(), candidato->getNomeUrna().c_str(),
                   candidato->getPartido()->getSigla().c_str(), candidato->getVotosNominais(),
                   getNomenclaturaVoto(candidato->getVotosNominais()).c_str());
        }
        if (idx == (int)candidatosEleitos.size())
            break;
        idx++;
    }
    cout << endl;
}

void Eleicao::gerarRelatorio05()
{
    sort(todosCandidatos.begin(), todosCandidatos.end(), Candidato::comparaCandidatoPorVotosNominais);
    cout << "Eleitos, que se beneficiaram do sistema proporcional:" << endl;
    cout << "(com sua posição no ranking de mais votados)" << endl;
    int idx = 1;
    int qntEleitos = 0;
    for (auto candidato : todosCandidatos)
    {
        if (candidato->getSituacao().compare("Eleito") == 0)
        {
            qntEleitos++;
            if (idx > (int)candidatosEleitos.size())
            {
                printf("%d - %s / %s (%s, %d %s)\n", idx, candidato->getNome().c_str(), candidato->getNomeUrna().c_str(), candidato->getPartido()->getSigla().c_str(), candidato->getVotosNominais(),
                       getNomenclaturaVoto(candidato->getVotosNominais()).c_str());
                if (qntEleitos == (int)candidatosEleitos.size())
                    break;
            }
        }
        idx++;
    }
    cout << endl;
}

void Eleicao::gerarRelatorio06()
{
    sort(partidos.begin(), partidos.end(), Partido::comparaPartidoPorTotalVotos);
    cout << "Votação dos partidos e número de candidatos eleitos:" << endl;
    int idx = 1;
    for (auto partido : partidos)
    {
        int votosNominais = partido->getVotosNominais();
        int votosLegenda = partido->getVotosLegenda();

        printf("%d - %s - %d, %d %s (%d %s e %d de legenda), %d %s\n",
               idx, (partido->getSigla()).c_str(), partido->getNumero(), votosNominais + votosLegenda, (getNomenclaturaVoto(votosNominais + votosLegenda)).c_str(), votosNominais, (getNomenclaturaNominal(votosNominais)).c_str(), votosLegenda, partido->getNumeroCandidatosEleitos(), (getNomenclaturaCandidatoEleito(partido->getNumeroCandidatosEleitos())).c_str());
        idx++;
    }
    cout << endl;
}

void Eleicao::gerarRelatorio07()
{
    sort(partidos.begin(), partidos.end(), Partido::comparaPartidoPorVotosLegenda);
    cout << "Votação dos partidos (apenas votos de legenda):" << endl;
    int idx = 1;
    for (auto partido : partidos)
    {
        int votosLegenda = partido->getVotosLegenda();
        int total = partido->getVotosNominais() + partido->getVotosLegenda();
        if (total == 0)
            printf("%d - %s - %d, %d %s de legenda (proporção não calculada, 0 voto no partido)\n",
                   idx, (partido->getSigla()).c_str(), partido->getNumero(), votosLegenda, (getNomenclaturaVoto(votosLegenda)).c_str());
        else
            printf("%d - %s - %d, %d %s de legenda (%s%% do total do partido)\n",
                   idx, (partido->getSigla()).c_str(), partido->getNumero(), votosLegenda, (getNomenclaturaVoto(votosLegenda)).c_str(), (formatDoubleCurrency((double)votosLegenda * 100 / total, LOCALE_PT_BR)).c_str());
        idx++;
    }
    cout << endl;
}

void Eleicao::gerarRelatorio08()
{
    sort(partidos.begin(), partidos.end(), Partido::comparaPartidoPorTotalVotosNominaisDoCandidatoMaisVotado);
    cout << "Primeiro e último colocados de cada partido:" << endl;
    int idx = 1;
    for (auto partido : partidos)
    {
        if (partido->getCandidato(0) != NULL)
        {
            Candidato *primeiro = partido->getCandidato(0);
            Candidato *ultimo  = partido->getCandidatoMenosVotado();

            printf("%d - %s - %d, %s (%d, %d %s) / %s (%d, %d %s)\n", idx, (partido->getSigla()).c_str(),
                   partido->getNumero(), (primeiro->getNomeUrna()).c_str(), primeiro->getNumeroUrna(), primeiro->getVotosNominais(), (getNomenclaturaVoto(primeiro->getVotosNominais())).c_str(),
                   (ultimo->getNomeUrna()).c_str(), ultimo->getNumeroUrna(), ultimo->getVotosNominais(), (getNomenclaturaVoto(ultimo->getVotosNominais())).c_str());
            idx++;
        }
    }
    cout << endl;
}

void Eleicao::gerarRelatorio09() const
{
    /*
     * [0] Idade < 30
     * [1] 30 <= Idade < 40
     * [2] 40 <= Idade < 50
     * [3] 50 <= Idade < 60
     * [4] 60 <= Idade
     */
    int faixaEtaria[5] = {};
    for (auto candidato : candidatosEleitos)
    {
        int idade = candidato->calculaIdade(dataAtual);
        if (idade < 30)
            faixaEtaria[0]++;
        else if (30 <= idade && idade < 40)
            faixaEtaria[1]++;
        else if (40 <= idade && idade < 50)
            faixaEtaria[2]++;
        else if (50 <= idade && idade < 60)
            faixaEtaria[3]++;
        else
            faixaEtaria[4]++;
    }
    cout << "Eleitos, por faixa etária (na data da eleição):" << endl;
    int total = faixaEtaria[0] + faixaEtaria[1] + faixaEtaria[2] + faixaEtaria[3] + faixaEtaria[4];
    if (total == 0)
    {
        printf("      Idade < 30: %d (0.00%%)\n", faixaEtaria[0]);
        printf("30 <= Idade < 40: %d (0.00%%)\n", faixaEtaria[1]);
        printf("40 <= Idade < 50: %d (0.00%%)\n", faixaEtaria[2]);
        printf("50 <= Idade < 60: %d (0.00%%)\n", faixaEtaria[3]);
        printf("60 <= Idade     : %d (0.00%%)\n", faixaEtaria[4]);
    }
    else
    {
        printf("      Idade < 30: %d (%s%%)\n", faixaEtaria[0], (formatDoubleCurrency((double)faixaEtaria[0] * 100 / total, LOCALE_PT_BR)).c_str());
        printf("30 <= Idade < 40: %d (%s%%)\n", faixaEtaria[1], (formatDoubleCurrency((double)faixaEtaria[1] * 100 / total, LOCALE_PT_BR)).c_str());
        printf("40 <= Idade < 50: %d (%s%%)\n", faixaEtaria[2], (formatDoubleCurrency((double)faixaEtaria[2] * 100 / total, LOCALE_PT_BR)).c_str());
        printf("50 <= Idade < 60: %d (%s%%)\n", faixaEtaria[3], (formatDoubleCurrency((double)faixaEtaria[3] * 100 / total, LOCALE_PT_BR)).c_str());
        printf("60 <= Idade     : %d (%s%%)\n", faixaEtaria[4], (formatDoubleCurrency((double)faixaEtaria[4] * 100 / total, LOCALE_PT_BR)).c_str());
    }

    cout << endl;
}
void Eleicao::gerarRelatorio10() const
{
    cout << "Eleitos, por sexo:" << endl;
    string F = "F";
    string M = "M";
    int eleitosF = getEleitosPorSexo(F);
    int eleitosM = getEleitosPorSexo(M);
    int total = (eleitosF + eleitosM);
    if (total == 0)
    {
        printf("Feminino:  %d (0.00%%)\n", eleitosF);
        printf("Masculino: %d (0.00%%)\n", eleitosM);
    }
    else
    {
        printf("Feminino:  %d (%s%%)\n", eleitosF, (formatDoubleCurrency((double)eleitosF * 100 / total, LOCALE_PT_BR)).c_str());
        printf("Masculino: %d (%s%%)\n", eleitosM, (formatDoubleCurrency((double)eleitosM * 100 / total, LOCALE_PT_BR)).c_str());
    }
    cout << endl;
}

void Eleicao::gerarRelatorio11() const
{
    int votosLegenda = 0, votosNominais = 0;
    for (auto partido : partidos)
    {
        votosLegenda = votosLegenda + partido->getVotosLegenda();
        votosNominais = votosNominais + partido->getVotosNominais();
    }
    printf("Total de votos válidos:    %d\n", votosLegenda + votosNominais);
    int total = votosLegenda + votosNominais;
    if (total == 0)
    {
        printf("Total de votos nominais:   %d (0.00%%)\n", votosNominais);
        printf("Total de votos de legenda: %d (0.00%%)\n", votosLegenda);
    }
    else
    {
        printf("Total de votos nominais:   %d (%s%%)\n", votosNominais, (formatDoubleCurrency((double)votosNominais * 100 / total, LOCALE_PT_BR).c_str()));
        printf("Total de votos de legenda: %d (%s%%)\n", votosLegenda, (formatDoubleCurrency((double)votosLegenda * 100 / total, LOCALE_PT_BR).c_str()));
    }
    cout << endl;
}

void Eleicao::liberaPartidos()
{
    for (auto partido : partidos)
        delete partido;
}

void Eleicao::liberaCandidatos()
{
    for (auto candidato : todosCandidatos)
        delete candidato;
}

Eleicao::~Eleicao()
{
    liberaPartidos();
    liberaCandidatos();
}