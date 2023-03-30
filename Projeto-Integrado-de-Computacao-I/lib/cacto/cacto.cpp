#include <cacto.hpp>
#include <Arduino.h>
#include <cacto_bitmap.hpp>

Cacto::Cacto(){
    cacto = random(1, 10000) % 4;
    x=130;
    y=32;
    vx = 0;
    vy = 0;
};

void Cacto::atualizar(int vx=1){
    x -= vx;
    y += vy;
}

bool Cacto::passouDaTela(){
    return x <= -20;
}

void Cacto::printarNaTela(U8GLIB_SSD1306_128X64 tela){    
    if (cacto == 0) {
        tela.drawBitmapP(x, y, 4, 26, cacto_allArray[0]);
    }
    if (cacto == 1) {
        tela.drawBitmapP(x, y, 3, 26, cacto_allArray[1]);
    }
    if (cacto == 2) {
        tela.drawBitmapP(x, y, 3, 27, cacto_allArray[2]);
    }
    if (cacto == 3) {
        tela.drawBitmapP(x, y, 4, 26, cacto_allArray[3]);
    }
}