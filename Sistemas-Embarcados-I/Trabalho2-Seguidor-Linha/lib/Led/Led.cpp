#include <led.hpp>

Led::Led(){}

Led::Led(const uint8_t p){
    this->estado = false;
    this->pino = p;
}

void Led::setup(){
    pinMode(this->pino, OUTPUT);
}

void Led::mudarEstado(){
    this->estado = !estado;
}

void Led::escrever(){
    digitalWrite(this->pino, this->estado);
}

void Led::piscar(int tempo){
    this->mudarEstado();
    this->escrever();
    delay(tempo);
    this->mudarEstado();
    this->escrever();
}

void Led::piscar(){
    this->mudarEstado();
    this->escrever();
}