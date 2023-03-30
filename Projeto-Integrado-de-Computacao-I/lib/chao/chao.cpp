#include <chao.hpp>
#include <paisagem_bitmap.hpp>

Chao::Chao() {
    i = 0;
    x = 0;
}

void Chao::atualizar(int vx =  1) {
    if (x <= -64) {
        i += 1;
        x = 0;
    }
    x -= vx;
}

void Chao::printarNaTela(U8GLIB_SSD1306_128X64 tela) {
    tela.drawBitmapP(x, 52, 8, 12, chao_array[i % 5]);
    tela.drawBitmapP(x+64, 52, 8, 12, chao_array[(i + 1) % 5]);
    tela.drawBitmapP(x+128, 52, 8, 12, chao_array[(i + 2) % 5]);    
}
