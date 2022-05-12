#include <iostream>
#include "Pessoa.h"

using namespace std;

Pessoa::Pessoa() {}

Pessoa::Pessoa(const string &nome, const string &sexo, const string &dataNascimento)
{
  this->nome = nome;
  this->sexo = sexo;
  this->dataNascimento = parseDate(dataNascimento, DATE_FORMAT_PT_BR_SHORT);
}

Pessoa::Pessoa(const Pessoa &o)
{
  this->nome = o.nome;
  this->sexo = o.sexo;
  this->dataNascimento = o.dataNascimento;
}

Pessoa &Pessoa::operator=(const Pessoa &o)
{
  this->nome = o.nome;
  this->sexo = o.sexo;
  this->dataNascimento = o.dataNascimento;
  return *this;
}

const string &Pessoa::getNome() const
{
  return this->nome;
}

void Pessoa::setNome(const string &nome)
{
  this->nome = nome;
}

const string &Pessoa::getSexo() const
{
  return this->sexo;
}

void Pessoa::setSexo(const string &sexo)
{
  this->sexo = sexo;
}

const time_t &Pessoa::getDataNascimento() const
{
  return this->dataNascimento;
}

void Pessoa::setDataNascimento(const time_t &dataNascimento)
{
  this->dataNascimento = dataNascimento;
}

int Pessoa::calculaIdade(const time_t &dataAtual) const {
  tm *tm = localtime(&dataAtual);
  int dayda = tm->tm_mday;
  int monthda = tm->tm_mon + 1;
  int yearda = tm->tm_year + 1900;
  tm = localtime(&dataNascimento);
  int daydn = tm->tm_mday;
  int monthdn = tm->tm_mon + 1;
  int yeardn = tm->tm_year + 1900;
  int idade = yearda - yeardn;
  if ((monthdn == monthda && daydn > dayda) || monthdn > monthda) {
    return idade - 1;
  }
  return idade;
}

int Pessoa::comparaIdade(Pessoa *o2)
{
  if (difftime(this->dataNascimento, o2->dataNascimento) < 0)
    return -1;
  else if (difftime(this->dataNascimento, o2->dataNascimento) == 0)
    return 0;
  return 1;
}

Pessoa::~Pessoa() {}