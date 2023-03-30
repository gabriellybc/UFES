#include "Motor.hpp"

Motor::Motor(){}

Motor::Motor(uint8_t in1_pin, uint8_t in2_pin, uint8_t vel_pin, String descricao){
  _in1_pin = in1_pin;
  _in2_pin = in2_pin;
  _vel_pin = vel_pin;
  _descricao = descricao;
}

void Motor::setup(){
  pinMode(_in1_pin, OUTPUT);
  pinMode(_in2_pin, OUTPUT);
  pinMode(_vel_pin, OUTPUT);
}

void Motor::print(){
  Serial.print("Descricao: ");
  Serial.print(_descricao);
  Serial.print(", PIN_IN1: ");
  Serial.print(_in1_pin);
  Serial.print(", PIN_IN2: ");
  Serial.print(_in2_pin);
  Serial.print(", VEL_PIN: ");
  Serial.print(_vel_pin);
  Serial.print(", ");
}

void Motor::mudar_velocidade(int vel){
  _vel = vel;
  analogWrite(_vel_pin, vel);
}

void Motor::andar_frente(){
  digitalWrite(_in1_pin, LOW);
  digitalWrite(_in2_pin, HIGH);
}

void Motor::andar_tras(){
  digitalWrite(_in1_pin, HIGH);
  digitalWrite(_in2_pin, LOW);
}

void Motor::desligar(){
  digitalWrite(_in1_pin, LOW);
  digitalWrite(_in2_pin, LOW);
}

void Motor::frear(){
  digitalWrite(_in1_pin, HIGH);
  digitalWrite(_in2_pin, HIGH);
}