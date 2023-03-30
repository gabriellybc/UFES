#include <jogo.hpp>
#include <constantes.hpp>
#include <passaro.hpp>
#include <cacto.hpp>
#include <fim_bitmap.hpp>

Jogo::Jogo() {
    tela = U8GLIB_SSD1306_128X64(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);
    status = JOGANDO;
    passaro = Passaro();
    cacto = Cacto();
    velocidade = 8;
    pontuacao = 0;

    vezDoCacto = true;
}

void Jogo::setup() {
    randomSeed(analogRead(A3));
    Wire.begin();
    Wire.beginTransmission(MPU);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
    Serial.begin(9600);
}

void Jogo::loop() {
    
    atualiza();

    if (status == MENU) {
        renderizaMenuIniciarJogo();
    }
    if (status == JOGANDO) {
        renderizaPartida();
    }
    if (status == PERDEU) {

        renderizaPerdeuJogo();
    }
}

void Jogo::atualiza() {
    acel.atualizaDados();
    pontuacao += 1;
}

void Jogo::renderizaMenuIniciarJogo() {

}

void Jogo::renderizaPartida() {
    tela.firstPage();

    char s_str[20];
    itoa(pontuacao, s_str, 10);
    tela.setFont(u8g_font_04b_24);

    
    do {
        chao.printarNaTela(tela);
        dino.printarNaTela(tela);

        if (vezDoCacto) {
            cacto.printarNaTela(tela);
        } else {
            passaro.printarNaTela(tela);
        }

        tela.drawStr(5, 10, s_str);
    } while (tela.nextPage());


   acel.detectaMovimento();
   
    if(acel.detectaPulou()){
        dino.pularDino();
    } else if(acel.detectaAbaixou()){
        dino.abaixaDino();
    } else if (acel.detectaParado()){
        dino.andaDino();
    }

    chao.atualizar(velocidade);
    dino.atualizar();

    if(colisaoCacto() or colisaoPassaro()){
        status=PERDEU;
        dino.status = MORREU;
        return;
    }

    if (vezDoCacto) {
        if (cacto.passouDaTela()) {
            vezDoCacto = !vezDoCacto;
            passaro = Passaro();
        } else {
            cacto.atualizar(velocidade);
        }
    } else {
        if (passaro.passouDaTela()) {
            vezDoCacto = !vezDoCacto;
            cacto = Cacto();
        } else {
            passaro.atualizar(velocidade);
        }
    }

}

void Jogo::renderizaPerdeuJogo() {
    tela.firstPage();

    do {

        chao.printarNaTela(tela);
        dino.printarNaTela(tela);

        if (vezDoCacto) {
            cacto.printarNaTela(tela);
        } else {
            passaro.printarNaTela(tela);
        }
        
        tela.drawBitmapP(15, 20, 13, 7, fim_game_over);
        tela.drawBitmapP(55, 35, 3, 14, fim_restart_icon);
    } while (tela.nextPage());

   acel.detectaMovimento();

    if (acel.detectaRestart()) {
        *this = Jogo();
    }
}

bool Jogo::colisaoCacto(){
    if((dino.x<=cacto.x and dino.x>=cacto.x-20) and (dino.y>=cacto.y-10 and dino.y<=cacto.y+50)){
        return true;
    }
    return false;
}

bool Jogo::colisaoPassaro(){
    if((dino.x<=passaro.x and dino.x>=passaro.x-20) and (dino.status != ABAIXOU)){
        return true;
    }
    return false;
}