#pragma once
#include <U8glib.h>
#include <constantes.hpp>

struct Cacto {
    
    int x;
    int y;
    int vx;
    int vy;
    int cacto;
    Cacto();
    bool passouDaTela();
    void atualizar(int vx);
    void printarNaTela(U8GLIB_SSD1306_128X64 tela);
};
