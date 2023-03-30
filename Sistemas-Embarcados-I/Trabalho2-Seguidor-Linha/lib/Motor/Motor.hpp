#pragma once

#include <Arduino.h>

class Motor{
  public:
    uint8_t _in1_pin, _in2_pin, _vel_pin;
    String _descricao;
    int _vel;
  
    Motor();
    Motor(uint8_t in1_pin, uint8_t in2_pin, uint8_t vel_pin, String descricao);
    void setup();
    void desligar();
    void frear();
    void andar_frente();
    void andar_tras();
    void mudar_velocidade(int vel);
    void print();
};