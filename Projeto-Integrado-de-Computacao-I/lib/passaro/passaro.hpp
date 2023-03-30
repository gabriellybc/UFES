#pragma once
#include <U8glib.h>
#include <constantes.hpp>

struct Passaro {
    
    int frame;
    int x;
    int y;
    int vx;
    int vy;
    Passaro();
    void atualizar(int vx);
    bool passouDaTela();
    void printarNaTela(U8GLIB_SSD1306_128X64 tela);
};
