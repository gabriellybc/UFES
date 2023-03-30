#include "Carro.hpp"

Carro::Carro(){}

Carro::Carro(String nome, int tempo_movimento, int tempo_parado, int velocidade_minima, int tempo_curva, int distancia_maxima, int numero_leituras, uint8_t motor_in1, uint8_t motor_in2, uint8_t motor_in3, uint8_t motor_in4, uint8_t pin_vel_a, uint8_t pin_vel_b, uint8_t sensor_esquerdo, uint8_t sensor_direito, uint8_t sensor_meio, uint8_t led_esquerdo, uint8_t led_direito){
  this->_motor_esquerdo = Motor(motor_in1, motor_in2, pin_vel_a, "Motor Esquerdo");
  this->_motor_direito = Motor(motor_in3, motor_in4, pin_vel_b, "Motor Direito");
  this->_nome = nome;
  this->led_esquerdo = Led(led_esquerdo);
  this->led_direito = Led(led_direito);
  this->sensor_esquerdo = SensorInfravermelho(sensor_esquerdo, numero_leituras);
  this->sensor_direito = SensorInfravermelho(sensor_direito, numero_leituras);
  this->sensor_meio = SensorInfravermelho(sensor_meio, numero_leituras);
  this->distancia_maxima = distancia_maxima;
  this->velocidade_minima = velocidade_minima;
  this->tempo_curva = tempo_curva;
  this->ultimo_linha = 'e';
  this->tempo_movimento = tempo_movimento;
  this->tempo_parado = tempo_parado;
}

void Carro::setup(uint8_t servo){
  Serial.begin(9600);
  this->_motor_esquerdo.setup();
  this->_motor_direito.setup();
  this->led_esquerdo.setup();
  this->led_direito.setup();
  this->sensor_esquerdo.setup();
  this->sensor_direito.setup();
  this->sensor_meio.setup();
  this->servo.attach(servo);
  this->olhar_frente(0);
}

void Carro::calibrar(){
  this->sensor_esquerdo.calibrar(5000, led_esquerdo);
  this->sensor_direito.calibrar(5000, led_direito);
  this->sensor_meio.calibrar(5000, led_esquerdo);
}

void Carro::print(){
  Serial.print("Oi! Meu nome eh ");
  Serial.print(_nome);
  Serial.println(" ! E essa eh minha info:");
  _motor_esquerdo.print();
  Serial.println("");
  _motor_direito.print();
  Serial.println("");
}

void Carro::desligar(){
  _motor_esquerdo.desligar();
  _motor_direito.desligar();
}

void Carro::frear()
{
  _motor_esquerdo.frear();
  _motor_direito.frear();
}

void Carro::seguir_frente(int vel){
  _motor_esquerdo.mudar_velocidade(vel);
  _motor_direito.mudar_velocidade(vel);
  _motor_esquerdo.andar_frente();
  _motor_direito.andar_frente();
}

void Carro::re(int vel){
  _motor_esquerdo.mudar_velocidade(vel);
  _motor_direito.mudar_velocidade(vel);
  _motor_esquerdo.andar_tras();
  _motor_direito.andar_tras();
}

void Carro::virar(int vel_mot_esq, int vel_mot_dir, unsigned long tempo){
  _motor_esquerdo.mudar_velocidade(vel_mot_esq);
  _motor_direito.mudar_velocidade(vel_mot_dir);
  _motor_esquerdo.andar_frente();
  _motor_direito.andar_frente();
  delay(tempo);
  desligar();
}

void Carro::virar(int vel_mot_esq, int vel_mot_dir){
  _motor_esquerdo.mudar_velocidade(vel_mot_esq);
  _motor_direito.mudar_velocidade(vel_mot_dir);
  _motor_esquerdo.andar_frente();
  _motor_direito.andar_frente();
}

void Carro::virar_esquerda(int vel, unsigned long tempo){
  _motor_esquerdo.mudar_velocidade(vel);
  _motor_direito.mudar_velocidade(vel);
  _motor_esquerdo.andar_frente();
  _motor_direito.desligar();
  delay(tempo);
  desligar();
}

void Carro::virar_direita(int vel, unsigned long tempo){
  _motor_esquerdo.mudar_velocidade(vel);
  _motor_direito.mudar_velocidade(vel);
  _motor_esquerdo.desligar();
  _motor_direito.andar_frente();
  delay(tempo);
  desligar();
}

void Carro::virar_esquerda(int vel){
  _motor_esquerdo.mudar_velocidade(vel);
  _motor_direito.mudar_velocidade(vel);
  _motor_esquerdo.andar_frente();
  _motor_direito.desligar();
}

void Carro::virar_direita(int vel){
  _motor_esquerdo.mudar_velocidade(vel);
  _motor_direito.mudar_velocidade(vel);
  _motor_esquerdo.desligar();
  _motor_direito.andar_frente();
}

void Carro::virar_esquerda_cruzamento(int vel){
  _motor_esquerdo.mudar_velocidade(vel);
  _motor_direito.mudar_velocidade(vel);
  _motor_esquerdo.andar_frente();
  _motor_direito.andar_tras();
}

void Carro::virar_direita_cruzamento(int vel){
  _motor_esquerdo.mudar_velocidade(vel);
  _motor_direito.mudar_velocidade(vel);
  _motor_esquerdo.andar_tras();
  _motor_direito.andar_frente();
}

bool Carro::achou_trilha(){
  return sensor_esquerdo.achou_trilha(led_esquerdo) || sensor_direito.achou_trilha(led_direito);
}

bool Carro::saiu_trilha_esquerda(){
  bool carrinho_na_trilha_antes = sensor_esquerdo.achou_trilha(led_esquerdo);
  atualizar();
  bool carrinho_na_trilha_depois = sensor_esquerdo.achou_trilha(led_direito);
  return carrinho_na_trilha_antes && !carrinho_na_trilha_depois;
}

bool Carro::saiu_trilha_direita(){
  bool carrinho_na_trilha_antes = sensor_direito.achou_trilha(led_direito);
  atualizar();
  bool carrinho_na_trilha_depois = sensor_direito.achou_trilha(led_esquerdo);
  return carrinho_na_trilha_antes && !carrinho_na_trilha_depois;
}

void Carro::atualizar(){
  sensor_esquerdo.ler();
  sensor_direito.ler();
  sensor_meio.ler();
}

bool Carro::achar_parede(UltraSonicDistanceSensor ultrassom){
  if (ultrassom.measureDistanceCm() < this->distancia_maxima){
    led_direito.piscar(500);
    return true;
  }
  return false;
}

void Carro::olhar_frente(int tempo){
  servo.write(70);
  delay(tempo);
}

void Carro::olhar_esquerda(int tempo){
  servo.write(170);
  delay(tempo);
}

void Carro::olhar_direita(int tempo){
  servo.write(0);
  delay(tempo);
}

bool Carro::detectar_cruzamento(){
  if (sensor_meio.achou_trilha(led_direito)){
    this->desligar();
    led_esquerdo.piscar(1000);
    return true;
  }
  return false;
}

void Carro::resolver_cruzamento(UltraSonicDistanceSensor ultrassom){
  // this->olhar_frente(1000);
  // if (this->achar_parede(ultrassom)){
  //   this->olhar_esquerda(1000);
  //   if (this->achar_parede(ultrassom)){
  //     this->olhar_direita(1000);
  //     if (this->achar_parede(ultrassom)){
  //       this->virar_direita(this->velocidade_minima, this->tempo_curva*2);
  //     } else this->virar_direita(this->velocidade_minima, this->tempo_curva);
  //   } else this->virar_esquerda(this->velocidade_minima, this->tempo_curva);
  // } else this->seguir_frente(this->velocidade_minima);
  this->olhar_frente(1000);
  if (this->achar_parede(ultrassom)){
    this->olhar_esquerda(1000);
    if (this->achar_parede(ultrassom)){
      this->olhar_direita(1000);
      if (this->achar_parede(ultrassom))
        trocar_pista(1, 'd');
      else
        trocar_pista(0, 'd');
    }
    else
      trocar_pista(0, 'e');
  }
  else{
    this->seguir_frente(this->velocidade_minima);
    delay(this->tempo_movimento*2);
  }
}

void Carro::mapear_velocidade(){
  int nova_velocidade_dir, nova_velocidade_esq;
  nova_velocidade_dir = nova_velocidade_esq = 0;
  nova_velocidade_dir = map(sensor_esquerdo.valor_atual, sensor_esquerdo.minimo_branco, sensor_esquerdo.maximo_preto, this->velocidade_minima, this->velocidade_minima+10);
  nova_velocidade_esq = map(sensor_direito.valor_atual, sensor_direito.minimo_branco, sensor_direito.maximo_preto, this->velocidade_minima, this->velocidade_minima+10);

  this->_motor_direito.mudar_velocidade(nova_velocidade_esq);
  this->_motor_esquerdo.mudar_velocidade(nova_velocidade_dir);
}

void Carro::salvar_ultimo_linha(){
  if (sensor_esquerdo.achou_trilha(led_esquerdo)){
    this->ultimo_linha = 'e';
  } else if (sensor_direito.achou_trilha(led_direito)){
    this->ultimo_linha = 'd';
  }
}

void Carro::seguir_linha(UltraSonicDistanceSensor ultrassom){
  int ti, tf;
  this->atualizar();
  while(this->achou_trilha()){
    this->seguir_frente(this->velocidade_minima);
    ti = millis();
    tf = ti;
    while((tf-ti) < this->tempo_movimento){
      this->atualizar();
      this->salvar_ultimo_linha();
      tf = millis();
      if(!this->achou_trilha()){
        break;
      }
      if(this->detectar_cruzamento()) this->resolver_cruzamento(ultrassom);
    }
    this->desligar();
    this->atualizar();
    delay(this->tempo_parado);
  }
  this->desligar();

  if(this->ultimo_linha == 'e'){
    while(!this->sensor_direito.achou_trilha(this->led_direito)){
      this->virar_esquerda(this->velocidade_minima);
      ti = millis();
      tf = ti;
      this->led_esquerdo.piscar();
      while((tf-ti) < this->tempo_movimento){
        this->atualizar();
        this->salvar_ultimo_linha();
        tf = millis();
        if(this->sensor_direito.achou_trilha(this->led_direito)){
          break;
        }
        if(this->detectar_cruzamento()){
          this->resolver_cruzamento(ultrassom);
          break;
        }      
      }
      this->led_esquerdo.piscar();
      this->desligar();
      delay(this->tempo_parado);
      this->atualizar();
    };
  }
  else{
    while(!this->sensor_esquerdo.achou_trilha(this->led_esquerdo)){
      this->virar_direita(this->velocidade_minima);
      ti = millis();
      tf = ti;
      this->led_direito.piscar();
      while((tf-ti) < this->tempo_movimento){
        this->atualizar();
        this->salvar_ultimo_linha();
        tf = millis();
        if(this->sensor_esquerdo.achou_trilha(this->led_esquerdo)){
          break;
        }
        if(this->detectar_cruzamento()){
          this->resolver_cruzamento(ultrassom);
          break;
        }      
      }
      this->led_direito.piscar();
      this->desligar();
      delay(this->tempo_parado);
      this->atualizar();
    };
  }
  this->seguir_frente(this->velocidade_minima);
  this->desligar();
}

void Carro::trocar_pista(int numero_pistas_pular, char lado){
  int ti, tf;
  this->atualizar();
  for(int i = 0; i<(numero_pistas_pular+1); i++){

    while(this->achou_trilha()){ //vou sair do preto e entrar no branco
      // Serial.println("Fred ve trilha");
      if(lado == 'd'){
        Serial.println("Fred ve trilha e tenta virar para direita para sair dela");
        this->sensor_direito.print();
        ti = millis();
        tf = ti;
        virar_direita_cruzamento(this->velocidade_minima);
        while((tf-ti) < this->tempo_movimento*2){
          this->atualizar();
          tf = millis();
          if(!this->achou_trilha()){
            break;
          }
        }
        this->desligar();
        this->atualizar();
        delay(this->tempo_parado);
        this->led_direito.piscar();
      }
      else{
        Serial.println("Fred ve trilha e tenta virar para esquerda para sair dela");
        this->led_esquerdo.piscar();
        ti = millis();
        tf = ti;
        virar_esquerda_cruzamento(this->velocidade_minima);
        while((tf-ti) < this->tempo_movimento*3){
          this->atualizar();
          tf = millis();
          if(!this->achou_trilha()){
            break;
          }
        }
        this->desligar();
        this->atualizar();
        delay(this->tempo_parado);
        this->led_esquerdo.piscar();
      }
      this->atualizar();
    }
    Serial.println("Fred perdeu trilha E vai tenatar encontrar a prox");
    this->desligar();
    delay(500);

    while(!this->achou_trilha()){ //vou sair do branco e entrar no preto
      if(lado == 'd'){
        Serial.println("Fred nao ve a trilha e tenta virar para direita para encontrar ela");
        this->sensor_direito.print();
        ti = millis();
        tf = ti;
        while((tf-ti) < this->tempo_movimento*2){
          this->atualizar();
          tf = millis();
          virar_direita_cruzamento(this->velocidade_minima);
          if(this->achou_trilha()){
            break;
          }
        }
        this->desligar();
        this->atualizar();
        delay(this->tempo_parado);
        this->led_direito.piscar();
      }
      else{
        Serial.println("Fred nao ve a trilha e tenta virar para esquerda para encontrar ela");
        this->led_esquerdo.piscar();
        ti = millis();
        tf = ti;
        while((tf-ti) < this->tempo_movimento*3){
          this->atualizar();
          tf = millis();
          virar_esquerda_cruzamento(this->velocidade_minima);
          if(this->achou_trilha()){
            break;
          }
        }
        this->desligar();
        this->atualizar();
        delay(this->tempo_parado);
        this->led_esquerdo.piscar();
      }
    this->atualizar();
  }
  Serial.println("Fred fez a virada!");
  this->desligar();
  delay(500);
  }
}