#pragma once

#include <Arduino.h>
#include "Led.hpp"

class SensorInfravermelho{
  public:
    uint8_t _pin;
    unsigned short _numero_leituras;
    int _referencia;
    int minimo_branco, maximo_branco, minimo_preto, maximo_preto;
    float  medio_preto,medio_branco;
    float valor_atual;
    
    SensorInfravermelho();
    SensorInfravermelho(uint8_t pin, int numero_leituras);
    void setup();
    float ler();
    bool achou_trilha(Led led);
    void print();
    void calibrar(unsigned long tempo, Led led);
    void set_valores(int referencia, int minimo_branco, float medio_branco, int maximo_branco, int minimo_preto, float medio_preto, float maximo_preto);
};