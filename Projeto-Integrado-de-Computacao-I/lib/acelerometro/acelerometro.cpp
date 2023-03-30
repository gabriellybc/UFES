#include <acelerometro.hpp>
#include <constantes.hpp>
#include <Wire.h>


void Acelerometro::detectaMovimento(){
    x=(Wire.read()<<8|Wire.read());
    y=(Wire.read()<<8|Wire.read());
    z=(Wire.read()<<8|Wire.read());
    x/= 1000;
    y/= 1000;
    z /= 1000;
}
bool Acelerometro:: detectaAbaixou(){
    if(x>5){
        Serial.println("abaixou");
        return true;
    }
    return false;
}

bool Acelerometro:: detectaPulou(){
    if(x<-5){
        Serial.println("pulou");
        return true;
    }
    return false;
}

bool Acelerometro::detectaRestart(){
    if(y>5){
        Serial.println("restart");
        return true;
    }
    return false;
}


bool Acelerometro:: detectaParado(){
    if(x>-3 && x<3){
        Serial.println("ta paradao");
        return true;
    }
    return false;
}
void Acelerometro::atualizaDados(){
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU,14,true);
}

