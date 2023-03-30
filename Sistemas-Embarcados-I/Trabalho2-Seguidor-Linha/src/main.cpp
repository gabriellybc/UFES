#include "config.hpp"
#include "Carro.hpp"

Carro fred = Carro("fred", TEMPO_MOVIMENTO, TEMPO_PARADO, VELOCIDADE_MINIMA, TEMPO_CURVA, DISTANCIA_MAXIMA, QUANTIDADE_AMOSTRAS, MOTOR_IN1, MOTOR_IN2, MOTOR_IN3, MOTOR_IN4, PIN_VEL_A, PIN_VEL_B, SENSOR_ESQUERDO, SENSOR_DIREITO, SENSOR_MEIO, LED_ESQUERDO, LED_DIREITO);
UltraSonicDistanceSensor ultrassom(TRIGGER, ECHO);
// Direito eh mais forte

void setup() {
  fred.setup(SERVO);
  // fred.calibrar();

  // antigo
  // fred.sensor_esquerdo.set_valores(551, 214, 889, 889.4, 183.00);
  // fred.sensor_direito.set_valores(442, 264, 620, 763.52, 240.0);
  // fred.sensor_meio.set_valores(476, 116, 856, 878.05, 107.05);

  // novo 1 medicao
  // fred.sensor_esquerdo.set_valores(470, 254, 280.12, 308, 633, 845.31, 888);
  // fred.sensor_direito.set_valores(391, 287, 313.94, 334, 449, 795.12, 889);
  // fred.sensor_meio.set_valores(414, 46, 51.06, 60, 768, 836.96, 875);

  // novo 2 medicao
  // fred.sensor_esquerdo.set_valores(613, 205, 279.19, 352, 871, 880.33, 904);
  // fred.sensor_direito.set_valores(685, 274, 295.97, 315, 912, 916.32, 927);
  // fred.sensor_meio.set_valores(420, 50, 62.8, 81, 760, 832.92, 861);

  // novo 3 medicao
  fred.sensor_esquerdo.set_valores(630, 448, 472.06, 489, 771, 870.69, 986);
  fred.sensor_direito.set_valores(700, 657, 666.25, 676, 964, 977.52, 989);
  fred.sensor_meio.set_valores(420, 50, 62.8, 81, 760, 832.92, 861);


  // 1) fred segue a linha (ele esta na linha)
  // 2) fred saiu da linha (fred para
  // 3) fred olha o ultimo sensor na linha
  // 4) fred decide pra qual lado virar baseado no ultimo sensor na linha
  // 5) fred começa a virar enquanto 
  Serial.println("Comecei");

  
  // int velocidade_inicial = 163;
  // fred._motor_direito.mudar_velocidade(fred.velocidade_minima);
  // fred._motor_esquerdo.mudar_velocidade(velocidade_inicial);
  // for(int i=0; i<20; i++){ //163 - 165 foi bom
  //   Serial.print("Testando velocidade ");
  //   Serial.println(velocidade_inicial+i);
  //   fred._motor_esquerdo.mudar_velocidade(velocidade_inicial+i);
  //   fred._motor_direito.andar_frente();
  //   fred._motor_esquerdo.andar_frente();
  //   delay(300);
  //   fred.desligar();
  //   Serial.println("Corra! Voce tem 7 segundos para reposicionar o carrinho!");
  //   delay(7000);
  // }
  

//  for (int i = 50; i < 255; i++)
//  {
//   fred.seguir_frente(i);
//   Serial.print("Velocidade: ");
//   Serial.println(i);
//   delay(1000);
//  }

  // while(1){
  //   fred.atualizar();
  //   Serial.print("Leitura do sensor esquerdo: ");
  //   fred.sensor_esquerdo.print();
  //   fred.led_esquerdo.piscar(1000);
  //   fred.atualizar();
  //   Serial.print("Leitura do sensor direito: ");
  //   fred.sensor_direito.print();
  //   fred.led_direito.piscar(1000);
  //   Serial.print("Leitura do sensor meio: ");
  //   fred.sensor_meio.print();
  //   fred.atualizar();
  //   delay(1000);
  //   Serial.println("-------------------------------------------------");
  //   Serial.println(ultrassom.measureDistanceCm());
  //   Serial.println("-------------------------------------------------");
  //   delay(1000);
  // }
  // fred.seguir_linha(ultrassom);

 
}

void loop() {
    fred.atualizar();
    fred.seguir_linha(ultrassom);
    // fred.sensor_esquerdo.print();  // fred.seguir_frente(255);
    // fred.sensor_direito.print();
  // delay(500);
  // fred.desligar();
  // fred.led_direito.piscar(10000);


  // fred.seguir_frente(fred.velocidade_minima);
  // fred.sensor_esquerdo.print();
  // fred.sensor_direito.print();
  // fred.sensor_meio.print();

  // fred.atualizar();
  // if(fred.achou_trilha()){
  //   Serial.println("Estou no preto!");
  // } else {
  //   Serial.println("Estou no branco!");
  // }

  // if(fred.detectar_cruzamento()){
  //   Serial.println("Cruzamento!");
  // }
  // else{
  //   Serial.println("Nao eh cruzamento!");
  // }
  // delay(500);
}
