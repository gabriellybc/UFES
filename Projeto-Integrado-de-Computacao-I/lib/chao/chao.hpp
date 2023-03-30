#pragma once

#include <U8glib.h>

struct Chao {
    int i;
    int x;

    Chao();
    void atualizar(int vx);
    void printarNaTela(U8GLIB_SSD1306_128X64 tela);
};
