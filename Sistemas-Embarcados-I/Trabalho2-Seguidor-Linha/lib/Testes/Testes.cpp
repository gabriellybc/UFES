// #include "Testes.hpp"
// #include "Arduino.h"
// #include "Carro.hpp"
// #include "Motor.hpp"
// #include "SensorInfravermelho.hpp"

// void Testes::achar_trilha(Carro &carrinho, int velocidade){
//   Serial.println("Iniciando teste de achar trilha");

//   carrinho.print();

//   carrinho.seguir_frente(velocidade);
//   while(1){
//     if(carrinho.achou_trilha()) break;
//     carrinho.atualizar();
//   }
//   carrinho.desligar();

//   Serial.println("Finalizando teste de achar trilha");
// }

// void Testes::saiu_trilha_esquerda(Carro &carrinho, int velocidade){
//   Serial.println("Iniciando teste de que o carrinho saiu da trilha pelo lado esquerdo");
//   bool achou = false;

//   carrinho.print();

//   carrinho.seguir_frente(velocidade);
//   while(1){
//     if(carrinho.achou_trilha()){
//       Serial.println("Carrinho achou trilha");
//       achou = true;
//     }
//     if(achou && carrinho.saiu_trilha_esquerda()){
//       Serial.println("Carrinho saiu da trilha pelo lado esquerdo");
//       break;
//     }
//     carrinho.atualizar();
//   }

//   carrinho.desligar();
//   while(1){
//     Serial.println("Dando re...");
//     carrinho.re(velocidade);
//     delay(100);
//     carrinho.desligar();
//     carrinho.atualizar();
//     if(carrinho.achou_trilha()){
//       Serial.println("Carrinho reencontrou a trilha");
//       break;
//     }
//   }

//   Serial.println("Finalizando teste de que o carrinho saiu da trilha pelo lado esquerdo");
// }

// void Testes::saiu_trilha_direita(Carro &carrinho, int velocidade){
//   Serial.println("Iniciando teste de que o carrinho saiu da trilha pelo lado direito");
//   bool achou = false;

//   carrinho.print();

//   carrinho.seguir_frente(velocidade);
//   while(1){
//     if(!achou && carrinho.achou_trilha()){
//       Serial.println("Carrinho achou trilha");
//       achou = true;
//     }
//     if(achou && carrinho.saiu_trilha_direita()){
//       Serial.println("Carrinho saiu da trilha pelo lado direito");
//       break;
//     }
//     carrinho.atualizar();
//   }

//   carrinho.desligar();
//   while(1){
//     Serial.println("Dando re...");
//     carrinho.re(velocidade);
//     delay(100);
//     carrinho.desligar();
//     carrinho.atualizar();
//     if(carrinho.achou_trilha()){
//       Serial.println("Carrinho reencontrou a trilha");
//       break;
//     }
//   }

//   Serial.println("Finalizando teste de que o carrinho saiu da trilha pelo lado direito");
// }

// void Testes::monitorar_sensor_estatico(SensorInfravermelho &sensor){
//   float valor_antigo, valor_recente = 0;
//   while(1){
//     valor_antigo = valor_recente;
//     Serial.print("Valor lido pelo sensor: ");
//     Serial.print((valor_recente = sensor.ler()));

//     if(valor_antigo){
//       Serial.print(", Variacao: ");
//       Serial.print((valor_recente - valor_antigo));
//     }

//     if(sensor.achou_trilha()){
//       Serial.print(", Sensor achou trilha!");
//     }

//     Serial.println("");
//   }
// }

// void Testes::monitorar_sensor_em_movimento(SensorInfravermelho &sensor, Carro &carrinho, int velocidade, unsigned long tempo){
//   Serial.print("Iniciando teste de monitoramento do sensor com carrinho em movimento a ");
//   Serial.print(velocidade);
//   Serial.print(" durante ");
//   Serial.print(tempo);
//   Serial.println(" ms");

//   float valor_antigo, valor_recente = 0;
//   unsigned long ti = millis(), tf;

//   carrinho.seguir_frente(velocidade);
//   while(1){
//     valor_antigo = valor_recente;
//     Serial.print("Valor lido pelo sensor: ");
//     Serial.print((valor_recente = sensor.ler()));

//     if(valor_antigo){
//       Serial.print(", Variacao: ");
//       Serial.print((valor_recente - valor_antigo));
//     }

//     if(sensor.achou_trilha()){
//       Serial.print(", Sensor achou trilha!");
//     }

//     Serial.println("");
//     tf = millis();

//     if((tf - ti) > tempo) break;
//   }
//   carrinho.desligar();

//   Serial.println("Finalizando teste de monitoramento do sensor com carrinho em movimento");
// }

// void Testes::monitores_sensores_estatico(SensorInfravermelho &sensor1, SensorInfravermelho &sensor2){
//   float valor_antigo, valor_recente = 0;
//   while(1){
//     valor_antigo = valor_recente;
//     Serial.print("Valor lido pelo sensor1: ");
//     Serial.print((valor_recente = sensor1.ler()));

//     if(valor_antigo){
//       Serial.print(", Variacao: ");
//       Serial.print((valor_recente - valor_antigo));
//     }

//     if(sensor1.achou_trilha()){
//       Serial.print(", Sensor1 achou trilha!");
//     }
    
//     Serial.print(", ");

//     valor_antigo = valor_recente;
//     Serial.print("Valor lido pelo sensor2: ");
//     Serial.print((valor_recente = sensor2.ler()));

//     if(valor_antigo){
//       Serial.print(", Variacao: ");
//       Serial.print((valor_recente - valor_antigo));
//     }

//     if(sensor2.achou_trilha()){
//       Serial.print(", Sensor2 achou trilha!");
//     }

//     Serial.println("");
//   }
// }

// void Testes::controle_carrinho_em_movimento(Carro &carrinho, int velocidade_inicial){
//   Serial.println("Iniciando teste de controle do carrinho em movimento");

//   int valor_sensor_esq, valor_sensor_dir, nova_velocidade_dir, nova_velocidade_esq;
//   unsigned long ti = millis(), tf;

//   while(1){
//     Motor motor_esquerdo = carrinho.get_motor_esquerdo();
//     Motor motor_direito = carrinho.get_motor_direito();
//     SensorInfravermelho sensor_esquerdo = motor_esquerdo.get_sensor();
//     SensorInfravermelho sensor_direito = motor_direito.get_sensor();

//     valor_sensor_esq = sensor_esquerdo.valor_atual;
//     valor_sensor_dir = sensor_direito.valor_atual;

//     nova_velocidade_dir = map(valor_sensor_esq, sensor_esquerdo.minimo_branco, sensor_esquerdo.maximo_preto, 80, 200);
//     nova_velocidade_esq = map(valor_sensor_esq, sensor_direito.minimo_branco, sensor_direito.maximo_preto, 80, 200);

//     carrinho.get_motor_esquerdo().mudar_velocidade(nova_velocidade_esq);
//     carrinho.get_motor_direito().muda=r_velocidade(nova_velocidade_dir);

//     // if(!carrinho.achou_trilha()){
//     //   Serial.println("Carrinho saiu da trilha! Dando re...");
//     //   while(!carrinho.achou_trilha()){
//     //     carrinho.re(velocidade_inicial);
//     //     carrinho.atualizar();
//     //     if((tf - ti) > 2200) break;
//     //   }
//     //   Serial.println("Carrinho reencontrou trilha! Prosseguindo...");
//     //   carrinho.seguir_frente(velocidade_inicial);      
//     // }
//     carrinho.atualizar();
//     tf = millis();

//     if((tf - ti) > 10000) break;
//   }
//   carrinho.desligar();

//   Serial.println("Finalizando teste de controle do carrinho em movimento");
// }

// void Testes::estrategia_1_redirecionamento_carrinho(Carro &carrinho, int velocidade_inicial, int tempo){
//   Serial.println("Iniciando teste de estrategia 1 de redirecionamento do carrinho");

//   SensorInfravermelho sensor_que_saiu;

//   while(1){
//     // 1
//     carrinho.led1.piscar(100);
//     Serial.println("Seguindo em frente...");
//     carrinho.seguir_frente(velocidade_inicial);
//     while(carrinho.achou_trilha()){
//       carrinho.atualizar();
//     }
//     carrinho.desligar();
    
//     if(!carrinho.get_motor_esquerdo().get_sensor().achou_trilha()){
//       sensor_que_saiu = carrinho.get_motor_esquerdo().get_sensor();
//     }
//     else sensor_que_saiu = carrinho.get_motor_direito().get_sensor();
//     sensor_que_saiu.print();
    
//     // 2
//     carrinho.led2.piscar(100);
//     Serial.println("Saindo da trilha! Dando re...");
//     carrinho.re(velocidade_inicial);
    
//     while(!sensor_que_saiu.achou_trilha()){
//       sensor_que_saiu.ler();
//     }
//     carrinho.desligar();

//     //3
//     // carrinho.led3.piscar(100);
//     Serial.println("Reencontrou trilha! Curvando...");
//     if(&sensor_que_saiu == &carrinho.get_motor_esquerdo().get_sensor()){
//       carrinho.virar_direita(200, 90, tempo);
//       Serial.println("Virou para direita");
//     }
//     else{
//       carrinho.virar_esquerda(90, 200, tempo);
//       Serial.println("Virou para esquerda");
//     }

//     carrinho.atualizar();
//     if(carrinho.achou_trilha()){
//       //break;
//     }
//   }

//   Serial.println("Finalizando teste de estrategia 1 de redirecionamento do carrinho");
// }

// void Testes::segue_linha(Carro &carro){
//   carro.atualizar();

// }