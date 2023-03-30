#pragma once

#include <Servo.h>
#include <HCSR04.h>
#include "Motor.hpp"
#include "SensorInfravermelho.hpp"
#include "Led.hpp"

class Carro{
  public:
    Motor _motor_esquerdo, _motor_direito;
    String _nome;
    Led led_esquerdo, led_direito;
    SensorInfravermelho sensor_esquerdo, sensor_direito, sensor_meio;
    Servo servo;
    int distancia_maxima, velocidade_minima, tempo_curva, tempo_movimento, tempo_parado;
    char ultimo_linha;

    Carro();
    Carro(String nome,int tempo_movimento, int tempo_parado, int velocidade_minima, int tempo_curva, int distancia_maxima, int numero_leituras, uint8_t motor_in1, uint8_t motor_in2, uint8_t motor_in3, uint8_t motor_in4, uint8_t pin_vel_a, uint8_t pin_vel_b, uint8_t sensor_esquerdo, uint8_t sensor_direito, uint8_t sensor_meio, uint8_t led_esquerdo, uint8_t led_direito);
    void setup(uint8_t servo);
    void calibrar();
    void desligar();
    void frear();
    void seguir_frente(int vel);
    void re(int vel);
    void virar(int vel_mot_esq, int vel_mot_dir, unsigned long tempo);
    void virar(int vel_mot_esq, int vel_mot_dir);
    void virar_esquerda(int vel, unsigned long tempo);
    void virar_direita(int vel, unsigned long tempo);
    void virar_esquerda(int vel);
    void virar_direita(int vel);
    void virar_esquerda_cruzamento(int vel);
    void virar_direita_cruzamento(int vel);
    bool achou_trilha();
    bool saiu_trilha_esquerda();
    bool saiu_trilha_direita();
    void atualizar();
    void print();
    bool achar_parede(UltraSonicDistanceSensor ultrassom);
    void olhar_esquerda(int tempo);
    void olhar_direita(int tempo);
    void olhar_frente(int tempo);
    bool detectar_cruzamento();
    void resolver_cruzamento(UltraSonicDistanceSensor ultrassom);
    void mapear_velocidade();
    void salvar_ultimo_linha();
    void seguir_linha(UltraSonicDistanceSensor ultrassom);
    void trocar_pista(int numero_pistas_pular, char lado);
};