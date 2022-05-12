#include <iostream>
#include "Partido.h"

Partido::Partido() {}
Partido::Partido(int numero, int votosLegenda,const string& nome, const string& sigla)
{
    this->numero = numero;
    this->votosLegenda = votosLegenda;
    this->nome = nome;
    this->sigla = sigla;
    this->numeroCandidatosEleitos = 0;
    this->votosNominais = 0;
}

Partido::Partido(const Partido &o)
{
    this->numero = o.numero;
    this->votosLegenda = o.votosLegenda;
    this->nome = o.nome;
    this->sigla = o.sigla;
    this->numeroCandidatosEleitos = o.numeroCandidatosEleitos;
    this->votosNominais = o.votosNominais;
}

Partido &Partido::operator=(const Partido &o)
{
    this->numero = o.numero;
    this->votosLegenda = o.votosLegenda;
    this->nome = o.nome;
    this->sigla = o.sigla;
    this->numeroCandidatosEleitos = o.numeroCandidatosEleitos;
    this->votosNominais = o.votosNominais;
    return *this;
}

int Partido::getNumero() const
{
    return numero;
}

int Partido::getVotosLegenda() const
{
    return votosLegenda;
}

const string &Partido::getNome() const
{
    return nome;
}

const string &Partido::getSigla() const
{
    return sigla;
}

int Partido::getVotosNominais() const
{
    return votosNominais;
}

int Partido::getNumeroCandidatosEleitos() const
{
    return numeroCandidatosEleitos;
}

Candidato* Partido::getCandidato(int idx) const
{
    if (candidatos.size() > 0)
        return candidatos[idx]; 
    return NULL;
}

Candidato* Partido::getUltimoCandidato() const {
    return candidatos[candidatos.size()-1];
}

void Partido::setNumero(const int numero) {
    this->numero = numero;
}

void Partido::setVotosLegenda(const int votosLegenda)
{
    this->votosLegenda = votosLegenda;
}

void Partido::setNome(const string &nome)
{
    this->nome = nome;
}

void Partido::setSigla(const string &sigla)
{
    this->sigla = sigla;
}

void Partido::setVotosNominais(const int votosNominais)
{
    this->votosNominais = votosNominais;
}

void Partido::addNumeroCandidatosEleitos()
{
    this->numeroCandidatosEleitos++;
}

void Partido::adicionarCandidato(Candidato *candidato)
{
    votosNominais = votosNominais + candidato->getVotosNominais();
    // Outra forma de apontar para partido em candidato, mas optamos por deixar na criação do candidato
    //candidato->partido = this; 

    // Ordenando a lista de forma que o primeiro candidato com mais votos nominais será sempre o primeiro da lista
    // importante na geração do relatório 08
    if (this->getCandidato(0) != NULL) {
        if ((candidato->getVotosNominais() > this->getCandidato(0)->getVotosNominais()) || 
        (candidato->getVotosNominais() == this->getCandidato(0)->getVotosNominais() && candidato->comparaIdade(this->getCandidato(0)))) {
            candidatos.insert(candidatos.begin(), candidato);
        } else {
            candidatos.push_back(candidato);
        }
    } else {
        candidatos.push_back(candidato);
    }
    
    // Se eleito conta +1
    if (candidato->getSituacao().compare("Eleito") == 0)
        addNumeroCandidatosEleitos();
}

Candidato* Partido::getCandidatoMenosVotado() const {
    Candidato* ultimoCandidato = NULL;
    for (auto candidato : candidatos) {
        if (ultimoCandidato == NULL) {
            ultimoCandidato = candidato;
            continue;
        }

        if (candidato->getVotosNominais() < ultimoCandidato->getVotosNominais()) {
            ultimoCandidato = candidato;
        } else if (candidato->getVotosNominais() == ultimoCandidato->getVotosNominais()) {
            if (candidato->comparaIdade(ultimoCandidato) > 0) {
                ultimoCandidato = candidato;
            }
            else if (candidato->comparaIdade(ultimoCandidato) == 0 && candidato->getNumeroUrna() > ultimoCandidato->getNumeroUrna()) {
                ultimoCandidato = candidato;
            } 
        }
    }
    return ultimoCandidato;
}

bool Partido::comparaPartidoPorTotalVotos(Partido *o1, Partido *o2)
{
    int totalVotos1 = o1->getVotosLegenda() + o1->getVotosNominais();
    int totalVotos2 = o2->getVotosLegenda() + o2->getVotosNominais();
    int numeroPartido1 = o1->getNumero();
    int numeroPartido2 = o2->getNumero();
    if (totalVotos1 < totalVotos2)
        return false;
    else if (totalVotos1 > totalVotos2)
        return true;
    else
    {
        if (numeroPartido1 < numeroPartido2)
            return true;
        else
            return false;
    }
}

bool Partido::comparaPartidoPorVotosLegenda(Partido *o1, Partido *o2)
{
    int votosLegenda1 = o1->getVotosLegenda();
    int votosLegenda2 = o2->getVotosLegenda();
    int votosNominais1 = o1->getVotosNominais();
    int votosNominais2 = o2->getVotosNominais();
    int numeroPartido1 = o1->getNumero();
    int numeroPartido2 = o2->getNumero();
    if (votosLegenda1 < votosLegenda2)
        return false;
    else if (votosLegenda1 > votosLegenda2)
        return true;
    else
    {
        if (votosNominais1 < votosNominais2)
            return false;
        else if (votosNominais1 > votosNominais2)
            return true;
        else
        {
            if (numeroPartido1 < numeroPartido2)
                return true;
            else
                return false;
        }
    }
}

bool Partido::comparaPartidoPorTotalVotosNominaisDoCandidatoMaisVotado(Partido *o1, Partido *o2)
{
    if (o1->getCandidato(0) == NULL) {
        return false;
    }
    if (o2->getCandidato(0) == NULL) {
        return true;
    }
    int totalVotos1 = o1->getCandidato(0)->getVotosNominais(); 
    int totalVotos2 = o2->getCandidato(0)->getVotosNominais(); 
    int numeroPartido1 = o1->getNumero();
    int numeroPartido2 = o2->getNumero();
    if (totalVotos1 < totalVotos2)
        return false;
    else if (totalVotos1 > totalVotos2)
        return true;
    else
    {
        if (numeroPartido1 < numeroPartido2)
            return true;
        else
            return false;
    }
}

Partido::~Partido() {

}