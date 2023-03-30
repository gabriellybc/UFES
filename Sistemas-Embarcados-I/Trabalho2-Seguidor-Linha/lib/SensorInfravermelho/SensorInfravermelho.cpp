#include "SensorInfravermelho.hpp"

SensorInfravermelho::SensorInfravermelho(){}

SensorInfravermelho::SensorInfravermelho(uint8_t pin, int numero_leituras){
  _pin = pin;
  _numero_leituras = numero_leituras;
  _referencia = 0;
  valor_atual = 0;
  minimo_branco = maximo_branco = minimo_preto = maximo_preto = medio_preto = medio_branco = 0;
}

void SensorInfravermelho::setup(){
  pinMode(_pin, INPUT);
}

void SensorInfravermelho::print(){
  Serial.print("Sensor infravermelho no pino ");
  Serial.print(_pin);
  Serial.print(", valor atual:");
  Serial.println(this->valor_atual);
}

float SensorInfravermelho::ler(){
  float media_valores = 0;
  
  for(unsigned short i=0; i<_numero_leituras; i++){
    media_valores += analogRead(_pin);
  }

  media_valores /= _numero_leituras;
  valor_atual = media_valores;

  return media_valores;
}

bool SensorInfravermelho::achou_trilha(Led led){
  if(valor_atual > _referencia){
    led.piscar(0);
    return true;
  }
  return false;
}

void SensorInfravermelho::calibrar(unsigned long tempo, Led led){
  Serial.println("Iniciando calibracao do sensor infravermelho");
  Serial.println("Coloque o sensor sobre uma superficie branca");
  Serial.println("Voce tem 10 segundos para isso");
  led.piscar(10000);
  unsigned long quantidade_medicao = 0;
  minimo_branco = 1023;
  medio_branco = 0;
  maximo_branco = 0;

  unsigned long ti = millis(), tf;
  while(1){
    float valor = ler();
    quantidade_medicao += 1;
    if(valor < minimo_branco) minimo_branco = valor;
    if(valor > maximo_branco) maximo_branco = valor;
    medio_branco = medio_branco + valor;
    tf = millis();
    if((tf - ti) > tempo) break;
  }
  medio_branco = medio_branco/quantidade_medicao;
  quantidade_medicao = 0;

  Serial.println("Coloque o sensor sobre uma superficie preta");
  Serial.println("Voce tem 10 segundos para isso");
  led.piscar(10000);

  minimo_preto = 1023;
  medio_preto = 0;
  maximo_preto = 0;

  ti = millis();
  while(1){
    float valor = ler();
    quantidade_medicao += 1;
    if(valor < minimo_preto) minimo_preto = valor;
    if(valor > maximo_preto) maximo_preto = valor;
    medio_preto = medio_preto + valor;

    tf = millis();
    if((tf - ti) > tempo) break;
  }
  medio_preto = medio_preto/quantidade_medicao;

  _referencia = (maximo_branco + minimo_preto) / 2;

  Serial.println("Calibracao finalizada");
  Serial.print("Valor de referencia: ");
  Serial.println(_referencia);
  Serial.print("Valor de minimo_branco: ");
  Serial.println(minimo_branco);
  Serial.print("Valor medio branco: ");
  Serial.println(medio_branco);
  Serial.print("Valor de maximo_branco: ");
  Serial.println(maximo_branco);
  Serial.print("Valor de minimo_preto: ");
  Serial.println(minimo_preto);
  Serial.print("Valor medio preto: ");
  Serial.println(medio_preto);
  Serial.print("Valor de maximo_preto: ");
  Serial.println(maximo_preto);
}

void SensorInfravermelho::set_valores(int referencia, int minimo_branco, float medio_branco, int maximo_branco, int minimo_preto, float medio_preto, float maximo_preto){
  this->_referencia = referencia;
  this->minimo_branco = minimo_branco;
  this->medio_branco = medio_branco;
  this->maximo_branco = maximo_branco;
  this->minimo_preto = minimo_preto;
  this->medio_preto = medio_preto;
  this->maximo_preto = maximo_preto;
}