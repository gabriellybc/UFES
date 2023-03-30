#pragma once

#include <Arduino.h>

class Led{
public:
    volatile bool estado;
    uint8_t pino;

    Led();
    Led(const uint8_t p);
    void setup();
    void mudarEstado();
    void escrever();
    void piscar(int tempo);
    void piscar();
};