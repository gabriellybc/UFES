#pragma once

#include <U8glib.h>

enum StatusDino {
    ANDA = 0,
    PULOU = 1,
    ABAIXOU = 2,
    MORREU = 3
};

struct Dino {
    int x, y;
    int vx, vy;
    int accx, accy;
    StatusDino status;
    int i, ii;

    Dino();
    void atualizar();
    void pularDino();
    void abaixaDino();
    void andaDino();
    void printarNaTela(U8GLIB_SSD1306_128X64 tela);
};
