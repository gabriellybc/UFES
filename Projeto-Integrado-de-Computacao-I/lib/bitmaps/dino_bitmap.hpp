#pragma once

#include <Arduino.h>

// 'trex-up-1s', 22x23px
const unsigned char dino_andando_1 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x1b, 0xf8, 0x00, 0x1f, 0xf8, 0x00, 0x1f, 0xf8, 0x00, 
	0x1f, 0xf8, 0x00, 0x1f, 0x00, 0x00, 0x1f, 0xe0, 0x40, 0x3e, 0x00, 0x40, 0xfe, 0x00, 0x61, 0xff, 
	0x80, 0x73, 0xfe, 0x80, 0x7f, 0xfe, 0x00, 0x7f, 0xfe, 0x00, 0x3f, 0xfc, 0x00, 0x1f, 0xfc, 0x00, 
	0x0f, 0xf8, 0x00, 0x07, 0xf0, 0x00, 0x03, 0xb0, 0x00, 0x03, 0x10, 0x00, 0x02, 0x10, 0x00, 0x03, 
	0x18, 0x00, 0x00, 0x00, 0x00
};
// 'trex-up-2s', 22x23px
const unsigned char dino_andando_2 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x1b, 0xf8, 0x00, 0x1f, 0xf8, 0x00, 0x1f, 0xf8, 0x00, 
	0x1f, 0xf8, 0x00, 0x1f, 0x00, 0x00, 0x1f, 0xe0, 0x40, 0x3e, 0x00, 0x40, 0xfe, 0x00, 0x61, 0xff, 
	0x80, 0x73, 0xfe, 0x80, 0x7f, 0xfe, 0x00, 0x7f, 0xfe, 0x00, 0x3f, 0xfc, 0x00, 0x1f, 0xfc, 0x00, 
	0x0f, 0xf8, 0x00, 0x07, 0xf0, 0x00, 0x03, 0x98, 0x00, 0x03, 0x00, 0x00, 0x02, 0x00, 0x00, 0x03, 
	0x00, 0x00, 0x00, 0x00, 0x00
};
// 'trex-up-3s', 22x23px
const unsigned char dino_andando_3 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x1b, 0xf8, 0x00, 0x1f, 0xf8, 0x00, 0x1f, 0xf8, 0x00, 
	0x1f, 0xf8, 0x00, 0x1f, 0x00, 0x00, 0x1f, 0xe0, 0x40, 0x3e, 0x00, 0x40, 0xfe, 0x00, 0x61, 0xff, 
	0x80, 0x73, 0xfe, 0x80, 0x7f, 0xfe, 0x00, 0x7f, 0xfe, 0x00, 0x3f, 0xfc, 0x00, 0x1f, 0xfc, 0x00, 
	0x0f, 0xf8, 0x00, 0x07, 0xf0, 0x00, 0x03, 0x30, 0x00, 0x01, 0x90, 0x00, 0x00, 0x10, 0x00, 0x00, 
	0x18, 0x00, 0x00, 0x00, 0x00
};

const unsigned char* dino_andando_array[3] = {
	dino_andando_1,
	dino_andando_2,
	dino_andando_3
};

// 'trex-duck-1s', 29x15px
const unsigned char dino_deitado_1 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x1f, 0xe0, 0x70, 0xff, 0x3f, 0xf0, 0x7f, 0xff, 0xf7, 0xf0, 
	0x3f, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x07, 0xff, 0xfe, 0x00, 
	0x03, 0xff, 0x9f, 0xc0, 0x01, 0xf9, 0x00, 0x00, 0x02, 0x71, 0x80, 0x00, 0x03, 0x60, 0x00, 0x00, 
	0x00, 0x40, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'trex-duck-2s', 29x15px
const unsigned char dino_deitado_2 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x1f, 0xe0, 0x70, 0xff, 0x3f, 0xf0, 0x7f, 0xff, 0xf7, 0xf0, 
	0x3f, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x07, 0xff, 0xfe, 0x00, 
	0x03, 0xff, 0x9f, 0xc0, 0x01, 0xf9, 0x00, 0x00, 0x03, 0x9d, 0x80, 0x00, 0x03, 0x00, 0x00, 0x00, 
	0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char* dino_deitado_array[2] = {
	dino_deitado_1,
	dino_deitado_2
};


// 'trex-dead-1s', 22x23px
const unsigned char dino_morto_reto_1 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x18, 0xf8, 0x00, 0x1a, 0xf8, 0x00, 0x18, 0xf8, 0x00, 
	0x1f, 0xf8, 0x00, 0x1f, 0xf8, 0x00, 0x1f, 0xe0, 0x40, 0x3e, 0x00, 0x40, 0xfe, 0x00, 0x61, 0xff, 
	0x80, 0x73, 0xfe, 0x80, 0x7f, 0xfe, 0x00, 0x7f, 0xfe, 0x00, 0x3f, 0xfc, 0x00, 0x1f, 0xfc, 0x00, 
	0x0f, 0xf8, 0x00, 0x07, 0xf0, 0x00, 0x03, 0xb0, 0x00, 0x03, 0x10, 0x00, 0x02, 0x10, 0x00, 0x03, 
	0x18, 0x00, 0x00, 0x00, 0x00
};
// 'trex-dead-1s-no-outline', 22x23px
const unsigned char dino_morto_reto_2 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x18, 0xf8, 0x00, 0x1a, 0xf8, 0x00, 0x18, 0xf8, 0x00, 
	0x1f, 0xf8, 0x00, 0x1f, 0xf8, 0x00, 0x1f, 0xe0, 0x40, 0x3e, 0x00, 0x40, 0xfe, 0x00, 0x61, 0xff, 
	0x80, 0x73, 0xfe, 0x80, 0x7f, 0xfe, 0x00, 0x7f, 0xfe, 0x00, 0x3f, 0xfc, 0x00, 0x1f, 0xfc, 0x00, 
	0x0f, 0xf8, 0x00, 0x07, 0xf0, 0x00, 0x03, 0xb0, 0x00, 0x03, 0x10, 0x00, 0x02, 0x10, 0x00, 0x03, 
	0x18, 0x00, 0x00, 0x00, 0x00
};

const unsigned char* dino_morto_reto_array[2] = {
	dino_morto_reto_1,
	dino_morto_reto_2
};

// 'trex-dead-2s', 29x15px
const unsigned char dino_morto_deitado_1 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x1f, 0xe0, 0x70, 0xff, 0x31, 0xf0, 0x7f, 0xff, 0xf5, 0xf0, 
	0x3f, 0xff, 0xf1, 0xf0, 0x1f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x07, 0xff, 0xff, 0xc0, 
	0x03, 0xff, 0x80, 0x00, 0x01, 0xf9, 0x00, 0x00, 0x02, 0x71, 0x80, 0x00, 0x03, 0x60, 0x00, 0x00, 
	0x00, 0x40, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'trex-dead-2s-no-outline', 29x15px
const unsigned char dino_morto_deitado_2 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x1f, 0xe0, 0x70, 0xff, 0x31, 0xf0, 0x7f, 0xff, 0xf5, 0xf0, 
	0x3f, 0xff, 0xf1, 0xf0, 0x1f, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x07, 0xff, 0xff, 0xc0, 
	0x03, 0xff, 0x80, 0x00, 0x01, 0xf9, 0x00, 0x00, 0x02, 0x71, 0x80, 0x00, 0x03, 0x60, 0x00, 0x00, 
	0x00, 0x40, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char* dino_morto_deitado_array[2] = {
	dino_morto_deitado_1,
	dino_morto_deitado_2
};
