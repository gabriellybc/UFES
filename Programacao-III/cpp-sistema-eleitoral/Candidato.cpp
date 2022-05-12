#include "Candidato.h"

Candidato::Candidato() {}

Candidato::Candidato(int numeroUrna, int votosNominais, const string &situacao, const string &nome, const string &nomeUrna, const string &sexo, const string &dataNascimento, Partido *partido) : Pessoa(nome, sexo, dataNascimento)
{
  this->numeroUrna = numeroUrna;
  this->votosNominais = votosNominais;
  this->situacao = situacao;
  this->nomeUrna = nomeUrna;
  this->partido = partido;
}

Candidato::Candidato(const Candidato &o)
{
  this->numeroUrna = o.numeroUrna;
  this->votosNominais = o.votosNominais;
  this->situacao = o.situacao;
  this->nome = o.nome;
  this->nomeUrna = o.nomeUrna;
  this->sexo = o.sexo;
  this->dataNascimento = o.dataNascimento;
  this->partido = o.partido;
}

Candidato &Candidato::operator=(const Candidato &o)
{
  this->numeroUrna = o.numeroUrna;
  this->votosNominais = o.votosNominais;
  this->situacao = o.situacao;
  this->nome = o.nome;
  this->nomeUrna = o.nomeUrna;
  this->sexo = o.sexo;
  this->dataNascimento = o.dataNascimento;
  this->partido = o.partido;
  return *this;
}

int Candidato::getNumeroUrna() const
{
  return this->numeroUrna;
}

int Candidato::getVotosNominais() const
{
  return this->votosNominais;
}

const string &Candidato::getSituacao() const
{
  return this->situacao;
}

const string &Candidato::getNomeUrna() const
{
  return this->nomeUrna;
}

Partido *Candidato::getPartido() const
{
  return this->partido;
}

void Candidato::setNumeroUrna(int numeroUrna)
{
  this->numeroUrna = numeroUrna;
}

void Candidato::setVotosNominais(int votosNominais)
{
  this->votosNominais = votosNominais;
}

void Candidato::setSituacao(const string &situacao)
{
  this->situacao = situacao;
}

void Candidato::setNomeUrna(const string &nomeUrna)
{
  this->nomeUrna = nomeUrna;
}

void Candidato::setPartido(Partido *partido)
{
  this->partido = partido;
}

bool Candidato::comparaCandidatoPorVotosNominais(Candidato *o1,Candidato *o2)
{
  int votosNominais1 = o1->getVotosNominais();
  int votosNominais2 = o2->getVotosNominais();
  if (votosNominais1 < votosNominais2)
    return false;
  else if (votosNominais1 > votosNominais2)
    return true;
  else {
    if (o1->comparaIdade(o2) >= 0)
      return false;
    return true;
  }
}

Candidato::~Candidato() {}