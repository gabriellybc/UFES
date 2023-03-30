#pragma once

#include <U8glib.h>
#include <dino.hpp>
#include <cacto.hpp>
#include <chao.hpp>
#include <acelerometro.hpp>
#include <passaro.hpp>

enum StatusJogo {
    MENU = 0,
    JOGANDO = 1,
    PERDEU = 2,
};

struct Jogo {
    U8GLIB_SSD1306_128X64 tela;
    Dino dino;
    Chao chao;
    Cacto cacto;
    Passaro passaro;
    int pontuacao, velocidade;
    StatusJogo status;
    Acelerometro acel;
    bool vezDoCacto;


    Jogo();

    void setup();
    void loop();
    void atualiza();
    void renderizaMenuIniciarJogo();
    void renderizaPartida();
    void renderizaPerdeuJogo();
    bool colisaoCacto();
    bool colisaoPassaro();
};