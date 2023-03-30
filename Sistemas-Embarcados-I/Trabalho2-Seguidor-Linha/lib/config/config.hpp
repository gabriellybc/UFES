#pragma once

#define MOTOR_IN1 12 //Motor A
#define MOTOR_IN2 11 //Motor A
#define MOTOR_IN3 2 //Motor B
#define MOTOR_IN4 4 //Motor B
#define PIN_VEL_A 13 //Motor A
#define PIN_VEL_B 3 //Motor B
#define SENSOR_ESQUERDO A0
#define SENSOR_DIREITO A5
#define SENSOR_MEIO A1
#define LED_ESQUERDO 10
#define LED_DIREITO 5
#define TRIGGER 9
#define ECHO 8
#define SERVO 6

// Quanto mais amostras, mais leituras dos sensores infravermelhos sao feitas durante o calculo de media de leituras
// Isso aumenta a confiabilidade da leitura final dos sensores, pois diminui o efeito de ruidos, mas tambem diminui a eficiencia do carrinho como um todo (o carrinho passa mais tempo lendo, quando poderia estar fazendo processamento dos dados)
#define QUANTIDADE_AMOSTRAS 10 // Deve ser igual ou maior que 1

#define DISTANCIA_MAXIMA 37 // Em centimetros

#define VELOCIDADE_MINIMA 255 // Deve ser igual ou maior que 0

#define TEMPO_CURVA 700 // Em microsegundos

#define TEMPO_MOVIMENTO 100 // Em microsegundos

#define TEMPO_PARADO 300 // Em microsegundos