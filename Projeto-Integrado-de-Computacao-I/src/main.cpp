#include <Arduino.h>
#include <jogo.hpp>

Jogo jogo = Jogo();

void setup(void) {
    randomSeed(analogRead(A0));
	jogo.setup();
}

void loop(void) {
	jogo.loop();
}
